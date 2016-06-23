#include "CollisionMan.h"


//## Lua interface to CollisionMan
//## Lua interface to CollisionMan
///
/// \brief lua_createtable
/// \param luaState
/// LUA STACK
/// 5 h         -1
/// 4 w         -2
/// 3 y         -3
/// 2 x         -4
/// 1 layerId   -5
/// \return
///
int CollisionMan::luaCreateCollisionGrid( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) { assert( "You did not pass a valid layerId" == std::string( ) ); }
    std::string id = lua_tostring( luaState, 1 );
    // make sure the layer does not already exist in the collision manager
    if( objRects.find( id.c_str( ) ) == objRects.end( ) ) {
        objRects.insert( std::pair<std::string, std::vector<Obj>>( id.c_str( ), std::vector<Obj>( ) ) );
    }else {
        assert( "You can't add duplicate layers" == std::string( ) );
    }

    // return the layer id to lua
    lua_pushstring( luaState, id.c_str( ) );
    return 1;
}

int CollisionMan::luaAddObj( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) { assert( "You did not pass a valid id to the collision Manager" == std::string( ) ); }
    if( !lua_isstring( luaState, 2 ) ) { assert( "You did not pass a valid layerId" == std::string( ) ); }
    if( !lua_isnumber( luaState, 3 ) ) { assert( "You did not pass a valid x position of rectangle to collision Manager" == std::string( ) ); }
    if( !lua_isnumber( luaState, 4 ) ) { assert( "You did not pass a valid y position of rectangle to collision Manager" == std::string( ) ); }
    if( !lua_isnumber( luaState, 5 ) ) { assert( "You did not pass a valid w position of rectangle to collision Manager" == std::string( ) ); }
    if( !lua_isnumber( luaState, 6 ) ) { assert( "You did not pass a valid h position of rectangle to collision Manager" == std::string( ) ); }
    std::string id = lua_tostring( luaState, 1 );
    std::string layerId = lua_tostring( luaState, 2 );

    if( objRects.find( layerId ) != objRects.end( ) ) {
        bool flag = false;
        // for loop protects against adding duplicate objects to the collision algorithm
        for( auto o : objRects.at( layerId ) ) { if( o.id == id ) { flag = true; break; } }
        if( !flag ) objRects.at( layerId ).push_back(  Obj( id.c_str( ), sf::Rect<float>( (float)lua_tonumber( luaState, 3 ),
                                                                                 (float)lua_tonumber( luaState, 4 ),
                                                                                 (float)lua_tonumber( luaState, 5 ),
                                                                                 (float)lua_tonumber( luaState, 6 ) ) ) );
    }
    else assert( "You passed an invalid collision layer id!!" == std::string( ) );
    return 0;
}
/// \brief update
/// Updates the current list of rectangles to be used in algorithm, then runs
/// the collisoin algorithm afterwards sending event messages telling of any
/// events that occured.
void CollisionMan::update( void ) {
    // get the most current collisions and save them to createt events
    for( auto layer : objRects ) {
        QUAD_TREE.root->clear();
        std::vector<std::pair<std::string, std::string>> pairs = QUAD_TREE.update( objRects.at( layer.first ) );
        // loop through all colliding objects and send collision Events
        for( auto p : pairs ) {
            // create event for p.first
            SystemMan::Events::addCustomEvent( SystemMan::Events::Event( "COLLISION", p.second.c_str(), p.first.c_str( ), 0 ) );
            // create event for p.second
            SystemMan::Events::addCustomEvent( SystemMan::Events::Event( "COLLISION", p.first.c_str(), p.second.c_str( ), 0 ) );
        }
    }
}
int CollisionMan::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, CollisionMan::luaCreateCollisionGrid );
        lua_setglobal( luaState, "create_collisionGrid" );
        lua_pushcfunction( luaState, CollisionMan::luaAddObj );
        lua_setglobal( luaState, "collision_add" );
        alreadyRegistered = true;
    }
    return 0;
}
