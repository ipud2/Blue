#include "GraphicsMan.h"


// transform interface

/// \brief luaGetInverseTransform
/// \param luaState
/// \return
/// returns a 4X4 matrix
int GraphicsMan::GlyphMan::luaGetInverseTransform( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyphs_getInverseTransform" == std::string( ) );

    // run method
    const float* matrix = glyphs.at( id )->getInverseTransform().getMatrix();

    // 16 becuase it's a 4x4 matrix DUH!! read the header comments!
    for( unsigned int i = 0; i < 16; ++i ) { lua_pushnumber( luaState, matrix[i] ); }
    delete matrix;
    return 16;
}
/// \brief luaGetTransform
/// \param luaState
/// \return
/// returns a 4X4 matrix combining pos, rotation, scale, origin of asset
int GraphicsMan::GlyphMan::luaGetTransform( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyph_getInverseTransform" == std::string( ) );

    // run method
    const float* matrix = glyphs.at( id )->getTransform().getMatrix();
    // 16 becuase it's a 4x4 matrix DUH!! read the header comments!
    for( unsigned int i = 0; i < 16; ++i ) { lua_pushnumber( luaState, matrix[i] ); }
    return 16;
}
/// \brief luaSetOrigin
/// The defualt origon for all objects is 0,0 (top-left corner)
/// \param luaState
/// \param X, Y
/// The Cordinates for the new origin
int GraphicsMan::GlyphMan::luaSetOrigin( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );

    // validate obj exists
    //if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyph_getInverseTransform" == std::string( ) );
    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid xOrigin parameter sent to glyphs_setOrigin" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid yOrigin parameter sent to glyphs_setOrigin" == std::string( ) );
    glyphs.at( id )->setOrigin( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );
    return 0;
}
/// \brief luaSetPosition
/// \param luaState
/// \param X, Y
/// The new Position
/// The ID of the shape or sprite being manipulated
int GraphicsMan::GlyphMan::luaSetPosition( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );
    // validate obj exists
    if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyph_setPos" == std::string( ) );
    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid xPos parameter sent to glyph_setPosition" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid yPos parameter sent to glyph_setPosition" == std::string( ) );
    glyphs.at( id )->setPosition( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );
    return 0;
}
/// \brief luaSetRotation
/// \param luaState
/// \param angle
/// The new Angle about the origin. Range: 0 - 360
int GraphicsMan::GlyphMan::luaSetRotation( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );
    // validate obj exists
    if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyph_setRotation" == std::string( ) );
    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid angle parameter sent to glyph_setRotation" == std::string( ) );
    glyphs.at( id )->setRotation( (float)lua_tonumber( luaState, 2 ) );
    return 0;
}
/// \brief luaSetScale
/// \param luaState
/// \param X, Y
/// The new Scale factors for the asset
int GraphicsMan::GlyphMan::luaSetScale( lua_State* luaState ) {
    // Get Params from stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) asert( "You sent invalid id to glyphs_getInverseTransform" == std::string( ) );
    // run method
    // get other params
    if( !lua_isnumber( luaState, 2 ) ) assert( "invalid scale parameter sent to glyph_setScale" == std::string( ) );
    if( !lua_isnumber( luaState, 3 ) ) assert( "invalid scale parameter sent to glyph_setScale" == std::string( ) );
    glyphs.at( id )->setScale( (float)lua_tonumber( luaState, 2 ), (float)lua_tonumber( luaState, 3 ) );
    return 0;
}
// Font interface

/// \brief luaLoadFromFile
/// Load a font from file for use later with sf::Text
///  \param luaState
/// STACK
/// 2 fileName -1
/// 1 ID       -2
/// \return 
/// the id of new font
int GraphicsMan::GlyphMan::luaLoadFromFile( lua_State* luaState ) {
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isstring( luaState, 2 ) ) assert( "You passed invalid fileName" == std::string( ) );
    std::string id = lua_tostring( luaState, 1 );
    fonts.insert( std::pair<std::string, sf::Font*>( id, new sf::Font( ) ) );
    fonts.at( id )->loadFromFile( lua_tostring( luaState, 2 ) );
    // return id
    lua_pushstring( luaState, id.c_str( ) );
    return 1;
}
// Text interface

