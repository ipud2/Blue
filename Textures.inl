#include "GraphicsMan.h"
/// \brief luaLoadFromFile
/// \param luaState
/// STACK
/// 2 fileName -1
/// 1 ID       -2
int GraphicsMan::Textures::luaLoadFromFile( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isstring( luaState, 2 ) ) assert( "You passed invalid fileName" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );
    textures.insert( std::pair<std::string, sf::Texture*>( id, new sf::Texture( ) ) );
    textures.at( id )->loadFromFile( lua_tostring( luaState, 2 ) );
    // return id
    lua_pushstring( luaState, id.c_str( ) );
    return 1;
}
/// \brief luaRemoveTexture
/// \param luaState
/// STACK
/// 1 ID -1
int GraphicsMan::Textures::luaRemoveTexture( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalid id" == std::string( ) );
    if( textures.find( lua_tostring( luaState, 1 ) ) != textures.end( ) ) textures.erase( lua_tostring( luaState, 1 ) );
    return 0;
}
/// \brief luaSetIsSmooth
/// \param luaState
/// STACK
/// 2 isSmooth -1
/// 1 ID       -2
int GraphicsMan::Textures::luaSetIsSmooth( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isboolean( luaState, 2 ) ) assert( "You passed invalid isSmooth boolean" == std::string( ) );
    textures.at( lua_tostring( luaState, 1 ) )->setSmooth( (bool)lua_toboolean( luaState, 2 ) );
    return 0;
}
/// \brief luaSetIsRepeated
/// \param luaState
/// 2 isRepeated -1
/// 1 ID         -2
int GraphicsMan::Textures::luaSetIsRepeated( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isboolean( luaState, 2 ) ) assert( "You passed invalid isRepeated boolean" == std::string( ) );
    textures.at( lua_tostring( luaState, 1 ) )->setRepeated( (bool)lua_toboolean( luaState, 2 ) );
    return 0;
}
/// \brief luaRegister
/// register all Texture Methods to lua
/// \param luaState
int GraphicsMan::Textures::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, luaLoadFromFile );
        lua_setglobal( luaState, "texture_loadFromFile" );
        lua_pushcfunction( luaState, luaRemoveTexture );
        lua_setglobal( luaState, "remove_texture" );
        lua_pushcfunction( luaState, luaSetIsSmooth );
        lua_setglobal( luaState, "texture_setIsSmooth" );
        lua_pushcfunction( luaState, luaSetIsRepeated );
        lua_setglobal( luaState, "texture_setIsRepeated" );
        alreadyRegistered = true;
    }
    return 0;
}
