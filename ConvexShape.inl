#include "GraphicsMan.h"


// transform interface

/// \brief luaGetInverseTransform
/// \param luaState
/// \return
/// returns a 4X4 matrix
int GraphicsMan::ConvexShape::luaGetInverseTransform( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    // run method
    const float* matrix = convexShapes.at( id )->getInverseTransform().getMatrix();
    // 16 becuase it's a 4x4 matrix DUH!! read the header comments!
    for( unsigned int i = 0; i < 16; ++i ) { lua_pushnumber( luaState, matrix[i] ); }
    delete matrix;
    return 16;
}
/// \brief luaGetTransform
/// \param luaState
/// \return
/// returns a 4X4 matrix combining pos, rotation, scale, origin of asset
int GraphicsMan::ConvexShape::luaGetTransform( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    // run method
    const float* matrix = convexShapes.at( id )->getTransform().getMatrix();
    // 16 becuase it's a 4x4 matrix DUH!! read the header comments!
    for( unsigned int i = 0; i < 16; ++i ) { lua_pushnumber( luaState, matrix[i] ); }
    return 16;
}
/// \brief luaSetOrigin
/// The defualt origon for all objects is 0,0 (top-left corner)
/// \param luaState
/// \param X, Y
/// The Cordinates for the new origin
int GraphicsMan::ConvexShape::luaSetOrigin( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );
    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid xOrigin parameter sent to convexShape_setOrigin" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid yOrigin parameter sent to convexShape_setOrigin" == std::string( ) );
    convexShapes.at( id )->setOrigin( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );
    return 0;
}
/// \brief luaSetPosition
/// \param luaState
/// \param X, Y
/// The new Position
/// The ID of the shape or sprite being manipulated
int GraphicsMan::ConvexShape::luaSetPosition( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_setPos" == std::string( ) );

    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid xPos parameter sent to convexShape_setPosition" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid yPos parameter sent to convexShape_setPosition" == std::string( ) );

    convexShapes.at( id )->setPosition( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );
    return 0;
}
/// \brief luaSetRotation
/// \param luaState
/// \param angle
/// The new Angle about the origin. Range: 0 - 360
int GraphicsMan::ConvexShape::luaSetRotation( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_setRotation" == std::string( ) );

    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid angle parameter sent to convexShape_setRotation" == std::string( ) );

    convexShapes.at( id )->setRotation( (float)lua_tonumber( luaState, 2 ) );
    return 0;
}
/// \brief luaSetScale
/// \param luaState
/// \param X, Y
/// The new Scale factors for the asset
int GraphicsMan::ConvexShape::luaSetScale( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    // if( convexShapes.find( id ) == rectShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid scale parameter sent to convexShape_setScale" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid scale parameter sent to convexShape_setScale" == std::string( ) );

    convexShapes.at( id )->setScale( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );
    return 0;
}
/// Shape interface

