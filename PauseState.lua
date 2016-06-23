# usr/bin/lua
 
local Clone = require( "Clone" );
local pauseState = Clone( require( "State" ) );
local ControlMap = require( "ControlMap" );

function pauseState:onBegin( owner )
	self.owner = owner;
	self.world = Clone( require( "World" ) );
	self.world:create();
	-- resources
	self.world.layers.gui = addLayer( ); 
	self.world.layers.labels = addLayer( );

	self.world.fonts.font = font_loadFromFile( "font1", "Unique.ttf" );
	local Texture = require( "Texture" );
	self.world.textures.button = Clone( Texture );
	self.world.textures.button:create( "buttonTex", "button.png" );	
	self.world.glyphs = {};
	
	-- need to get the origin of the camera being used so the buttons get drawn on screen
	local originX = self.owner.fsm.prevState.mainView.x; -- wold return middle of the view..
	local originY = self.owner.fsm.prevState.mainView.y;
	
	-- title!
	self.world.glyphs.title = Clone( require( "Glyph" ) );
	self.world.glyphs.title:create( "titleLabel1", self.world.layers.labels, self.world.fonts.font, 48, "Paused", originX - 100, originY - 100 );
	self.world.glyphs.title:setTextColor( { r = 0; b = 255; g = 0; a = 255  } );
	
	-- Buttons n stuff
	self.world.objs.resumeButton = Clone( require( "Button" ) );
	self.world.objs.resumeButton:create( "resumeButton", self.world.layers.gui, "exit_pauseState", "Game", originX - 100, originY, 200, 50 );
	shape_setTexture( self.world.objs.resumeButton.id, self.world.textures.button.id, true ); -- no need to settexRect becuase it uses the whole image
	
	self.world.glyphs.resumeButtonLabel = Clone( require( "Glyph" ) );
	self.world.glyphs.resumeButtonLabel:create( "resumeButtonLabel", self.world.layers.labels, self.world.fonts.font, 48, "Resume", originX -100, originY );	
	
		-- exit
	self.world.objs.exitButton = Clone( require( "Button" ) );
	self.world.objs.exitButton:create( "exitButton", self.world.layers.gui, "pauseToMainMenu", "Game", originX - 100, originY + 100, 200, 50 );
	shape_setTexture( self.world.objs.exitButton.id, self.world.textures.button.id, true ); -- no need to settexRect becuase it uses the whole image
	
	self.world.glyphs.exitButtonLabel = Clone( require( "Glyph" ) );
	self.world.glyphs.exitButtonLabel:create( "exitButtonLabel", self.world.layers.labels, self.world.fonts.font, 48, "Back to Menu", originX - 100, originY + 100 );
	
	--self.gui:addButton( "exitButton", self.world.textures.button.id, self.world.layers.gui, "exitButtonClicked", "menuState", 200, 260, 200, 50 );
	--self.gui:addLabel( "exitButtonLabel", self.world.layers.labels, self.world.fonts.font, 48, "Exit!", 200, 260 );
	
	-- Currently selected Button shader
	self.world.sprites.selectorBox = Clone( require( "Rectangle" ) );
	self.world.sprites.selectorBox:create( "SelectorBox", self.world.layers.labels, originX - 100, originY, 200, 50 );
	self.world.sprites.selectorBox:setFillColor( { r = 255; g = 0; b = 0; a = 150; } );
end

function pauseState:onExit( )
	self.world:destroy( );
	self.world = nil;
end

function pauseState:handleEvent( event )
	if event.receiverId ~= "pauseState" then
		for i, j in pairs( self.world.objs ) do 
			if i == event.receiverId then j:handleEvent( event ); end
		end
	else print( "pauseState got an event" );
	end
end

function pauseState:update(  )
	for i, j in pairs( self.world.objs ) do j:update(); end
	if Keyboard:isKeyPressed( ControlMap.PauseMenu.moveUp ) then
		if self.world.objs.resumeButton.isSelected == false then
			self.world.objs.exitButton.isSelected = false;
			self.world.objs.resumeButton.isSelected = true;
			self.world.sprites.selectorBox:setPos( self.world.objs.resumeButton.x, self.world.objs.resumeButton.y, 200, 50 );
		end
	elseif Keyboard:isKeyPressed( ControlMap.PauseMenu.moveDown ) then
		if self.world.objs.exitButton.isSelected == false then
			self.world.objs.resumeButton.isSelected = false;
			self.world.objs.exitButton.isSelected = true;
			self.world.sprites.selectorBox:setPos( self.world.objs.exitButton.x, self.world.objs.exitButton.y, 200, 50 );
		end
	elseif Keyboard:isKeyPressed( ControlMap.PauseMenu.select ) then
		if self.world.sprites.selectorBox.y == self.world.objs.resumeButton.y then
			add_event( { name = self.world.objs.resumeButton.clickedEventName; receiverId = "Game"; senderID = self.world.objs.resumeButton.id; delay = 0; } );
		elseif self.world.sprites.selectorBox.y == self.world.objs.exitButton.y then
			add_event( { name = self.world.objs.exitButton.clickedEventName; receiverId = "Game"; senderID = self.world.objs.exitButton.id; delay = 0; } );
		end
	end

end

return pauseState;
