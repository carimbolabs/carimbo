#include "io.hpp"

using namespace storage;

const std::vector<uint8_t> io::read(std::string_view filename) {
  std::unique_ptr<PHYSFS_File, decltype(&PHYSFS_close)> fp{nullptr, PHYSFS_close};

  fp.reset(PHYSFS_openRead(filename.data()));

  if (!fp) {
    throw std::runtime_error(fmt::format("[PHYSFS_openRead] error while opening file: {}, error: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }

  PHYSFS_sint64 length = PHYSFS_fileLength(fp.get());
  std::vector<uint8_t> buffer(length);
  PHYSFS_readBytes(fp.get(), &buffer[0], length);

  return buffer;
}
