#include "world.hpp"

using namespace framework;

world::world(float_t gravity, std::shared_ptr<graphics::renderer> renderer)
    : _renderer(std::move(renderer)) {
  UNUSED(gravity);
}

void world::update(float_t delta) const noexcept {
  UNUSED(delta);
}

void world::draw() noexcept {
  // auto drawShape = [&](cpShape *shape) {
  //   const auto *body = cpShapeGetBody(shape);
  //   const auto &position = cpBodyGetPosition(body);

  //   const int n = cpPolyShapeGetCount(shape);
  //   std::vector<cpVect> vertices(n);
  //   std::ranges::generate(vertices, [&, i = 0]() mutable {
  //     return cpPolyShapeGetVert(shape, i++);
  //   });

  //   static constexpr std::array<std::tuple<uint8_t, uint8_t, uint8_t>, 6> colors = {{{255, 255, 255}, {255, 0, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}, {0, 255, 0}}};

  //   auto [r, g, b] = colors[std::min(cpShapeGetCollisionType(shape), static_cast<cpCollisionType>(5))];

  //   SDL_SetRenderDrawColor(*_renderer, r, g, b, 255);

  //   for (int i = 0; i < n; ++i) {
  //     int next = (i + 1) % n;
  //     int x1 = static_cast<int>(position.x + vertices[i].x);
  //     int y1 = static_cast<int>(position.y + vertices[i].y);
  //     int x2 = static_cast<int>(position.x + vertices[next].x);
  //     int y2 = static_cast<int>(position.y + vertices[next].y);
  //     SDL_RenderDrawLine(*_renderer, x1, y1, x2, y2);
  //   }
  // };

  // cpSpaceEachShape(
  //     _space.get(),
  //     [](cpShape *shape, void *data) {
  //       (*static_cast<decltype(drawShape) *>(data))(shape);
  //     },
  //     &drawShape
  // );
}
