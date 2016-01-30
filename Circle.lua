# usr/bin/lua

register_graphics( );
register_convexShape( );

local Circle = {};
function Circle:create( id, x, y, radius, color )
	self.id = id or "UNDEFINED ASSET ID";
	self.x = x or 0;
	self.y = y or 0;
	self.radius = radius or 0;
	self.rotation = 0;
	self.scale = { x = 1, y = 1 };
	self.color = color or { r = 255, g = 0, b = 255, a = 255 };
	self.outlineColor = { r = 255, g = 0, b = 255, a = 0 };
	self.outlineThickness = 0;
	self.origin = { x = 0, y = 0 };
	self.segments = 30;
	create_shape( self.id, self.x, self.y, self.segments, self.color.r, self.color.g, self.color.b, self.color.a );
	shape_setOrigin( self.id, self.x, self.y );
	self:defineCircle( );
end
function Circle:setRadius( radius )
	self.radius = radius or 0;
	self:defineCircle();
end
function Circle:setPos( x, y )
	self.x = x or 0;
	self.y = y or 0;
	shape_setPos( self.id, self.x, self.y );
end
function Circle:rotate( angle )
	self.rotation = self.rotation + angle or 0;
	shape_setRotation( self.id, self.rotation );
end
function Circle:move( x, y )
	self.x = self.x + x;
	self.y = self.y + y;
	shape_setPos( self.id, self.x, self.y );
end
function Circle:scale( scaleX, scaleY )
	self.scale.x = scaleX or 0;
	self.scale.y = scaleY or 0;
	shape_setScale( self.id, self.scale.x, self.scale.y );
end
function Circle:setFillColor( color )
	self.color = color or { r = 255, g = 0, b = 255, a = 255 };
	shape_setColor( self.id, self.color.r, self.color.g, self.color.b, self.color.a );
end
function Circle:setOutLineColor( outlineColor )
	self.outlineColor = outlineColor or { r = 255, g = 0, b = 255, a = 255 };
	shape_setOutlineColor( self.id, self.outlineColor.r, self.outlineColor.g, self.outlineColor.b, self.outlineColor.a );
end
function Circle:setOutlineThickness( thickness )
	self.outlineThickness = thickness or 0;
	shape_setOutlineThickness( self.id, self.outlineThickness );
end
function Circle:defineCircle( )
	a = 0;
	i = 0;
	-- loop mathimaticly sets all the tiny segments to create a decent looking circle
	while a < 360 and i < self.segments + 1 do
		a = i * 2 * math.pi / self.segments - math.pi / 2;
        x = math.cos(a) * self.radius;
        y = math.sin(a) * self.radius;  
     	shape_setPoint( self.id, i, self.x + self.radius + x, self.y + self.radius + y );    
     	i = i + 1;
	end	
end

return Circle;
