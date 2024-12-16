#include "filesystem.hpp"

using namespace storage;

void filesystem::mount(const std::string &filename, const std::string &mountpoint) {
  if (PHYSFS_mount(filename.c_str(), mountpoint.c_str(), true) == 0) [[unlikely]] {
    std::ostringstream oss;
    oss << "[PHYSFS_mount] failed to mount " << filename << " to " << mountpoint << ". reason: " << PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
    throw std::runtime_error(oss.str());
  }
}
