#ifndef LUAMAN
#define LUAMAN

extern "C" {
    #include <lua.hpp>
}

namespace LuaMan {

// The current lua state used by the entire engine there can only be one lua state per game.
static lua_State* state;

///
/// This namespace may someday be populated with methods to help make lua easier
/// as well as methods to return the state to  a pre-saved point in history
///
///

}


#endif // LUAMAN

