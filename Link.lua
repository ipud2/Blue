# usr/bin/lua
local Clone = require( "Clone" );
local AnimatedSprite = require( "AnimatedSprite" );
local State = require( "State" );
local ControlMap = require( "ControlMap" );

local LinkGlobal = Clone( State );
local LinkBlack = Clone( State );
local LinkGreen = Clone( State );

function LinkGlobal:onBegin( owner )
	self.owner = owner or print( "invalid owner!!!" );
	self.owner.sprite:setCurrentAnimation( "greenStandDown" );
end

function LinkGlobal:onExit( owner )
	-- still working on this...
end

function LinkGlobal:handleEvent( event )
	if event.name == "COLLISION" then -- need to add link to the collision Man for this to work
		print( "Something Has collided with link!!" );
	end
end

function LinkGlobal:update()
	self.owner.isStandingStill = true;
	if Keyboard:isKeyPressed( ControlMap.Game.moveLeft ) then 
		self.owner.direction = "Left";
		self.owner:move( -2, 0 );
		self.owner.isStandingStill = false;
	elseif Keyboard:isKeyPressed( ControlMap.Game.moveRight ) then 
		self.owner.direction = "Right";
		self.owner:move( 2, 0 );
		self.owner.isStandingStill = false;
	end
	if Keyboard:isKeyPressed( ControlMap.Game.moveUp ) then 
		self.owner.direction = "Up";
		self.owner:move( 0, -2 );
		self.owner.isStandingStill = false;
	elseif Keyboard:isKeyPressed( ControlMap.Game.moveDown ) then 
		self.owner.direction = "Down";
		self.owner:move( 0, 2 );
		self.owner.isStandingStill = false;
	end
end
-- ========================================================================================================
function LinkGreen:onBegin( owner )
	self.owner = owner or print( "invalid owner!!!" );
	--self.owner.Width = 32; self.owner.Height = 32;
	--self.owner.sprite:setSize( 32, 32 );
end

function LinkGreen:onExit( owner )
	-- still working on this...
end

function LinkGreen:handleEvent( event )

end

function LinkGreen:update( )
	if self.owner.isStandingStill then self.owner.sprite:setCurrentAnimation( "greenStand" .. self.owner.direction );
	else self.owner.sprite:setCurrentAnimation( "greenWalk" .. self.owner.direction ); end
	if Keyboard:isKeyPressed( ControlMap.Game.changeBlack ) then self.owner.fsm:changeState( LinkBlack ); end
end

-- ========================================================================================================

function LinkBlack:onBegin( owner )
	self.owner = owner or print( "invalid owner!!!" );
end
function LinkBlack:onExit( owner )
	-- still working on this...
end
function LinkBlack:handleEvent( event )
end
function LinkBlack:update()
	if self.owner.isStandingStill then self.owner.sprite:setCurrentAnimation( "blackStand" .. self.owner.direction );
	else self.owner.sprite:setCurrentAnimation( "blackWalk" .. self.owner.direction ); end
	if Keyboard:isKeyPressed( ControlMap.Game.changeGreen ) then self.owner.fsm:changeState( LinkGreen ); end
end

-- ========================================================================================================

local Link = Clone( require( "Object" ) );


function Link:create( )
	self.direction = "Down";
	self.isStandingStill = true;
	-- create sprite
	self.sprite = Clone( AnimatedSprite );
	self.sprite:create( "linkSprite",  self.layer, self.x, self.y, self.width, self.height );
	shape_setTexture( self.sprite.id, self.texId, true );

	self.sprite:addAnimation( "greenWalkLeft",   32, 32, 96, 32, 3, 10 );
	self.sprite:addAnimation( "greenWalkRight",  32, 32, 96, 64, 3, 10 );
	self.sprite:addAnimation( "greenWalkUp",     32, 32, 96, 96, 3, 10 );
	self.sprite:addAnimation( "greenWalkDown",   32, 32, 96,  0, 3, 10 );
	self.sprite:addAnimation( "greenStandLeft",  32, 32, 96, 32, 1, 10 );
	self.sprite:addAnimation( "greenStandRight", 32, 32, 96, 64, 1, 10 );
	self.sprite:addAnimation( "greenStandUp",    32, 32, 96, 96, 1, 10 );
	self.sprite:addAnimation( "greenStandDown",  32, 32, 96,  0, 1, 10 );
	
	self.sprite:addAnimation( "blackWalkLeft",   32, 32, 288, 160, 3, 10 );
	self.sprite:addAnimation( "blackWalkRight",  32, 32, 288, 192, 3, 10 );
	self.sprite:addAnimation( "blackWalkUp",     32, 32, 288, 224, 3, 10 );
	self.sprite:addAnimation( "blackWalkDown",   32, 32, 288, 128, 3, 10 );
	self.sprite:addAnimation( "blackStandLeft",  32, 32, 288, 160, 1, 10 );
	self.sprite:addAnimation( "blackStandRight", 32, 32, 288, 192, 1, 10 );
	self.sprite:addAnimation( "blackStandUp",    32, 32, 288, 224, 1, 10 );
	self.sprite:addAnimation( "blackStandDown",  32, 32, 288, 128, 1, 10 );

	self.fsm = Clone( require( "FSM" ) );
	self.fsm:create( self, LinkGreen, LinkGlobal );
end

function Link:destroy()
	self.fsm.currentState:onExit();
	self.sprite:destroy( );
	self.sprite = nil;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
end

function Link:handleEvent( event )
	self.fsm:handleEvent( event );
end

function Link:update(  )
	self.fsm:update( );
	self.sprite:update( );
end

function Link:move( x, y )
	self.x = self.x + x;
	self.y = self.y + y;
	self.sprite:setPos( self.x, self.y );
end

return Link;
