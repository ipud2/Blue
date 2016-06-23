#include "CameraMan.h"

/// \brief luaSetSize
/// \param luaState
///LUA STACK
/// 3 height -1
/// 2 width  -2
/// 1 id     -3
int CameraMan::luaSetSize( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid Camera id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid width" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid Height" == std::string() );

    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) )
    {
        cameras.at( lua_tostring( luaState, 1 ) ).setSize( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );

    }else std::cout << "No Camera by that id!" << std::endl;
    return 0;
}

/// \brief luaSetRotation
/// \param luaState
/// LUA STACK
/// 2 Angle -1
/// 1 id    -2
int CameraMan::luaSetRotation( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid angle" == std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) )
    {
        cameras.at( lua_tostring( luaState, 1 ) ).setRotation( (float)lua_tonumber( luaState, 2 ) );

    }else std::cout << "No Camera by that id!" << std::endl;

    return 0;
}

/// \brief luaSetCenter
/// \param luaState
/// LUA STACK
/// 3 y  -1
/// 2 x  -2
/// 1 id -3
int CameraMan::luaSetCenter( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid x" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid y" == std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) )
    {
        cameras.at( lua_tostring( luaState, 1 ) ).setCenter( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );

    }else std::cout << "No Camera by that id!" << std::endl;

    return 0;
}

/// \brief luaSetVeiwPort
/// \param luaState
/// LUA STACK
/// 5 height -1
/// 4 width  -2
/// 3   y    -3
/// 2   x    -4
/// 1  id    -5
int CameraMan::luaSetViewPort( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid x" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid y" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "invalid width" == std::string( ) );
    if( !lua_isnumber( luaState, 5 ) ) assert( "invalid height" ==std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) )
    {
        cameras.at( lua_tostring( luaState, 1 ) ).setViewport( sf::Rect<float>( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ), (float)lua_tonumber( luaState, 4 ), (float)lua_tonumber( luaState, 5 ) ) );

    }else std::cout << "No Camera by that id!" << std::endl;
    return 0;
}

/// \brief luaReset
/// \param luaState
/// LUA STACK
/// 5 hegiht -1
/// 4  width -2
/// 3   y    -3
/// 2   x    -4
/// 1  id    -5
int CameraMan::luaReset( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid x" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid y" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "invalid width" == std::string( ) );
    if( !lua_isnumber( luaState, 5 ) ) assert( "invalid height" ==std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) )
    {
        cameras.at( lua_tostring( luaState, 1 ) ).reset( sf::Rect<float>( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ), (float)lua_tonumber( luaState, 4 ), (float)lua_tonumber( luaState, 5 ) ) );
    }else std::cout << "No Camera by that id!" << std::endl;
    return 0;
}

/// \brief luaMove
/// \param luaState
/// LUA STACK
/// 3 y  -1
/// 2 x  -2
/// 1 id -3
int CameraMan::luaMove( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid x" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid y" == std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) )
    {
        cameras.at( lua_tostring( luaState, 1 ) ).move( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );

    }else std::cout << "No Camera by that id!" << std::endl;

    return 0;
}

/// \brief luaCreateView
/// \param luaState
/// LUA STACK
/// 5 height -1
/// 4 width  -2
/// 3   y    -3
/// 2   x    -4
/// 1  id    -5
int CameraMan::luaCreateView( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid x" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid y" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "invalid width" == std::string( ) );
    if( !lua_isnumber( luaState, 5 ) ) assert( "invalid height" ==std::string( ) );

    if( cameras.find( lua_tostring( luaState, 1 ) ) == cameras.end( ) )
        cameras.insert( std::pair<std::string, sf::View>( lua_tostring( luaState, 1 ), sf::View(
                                                              sf::Vector2f( (float)lua_tonumber( luaState, 2 ),
                                                                            (float)lua_tonumber( luaState, 3 ) ),
                                                              sf::Vector2f( (float)lua_tonumber( luaState, 4 ),
                                                                            (float)lua_tonumber( luaState, 5 ) ) ) ) );
    else std::cout << "There is already a camera with that ID! Can not create." << std::endl;
    // push the id
    lua_pushstring( luaState, lua_tostring( luaState, 1 ) );
    return 1;
}

/// Lua Stack
/// 1 id -1
int CameraMan::luaRemoveView( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalied camera id" == std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end() ) {
        cameras.erase( lua_tostring( luaState, 1 ) );
    } else std::cout << "You passed the wrong id to remove camera" << std::endl;
    return 0;
}

/// \brief luaSetRotation
/// \param luaState
/// LUA STACK
/// 2 angle -1
/// 1  id   -2
int CameraMan::luaRotate( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid angle" == std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) ) cameras.at( lua_tostring( luaState, 1 ) ).rotate( (float)lua_tonumber( luaState, 2 ) );
    else std::cout << "No Camera by that id!" << std::endl;
    return 0;
}
/// \brief luaZoom
/// \param luaState
/// LUA STACK
/// 2 factor -1
/// 1 id     -2
int CameraMan::luaZoom( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid factor" == std::string( ) );
    if( cameras.find( lua_tostring( luaState, 1 ) ) != cameras.end( ) ) cameras.at( lua_tostring( luaState, 1 ) ).zoom( (float)lua_tonumber( luaState, 2 ) );
    else std::cout << "No Camera by that id!" << std::endl;
    return 0;
}

int CameraMan::luaRegister( lua_State* luaState )
{
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, CameraMan::luaSetSize );
        lua_setglobal( luaState, "camera_setSize" );
        lua_pushcfunction( luaState, CameraMan::luaSetRotation );
        lua_setglobal( luaState, "camera_setRotation" );
        lua_pushcfunction( luaState, CameraMan::luaSetCenter );
        lua_setglobal( luaState, "camera_setCenter" );
        lua_pushcfunction( luaState, CameraMan::luaSetViewPort );
        lua_setglobal( luaState, "camera_setViewport" );
        lua_pushcfunction( luaState, CameraMan::luaMove );
        lua_setglobal( luaState, "camera_move" );
        lua_pushcfunction( luaState, CameraMan::luaRotate );
        lua_setglobal( luaState, "camera_rotate" );
        lua_pushcfunction( luaState, CameraMan::luaZoom );
        lua_setglobal( luaState, "camera_zoom" );
        lua_pushcfunction( luaState, CameraMan::luaCreateView );
        lua_setglobal( luaState, "create_camera" );
        lua_pushcfunction( luaState, CameraMan::luaRemoveView );
        lua_setglobal( luaState, "remove_camera" );
        alreadyRegistered = true;
    }
    return 0;
}
