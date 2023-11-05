local engine = EngineFactory.new()
    :set_title("Carimbo")
    :set_width(800)
    :set_height(600)
    :create()

engine:prefetch({ "ball.avif" })

local e = engine:spawn()

e:set_pixmap("ball.avif")

local angle = 0

e:on_update(function(self)
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
  self.y = self.y + 1
end)

engine:run()
