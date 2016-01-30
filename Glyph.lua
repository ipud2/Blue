# usr/bin/lua

register_glyph( );

local Glyph = {};
function Glyph:create( id, fontId, fontSize, text, x, y )
	self.id = id or "Undefined Glyph";
	self.fontStyles = { };
	self.fontStyles["regular"] = 0;
	self.fontStyles["bold"] = 1;
	self.fontStyles["italic"] = 2; 
	self.font = fontId or "Undefined Font";
	self.fontSize = fontSize or 0;
	self.text = text or "";
	self.textColor = { r = 255, g = 255, b = 255, a = 255 };
	self.style = self.fontStyles["regular"];
	self.x = x or 0;
	self.y = y or 0;
	create_glyph( self.id, self.font, text, self.x, self.y );
end
function Glyph:setPos( x, y )
	self.x = x or 0;
	self.y = y or 0;
	glyph_setPos( self.id, self.x, self.y );
end
function Glyph:rotate( angle )
	self.rotation = self.rotation + angle or 0;
	glyph_setRotation( self.id, self.rotation );
end
function Glyph:move( x, y )
	self.x = self.x + x or 0;
	self.y = self.y + y or 0;
	glyph_setPos( self.id, self.x, self.y );
end
function Glyph:scale( scaleX, scaleY )
	self.scale.x = scaleX or 0;
	self.scale.y = scaleY or 0;
	glyph_setScale( self.id, self.scale.x, self.scale.y );
end
function Glyph:setText( text )
	self.text = text or "";
	glyh_setstring( self.id, self.text );
end
function Glyph:setFont( fontId )
	self.font = fontId or "";
	glyph_setFont( self.id, self.font );
end
function Glyph:setFontSize( fontSize )
	self.fontSize = fontSize or 30;
	glyph_setCharSize( self.id, self.fontSize ); 
end
function Glyph:setTextColor( color )
	self.textColor = color or { r = 255, g = 255, b = 255, a = 255 };
	glyph_setTextColor( self.id, self.textColor.r, self.textColor.g, self.textColor.b, self.textColor.a );
end
function Glyph:setStyle( fontStyle )
	self.style = self.fontStyles[fontStyle] or self.fontStyles["regular"];
	glyph_setStyle( self.id, self.style );
end
function Glyph:getGlobalBounds()
	print( "Glyph:getGlobalBounds is still in development!" );
	--rect = glyph_getGlobalBounds( self.id );
	--return rect;
end
return Glyph;
