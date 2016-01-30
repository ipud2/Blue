#ifndef OBJECTMAN
#define OBJECTMAN

///
///
/// The ObjectMan namespace is incomplete
///
/// Currently the objman vreates its own representation of a lua obj and saves it with the objects
/// id as index to its location.
///
/// the way it should be is to save the actual lua obj methods and all and still have indexable by id
///
///

#include <iostream>
#include <assert.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include <list>
extern "C" {
#include "lua.hpp"
}
namespace ObjectMan{
///
/// \brief The Object class
/// Designed to represent all lua Objects in C++ the only thing this class has is the id of the lua member it represents
    struct Object {
        //## Constructor
        Object( void ) { }
        Object( std::string id ) : id( id ) { }
        //## Interface
        const std::string getId( void ) { return id; }
        //## Attributes
        std::string id;
        std::map<std::string, std::string> attributes;
    };
    /// The main data structure that this namespace manipulates
    /// id, Obj Definition
    static std::map<std::string, Object> gameObjs;
        
    ///
    ///
    /// The Lua Interface to interact with gameObjs
    ///
    ///
    static int luaRemove_Obj( lua_State* luaState ) {
        if( !lua_isstring( luaState, 1 ) ) assert( "You Sent an invalid Object ID" );
        std::string id = lua_tostring( luaState, 1 );
        // validate the id by finding Obj in gameObjs.
        if( gameObjs.find( id ) != gameObjs.end( ) ) {
            gameObjs.erase( id ); std::cout << "Object has been removed: " << id << std::endl;
        }
        else std::cout << "Attempting to remove an Object that doesn't exist: " << id << std::endl;
        return 0;
    }
    static int luaCreate_Obj( lua_State* luaState ) {
        // table is in the stack at index 't'
        if( !lua_istable( luaState, 1 ) ) assert( "No obj passed to the add object method!!" == std::string( ) );

        Object obj = Object( );
        lua_pushnil( luaState );  // first key
        while( lua_next( luaState, 1 ) != 0 ) {
            if( lua_isstring( luaState, -2  ) && lua_isstring( luaState, -1 ) )
                obj.attributes.insert( std::pair<std::string, std::string>( lua_tostring( luaState, -2 ), lua_tostring( luaState, -1 )  ) );
            else assert( "INVALID OBJECT ATTRIBUTE" == std::string( ) );
            // removes 'value'; keeps 'key' for next iteration
            lua_pop( luaState, 1);
        }
        gameObjs.insert( std::pair<std::string, Object>( obj.attributes.at( "id" ).c_str( ), obj ) );

        // return id
        lua_pushstring( luaState, obj.attributes.at( "id" ).c_str( ) );
        return 1;

        /*if( !lua_isstring( luaState, 1 ) ) assert( "You Sent an invalid Object ID" );
        std::string  id = lua_tostring( luaState, 1 );
        if( gameObjs.find( id ) == gameObjs.end( ) ) {
            Object obj( id );
            gameObjs.insert( std::pair<std::string, Object>( obj.getId(), obj ) );
            // std::cout << "Object has been created: " << id << std::endl;
            // return id
            lua_pushstring( luaState, id.c_str( ) );
            return 1;
        }
        return 0;
        */
    }
    static int luaGetObject( lua_State* luaState ) {
        if( !lua_isstring( luaState, 1 ) ) assert( "You Sent an invalid Object ID" );
        std::string  id = lua_tostring( luaState, 1 );
        if( gameObjs.find( id ) != gameObjs.end( ) ) {
            Object obj = gameObjs.at( id );
            lua_createtable( luaState, 0, 0 );
            for( auto i : obj.attributes ) {
                lua_pushstring( luaState, i.second.c_str( ) );
                lua_setfield( luaState, -2, i.first.c_str( ) );
            }
            // return id
            return 1;
        }
        lua_pushnil( luaState );
        return 1;
    }

    static int luaRegister( lua_State* luaState ) {
        lua_pushcfunction( luaState, luaRemove_Obj );
        lua_setglobal( luaState, "remove_obj" );
        lua_pushcfunction( luaState, luaCreate_Obj );
        lua_setglobal( luaState, "create_obj" );
        lua_pushcfunction( luaState, luaGetObject );
        lua_setglobal( luaState, "get_obj" );
        return 0;
    }
}


#endif // OBJECTMAN

