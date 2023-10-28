#include "filesystem.hpp"

void filesystem::mount(const std::string &filename, const std::string &mountpoint) {
  if (PHYSFS_mount(filename.c_str(), mountpoint.c_str(), true) == 0) {
    throw std::runtime_error(fmt::format("[PHYSFS_mount] Failed to mount {} to {}", filename, mountpoint));
  }
}
