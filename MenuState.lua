# usr/bin/lua

local Clone = require( "Clone" );
local ControlMap = require( "ControlMap" );
local menuState = Clone( require( "State" ) );
local Camera = Clone( require( "Camera" ) );

function menuState:onBegin( owner )
	self.owner = owner;
	self.world = Clone( require( "World" ) );
	self.world:create( );
	-- resources
	self.world.layers.bg = addLayer( );
	self.world.layers.gui = addLayer( ); 
	self.world.layers.labels = addLayer( );

	self.world.fonts.font = font_loadFromFile( "font1", "Unique.ttf" );
	local Texture = require( "Texture" );
	self.world.textures.button = Clone( Texture );
	self.world.textures.button:create( "buttonTex", "button.png" );
	self.world.textures.background = Clone( Texture );
	self.world.textures.background:create( "MenuBackground", "menuBg.png" )	
	-- bg image
	self.sprites = {};
	--self.sprites.bg = Clone( require( "Sprite" ) );
	--self.sprites.bg:create( "bgSprite", self.world.layers.bg, 0, 0, 800, 600 );
	--shape_setTexture( self.sprites.bg.id, self.world.textures.background.id, true ); 
	
	-- title!
	self.world.glyphs.title = Clone( require( "Glyph" ) );
	self.world.glyphs.title:create( "titleLabel", self.world.layers.labels, self.world.fonts.font, 100, "GAME TITLE", 100,200 );
	self.world.glyphs.title:setTextColor( { r = 255; b = 0; g = 0; a = 255  } );
	
	-- Buttons n stuff
	-- play
	self.world.objs.playButton = Clone( require( "Button" ) );
	self.world.objs.playButton:create( "playButton", self.world.layers.gui, "goto_runState", "Game", 100, 300, 200, 50 );
	shape_setTexture( self.world.objs.playButton.id, self.world.textures.button.id, true ); -- no need to settexRect becuase it uses the whole image
	
	self.world.glyphs.playButtonLabel = Clone( require( "Glyph" ) );
	self.world.glyphs.playButtonLabel:create( "playButtonLabel", self.world.layers.labels, self.world.fonts.font, 48, "Play", 100, 300 );

	-- exit
	self.world.objs.exitButton = Clone( require( "Button" ) );
	self.world.objs.exitButton:create( "exitButton", self.world.layers.gui, "exit_game", "Game", 100, 410, 200, 50 );
	shape_setTexture( self.world.objs.exitButton.id, self.world.textures.button.id, true ); -- no need to settexRect becuase it uses the whole image
	
	self.world.glyphs.exitButtonLabel = Clone( require( "Glyph" ) );
	self.world.glyphs.exitButtonLabel:create( "exitButtonLabel", self.world.layers.labels, self.world.fonts.font, 48, "Exit", 100, 410 );
	
	-- Currently selected Button shader
	self.world.sprites.selectorBox = Clone( require( "Rectangle" ) );
	self.world.sprites.selectorBox:create( "SelectorBox", self.world.layers.labels, 100, 300, 200, 50 );
	self.world.sprites.selectorBox:setFillColor( { r = 255; g = 0; b = 0; a = 150; } );
	
	-- set up the camera
	self.mainView = Clone( Camera );
	self.mainView:create( "mainView", _SCREEN_WIDTH / 2, _SCREEN_HEIGHT / 2, _SCREEN_WIDTH, _SCREEN_HEIGHT );	
end

function menuState:onExit(  )
	self.world:destroy( );
	self.mainView:destroy( );
	self.mainView = nil;
	self.world = nil;
end

function menuState:handleEvent( event )
	if event.receiverId ~= "menuState" then
		for i, j in pairs( self.world.objs ) do 
			if i == event.receiverId then j:handleEvent( event ); end
		end
	else print( "menuState got an event" );
	end
end

function menuState:update( )
	for i, j in pairs( self.world.objs ) do j:update(); end
	if Keyboard:isKeyPressed( ControlMap.MainMenu.moveUp ) then
		if self.world.objs.playButton.isSelected == false then
			self.world.objs.exitButton.isSelected = false;
			self.world.objs.playButton.isSelected = true;
			self.world.sprites.selectorBox:setPos( 100, 300, 200, 50 );
		end
	elseif Keyboard:isKeyPressed( ControlMap.MainMenu.moveDown ) then
		if self.world.objs.exitButton.isSelected == false then
			self.world.objs.playButton.isSelected = false;
			self.world.objs.exitButton.isSelected = true;
			self.world.sprites.selectorBox:setPos( 100, 410, 200, 50 );
		end
	elseif Keyboard:isKeyPressed( ControlMap.MainMenu.select ) then
		if self.world.sprites.selectorBox.y == self.world.objs.playButton.y then
			add_event( { name = self.world.objs.playButton.clickedEventName; receiverId = "Game"; senderID = self.world.objs.playButton.id; delay = 0; } );
		elseif self.world.sprites.selectorBox.y == self.world.objs.exitButton.y then
			add_event( { name = self.world.objs.exitButton.clickedEventName; receiverId = "Game"; senderID = self.world.objs.exitButton.id; delay = 0; } );
		end
 	elseif Keyboard:isKeyPressed( ControlMap.MainMenu.exit ) then
		app_closeWindow( );
	end
end

return menuState;
