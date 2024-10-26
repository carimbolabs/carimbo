#include "io.hpp"

using namespace storage;

std::vector<uint8_t> io::read(std::string_view filename) noexcept(false) {
  std::unique_ptr<PHYSFS_File, decltype(&PHYSFS_close)> ptr(PHYSFS_openRead(filename.data()), PHYSFS_close);
  if (!ptr) {
    throw std::runtime_error(fmt::format("[PHYSFS_openRead] error while opening file: {}, error: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }

  PHYSFS_sint64 length = PHYSFS_fileLength(ptr.get());
  if (length <= 0) {
    throw std::runtime_error(
        fmt::format("[PHYSFS_fileLength] invalid file length, file: {}, error: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()))
    );
  }

  std::vector<uint8_t> buffer(length);
  auto bytesRead = PHYSFS_readBytes(ptr.get(), buffer.data(), length);
  if (bytesRead != length) {
    throw std::runtime_error(fmt::format("[PHYSFS_readBytes] error reading file: {}, expected {} bytes but read {}, error: {}", filename, length, bytesRead, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }

  return buffer;
}
