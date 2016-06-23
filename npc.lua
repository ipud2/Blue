# usr/bin/lua

local Clone = require( "Clone" );
local AnimatedSprite = require( "AnimatedSprite" );
local Ai = require( "Ai" );

local npc = {};

--inherits create method
function npc:create( )
	self.velocity = { heading = { x = 0; y = 0; }; speed = { hor = 0; ver = 0; }; };
	self.maxSpeed = 1.8;
	self.accel = 0;
	self.maxAccel = .01;
	self.rotation = 0;
	
	
	-- create sprite
	self.sprite = Clone( AnimatedSprite );
	self.sprite:create( "NPCSprite",  self.layer, self.x, self.y, self.width, self.height );
	shape_setTexture( self.sprite.id, self.texId, true );
	
	self.sprite:addAnimation( "NpcWalkLeft",   32, 32, 96, 32, 3, 10 );
	self.sprite:setCurrentAnimation( "NpcWalkLeft" );
	print( self.id .. " Created" );
end

function npc:destroy( )

end

function npc:handleEvent( event )

end

function npc:update( dt )
	if self.x ~= Game.fsm.currentState.world.objs.link1.x or self.y ~= Game.fsm.currentState.world.objs.link1.y then
		local x, y, vel = Ai:seekPos( self.x, self.y, Game.fsm.currentState.world.objs.link1.x, Game.fsm.currentState.world.objs.link1.y, self.velocity, self.maxSpeed, self.maxAccel );
		self:setPos( x, y );
		self.velocity = vel;
	print( self.id .. " Updated!" );

	else
		self.velocity = 0;
	end
	self.sprite:update();
end

function npc:setPos( x, y );
	self.x = x;
	self.y = y;
	self.sprite:setPos( self.x, self.y );
end

function npc:seekPos( x, y )
	
end

return npc;
