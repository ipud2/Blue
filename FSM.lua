# usr/bin/lua

local Clone = require( "Clone" );
local State = require( "State" );


local FSM = {};

function FSM:create( owner, currentState, globalState )
	self.owner = owner or print( "invalid Owner passed to FSM" );
	self.prevState = nil;
	self.globalState = globalState or print( "Passed an invalid globalState to FSM" );
	self.currentState = currentState or self.globalState;
	if self.currentState ~= nil then self.currentState:onBegin( self.owner ); end       
	if self.globalState ~= nil then self.globalState:onBegin( self.owner ); end
end

function FSM:setCurrentState( currentState )
	self.currentState = currentState or print( "invalid state passed to setCurrentState" );
end

function FSM:setGlobalState( globalState )
	self.globalState = globalState or print( "invalid state passed to setGlobalState" );
end

function FSM:setPrevState( prevState ) 
	self.prevState = prevState or print( "invalid state sent to setPrevState" );
end

function FSM:handleEvent( event )
	local globalEvent = false; 	
	if self.globalState ~= nil then 
		if self.globalState:handleEvent( event ) then
			globalEvent = true;
		end
	end
	if globalEvent == false then
		if self.currentState ~= nil then 
			self.currentState:handleEvent( event );
		end
	end
end

function FSM:update( )
	if self.globalState then self.globalState:update( self.owner ); end
	if self.currentState then self.currentState:update( self.owner ); end
end

function FSM:changeState( newState )
	if newState ~= nil then 
		self:setPrevState( self.currentState );
		self.currentState:onExit( );
		self:setCurrentState( newState );
		self.currentState:onBegin( self.owner );
	else print( "invalid newState sent to changeState method" ); 
	end
end

function FSM:isInState( state )
	return self.currentState == state;
end

return FSM;
