# usr/bin/lua
register_graphics( );
register_texture( );

local Texture = { };
function Texture:create( id, fileName )
	self.id = id;
	self.fileName = fileName;
	self.isRepeated = false;
	self.isSmooth = false;
	texture_loadFromFile( id, fileName );
end
function Texture:setIsSmooth( isSmooth )
	self.isSmooth = isSmooth or false;
	texture_setIsSmooth( self.id, self.isSmooth );
end
function Texture:setIsRepeated( isRepeated )
	self.isRepeated = isRepeated or false;
	texture_setIsRepeated( self.id, self.isRepeated );
end

return Texture;
