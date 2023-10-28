#include "filesystem.hpp"

void filesystem::mount(const std::string_view &filename, const std::string_view &mountpoint) {
  if (PHYSFS_mount(filename.data(), mountpoint.data(), true) == 0) {
    throw std::runtime_error(fmt::format(
        "[PHYSFS_mount] Failed to mount '{}' to '{}'. Reason: '{}'", filename, mountpoint, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())));
  }
}
