# usr/bin/lua
--[[
This is the base table for all "things" the user creates in the world
this class is meant to make creating "things" in the engine much easier
it also acts as a container for all the assets the "thing" might need.
What is really great about this table is it also adds the possibilty 
to add a layer of error proofing in lua. it does this by telling the 
user whenever they forget to implement a method in there object file
that is implemented in this file becuase all of these methods are needed
to make a fully functioning object.
--]]
register_object();
local Object = {};

Object.id = "NO_ID";

function Object:create( id )
	self.id = id or "NO_ID";
	create_obj( self.id );
	print( "if you are reading this then " .. self.id .. " does not a have a create method defined!" );
end

function Object:destroy()
	remove_obj( self.id );
	print( "if you are reading this then " .. self.id .. " does not a have a destroy method defined!" );
end

function Object:handleEvent( event )
	print( "if you are reading this then " .. self.id .. " does not a have a handleEvents method defined!" );
end

function Object:update()
	print( "if you are reading this then " .. self.id .. " does not a have a update method defined!" );
end

return Object;
