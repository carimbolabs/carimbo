#include "filesystem.hpp"

using namespace storage;

void filesystem::mount(std::string_view filename, std::string_view mountpoint) noexcept(false) {
  if (PHYSFS_mount(filename.data(), mountpoint.data(), true) == 0) [[unlikely]] {
    std::ostringstream oss;
    oss << "[PHYSFS_mount] failed to mount " << filename << " to " << mountpoint << ". reason: " << PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
    throw std::runtime_error(oss.str());
  }
}
