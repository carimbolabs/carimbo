#include "scenemanager.hpp"
#include "point.hpp"

using namespace framework;

using json = nlohmann::json;

scenemanager::scenemanager(const std::shared_ptr<graphics::pixmappool> pixmappool)
    : _pixmappool(pixmappool) {}

void scenemanager::load(const std::string_view name) {
  const auto buffer = storage::io::read(fmt::format("scenes/{}.json", name));
  const auto j = json::parse(buffer);
  _background = _pixmappool->get(j["background"].template get<std::string_view>());
  _size = {j.at("width").get<int32_t>(), j.at("height").get<int32_t>()};
}

void scenemanager::update(double_t delta) {
  UNUSED(delta);
}

void scenemanager::draw() {
  if (!_background) {
    return;
  }

  static geometry::point point{0, 0};
  _background->draw({point, _size}, {point, _size});
}
