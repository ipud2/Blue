#ifndef AI_H
#define AI_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>
#include <map>
#include <math.h>
namespace Ai {

namespace Movement {
    static std::pair<float, float> pursuit( sf::Vector2f targetPos, sf::Vector2f currentPos, float maxVelocity, float currentVelocity, float MaxAcceleration )
    {
        // establish where target pos is relative to currentPos
         if( currentPos.x < targetPos.x )
         {

         }

    }

    static sf::Vector2f seek( sf::Vector2f pos, sf::Vector2f target )
    {
        // do stuff here to make this behave like seek  should
        // need to apply acceleration in a way that sticks from frame to frame
        // need to access lua member and modify values directly so that all values stay in synk.
        // or write a "track pos" method and write all other logic for how the object tracks in lua!!!!!!!!!!!!

        sf::Vector2f heading;
        float bLineDistance = std::sqrt( ((pos.x - target.x)*(pos.x - target.x)) + ((pos.y - target.y)*(pos.y - target.y)) );
        heading.x = ( pos.x - target.x ) / bLineDistance;
        heading.y = ( pos.y - target.y ) / bLineDistance;
        return heading;

/*
        sf::Vector2f newPos;
        float bLineDistance = std::sqrt( ((pos.x - target.x)*(pos.x - target.x)) + ((pos.y - target.y)*(pos.y - target.y)) );
        newPos.x = pos.x - ((( pos.x - target.x ) / bLineDistance) * currentVel);
        newPos.y = pos.y - ((( pos.y - target.y ) / bLineDistance) * currentVel);
        return newPos;
        */
    }


   static int luaSeek( lua_State* luaState ) {
       // test incoming lua values here!! lol
       sf::Vector2f newPos = Ai::Movement::seek( sf::Vector2f( (float)lua_tonumber( luaState, 1 ), (float)lua_tonumber( luaState, 2 ) ),
                                                 sf::Vector2f( (float)lua_tonumber( luaState, 3 ), (float)lua_tonumber( luaState, 4 ) ) );
       lua_pushnumber( luaState, newPos.x );
       lua_pushnumber( luaState, newPos.y );
       return 2;
   }

   // static std::pair<float, float> evade(  );
   // static void setPath( std::vector<sf::vector<float> wayPoints );
   static int luaRegister( lua_State* luaState ) {
       static bool alreadyRegistered = false;
       if( !alreadyRegistered ) {
           lua_pushcfunction( luaState, Ai::Movement::luaSeek );
           lua_setglobal( luaState, "ai_track" );

           alreadyRegistered = true;
       }
       return 0; // returns SYSTEM_EVENTS table

   }

}


}


#endif // AI_H
