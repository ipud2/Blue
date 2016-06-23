# usr/bin/lua

local Clone = require( "Clone" );
local MapMan = require( "MapManager" );
local runState = Clone( require( "State" )  );
local Camera = require( "Camera" );
local testLevel = require( "test2" );
local ControlMap = require( "ControlMap" );

function runState:onBegin( owner )
	self.owner = owner or print( "failed to give proper owner to Game's runState" );
	-- load resources: textures, sounds, etc..
	self.world = MapMan:loadMap( testLevel );
	self.mainView = Clone( Camera );
	self.mainView:create( "mainView", _SCREEN_WIDTH / 2, _SCREEN_HEIGHT / 2, _SCREEN_WIDTH, _SCREEN_HEIGHT );
	print( "RunState:onBegin() complete!" );
 end
 
 function runState:onExit(  )
	-- need to destroy resources being used in the engine here!!
	self.world:destroy();
	self.mainView:destroy( );
	self.world = nil;
 end
 
 function runState:handleEvent( event )
	if event.receiverId ~= "runState" then 	
		for i, j in pairs( self.world.objs ) do 
			if i == event.receiverId then j:handleEvent( event ); end
		end
	else print( "runState got an event!! ... now what?" );
	end
 end
 
 function runState:update()
 --[[
 This is were it is broken!!!!
 --]]
 -- the if statment crashes the code not the add_event method
	if Keyboard:isKeyPressed( ControlMap.Game.pauseGame ) then 
		add_event( { name = "goto_pauseState"; receiverId = "Game"; senderId = "pauseState"; delay = 0; } );
	end
	
	for i, j in pairs( self.world.objs ) do j:update(); end
	self.mainView:setPos( self.world.objs.link1.x, self.world.objs.link1.y );
 end

return runState;
