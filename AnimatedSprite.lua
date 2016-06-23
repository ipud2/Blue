# usr/bin/lua

local Animation = require( "Animation" );
local Clone = require( "Clone" );

local AnimatedSprite = Clone( require( "Rectangle" ) );

AnimatedSprite.id = "NONE";
AnimatedSprite.texId = "NONE";
AnimatedSprite.x = 0;
AnimatedSprite.y = 0;
AnimatedSprite.width = 0;
AnimatedSprite.height = 0;
AnimatedSprite.currentAnimation = Clone( Animation );

function AnimatedSprite:update()
	local rect = self.currentAnimation:update();
	shape_setTexRect( self.id, rect.x, rect.y, rect.width, rect.height );
end

function AnimatedSprite:addAnimation( id, frameWidth, frameHeight, startX, startY, numFrames, frameTime )
	if self[id] == nil then
		local animation = Clone( Animation );
		animation:create( frameWidth, frameHeight, startX, startY, numFrames, frameTime );
		self[id] = animation;
	else
		print( "There is already an animation with the id: " .. id );
	end
end

function AnimatedSprite:setCurrentAnimation( id )
	if self[id] ~= nil then 
		self.currentAnimation = self[id];
	else
		print( "invalid animation id" );
	end
end

return AnimatedSprite;
