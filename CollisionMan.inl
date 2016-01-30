#include "CollisionMan.h"


//## Lua interface to CollisionMan
int CollisionMan::luaAddObj( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) { assert( "You udid not pass a valid id to the collision Manager" ); }
    if( !lua_isnumber( luaState, 2 ) ) { assert( "You did not pass a valid x position of rectangle to colliosion Manager" ); }
    if( !lua_isnumber( luaState, 3 ) ) { assert( "You did not pass a valid y position of rectangle to colliosion Manager" ); }
    if( !lua_isnumber( luaState, 4 ) ) { assert( "You did not pass a valid w position of rectangle to colliosion Manager" ); }
    if( !lua_isnumber( luaState, 5 ) ) { assert( "You did not pass a valid h position of rectangle to colliosion Manager" ); }
    std::string id = lua_tostring( luaState, 1 );
    Obj obj = Obj( id.c_str( ), sf::Rect<float>( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ),
                   (float)lua_tonumber( luaState, 4 ), (float)lua_tonumber( luaState, 5 ) ) );
    CollisionMan::objRects.push_back( obj );
    return 0;
}
/// \brief update
/// Updates the current list of rectangles to be used in algorithm, then runs
/// the collisoin algorithm afterwards sending event messages telling of any
/// events that occured.
void CollisionMan::update( lua_State* luaState ) {
    // get the most current collisions and save them to createt events

    QUAD_TREE.root->clear();
    std::vector<std::pair<std::string, std::string>> pairs = QUAD_TREE.update( objRects );
    // loop through all colliding objects and send collision Events
    for( auto p : pairs ) {
        // create event for p.first
        SystemMan::Events::addCustomEvent( SystemMan::Events::Event( "COLLISION", p.second.c_str(), p.first.c_str( ), 0 ) );
        // create event for p.second
        SystemMan::Events::addCustomEvent( SystemMan::Events::Event( "COLLISION", p.first.c_str(), p.second.c_str( ), 0 ) );
       //  std::cout << "Collision Event: " << p.first << " , " << p.second << std::endl;
    }
}
int CollisionMan::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, CollisionMan::luaAddObj );
        lua_setglobal( luaState, "collision_add" );
        alreadyRegistered = true;
    }
    return 0;
}
