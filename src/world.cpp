#include "world.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <chipmunk/chipmunk.h>
#include <cmath>
#include <memory>
#include <vector>

using namespace framework;

cpBool collision_callback(cpArbiter *arb, cpSpace *, void *) {
  printf("Collision detected! Stopping objects.\n");

  cpBody *bodyA, *bodyB;
  cpArbiterGetBodies(arb, &bodyA, &bodyB);

  cpBodySetVelocity(bodyA, cpvzero);
  cpBodySetVelocity(bodyB, cpvzero);

  return cpFalse;
}

world::world(float_t gravity, std::shared_ptr<graphics::renderer> renderer)
    : _space(cpSpaceNew(), &cpSpaceFree), _renderer(renderer) {
  cpVect gravityVect = cpv(0, gravity);
  cpSpaceSetGravity(_space.get(), gravityVect);

  cpCollisionHandler *handler = cpSpaceAddDefaultCollisionHandler(_space.get());
  handler->beginFunc = collision_callback;
}

space_ptr world::space() const noexcept {
  return _space;
}

void world::update(float_t delta) const noexcept {
  UNUSED(delta);

  cpSpaceStep(_space.get(), delta > 0 ? delta : 1.0 / 60.0);
  // cpSpaceStep(_space.get(), 1.0 / 60.0);
}

void world::draw() noexcept {
  auto drawShape = [&](cpShape *shape) {
    const auto *body = cpShapeGetBody(shape);
    const auto position = cpBodyGetPosition(body);

    const int n = cpPolyShapeGetCount(shape);
    std::vector<cpVect> vertices(n);
    std::ranges::generate(vertices, [&, i = 0]() mutable {
      return cpPolyShapeGetVert(shape, i++);
    });

    auto [r, g, b] = [](cpCollisionType type) -> std::tuple<uint8_t, uint8_t, uint8_t> {
      switch (type) {
      case 1:
        return {255, 0, 0};
      case 2:
        return {0, 0, 255};
      case 3:
        return {255, 255, 0};
      case 4:
        return {0, 255, 255};
      case 5:
        return {0, 255, 0};
      default:
        return {255, 255, 255};
      }
    }(cpShapeGetCollisionType(shape));

    SDL_SetRenderDrawColor(*_renderer, r, g, b, 255);

    for (int i = 0; i < n; ++i) {
      int next = (i + 1) % n;
      int x1 = static_cast<int>(position.x + vertices[i].x);
      int y1 = static_cast<int>(position.y + vertices[i].y);
      int x2 = static_cast<int>(position.x + vertices[next].x);
      int y2 = static_cast<int>(position.y + vertices[next].y);
      SDL_RenderDrawLine(*_renderer, x1, y1, x2, y2);
    }
  };

  cpSpaceEachShape(
      _space.get(),
      [](cpShape *shape, void *data) {
        (*static_cast<decltype(drawShape) *>(data))(shape);
      },
      &drawShape
  );
}
