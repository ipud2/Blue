# usr/bin/lua
register_graphics( );
register_convexShape( );

local Clone = require( "Clone" );
local RectangleShape = require( "Rectangle" );

local Sprite = {};
local Sprite = Clone( RectangleShape, Sprite );

function Sprite:setTexture( texId, texRect, resetFlag )
	self.texId = texId or print( "invalid texID: " .. texId ); self.texRect = texRect or { x = 0; y = 0; width = 0; height = 0; };
	shape_setTexture( self.id, self.texId, resetFlag );
	shape_setTexRect( self.id, self.texRect.x, self.texRect.y, self.textRect.width, self.textRect.height );
end

function Sprite:setTextureRect( rect )
	shape_setTexRect( self.id, rect.x, rect.y, rect.width, rect.height );
end

return Sprite;

