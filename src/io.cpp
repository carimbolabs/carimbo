#include "io.hpp"
#include <fmt/format.h>

using namespace storage;

const std::vector<uint8_t> io::read(std::string_view filename) {
  std::unique_ptr<PHYSFS_File, decltype(&PHYSFS_close)> file_ptr{nullptr, PHYSFS_close};

  file_ptr.reset(PHYSFS_openRead(filename.data()));
  if (!file_ptr) {
    throw std::runtime_error(
        fmt::format("[PHYSFS_openRead] error while opening file: {}, error: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }

  PHYSFS_sint64 length = PHYSFS_fileLength(file_ptr.get());
  if (length <= 0) {
    throw std::runtime_error(
        fmt::format("[PHYSFS_fileLength] invalid file length, file: {}, error: {}", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }

  std::vector<uint8_t> buffer(length);
  PHYSFS_readBytes(file_ptr.get(), buffer.data(), length);
  return buffer;
}
