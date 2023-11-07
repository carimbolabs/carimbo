local engine = EngineFactory.new()
    :set_title("Carimbo")
    :set_width(800)
    :set_height(600)
    :create()

engine:prefetch({ "blob/matrix.avif" })

local entity = engine:spawn()

entity:set_pixmap("blob/matrix.avif")

local angle = 0

entity:on_update(function(self)
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
end)

local gc = engine:spawn()
local memory_ceiling = 64
local max_steps = 1000
local time_budget = 0.001

gc:on_update(function(self)
  -- local steps = 0
  -- local start_time = love.timer.getTime()

  -- while
  --   love.timer.getTime() - start_time < time_budget and steps < max_steps
  -- do
  --   collectgarbage("step", 1)
  --   steps = steps + 1
  -- end
  if collectgarbage("count") / 1024 > memory_ceiling then
    collectgarbage("collect")
  end

  collectgarbage("step", 1)
  -- collectgarbage("collect")
end)

engine:run()
