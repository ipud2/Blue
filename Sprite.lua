# usr/bin/lua
register_graphics( );
register_convexShape( );

local Clone = require( "Clone" );
local RectangleShape = require( "Rectangle" );

local Sprite = {};
local Sprite = Clone( RectangleShape, Sprite );

function Sprite:setTexture( texId, resetFlag )
	self.texId = texId;
	shape_setTexture( self.id, self.texId, resetFlag );
end

return Sprite;

