# usr/bin/lua

register_camera( );

local Camera = {};

-- dont forget camera x, y coords refer to the center of the camera.. camera interface is wierd
function Camera:create( id, x, y, w, h )
	self.id = id or print( " invalid id sent to camera" );
	self.x = x or 0;
	self.y = y or 0;
	self.w = w or 0;
	self.h = h or 0;
	self.rotation = 0;
	self.zoom = 0;
	self.viewport = { x = 1; y = 1; w = 1; h = 1 };
	create_camera( self.id, self.x, self.y, self.w, self.h );
	print( "Camera: " .. self.id .. " created" );
end

function Camera:destroy( )
	remove_camera( self.id );
end

-- Don't forget the view port is measured from 0 to 1, 1 being the far left or bottom of the screen 0 being the far left or top section
function Camera:setViewport( x, y ,w, h )
	self.viewport.x = x or 0;
	self.viewport.y = y or 0;
	self.viewport.w = w or 0;
	self.viewport.h = h or 0;
	camera_setViewport( self.id, self.viewport.x, self.viewport.y, self.viewport.w, self.viewport.h );
end

function Camera:move( x, y )
	self.x = self.x + x;
	self.y = self.y + y;
	camera_move( self.id, x, y );
end

function Camera:rotate( angle )
	self.rotation = self.rotation + angle;
	camera_rotate( self.id, angle );
end

function Camera:zoom( factor )
	self.zoom = factor;
	camera_zoom( self.id, factor );
end

function Camera:setPos( x, y )
	self.x = x or print( "invalid X sent to camera:setPos" );
	self.y = y or print( "invalid Y sent to camera:setPos" );
	camera_setCenter( self.id, self.x, self.y );
end

function Camera:setRotation( rotation )
	self.rotation = rotation or 0;
	camera_setRotation( self.id, self.rotation );
end

return Camera;
