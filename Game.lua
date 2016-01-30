# usr/bin/lua
register_events();

local Clone = require( "Clone" );
local Keyboard = require( "Keyboard" );
local Mouse = require( "Mouse" );
local Texture = require( "Texture" ); 

math.randomseed( os.time( ) );
-- the main game table that holds everything
Game = {};

-- A list of all resources being used by the game
Resources = {};
ObjMan = require( "ObjMan" );

-- required engine functions
function init( )
	-- load resources

	-- Create initial objects
	print( "Init has ran!" );
end
function handleEvents( )
	local event = get_event();
	while event ~= false do
		-- handle event here
		if event.receiverID == "GAME" then 

		else ObjMan:handleEvent( event );
		end											
		-- if event.receiverID == "LUA" then
		event = get_event();
	end
end
function update( dt )
	if Keyboard:isKeyPressed( "R" ) then init( ); end
	-- if Mouse:isButtonClicked( Mouse["Right"] ) then print( "Right Button Clicked!!!!!" ); end
	
	ObjMan:update( );
end

