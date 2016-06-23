# usr/bin/lua
register_system();
register_input( )
register_event();
register_collision( );
register_graphics( );
register_glyph( );

-- global table that holds all game resources and data.. to much power?
Game = {};
Keyboard = require( "Keyboard" );
local Mouse = require( "Mouse" );
local State = require( "State" );
local Clone = require( "Clone" );
local FSM = require( "FSM" );
local pauseState = Clone( require( "PauseState" ) );
local menuState = Clone( require( "MenuState" ) );
local runState = Clone( require( "RunState" ) );
local globalState = Clone( require( "GlobalState" ) );

-- required engine functions
function init( )
	Game.fsm = Clone( FSM );
	Game.fsm:create( Game, menuState, globalState );
	print( "Init has ran!" );
end
function handleEvents( )
	local event = get_event();
	while event ~= false do
		-- handle event here
		if event.receiverID == "LUA" then 

		else 
			Game.fsm:handleEvent( event );
		end											
		event = get_event();
	end
end
function update( dt )
	if Keyboard:isKeyPressed( "R" ) then 
		Game.fsm.currentState:onExit( ); 
		init( ); 
	end
	Game.fsm:update( );
	-- if Mouse:isButtonClicked( Mouse["Right"] ) then print( "Right Button Clicked!!!!!" ); end	
	
end
