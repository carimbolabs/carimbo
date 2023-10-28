#include "file.hpp"

// std::ostream &operator<<(std::ostream &os, PHYSFS_ErrorCode ec) {
//   return os << static_cast<int>(ec);
// }

// template <typename ArgFormatter>
// void format_arg(fmt::BasicFormatter<char, ArgFormatter> &f,
//                 const char *&format_str, PHYSFS_ErrorCode e) {
//   f.writer() << (int)e;
// }

// template <typename T, typename std::enable_if_t<std::is_enum<T>::value, int> = 0>
// std::ostream &operator<<(std::ostream &os, const T &value) {
//   return os << static_cast<int>(value);
// }

const std::vector<uint8_t> file::read(const std::string &filename) {
  const auto fp = PHYSFS_openRead(filename.c_str());
  if (fp == nullptr) {
    throw std::runtime_error(fmt::format("[PHYSFS_openRead] Error while opening file: {}", filename /*, PHYSFS_getLastErrorCode()*/));
  }

  PHYSFS_sint64 length = PHYSFS_fileLength(fp);
  std::vector<uint8_t> buffer(length);
  PHYSFS_readBytes(fp, &buffer[0], length);
  PHYSFS_close(fp);

  return buffer;
}
