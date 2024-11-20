#include "world.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <chipmunk/chipmunk.h>
#include <cmath>
#include <memory>
#include <vector>

using namespace framework;

world::world(float_t gravity, std::shared_ptr<graphics::renderer> renderer)
    : _space(cpSpaceNew(), &cpSpaceFree), _renderer(renderer) {
  cpVect gravityVect = cpv(0, gravity);
  cpSpaceSetGravity(_space.get(), gravityVect);
}

space_ptr world::space() const noexcept {
  return _space;
}

void world::update(float_t delta) const noexcept {
  UNUSED(delta);

  cpSpaceStep(_space.get(), 1.0 / 60.0);
}

void world::draw() noexcept {
  auto drawShape = [&](cpShape *shape) {
    const cpBody *body = cpShapeGetBody(shape);
    const cpVect position = cpBodyGetPosition(body);

    int count = cpPolyShapeGetCount(shape);
    std::vector<cpVect> vertices(count);
    std::generate(vertices.begin(), vertices.end(), [&, i = 0]() mutable {
      return cpPolyShapeGetVert(shape, i++);
    });

    uint8_t r, g, b, a = 255;
    switch (cpShapeGetCollisionType(shape)) {
    case 1:
      r = 255;
      g = 0;
      b = 0;
      break;
    case 2:
      r = 0;
      g = 0;
      b = 255;
      break;
    case 3:
      r = 255;
      g = 255;
      b = 0;
      break;
    case 4:
      r = 0;
      g = 255;
      b = 255;
      break;
    case 5:
      r = 0;
      g = 255;
      b = 0;
      break;
    default:
      r = 255;
      g = 255;
      b = 255;
      break;
    }

    SDL_SetRenderDrawColor(*_renderer.get(), r, g, b, a);

    for (int i = 0; i < count; ++i) {
      int next = (i + 1) % count;

      int x1 = static_cast<int>(position.x + vertices[i].x);
      int y1 = static_cast<int>(position.y + vertices[i].y);
      int x2 = static_cast<int>(position.x + vertices[next].x);
      int y2 = static_cast<int>(position.y + vertices[next].y);

      SDL_RenderDrawLine(*_renderer.get(), x1, y1, x2, y2);
    }
  };

  cpSpaceEachShape(
      _space.get(), [](cpShape *shape, void *data) {
        auto draw = static_cast<decltype(drawShape) *>(data);
        (*draw)(shape);
      },
      &drawShape
  );
}
