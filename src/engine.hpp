#pragma once

#include "common.hpp"
#include "event.hpp"
#include "eventreceiver.hpp"

namespace framework {
class engine : public input::eventreceiver {
public:
  engine() noexcept;
  virtual ~engine() = default;

  std::shared_ptr<audio::audiodevice> audiodevice() const noexcept;
  std::shared_ptr<framework::entitymanager> entitymanager() const noexcept;
  std::shared_ptr<input::eventmanager> eventmanager() const noexcept;
  std::shared_ptr<graphics::overlay> overlay() const noexcept;
  std::shared_ptr<framework::resourcemanager> resourcemanager() const noexcept;
  std::shared_ptr<framework::scenemanager> scenemanager() const noexcept;
  std::shared_ptr<framework::statemanager> statemanager() const noexcept;
  std::shared_ptr<audio::soundmanager> soundmanager() const noexcept;
  std::shared_ptr<graphics::window> window() const noexcept;
  std::shared_ptr<graphics::renderer> renderer() const noexcept;
  std::shared_ptr<framework::world> world() const noexcept;

  int32_t height() const noexcept;
  int32_t width() const noexcept;

  void set_audiodevice(std::shared_ptr<audio::audiodevice> audiodevice) noexcept;
  void set_entitymanager(std::shared_ptr<framework::entitymanager> entitymanager) noexcept;
  void set_eventmanager(std::shared_ptr<input::eventmanager> eventmanager) noexcept;
  void set_overlay(std::shared_ptr<graphics::overlay> overlay) noexcept;
  void set_resourcemanager(std::shared_ptr<framework::resourcemanager> resourcemanager) noexcept;
  void set_scenemanager(std::shared_ptr<framework::scenemanager> scenemanager) noexcept;
  void set_statemanager(std::shared_ptr<framework::statemanager> statemanager) noexcept;
  void set_window(std::shared_ptr<graphics::window> window) noexcept;
  void set_renderer(std::shared_ptr<graphics::renderer> renderer) noexcept;
  void set_world(std::shared_ptr<framework::world> world) noexcept;

  void add_loopable(std::shared_ptr<loopable> loopable) noexcept;
  void destroy(const std::shared_ptr<entity> entity) noexcept;
  void flush() const noexcept;
  bool is_keydown(const input::keyevent &event) const noexcept;
  void prefetch(const std::vector<std::string> &filenames) noexcept;
  void run() noexcept;
  void set_scene(const std::string_view name) noexcept;
  std::shared_ptr<entity> spawn(const std::string &kind) noexcept;
  void _loop() noexcept;

protected:
  virtual void on_quit() noexcept override;

private:
  bool _running{true};
  int32_t _height{0};
  int32_t _width{0};

  std::shared_ptr<audio::audiodevice> _audiodevice;
  std::shared_ptr<framework::entitymanager> _entitymanager;
  std::shared_ptr<input::eventmanager> _eventmanager;
  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<graphics::overlay> _overlay;
  std::shared_ptr<framework::resourcemanager> _resourcemanager;
  std::shared_ptr<framework::scenemanager> _scenemanager;
  std::shared_ptr<framework::statemanager> _statemanager;
  std::shared_ptr<graphics::renderer> _renderer;
  std::shared_ptr<graphics::window> _window;
  std::shared_ptr<framework::world> _world;
};
}
