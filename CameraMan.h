#ifndef CAMERAMAN_H
#define CAMERAMAN_H

#include <map>
#include <assert.h>
#include <SFML/Graphics.hpp>


///
/// The Camera Manager wraps sf::view and sf::viewPort to lua and provides a map of cameras that
/// lua can control for single, multiplayer, mini maps, UI or whatever else you might want a seperate view of the world for
///
namespace CameraMan {
    static std::map<std::string, sf::View> cameras;

    /// \brief luaSetSize
    /// \param luaState
    ///LUA STACK
    /// 3 height -1
    /// 2 width  -2
    /// 1 id     -3
    static int luaSetSize( lua_State* luaState );
    /// \brief luaSetRotation
    /// \param luaState
    /// LUA STACK
    /// 2 Angle -1
    /// 1 id    -2
    static int luaSetRotation( lua_State* luaState );
    /// \brief luaSetCenter
    /// \param luaState
    /// LUA STACK
    /// 3 y  -1
    /// 2 x  -2
    /// 1 id -3
    static int luaSetCenter( lua_State* luaState );
    /// \brief luaSetVeiwPort
    /// \param luaState
    /// LUA STACK
    /// 5 height -1
    /// 4 width  -2
    /// 3   y    -3
    /// 2   x    -4
    /// 1  id    -5
    static int luaSetViewPort( lua_State* luaState );
    /// \brief luaReset
    /// \param luaState
    /// LUA STACK
    /// 5 hegiht -1
    /// 4  width -2
    /// 3   y    -3
    /// 2   x    -4
    /// 1  id    -5
    static int luaReset( lua_State* luaState );
    /// \brief luaMove
    /// \param luaState
    /// LUA STACK
    /// 3 y  -1
    /// 2 x  -2
    /// 1 id -3
    static int luaMove( lua_State* luaState );
    /// \brief luaCreateView
    /// \param luaState
    /// LUA STACK
    /// 5 height -1
    /// 4 width  -2
    /// 3   y    -3
    /// 2   x    -4
    /// 1  id    -5
    static int luaCreateView( lua_State* luaState );
    /// LUA STACK
    /// 1 id -1
    static int luaRemoveView( lua_State* luaState );
    /// \brief luaRotate
    /// \param luaState
    /// LUA STACK
    /// 2 angle -1
    /// 1  id   -2
    static int luaRotate( lua_State* luaState );
    /// \brief luaZoom
    /// \param luaState
    /// LUA STACK
    /// 2 factor -1
    /// 1 id     -2
    static int luaZoom( lua_State* luaState );


    static int luaRegister( lua_State* luaState );
}
#include "CameraMan.inl"

#endif // CAMERAMAN_H
