---@meta

---@class Enginefactory
Enginefactory = {}

---@return Engine
function Enginefactory.new() end

---@class Engine
local Engine = {}

---@param title string
---@return Engine
function Engine:set_title(title) end

---@param width number
---@return Engine
function Engine:set_width(width) end

---@param height number
---@return Engine
function Engine:set_height(height) end

---@return Engine
function Engine:create() end

---@param assets string[]
function Engine:prefetch(assets) end

---@return Entity
function Engine:spawn() end

---@class Entity
local Entity = {}

---@param pixmap string
function Entity:set_pixmap(pixmap) end

---@param updateFunc fun(self:Entity)
function Entity:on_update(updateFunc) end

-- See https://stackoverflow.com/questions/77429985/type-hints-for-lua
