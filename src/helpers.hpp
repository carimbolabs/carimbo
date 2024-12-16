#pragma once

namespace geometry {
class size;
}

template <typename T>
constexpr void UNUSED(const T &x) {
  (void)x;
}

constexpr int MINIMAL_USE_COUNT = 1;

std::pair<std::vector<uint8_t>, geometry::size> _load_png(const std::string &filename);
