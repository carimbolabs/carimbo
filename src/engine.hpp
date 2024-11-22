#pragma once

#include "common.hpp"
#include "event.hpp"
#include "eventreceiver.hpp"

namespace framework {
class engine : public input::eventreceiver {
public:
  engine();
  virtual ~engine() = default;

  void set_window(std::shared_ptr<graphics::window> window);
  std::shared_ptr<graphics::window> window() const;

  void set_renderer(std::shared_ptr<graphics::renderer> renderer);
  std::shared_ptr<graphics::renderer> renderer() const;

  void set_audiodevice(std::shared_ptr<audio::audiodevice> audiodevice);
  std::shared_ptr<audio::audiodevice> audiodevice() const;

  void set_world(std::shared_ptr<framework::world> world);
  std::shared_ptr<framework::world> world() const;

  void set_entitymanager(std::shared_ptr<framework::entitymanager> entitymanager);
  std::shared_ptr<framework::entitymanager> entitymanager() const;

  void set_eventmanager(std::shared_ptr<input::eventmanager> eventmanager);
  std::shared_ptr<input::eventmanager> eventmanager() const;

  void set_resourcemanager(std::shared_ptr<framework::resourcemanager> resourcemanager);
  std::shared_ptr<framework::resourcemanager> resourcemanager() const;

  std::shared_ptr<audio::soundmanager> soundmanager() const;

  void set_statemanager(std::shared_ptr<framework::statemanager> statemanager);
  std::shared_ptr<framework::statemanager> statemanager() const;

  void set_scenemanager(std::shared_ptr<framework::scenemanager> scenemanager);
  std::shared_ptr<framework::scenemanager> scenemanager() const;

  void prefetch(const std::vector<std::string> &filenames);
  void flush() const;

  bool is_keydown(const input::keyevent &event) const;

  std::shared_ptr<entity> spawn(const std::string &kind);
  void destroy(const std::shared_ptr<entity> entity);

  void add_loopable(std::shared_ptr<loopable> loopable);
  void set_scene(const std::string_view name);

  int32_t width() const;
  int32_t height() const;

  void run();
  void _loop();

protected:
  virtual void on_quit() noexcept override;

private:
  bool _running{true};

  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<graphics::window> _window;
  std::shared_ptr<graphics::renderer> _renderer;
  std::shared_ptr<audio::audiodevice> _audiodevice;
  std::shared_ptr<input::eventmanager> _eventmanager;
  std::shared_ptr<framework::world> _world;
  std::shared_ptr<framework::entitymanager> _entitymanager;
  std::shared_ptr<framework::resourcemanager> _resourcemanager;
  std::shared_ptr<framework::statemanager> _statemanager;
  std::shared_ptr<framework::scenemanager> _scenemanager;
};
}
