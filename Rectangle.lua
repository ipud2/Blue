# usr/bin/lua

register_graphics( );
register_convexShape( );

local Rectangle = { };
function Rectangle:create( id, x, y, w, h )
	self.id = id or "UNDEFINED ASSET ID";
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
	create_shape( self.id, self.x, self.y, 4, self.color.r, self.color.g, self.color.b, self.color.a );
	shape_setOrigin( self.id, self.x + self.width/2, self.y + self.height/2 );
	-- always set points in clockwise rotation!
	-- 2nd arg is index to array of points(X,Y values) that make up this shape in C++
	shape_setPoint( self.id, 0, self.x, self.y );
	shape_setPoint( self.id, 1, self.x + self.width, self.y );
	shape_setPoint( self.id, 2, self.x + self.width, self.y + self.height );
	shape_setPoint( self.id, 3, self.x, self.y + self.height );
end
function Rectangle:destroy( )
	remove_shape( self.id )
end

function Rectangle:setSize( width, height )
	self.width = width or 0;
	self.height = height or 0;
	shape_setPoint( self.id, 0, self.x, self.y );
	shape_setPoint( self.id, 1, self.x + self.width, self.y );
	shape_setPoint( self.id, 2, self.x + self.width, self.y + self.height );
	shape_setPoint( self.id, 3, self.x, self.y + self.height );
end
function Rectangle:getSize( )
	return { w = self.width, h = self.height };
end

function Rectangle:setPos( x, y )
	self.x = x or 0;
	self.y = y or 0;
	shape_setPos( self.id, self.x, self.y );
end
function Rectangle:getPos( )
	return { x = self.x, y = self.y };
end

function Rectangle:rotate( angle )
	self.rotation = self.rotation + angle or 0;
	shape_setRotation( self.id, self.rotation );
end
function Rectangle:move( x, y )
	self.x = self.x + x or 0;
	self.y = self.y + y or 0;
	shape_setPos( self.id, self.x, self.y );
end
function Rectangle:scale( scaleX, scaleY )
	self.scale.x = scaleX or 0;
	self.scale.y = scaleY or 0;
	shape_setScale( self.id, self.scale.x, self.scale.y );
end
function Rectangle:setFillColor( color )
	self.color = color or { r = 255, g = 0, b = 255, a = 255 };
	shape_setColor( self.id, self.color.r, self.color.g, self.color.b, self.color.a );
end
function Rectangle:setOutLineColor( outlineColor )
	self.outlineColor = outlineColor or { r = 255, g = 0, b = 255, a = 255 };
	shape_setOutlineColor( self.id, self.outlineColor.r, self.outlineColor.g, self.outlineColor.b, self.outlineColor.a );
end
function Rectangle:setOutlineThickness( thickness )
	self.outlineThickness = thickness or 0;
	shape_setOutlineThickness( self.id, self.outlineThickness );
end


return Rectangle;
