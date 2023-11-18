#include "soundfx.hpp"

#include "audiodevice.hpp"

using namespace audio;

static void callback(void *userdata, uint8_t *stream, int length) {
  auto &buffer = static_cast<soundfx *>(userdata)->buffer;

  if (buffer.empty()) {
    SDL_memset(stream, 0, length);
    return;
  }

  const auto to_copy = std::min(static_cast<size_t>(length), buffer.size());
  // SDL_memcpy(stream, buffer.data(), to_copy);
  SDL_MixAudio(stream, buffer.data(), to_copy, SDL_MIX_MAXVOLUME);
  buffer.erase(buffer.begin(), buffer.begin() + to_copy);
}

static size_t ovPHYSFS_read(void *ptr, size_t size, size_t nmemb, void *source) {
  auto file = reinterpret_cast<PHYSFS_file *>(source);

  PHYSFS_sint64 result = PHYSFS_readBytes(file, ptr, static_cast<PHYSFS_uint32>(size) * static_cast<PHYSFS_uint32>(nmemb));
  if (result <= 0)
    return 0;

  return static_cast<size_t>(result) / size;
}

static int ovPHYSFS_seek(void *source, ogg_int64_t offset, int whence) {
  auto file = reinterpret_cast<PHYSFS_file *>(source);

  switch (whence) {
  case SEEK_SET:
    if (PHYSFS_seek(file, static_cast<PHYSFS_uint64>(offset)) == 0)
      return -1;
    break;
  case SEEK_CUR:
    if (PHYSFS_seek(file, PHYSFS_tell(file) + offset) == 0)
      return -1;
    break;
  case SEEK_END:
    if (PHYSFS_seek(file, PHYSFS_fileLength(file) + offset) == 0)
      return -1;
    break;
  default:
    assert(false);
    return -1;
  }
  return 0;
}

static int ovPHYSFS_close(void *source) {
  auto file = reinterpret_cast<PHYSFS_file *>(source);
  PHYSFS_close(file);
  return 0;
}

static long ovPHYSFS_tell(void *source) {
  return static_cast<long>(PHYSFS_tell(reinterpret_cast<PHYSFS_file *>(source)));
}

static ov_callbacks PHYSFS_callbacks = {ovPHYSFS_read, ovPHYSFS_seek, ovPHYSFS_close, ovPHYSFS_tell};

const char *ov_strerror(int ret) {
  switch (ret) {
  case OV_FALSE:
    return "A request for an ov_read() returned 0.";
  case OV_EOF:
    return "End of file reached";
  case OV_HOLE:
    return "Missing or corrupt data in the bitstream";
  case OV_EREAD:
    return "Read error while fetching compressed data for decode";
  case OV_EFAULT:
    return "Internal inconsistency in encode or decode state. Continuing is likely not possible.";
  case OV_EIMPL:
    return "Feature not implemented";
  case OV_EINVAL:
    return "Invalid argument was passed to a call";
  case OV_ENOTVORBIS:
    return "The given file was not recognized as Ogg Vorbis data.";
  case OV_EBADHEADER:
    return "The file is apparently an Ogg Vorbis stream, but contains a corrupted or undecipherable header.";
  case OV_EVERSION:
    return "The bitstream format revision of the given file is not supported.";
  case OV_EBADLINK:
    return "The given link exists in the Vorbis data stream, but is not decipherable due to garbage or corruption.";
  case OV_ENOSEEK:
    return "File is not seekable";
  default:
    return "Unknown";
  }
}

soundfx::soundfx(const std::shared_ptr<audiodevice> audiodevice, std::string_view filename) : _audiodevice(audiodevice) {
  std::unique_ptr<PHYSFS_File, decltype(&PHYSFS_close)> fp{nullptr, PHYSFS_close};

  fp.reset(PHYSFS_openRead(filename.data()));
  if (!fp) {
    throw std::runtime_error(fmt::format("[PHYSFS_openRead] error while opening file: {}, error: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }

  std::unique_ptr<OggVorbis_File, decltype(&ov_clear)> vf{new OggVorbis_File, ov_clear};
  if (ov_open_callbacks(const_cast<void *>(reinterpret_cast<const void *>(fp.get())), vf.get(), nullptr, 0, PHYSFS_callbacks) < 0) {
    throw std::runtime_error("[ov_open_callbacks] error while opening file");
  }

  int32_t offset{0};
  const auto constexpr length = 1024 * 8;
  std::array<uint8_t, length> array{0};

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  const int bigendian = 0;
#else
  const int bigendian = 1;
#endif

  do {
    offset = ov_read(vf.get(), reinterpret_cast<char *>(array.data()), length, bigendian, 2, 1, nullptr);

    if (offset < 0) {
      throw std::runtime_error(fmt::format("[ov_read] error while reading file: {}, error: {}", filename, ov_strerror(offset)));
    }

    std::copy(array.begin(), array.begin() + offset, std::back_inserter(buffer));
  } while (offset > 0);

  UNUSED(callback);
}

soundfx::~soundfx() {
}

void soundfx::play() const {
  SDL_ClearQueuedAudio(_audiodevice->id());
  SDL_PauseAudioDevice(_audiodevice->id(), 0);
  SDL_QueueAudio(_audiodevice->id(), buffer.data(), buffer.size());
}
