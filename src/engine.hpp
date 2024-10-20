#pragma once

#include "common.hpp"

#include "eventreceiver.hpp"
#include <memory>

namespace framework {
class engine : public input::eventreceiver {
public:
  engine();

  virtual ~engine() = default;

  void set_window(std::shared_ptr<graphics::window> window);

  const std::shared_ptr<graphics::window> window() const;

  void set_renderer(std::shared_ptr<graphics::renderer> renderer);

  const std::shared_ptr<graphics::renderer> renderer() const;

  void set_audiodevice(std::shared_ptr<audio::audiodevice> audiodevice);

  const std::shared_ptr<audio::audiodevice> audiodevice();

  void set_entitymanager(std::shared_ptr<framework::entitymanager> entitymanager);

  const std::shared_ptr<framework::entitymanager> entitymanager() const;

  void set_eventmanager(std::shared_ptr<input::eventmanager> eventmanager);

  const std::shared_ptr<input::eventmanager> eventmanager() const;

  void set_resourcemanager(std::shared_ptr<framework::resourcemanager> resourcemanager);

  const std::shared_ptr<framework::resourcemanager> resourcemanager() const;

  const std::shared_ptr<audio::soundmanager> soundmanager() const;

  void set_statemanager(std::shared_ptr<framework::statemanager> statemanager);

  const std::shared_ptr<framework::statemanager> statemanager() const;

  void set_scenemanager(const std::shared_ptr<framework::scenemanager> scenemanager);

  const std::shared_ptr<framework::scenemanager> scenemanager() const;

  void set_fontfactory(const std::shared_ptr<graphics::fontfactory> fontfactory);

  const std::shared_ptr<graphics::fontfactory> fontfactory();

  void prefetch(const std::vector<std::string> &filenames);

  void load_font(const std::vector<std::string> &filename);

  void flush() const;

  bool is_keydown(const input::keyevent &event) const;

  const std::shared_ptr<entity> spawn(const std::string &kind);

  void destroy(const std::shared_ptr<entity> entity);

  void add_loopable(std::shared_ptr<loopable> loopable);

  void set_scene(const std::string_view name);

  int32_t width() const;

  int32_t height() const;

  void run();

  void _loop();

protected:
  virtual void on_quit() override;

private:
  bool _running;

  std::list<std::shared_ptr<loopable>> _loopables;
  std::shared_ptr<graphics::window> _window;
  std::shared_ptr<graphics::renderer> _renderer;
  std::shared_ptr<audio::audiodevice> _audiodevice;
  std::shared_ptr<input::eventmanager> _eventmanager;
  std::shared_ptr<framework::entitymanager> _entitymanager;
  std::shared_ptr<framework::resourcemanager> _resourcemanager;
  std::shared_ptr<framework::statemanager> _statemanager;
  std::shared_ptr<framework::scenemanager> _scenemanager;
  std::shared_ptr<graphics::fontfactory> _fontfactory;
};
}
