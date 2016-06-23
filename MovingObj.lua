# usr/bin/lua



local MovingObj = Clone( require( "Rectangle" ) );

function MovingObj:create( id, layerId, x, y, w, h, mass, heading, maxSpeed, maxForce, maxTurnRate )
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
	self.layerId = layerId or 0;
	self.mass = mass or 0;
	self.heading = { }; -- READ ME READ ME READ ME READ ME READ ME What defines a heading?!??!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?!?! 
	self.maxSpeed = maxSpeed or 0;
	self.maxForce = maxForce or 0;
	self.maxTurnRate = maxTurnRate or 0;
	create_shape( self.id, layerId, self.x, self.y, 4, self.color.r, self.color.g, self.color.b, self.color.a );
	shape_setOrigin( self.id, self.x, self.y );
	-- always set points in clockwise rotation!
	-- 2nd arg is index to array of points(X,Y values) that make up this shape in C++
	shape_setPoint( self.id, 0, self.x, self.y );
	shape_setPoint( self.id, 1, self.x + self.width, self.y );
	shape_setPoint( self.id, 2, self.x + self.width, self.y + self.height );
	shape_setPoint( self.id, 3, self.x, self.y + self.height );

end

function MovingObj:destroy( )
	remove_shape( self.id, self.layerId );
end

function MovingObj:handleEvent( event )

end

function MovingObj:update( dt )

end

return MovingObj;
