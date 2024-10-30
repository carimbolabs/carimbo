
#include "margin.hpp"

namespace geometry {
void from_json(const nlohmann::json &j, margin &m) {
  m.top = j.at("top").get<int32_t>();
  m.left = j.at("left").get<int32_t>();
  m.bottom = j.at("bottom").get<int32_t>();
  m.right = j.at("right").get<int32_t>();
}
}
