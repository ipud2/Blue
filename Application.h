/*
 * This class is the main starting point to the Blue Engine. It is the main controller
 * class of the entire application.
 * Author: Anthony Divitto
*/
#ifndef APPLICATION_H
#define APPLICATION_H
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
extern "C" {
    #include <lua.hpp>
}
#include "GraphicsMan.h"
#include "SystemMan.h"
#include "CollisionMan.h"
#include "Window.h"
#include "CameraMan.h"
#include "Ai.h"

static const sf::Time TimePerFrame = sf::seconds( 1.f / 60.f );
static sf::Color mBackgroundColor;


class Application {
public:
    Application( void );
    ~Application( void );
    //## Interface
    /// \brief run
    /// Starts the entire program. runs all init methods and houses the main update
    /// loop, which handles events and drawing frame by frame as well as game logic
    void run( void );
    /// \brief init
    /// Calls config.lua to setup basic program attributes then sets luaState
    /// to Game.lua
    void init( void );
    /// \brief update
    /// Calls the main update method in lua
    /// \param dt
    /// the deltaTime spent since the last update
    void update( sf::Time dt );
    /// \brief handleEvents
    /// Handle events such as screen closes, will soon also handle input events!
    void handleEvents( void );
    /// \brief draw
    /// handle all drawing.
    void draw( void );
    sf::Color getBackgroundColor( void ) { return mBackgroundColor; }
    void setBackgroundColor( sf::Color bgColor ) { mBackgroundColor = bgColor; }
private:
    //## Attributes
    lua_State* mLuaState;
    //## Behaviors
    // calls and run gets values from config.lua
    void runConfig( void );
    // sets up libraries and global scope variables for the lua environment
    void setUpBlueEnvironment( void );
    //## Lua Interface methods
    static int luaGetBackgroundColor( lua_State* luaState );
    static int luaSetBackgroundColor( lua_State* luaState );
    static int luaCloseWindow( lua_State* luaState );
};
#endif // APPLICATION_H
