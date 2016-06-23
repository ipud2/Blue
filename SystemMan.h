#ifndef SYSTEMMAN
#define SYSTEMMAN

#include <string>
#include <assert.h>
#include <iostream>

#include <vector>
#include <queue>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

extern "C" {
#include "lua.hpp"
}
#include "Window.h"

/*
 * The SystemMan is responsible for alowwing lua to access what is happening on the machine it is running on
 * it will include getting keyboard and mouse states (input) and facilitate passing system events to lua
 */
namespace SystemMan
{
    /*
     * reistering events will allow the lua file to get the currentList of systemEvents
     * by calling a simple method this method will also clear tbe current systemEvents list
     * ofcourse, Events also managers the currentEvent list
     *
     */
    namespace Events
    {
        struct Event {
            //## Attributes
            std::map<std::string, std::string> attributes;
            unsigned int delay;

            Event( void ) { }
            Event( std::string name, std::string receiverID, std::string senderID, unsigned int delay = 0 )
            {
                attributes.insert( std::pair<std::string, std::string>( "name", name.c_str( ) ) );
                attributes.insert( std::pair<std::string, std::string>( "receiverID", receiverID.c_str( ) ) );
                attributes.insert( std::pair<std::string, std::string>( "senderID", senderID.c_str( ) ) );
                this->delay = delay;
            }
        };
        static std::queue<Event> currentEvents;
        static std::vector<Event> delayedEvents;

        static void update( void );

        ///
        /// \brief addEvent
        /// This method is designed to add system (SFML) events to the queue
        static void addEvent( sf::Event event );
        ///
        /// \brief addEvent
        /// This method is to add custom game events to the event queue
        static void addCustomEvent( SystemMan::Events::Event event );
        /// \brief luaAddEvent
        /// This method allows lua to add events to the the event queue
        ///  \param luaState
        /// STACK
        /// 4 delay       -1
        /// 3 senderID    -2
        /// 2 receiverID  -3
        /// 1 name        -4
        static int luaAddEvent( lua_State* luaState );
        /// \brief luaGetEvent
        /// Pulls the next event off the current event queue and returns it to lua
        /// \return
        /// Returns an event
        static int luaGetEvent( lua_State* luaState );
        /// \brief luaRegister
        /// Registers the Event system to lua
        static int luaRegister( lua_State* luaState );
    }

    namespace Input
    {
        static int luaIsKeyPressed( lua_State* luaState );
        static int luaIsMouseClicked( lua_State* luaState );
        static int luaGetMousePosition( lua_State* luaState );
        static int luaRegister( lua_State* luaState );
    }
    static int luaRegister( lua_State* luaState );
}

#include "SystemMan.inl"
#endif // SYSTEMMAN
