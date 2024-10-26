#include "scenemanager.hpp"

using namespace framework;

using json = nlohmann::json;

scenemanager::scenemanager(std::shared_ptr<graphics::pixmappool> pixmappool) noexcept
    : _pixmappool(std::move(pixmappool)) {}

void scenemanager::load(const std::string_view name) {
  const auto buffer = storage::io::read(fmt::format("scenes/{}.json", name));
  const auto j = json::parse(buffer);
  _background = _pixmappool->get(j["background"].get<std::string>());
  _size = {j.at("width").get<int32_t>(), j.at("height").get<int32_t>()};
}

void scenemanager::update(double_t delta) noexcept {
  UNUSED(delta);
}

void scenemanager::draw() noexcept {
  if (!_background) {
    return;
  }

  static geometry::point point{0, 0};
  _background->draw({point, _size}, {point, _size});
}
