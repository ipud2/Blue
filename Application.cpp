#include "Application.h"

//## Constructors
Application::Application( void )
        : mLuaState( luaL_newstate( ) ) { }
Application::~Application( void ) { delete Window; }

//## Interface
void Application::run( void ) {
    // defines basic window properties
    this->init();
    // this is the main game loop!!
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while( Window->isOpen( ) ) {
        timeSinceLastUpdate += clock.restart();
        while( timeSinceLastUpdate > TimePerFrame ) {
            timeSinceLastUpdate -= TimePerFrame;
            update( timeSinceLastUpdate );
            handleEvents( );
        }
        draw( );
    }
}

void Application::init( void ) {
    runConfig( ); // run config.lua for defualt window values
    setUpBlueEnvironment( ); // set up engine methods for lua

    // read file or crash program

    if( luaL_dofile( mLuaState, "Game.lua" )   ) assert( "Can't find Game.lua!\n" == std::string( ) );

    // call Game.lua init for any user game specific setup
    lua_getglobal( mLuaState, "init" );
    if( !lua_isfunction( mLuaState, -1 ) ) assert( "You didn't create the init function in Game.lua!" == std::string() );
    lua_pcall( mLuaState, 0, 0, 0 ); // 0's == args, return vals, error checking C style
    // so the screen isnt blank during first update
    draw( );
}
void Application::update( sf::Time dt ) {
    // call Game.lua update
    lua_getglobal( mLuaState, "update" );
    // make sure "update" function exists
    if( !lua_isfunction( mLuaState, -1 ) ) assert( "You didn't create the update function in Game.lua!" == std::string() );
    // push dt on stack for arg
    lua_pushnumber( mLuaState, dt.asMilliseconds( ) );
    // call Game.lua update method
    lua_pcall( mLuaState, 1, 0, 0 ); // 0's == args, return vals, error checking C style

    // CollisionMan needs to be updated here
    CollisionMan::update( );
}
void Application::handleEvents( void ) {
    SystemMan::Events::update( );
    sf::Event event;
    while( Window->pollEvent( event ) ) {
        if( event.type == sf::Event::Closed )
            Window->close( );
        else
            SystemMan::Events::addEvent( event );
    }
    // Call lua handle Events Method here
    lua_getglobal( mLuaState, "handleEvents" );
    // make sure "update" function exists
    if( !lua_isfunction( mLuaState, -1 ) ) assert( "You didn't create the handleEvents function in Game.lua!" == std::string() );
    // call Game.lua handleEvents method
    lua_pcall( mLuaState, 0, 0, 0 ); // 0's == args, return vals, error checking C style

}
void Application::draw( void ) {
    // get list of drawables from GraphicsMan and draw them.
    Window->clear( mBackgroundColor );

    // set up all the views to be rendered
    for( auto camera : CameraMan::cameras ) {
        Window->setView( camera.second );
        // iterate through all the layers drawing all drawable assets in the structure
        for( auto layer : GraphicsMan::Layers::layers ) {
            for( auto asset : layer.mGraphics ) {
                Window->draw( *asset.second );
            }
        }
    }
    Window->display( );
}
//## Behaviors
void Application::runConfig( void ) {
    // setup lua libraries
    luaopen_base( mLuaState );    // basic lib
    luaopen_table( mLuaState );   // table lib
    luaopen_io( mLuaState );      // i/o lib
    luaopen_math( mLuaState );
    /// call lua config file get values setup window accordingly
    // read file or crash program
    // luaL_doFile is a macro that uses LuaL_loadfile and returns false if everything is okay
    // or true if there are errors present
    if( luaL_dofile( mLuaState, "config.lua" )   )
        assert( "Can't find config.lua!\n" == std::string( ) );
    int screenWidth = 0;
    int screenHeight = 0;
    int red, green, blue = 0;

    lua_getglobal( mLuaState, "SCREEN_WIDTH" );
    if( !lua_isnumber( mLuaState, -1 ) ) assert( "You didn't set the SCREEN_WIDTH in config.lua!" == std::string( ) );

    screenWidth = lua_tointeger( mLuaState, -1 );
    lua_pop( mLuaState, 1 ); // pop SCREEN_WIDTH

    lua_getglobal( mLuaState, "SCREEN_HEIGHT" );
    if( !lua_isnumber( mLuaState, -1 ) ) assert( "You didn't set the SCREEN_HEIGHT in config.lua!" == std::string( ) );

    screenHeight = lua_tointeger( mLuaState, -1 );
    lua_pop( mLuaState, 1 ); // pop SCREEN_HEIGHT

    // bgColor values...
    lua_getglobal( mLuaState, "BACKGROUND_COLOR" );
    if( !lua_istable( mLuaState, -1 ) ) assert( "You didn't set the BACKGROUND_COLOR in config.lua!" == std::string( ) );

    lua_getfield( mLuaState, -1, "RED" );
    if( !lua_isnumber( mLuaState, -1 ) ) assert( "You didn't set the RED option for BACKGROUND_COLOR in config.lua!" == std::string( ) );
    red = lua_tointeger( mLuaState, -1 );
    lua_pop( mLuaState, 1 );

    lua_getfield( mLuaState, -1, "GREEN" );
    if( !lua_isnumber( mLuaState, -1 ) ) assert( "You didn't set the GREEN option for BACKGROUND_COLOR in config.lua!" == std::string( ) );
    green = lua_tointeger( mLuaState, -1 );
    lua_pop( mLuaState, 1 );

    lua_getfield( mLuaState, -1, "BLUE" );
    if( !lua_isnumber( mLuaState, -1 ) ) assert( "You didn't set the BLUE option for BACKGROUND_COLOR in config.lua!" == std::string( ) );
    blue = lua_tointeger( mLuaState, -1 );
    lua_pop( mLuaState, 1 );

    // pop bgColor table
    lua_pop( mLuaState, 1 );

    // close config.lua
    lua_close( mLuaState );
    mLuaState = nullptr;

    // use values to setup game
    Window->create( sf::VideoMode( screenWidth, screenHeight ), "Project Blue" );
    mBackgroundColor = sf::Color( red, green, blue );
    // open new state
    mLuaState = luaL_newstate( );
}
void Application::setUpBlueEnvironment( void ) {
    /// Setup mLuaState for Game.lua
    // setup lua libraries
    luaL_openlibs( mLuaState );

    // register all C++ --> lua functions
    lua_pushcfunction( mLuaState, luaGetBackgroundColor );
    lua_setglobal( mLuaState, "app_getBackgroundColor" );
    lua_pushcfunction( mLuaState, luaSetBackgroundColor );
    lua_setglobal( mLuaState, "app_setBackgroundColor" );

    lua_pushcfunction( mLuaState, luaCloseWindow );
    lua_setglobal( mLuaState, "app_closeWindow" );

    // register all engine components to lua
    lua_pushcfunction( mLuaState, SystemMan::luaRegister );
    lua_setglobal( mLuaState, "register_system" );

    lua_pushcfunction( mLuaState, GraphicsMan::luaRegisterGraphicsMan );
    lua_setglobal( mLuaState, "register_graphics" );
    lua_pushcfunction( mLuaState, SystemMan::Events::luaRegister );
    lua_setglobal( mLuaState, "register_events" );
    lua_pushcfunction( mLuaState, CollisionMan::luaRegister );
    lua_setglobal( mLuaState, "register_collision" );
    lua_pushcfunction( mLuaState, CameraMan::luaRegister );
    lua_setglobal( mLuaState, "register_camera" );

    lua_pushcfunction( mLuaState, Ai::Movement::luaRegister );
    lua_setglobal( mLuaState, "register_ai" );


    // register global variables to lua for ease of use
    lua_pushnumber( mLuaState, Window->getSize().x );
    lua_setglobal( mLuaState, "_SCREEN_WIDTH" );
    lua_pushnumber( mLuaState, Window->getSize().y );
    lua_setglobal( mLuaState, "_SCREEN_HEIGHT" );
}

//## Lua Interface methods
int Application::luaGetBackgroundColor( lua_State* luaState ) {
    lua_pushnumber( luaState, mBackgroundColor.r );
    lua_pushnumber( luaState, mBackgroundColor.g );
    lua_pushnumber( luaState, mBackgroundColor.b );
    return 3;
}
int Application::luaSetBackgroundColor( lua_State* luaState ) {
    // make sure values on stack are valid
    // should be red, green , blue values..
    for( unsigned int i = 1; i < 4; ++i )
        if( !lua_isnumber( luaState, i ) ) assert( "You didn't pass correct args to setBackgroundColor!" == std::string() );

    mBackgroundColor = sf::Color( lua_tointeger( luaState, 1 ), lua_tointeger( luaState, 2 ), lua_tointeger( luaState, 3 )  );
    return 0;
}

int Application::luaCloseWindow( lua_State* )
{
    Window->close( );
}