/// \brief luaGetGlobalBounds
/// Returns rect in terms of global coords (Whole screen)
/// This is oppossed to getting local bounds which returns a rect relative to the
/// shape's origin
/// \param luaState
/// \graphicsAssetId
/// \return
/// returns X, Y, Width, Height of rectangle
int GraphicsMan::ConvexShape::luaGetGlobalBounds( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to cicleShape_getInverseTransform" == std::string( ) );

    sf::Rect<float> rect = convexShapes.at( id )->getGlobalBounds();
    lua_pushnumber( luaState, rect.left );
    lua_pushnumber( luaState, rect.top );
    lua_pushnumber( luaState, rect.width );
    lua_pushnumber( luaState, rect.height );
    return 4;
}
/// \brief luaGetLocalBounds
/// Returns rect in terms of local coords
/// This is oppossed to getting global bounds which returns a rect relative to the
/// entire world, this returns a rect based on the Asset's coords
/// \param luaState
/// \graphicsAssetId
/// \return
/// returns X, Y, Width, Height of rectangle
int GraphicsMan::ConvexShape::luaGetLocalBounds( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( cicleShapes.find( id ) == cicleShapes.end( ) ) assert( "You sent invalid id to cicleShape_getInverseTransform" == std::string( ) );

    sf::Rect<float> rect = convexShapes.at( id )->getLocalBounds();
    lua_pushnumber( luaState, rect.top );
    lua_pushnumber( luaState, rect.left );
    lua_pushnumber( luaState, rect.width );
    lua_pushnumber( luaState, rect.height );
    return 4;
}
/// \brief luaSetFillColor
/// \param luaState
/// \param graphicAssetId
/// \param Red, green, blue, alpha values of a color
int GraphicsMan::ConvexShape::luaSetFillColor( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( cicleShapes.find( id ) == cicleShapes.end( ) ) assert( "You sent invalid id to cicleShape_getInverseTransform" == std::string( ) );

    // validate other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid r value" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "Invalid g value" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "Invalid b value" == std::string( ) );
    if( !lua_isnumber( luaState, 5 ) ) assert( "Invalid a value" == std::string( ) );
    convexShapes.at( id )->setFillColor( sf::Color( (float)lua_tonumber( luaState, 2 ),
                                           (float)lua_tonumber( luaState, 3 ),
                                           (float)lua_tonumber( luaState, 4 ),
                                           (float)lua_tonumber( luaState, 5 ) ) );
    return 0;
}
/// \brief luaSetOutlineColor
/// \param luaState
/// \param graphicAssetId
/// \param Red, green, blue, alpha value of color
int GraphicsMan::ConvexShape::luaSetOutlineColor( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( cicleShapes.find( id ) == cicleShapes.end( ) ) assert( "You sent invalid id to cicleShape_getInverseTransform" == std::string( ) );

    // validate other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid red value" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "Invalid green value" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "Invalid blue value" == std::string( ) );
    if( !lua_isnumber( luaState, 5 ) ) assert( "Invalid alpha value" == std::string( ) );
    convexShapes.at( id )->setOutlineColor( sf::Color( (float)lua_tonumber( luaState, 2 ),
                                           (float)lua_tonumber( luaState, 3 ),
                                           (float)lua_tonumber( luaState, 4 ),
                                           (float)lua_tonumber( luaState, 5 ) ) );
    return 0;
}
/// \brief luaSetOutlineThickness
/// \param luaState
/// \param graphicAssetId
/// \param thickness
int GraphicsMan::ConvexShape::luaSetOutlineThickness( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    // validate outlineThickness
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid thickness value" == std::string( ) );

    convexShapes.at( id )->setOutlineThickness( lua_tonumber( luaState, 2 ) );
    return 0;
}
/// \brief luaSetTexture
/// \param luaState
/// \param graphicAssetId
/// \param TextureId, bool resetRect
int GraphicsMan::ConvexShape::luaSetTexture( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
   // if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    // validate texId
    if( !lua_isstring( luaState, 2 ) ) assert( "Invalid TextureId value" == std::string( ) );
    // validate reset flag
    if( !lua_isboolean( luaState, 3 ) ) assert( "You forgot to set resetRect flag!" == std::string( ) );

    convexShapes.at( id )->setTexture( GraphicsMan::Textures::textures.at( lua_tostring( luaState, 2 ) ), (bool)lua_toboolean( luaState, 3 ) );
    return 0;
}
/// \brief luaSetTextureRect
/// set the rect that represents where on the loaded texture you want to draw
/// \param luaState
/// \param graphicAssetId
/// \param X, Y, Width, Height of rect
int GraphicsMan::ConvexShape::luaSetTextureRect( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_setTextureRect" == std::string( ) );

    // validate other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid X value" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "Invalid Y value" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "Invalid Width value" == std::string( ) );
    if( !lua_isnumber( luaState, 5 ) ) assert( "Invalid Height value" == std::string( ) );
    convexShapes.at( id )->setTextureRect( sf::Rect<int>( (int)lua_tonumber( luaState, 2 ),
                                           (int)lua_tonumber( luaState, 3 ),
                                           (int)lua_tonumber( luaState, 4 ),
                                           (int)lua_tonumber( luaState, 5 ) ) );
    return 0;
}
// The sf::ConvexShape Interface

