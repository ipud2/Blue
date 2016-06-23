# usr/bin/lua

local globalState = {};
local Clone = require( "Clone" );
local runState = Clone( require( "RunState" ) );
local menuState = Clone( require( "MenuState" ) );
local pauseState = Clone( require( "PauseState" ) );

function globalState:onBegin( owner )
	self.owner = owner or print( "You sent an invalid owner to GlobalState" );
end

function globalState:onExit( )

end

function globalState:handleEvent( event )
	if event.receiverId == "Game" then
		if event.name == "goto_runState" then
			self.owner.fsm:changeState( runState );
		elseif event.name == "goto_menuState" then
			self.owner.fsm:changeState( menuState );
		elseif event.name == "goto_pauseState" then
			self.owner.fsm:setPrevState( self.owner.fsm.currentState );
			self.owner.fsm:setCurrentState( pauseState ); 
			self.owner.fsm.currentState:onBegin( self.owner );
		elseif event.name == "exit_pauseState" then
			self.owner.fsm.currentState:onExit( );
			self.owner.fsm:setCurrentState( self.owner.fsm.prevState );
		elseif event.name == "pauseToMainMenu" then
			self.owner.fsm.currentState:onExit( );
			self.owner.fsm:setCurrentState( self.owner.fsm.prevState );
			self.owner.fsm:changeState( menuState );
		elseif event.name == "exit_game" then 
			app_closeWindow( );
		end
	else return false;
	end
	return true;
end

function globalState:update()

end

return globalState;
