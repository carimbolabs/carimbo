#include "file.hpp"

const std::vector<uint8_t> file::read(const std::string &filename) {
  const auto fp = PHYSFS_openRead(filename.c_str());
  if (fp == nullptr) {
    throw std::runtime_error(fmt::format("[PHYSFS_openRead] Error while opening file: {}", filename /*, PHYSFS_getLastErrorCode()))*/));
  }

  PHYSFS_sint64 length = PHYSFS_fileLength(fp);
  std::vector<uint8_t> buffer(length);
  PHYSFS_readBytes(fp, &buffer[0], length);
  PHYSFS_close(fp);

  return buffer;
}
