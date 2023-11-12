local engine = EngineFactory.new()
    :set_title("Carimbo")
    :set_width(800)
    :set_height(600)
    :set_fullscreen(false)
    :create()

-- engine:prefetch({ "blob/matrix.avif", "blob/alarm.ogg" })

local angle = 0
local alpha = 0
local direction = 0

local me = engine:spawn()

me.pixmap = "blob/matrix.avif"
me.x = (800 // 2) - (me.width // 2)
me.y = (600 // 2) - (me.height // 2)

me:on_update(function(self)
  if engine:is_keydown(KeyEvent.w) then
    self.y = self.y - 1
  end

  if engine:is_keydown(KeyEvent.a) then
    self.x = self.x - 1
  end

  if engine:is_keydown(KeyEvent.s) then
    self.y = self.y + 1
  end

  if engine:is_keydown(KeyEvent.d) then
    self.x = self.x + 1
  end

  angle = angle + 1
  if angle > 360 then
    angle = 0
  end

  self.angle = angle

  if direction == 0 then
    alpha = alpha - 2
    if alpha <= 0 then
      alpha = 0
      direction = 1
    end
  else
    alpha = alpha + 2
    if alpha >= 255 then
      alpha = 255
      direction = 0
    end
  end

  self.alpha = alpha
end)

-- me:play_sound("blob/alarm.ogg")

-- local garbage = engine:spawn()
-- engine:destroy(garbage)
-- garbage = nil

local gc = engine:spawn()

gc:on_update(function(self)
  if collectgarbage("count") / 1024 > 8 then
    collectgarbage("collect")
  else
    collectgarbage("step", 1)
  end
end)

engine:run()
