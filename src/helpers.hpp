#pragma once

namespace geometry {
class size;
}

template <typename T>
constexpr void UNUSED(const T &x) { (void)x; }

std::pair<std::vector<uint8_t>, geometry::size> _load_png(std::string_view filename);