/// \brief luaGetPoint
/// inherited from sf::Shape returns exact points as they are defined
/// in the data structure that makes up a texture.
/// \param luaState
/// \param graphicAssetId
/// \param index
/// the index of the point you want returned
/// \return
/// returns X, Y of point requested
int GraphicsMan::ConvexShape::luaGetPoint( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    // if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );
    // validate index
    if( !lua_isnumber( luaState, 2 ) ) assert( "You passed invalid index" == std::string( ) );

    sf::ConvexShape* convex = convexShapes.at( id );
    unsigned int index = (unsigned int)lua_tonumber( luaState, 2 );
    lua_pushnumber( luaState, convex->getPoint( index ).x );
    lua_pushnumber( luaState, convex->getPoint( index ).y );

    delete convex;
    return 2;
}
/// \brief luaGetPointCount
/// \param luaState
/// \param graphicAssetId
///  \return
/// returns
/// the number of points that make up a shape as unsigned int
int GraphicsMan::ConvexShape::luaGetPointCount( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    lua_pushnumber( luaState, convexShapes.at(id)->getPointCount( ) );
    return 1;
}
/// \brief luaSetPoint
/// \param luaState
/// STACK
/// 4 Y     -1
/// 3 X     -2
/// 2 index -3
/// 1 ID    -4
int GraphicsMan::ConvexShape::luaSetPoint( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );
    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    if( !lua_isnumber( luaState, 2 ) ) assert( "You passed invalid index" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "You passed invalid X" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "You passed invalid Y" == std::string( ) );

    convexShapes.at( id )->setPoint( (int)lua_tonumber( luaState, 2 ), sf::Vector2f( (float)lua_tonumber( luaState, 3 ), (float)lua_tonumber( luaState, 4 ) ) );
    return 0;
}
/// \brief luaSetPointCount
/// \param luaState
/// STACK
/// 2 pointCount -1
/// 1 ID         -2
int GraphicsMan::ConvexShape::luaSetPointCount( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );
    // validate obj exists
    //if( convexShapes.find( id ) == convexShapes.end( ) ) assert( "You sent invalid id to convexShape_getInverseTransform" == std::string( ) );

    if( !lua_isnumber( luaState, 2 ) ) assert( "You passed pointCount index" == std::string( ) );


    convexShapes.at( id )->setPointCount( (int)lua_tonumber( luaState, 2 ) );
    return 0;
}
/// \brief GraphicsMan::ConvexShape::luaCreateConvexShape
/// \param luaState
/// STACK
/// 8 A             -1
/// 7 B             -2
/// 6 G             -3
/// 5 R             -4
/// 4 pointCount    -5
/// 3 Y             -6
/// 2 X             -7
/// 1 ID            -8
///  \return
/// the ID passed by the user
int GraphicsMan::ConvexShape::luaCreateConvexShape( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalid id" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid X value" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "Invalid Y value" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "Invalid PointCount value" == std::string( ) );
    if( !lua_isnumber( luaState, 5 ) ) assert( "Invalid red value" == std::string( ) );
    if( !lua_isnumber( luaState, 6 ) ) assert( "Invalid green value" == std::string( ) );
    if( !lua_isnumber( luaState, 7 ) ) assert( "Invalid blue value" == std::string( ) );
    if( !lua_isnumber( luaState, 8 ) ) assert( "Invalid alpha value" == std::string( ) );

    // create Id
    std::string id = lua_tostring( luaState, 1 );
    convexShapes.insert( std::pair<std::string, sf::ConvexShape*>( id, new sf::ConvexShape( (float)lua_tonumber( luaState, 4 ) ) ) );

    convexShapes.at( id )->setPosition( sf::Vector2f( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) ) );
    convexShapes.at( id )->setFillColor( sf::Color( (float)lua_tonumber( luaState, 5 ), (float)lua_tonumber( luaState, 6 ), (float)lua_tonumber( luaState, 7 ), (float)lua_tonumber( luaState, 8 )  ) );

    // std::cout << "new Assets Id: " << id << std::endl;
    // return id
    lua_pushstring( luaState, id.c_str( ) );
    return 1;
}
/// \brief luaRemoveConvexShape
/// Given the if of an ahape that exists this method removes it.
/// \param luaState
/// STACK
/// 1 ID -1
int GraphicsMan::ConvexShape::luaRemoveConvexShape( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalid id" == std::string( ) );
    if( convexShapes.find( lua_tostring( luaState, 1 ) ) != convexShapes.end( ) ) convexShapes.erase( lua_tostring( luaState, 1 ) );
    return 0;
}
/// \brief luaRegister
/// register all ConvexShape Methods to lua
/// \param luaState
/// \return
int GraphicsMan::ConvexShape::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        // transform interface
        lua_pushcfunction( luaState, luaGetInverseTransform );
        lua_setglobal( luaState, "shape_getInvMatrix" );
        lua_pushcfunction( luaState, luaGetTransform );
        lua_setglobal( luaState, "shape_getMatrix" );
        lua_pushcfunction( luaState, luaSetOrigin );
        lua_setglobal( luaState, "shape_setOrigin" );
        lua_pushcfunction( luaState, luaSetPosition );
        lua_setglobal( luaState, "shape_setPos" );
        lua_pushcfunction( luaState, luaSetRotation );
        lua_setglobal( luaState, "shape_setRotation" );
        lua_pushcfunction( luaState, luaSetScale );
        lua_setglobal( luaState, "shape_setScale" );
        lua_pushcfunction( luaState, luaGetGlobalBounds );
        lua_setglobal( luaState, "shape_getGlobalBounds" );
        lua_pushcfunction( luaState, luaGetLocalBounds );
        lua_setglobal( luaState, "shape_getLocalBounds" );
        // Shape interface
        lua_pushcfunction( luaState, luaSetFillColor);
        lua_setglobal( luaState, "shape_setColor" );
        lua_pushcfunction( luaState, luaSetOutlineColor );
        lua_setglobal( luaState, "shape_setOutlineColor" );
        lua_pushcfunction( luaState, luaSetOutlineThickness );
        lua_setglobal( luaState, "shape_setOutlineThickness" );
        lua_pushcfunction( luaState, luaSetTexture );
        lua_setglobal( luaState, "shape_setTexture" );
        lua_pushcfunction( luaState, luaSetTextureRect );
        lua_setglobal( luaState, "shape_setTexRect" );
        // convex shape interface
        lua_pushcfunction( luaState, luaGetPoint );
        lua_setglobal( luaState, "shape_getPoint" );
        lua_pushcfunction( luaState, luaGetPointCount );
        lua_setglobal( luaState, "shape_getPointCount" );
        lua_pushcfunction( luaState, luaSetPoint );
        lua_setglobal( luaState, "shape_setPoint" );
        lua_pushcfunction( luaState, luaSetPointCount );
        lua_setglobal( luaState, "shape_setPointCount" );
        lua_pushcfunction( luaState, luaRemoveConvexShape );
        lua_setglobal( luaState, "remove_shape" );
        lua_pushcfunction( luaState, luaCreateConvexShape );
        lua_setglobal( luaState, "create_shape" );
        alreadyRegistered = true;
    }
    return 0;
}





