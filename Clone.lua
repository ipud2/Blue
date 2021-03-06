# usr/bin/lua

-- function for implementing OOP
function clone( base_object, clone_object )
  if type( base_object ) ~= "table" then
    return clone_object or base_object 
  end
  clone_object = clone_object or { }
  clone_object.__index = base_object
  return setmetatable( clone_object, clone_object )
end

return clone;
