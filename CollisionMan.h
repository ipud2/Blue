#ifndef COLLISIONMAN
#define COLLISIONMAN
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
extern "C" {
    #include <lua.hpp>
}
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "SystemMan.h"
namespace CollisionMan {
    struct Obj {
        std::string id;
        sf::Rect<float> rect;
        //## Constructors
        Obj( void ) : id( "NO_ID" ), rect( sf::Rect<float>( ) ) { }
        Obj( std::string id, sf::Rect<float> boundingRect )
            : id( id ), rect( boundingRect ) { }
    };
    /// \brief objRects
    /// static member that gets built each frame by lua so that all its nodes can
    /// be checked for collision at the end of the check this dataStructure is wiped for the next
    /// frame where lua will do it again.
    static std::map<std::string, std::vector<Obj>> objRects = std::map<std::string, std::vector<CollisionMan::Obj>>();
    /// \brief The node struct
    /// the node represents a quadrant in the quad tree
    struct Node {
        Node* NE;
        Node* NW;
        Node* SE;
        Node* SW;
        Node* parent;
        std::vector<Obj> localObjs;
        sf::Rect<float> rect;
        sf::RectangleShape debugRect;
        float depth; // depth from the root of the stucture
        bool hasKids; // flag to tell if the node has been split yet or not
        const unsigned int MAX_DEPTH = 5; // the max depth a node can be before the tree ends
        const unsigned int MAX_LOCAL_OBJS = 1; // the max number of objs a node cn carry before it must be split.
        //## Constructor
        Node( Node* parent, float x, float y, float width, float height, float depth );
        ~Node( void );
        //## Interface
        /// \brief addObj
        /// Adds a obj to this node, or it's children if any and if they fit inside there boundries
        ///  \param obj
        bool addObj( Obj obj );
        /// \brief split
        /// Splits the node into 4 new smaller nodes
        /// Method gets called when the node is carrying to many objs
        void split( void );
        void getPairs( std::vector<std::pair<Obj, Obj>>& pairs );
        /// \brief clear
        /// This method is meant to be called by the root node to clear the entire
        /// tree it can of course also be called by any node to clear all objs and
        /// childern before it.
        void clear( void );
        /// \brief draw
        /// Temp Method debug only
        ///  \param mWindow
        ///
        void draw( sf::RenderWindow* mWindow ) {
            if( this->hasKids ) {
                NW->draw( mWindow );
                NE->draw( mWindow );
                SW->draw( mWindow );
                SE->draw( mWindow );
            }
            else mWindow->draw( debugRect );
        }
    };
    /// \brief The QuadTree class
    /// QuadTree designed to make collision detection as fast as possible
    /// by sending only the most likely objs to be colliding is does this
    /// by dividing sections of the screen with two or more objs until  it cant be
    /// divided anymore then passing the objs still in the same section to be checked for
    /// collision against each other
    class QuadTree {
    public:
        QuadTree( float x, float y, float width, float height );
        ~QuadTree( void );
        //## Interface
        std::vector<std::pair<std::string, std::string>> update( std::vector<Obj> &objRects );
        void setRootRect( float x, float y, float width, float height );
        Node* root;
    private:
        //## Attributes
        Node* current;
    };
    static QuadTree QUAD_TREE( -100, -100, 1000, 800 );
    /// \brief draw
    /// This is a temp method meant to draw the boundries of all the nodes in the QuadTree
    /// This is for debug only and will be removed
    ///  \param mWindow
    void draw( sf::Window* mWindow );

    //## Lua interface to CollisionMan
    static int luaCreateCollisionGrid( lua_State* luaState );
    static int luaAddObj( lua_State* luaState );
    /// \brief update
    /// Updates the current list of rectangles to be used in algorithm, then runs
    /// the collisoin algorithm afterwards sending event messages telling of any
    /// events that occured.
    static void update(void );
    static int luaRegister( lua_State* luaState );
}
#include "CollisionMan.inl"
#endif // COLLISIONMAN