/// \brief luaSetCharSize
/// STACK
/// 2 size -1
/// 1 ID   -2 
int GraphicsMan::GlyphMan::luaSetCharSize( lua_State* luaState ) {
    // Validate stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid Size Param" );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyphs_getInverseTransform" == std::string( ) );
    glyphs.at( lua_tostring( luaState, 1 ) )->setCharacterSize( (int)lua_tonumber( luaState, 2 ) );
    return 0;
}
/// \brief luaSetTextColor
/// STACK
/// 5 Alpha -1
/// 4 Blue  -2
/// 3 Green -3
/// 2 Red   -4
/// 1 ID    -5
/// \return 
int GraphicsMan::GlyphMan::luaSetTextColor( lua_State* luaState ) {
    // Validate stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid Red Param" );
    if( !lua_isnumber( luaState, 3 ) ) assert( "Invalid green Param" );
    if( !lua_isnumber( luaState, 4 ) ) assert( "Invalid Blue Param" );
    if( !lua_isnumber( luaState, 5 ) ) assert( "Invalid Alpha Param" );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyph_getInverseTransform" == std::string( ) );
    glyphs.at( lua_tostring( luaState, 1 ) )->setColor( sf::Color( (int)lua_tonumber( luaState, 2 ), (int)lua_tonumber( luaState, 3 ), (int)lua_tonumber( luaState, 4 ), (int)lua_tonumber( luaState, 5 ) ) );
    return 0;
}
/// \brief luaSetFont
/// \param luaState
/// STACK
/// 2 FontID -1
/// 1 ID     -2
///  \return 
int GraphicsMan::GlyphMan::luaSetFont( lua_State* luaState ) {
    // Validate Stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isstring( luaState, 2 ) ) assert( "Invalid FontID Param" );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyph_getInverseTransform" == std::string( ) );
    glyphs.at( lua_tostring( luaState, 1 ) )->setFont( *fonts.at( lua_tostring( luaState, 2 ) ) );
    return 0;
}
/// \brief luaSetString
/// \param luaState
/// STACK
/// 2 newString -1
/// 1 ID        -2
int GraphicsMan::GlyphMan::luaSetString( lua_State* luaState ) {
    // Validate Stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isstring( luaState, 2 ) ) assert( "Invalid newString Param" );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyphs_getInverseTransform" == std::string( ) );
    glyphs.at( lua_tostring( luaState, 1 ) )->setString( lua_tostring( luaState, 2 ) );
    return 0;
}
/// \brief luaSetStyle
/// \param luaState
/// STACK
/// 2 style(enum) -1
/// 1 ID          -2
int GraphicsMan::GlyphMan::luaSetStyle( lua_State* luaState ) {
    // Validate stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    if( !lua_isnumber( luaState, 2 ) ) assert( "Invalid Style Param" );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyphs_getInverseTransform" == std::string( ) );
    glyphs.at( lua_tostring( luaState, 1 ) )->setStyle( (int)lua_tonumber( luaState, 2 ) );
    return 0;
}
/// \brief luaGetGlobalBounds
/// Returns rect in terms of global coords (Whole screen)
/// This is oppossed to getting local bounds which returns a rect relative to the
/// shape's origin
/// \param luaState
/// \graphicsAssetId
/// \return
/// returns X, Y, Width, Height of rectangle
int GraphicsMan::GlyphMan::luaGetGlobalBounds( lua_State* luaState ) {
    // Validate stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyphs_getInverseTransform" == std::string( ) );
    sf::Rect<float> rect = glyphs.at( lua_tostring( luaState, 1 ) )->getGlobalBounds();
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
int GraphicsMan::GlyphMan::luaGetLocalBounds( lua_State* luaState ) {
    // Validate stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalide AssetId" == std::string( ) );
    // validate obj exists
    // if( glyphs.find( id ) == glyphs.end( ) ) assert( "You sent invalid id to glyphs_getInverseTransform" == std::string( ) );
    sf::Rect<float> rect = glyphs.at( lua_tostring( luaState, 1 ) )->getLocalBounds();
    lua_pushnumber( luaState, rect.left );
    lua_pushnumber( luaState, rect.top );
    lua_pushnumber( luaState, rect.width );
    lua_pushnumber( luaState, rect.height );
    return 4;
}
/// \brief luaCreateGlyph
/// STACK
/// 5 y      -1
/// 4 x      -2
/// 3 string -3
/// 2 fontID -4
/// 1 ID     -5
///  \param luaState
int GraphicsMan::GlyphMan::luaCreateGlyph( lua_State* luaState ) {
    // Validate stack
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalid AssetId" == std::string( ) );
    if( !lua_isstring( luaState, 2 ) ) assert( "Invalid FontID" == std::string( ) );
    if( !lua_isstring( luaState, 3 ) ) assert( "Invalid new string" == std::string( ) );
    if( !lua_isnumber( luaState, 4 ) ) assert( "Invalid x Param" );
    if( !lua_isnumber( luaState, 5 ) ) assert( "Invalid y Param" );
    glyphs.insert( std::pair<std::string, sf::Text*>(
                       lua_tostring( luaState, 1 ), new sf::Text( lua_tostring( luaState, 3 ), *fonts.at( lua_tostring( luaState, 2 ) ) ) ) );
    glyphs.at( lua_tostring( luaState, 1 ) )->setPosition( (float)lua_tonumber( luaState, 4 ), (float)lua_tonumber( luaState, 5 ) );
    lua_pushstring( luaState, lua_tostring( luaState, 1 ) );
    return 1;
}
/// \brief luaRemoveGlyph
/// \param luaState
/// STACK
/// 1 ID -1
int GraphicsMan::GlyphMan::luaRemoveGlyph( lua_State* luaState )
{
    if( !lua_isstring( luaState, 1 ) ) assert( "Invalid id" == std::string( ) );
    if( glyphs.find( lua_tostring( luaState, 1 ) ) != glyphs.end( ) ) glyphs.erase( lua_tostring( luaState, 1 ) );
    return 0;
}
int GraphicsMan::GlyphMan::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        // transform interface
        lua_pushcfunction( luaState, luaGetInverseTransform );
        lua_setglobal( luaState, "glyph_getInvMatrix" );
        lua_pushcfunction( luaState, luaGetTransform );
        lua_setglobal( luaState, "glyph_getMatrix" );
        lua_pushcfunction( luaState, luaSetOrigin );
        lua_setglobal( luaState, "glyph_setOrigin" );
        lua_pushcfunction( luaState, luaSetPosition );
        lua_setglobal( luaState, "glyph_setPos" );
        lua_pushcfunction( luaState, luaSetRotation );
        lua_setglobal( luaState, "glyph_setRotation" );
        lua_pushcfunction( luaState, luaSetScale );
        lua_setglobal( luaState, "glyph_setScale" );
        // font interface
        lua_pushcfunction( luaState, luaLoadFromFile );
        lua_setglobal( luaState, "font_loadFromFile" );
        // sf::Text interface
        lua_pushcfunction( luaState, luaSetCharSize );
        lua_setglobal( luaState, "glyph_setCharSize" );
        lua_pushcfunction( luaState, luaSetTextColor );
        lua_setglobal( luaState, "glyph_setTextColor" );
        lua_pushcfunction( luaState, luaSetFont );
        lua_setglobal( luaState, "glyph_setFont" );
        lua_pushcfunction( luaState, luaSetString );
        lua_setglobal( luaState, "glyph_setString" );
        lua_pushcfunction( luaState, luaSetStyle );
        lua_setglobal( luaState, "glyph_setStyle" );
        lua_pushcfunction( luaState, luaGetGlobalBounds );
        lua_setglobal( luaState, "glyph_getGlobalBounds" );
        lua_pushcfunction( luaState, luaGetLocalBounds );
        lua_setglobal( luaState, "glyph_getLocalBounds" );

        lua_pushcfunction( luaState, luaRemoveGlyph );
        lua_setglobal( luaState, "remove_glyph" );
        lua_pushcfunction( luaState, luaCreateGlyph );
        lua_setglobal( luaState, "create_glyph" );
        alreadyRegistered = true;
    }
    return 0;
}
