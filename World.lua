# usr/bin/lua

-- need to finish this it is meant to be able to rotate the tiles in the map based on a chosen origin 
-- plus any other helpful tools related to manipulating the game world on a macro scale

local World = {};

function World:create(  )
	self.textures = {};
	self.fonts = {};
	self.layers = {};
	self.tiles = {};
	self.sprites = {};
	self.glyphs = {};
	self.objs = {};
end 

function World:destroy( )
	for i, j in pairs( self.tiles ) do 
		--print( "Removing tile: " .. i )
		j:destroy( ); 
	end
	for i, j in pairs( self.glyphs ) do 
		print( "Removing Glyph: " .. i );
		j:destroy( ) ;
	end
	for i, j in pairs( self.objs ) do 
		print( "Removing Obj: " .. i )
		j:destroy( ); 
	end
	for i, j in pairs( self.textures ) do 
		print( "Removing Texture: " .. i );
		remove_texture( j.id ); 
	end
	for i, j in pairs( self.sprites ) do
	print( j.layerId );
		print( "Removing Sprite: " .. j.id );
		j:destroy( );
	end
	for i, j in pairs( self.fonts ) do
		print( "Removing font: " .. self.fonts[i] );
		remove_font( self.fonts[i] );
	end
	for i, j in pairs( self.layers ) do 
		print( "Removing layer: " .. i );
		remove_layer(  ); 
	end
	print( "=========================================================" );
end

function World:rotate( origin, angle )

end

return World;
