# usr/bin/lua
local Clone = require( "Clone" );
local Mouse = require( "Mouse" );

local Button = Clone( require( "Sprite" ) );

local ControlMap = require( "ControlMap" );

function Button:create( id, layerId, clickedEventName, eventReceiverId, x, y, w, h )
	self.id = id or "UNDEFINED ASSET ID";
	self.clickedEventName = clickedEventName or print( "Invalid event name sent to button " .. self.id );
	self.receiverId = eventReceiverId or print( "invalid receiverId" );
	self.isSelected = false;
	self.x = x or 0;
	self.y = y or 0;
	self.width = w or 0;
	self.height = h or 0;
	self.rotation = 0;
	self.scale = { x = 1, y = 1 };
	self.color = { r = 255, g = 255, b = 255, a = 255 };
	self.outlineColor = { r = 255, g = 0, b = 255, a = 0 };
	self.outlineThickness = 0;
	self.origin = { x = 0, y = 0 };
	self.layerId = layerId or print( "You passed an invalid layerID to: " .. self.id );
	create_shape( self.id, layerId, self.x, self.y, 4, self.color.r, self.color.g, self.color.b, self.color.a );
	shape_setOrigin( self.id, self.x, self.y );
	-- always set points in clockwise rotation!
	-- 2nd arg is index to array of points(X,Y values) that make up this shape in C++
	shape_setPoint( self.id, 0, self.x, self.y );
	shape_setPoint( self.id, 1, self.x + self.width, self.y );
	shape_setPoint( self.id, 2, self.x + self.width, self.y + self.height );
	shape_setPoint( self.id, 3, self.x, self.y + self.height );
end

function Button:handleEvent( event )
	
end

function Button:update()
	local temp = Mouse:getPos();
	if Mouse:isButtonClicked( Mouse["Left"] ) then
		if temp.x > self.x and temp.x < (self.x + self.width) 
			and temp.y > self.y and temp.y < (self.y + self.height ) then 
			-- create event to be heard by state state will now how to handle the button being clicked!
			add_event( { name = self.clickedEventName; receiverId = self.receiverId; senderId = self.id; delay = 0; } );
			print( self.id .. " Was Clicked" );
		end
	end	
end

return Button;
