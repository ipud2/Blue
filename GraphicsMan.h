#ifndef GRAPHICSMAN_H
#define GRAPHICSMAN_H

#include <string>
#include <assert.h>
#include <iostream>

#include <map>

extern "C" {
#include "lua.hpp"

}

#include <SFML/Graphics.hpp>

namespace GraphicsMan
{
namespace ConvexShape {
    // assetID, asset
    static std::map<std::string, sf::ConvexShape*> convexShapes;
    // transform interface

    /// \brief luaGetInverseTransform
    /// \param luaState
    /// \return
    /// returns a 4X4 matrix
    static int luaGetInverseTransform( lua_State* luaState );
    /// \brief luaGetTransform
    /// \param luaState
    /// \return
    /// returns a 4X4 matrix combining pos, rotation, scale, origin of asset
    static int luaGetTransform( lua_State* luaState );
    /// \brief luaSetOrigin
    /// The defualt origon for all objects is 0,0 (top-left corner)
    /// \param luaState
    /// \param X, Y
    /// The Cordinates for the new origin
    static int luaSetOrigin( lua_State* luaState );
    /// \brief luaSetPosition
    /// \param luaState
    /// \param X, Y
    /// The new Position
    /// The ID of the shape or sprite being manipulated
    static int luaSetPosition( lua_State* luaState );

    /// \brief luaSetRotation
    /// \param luaState
    /// \param angle
    /// The new Angle about the origin. Range: 0 - 360
    static int luaSetRotation( lua_State* luaState );
    /// \brief luaSetScale
    /// \param luaState
    /// \param X, Y
    /// The new Scale factors for the asset
    static int luaSetScale( lua_State* luaState );
    /// Shape interface

    /// \brief luaGetGlobalBounds
    /// Returns rect in terms of global coords (Whole screen)
    /// This is oppossed to getting local bounds which returns a rect relative to the
    /// shape's origin
    /// \param luaState
    /// \graphicsAssetId
    /// returns X, Y, Width, Height of rectangle
    static int luaGetGlobalBounds( lua_State* luaState );
    /// \brief luaGetLocalBounds
    /// Returns rect in terms of local coords
    /// This is oppossed to getting global bounds which returns a rect relative to the
    /// entire world, this returns a rect based on the Asset's coords
    /// \param luaState
    /// \graphicsAssetId
    /// \return X, Y, Width, Height of rectangle
    static int luaGetLocalBounds( lua_State* luaState );
    /// \brief luaSetFillColor
    /// \param luaState
    /// \param graphicAssetId
    /// \param Red, green, blue, alpha values of a color
    static int luaSetFillColor( lua_State* luaState );
    /// \brief luaSetOutlineColor
    /// \param luaState
    /// \param graphicAssetId
    /// \param Red, green, blue, alpha value of color
    static int luaSetOutlineColor( lua_State* luaState );
    /// \brief luaSetOutlineThickness
    /// \param luaState
    /// \param graphicAssetId
    /// \param thickness
    static int luaSetOutlineThickness( lua_State* luaState );
    /// \brief luaSetTexture
    /// \param luaState
    /// \param graphicAssetId
    /// \param TextureId, bool resetRect
    static int luaSetTexture( lua_State* luaState );
    /// \brief luaSetTextureRect
    /// set the rect that represents where on the loaded texture you want to draw
    /// \param luaState
    /// \param graphicAssetId
    /// \param X, Y, Width, Height of rect
    static int luaSetTextureRect( lua_State* luaState );
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
    static int luaGetPoint( lua_State* luaState );
    /// \brief luaGetPointCount
    /// \param luaState
    /// \param graphicAssetId
    ///  \return
    /// returns
    /// the number of points that make up a shape as unsigned int
    static int luaGetPointCount( lua_State* luaState );
    /// \brief luaSetPoint
    /// \param luaState
    /// STACK
    /// 4 Y     -1
    /// 3 X     -2
    /// 2 index -3
    /// 1 ID    -4
    static int luaSetPoint( lua_State* luaState );
    /// \brief luaSetPointCount
    /// \param luaState
    /// STACK
    /// 2 pointCount -1
    /// 1 ID         -2
    static int luaSetPointCount( lua_State* luaState );
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
    static int luaCreateConvexShape( lua_State* luaState );
    /// \brief luaRemoveConvexShape
    /// Given the if of an ahape that exists this method removes it.
    /// \param luaState
    /// STACK
    /// 1 ID -1
    static int luaRemoveConvexShape( lua_State* luaState );
    /// \brief luaRegister
    /// register all ConvexShape Methods to lua
    /// \param luaState
    /// \return
    static int luaRegister( lua_State* luaState );
}
namespace Textures {
    // assetID, asset
    static std::map<std::string, sf::Texture*> textures;
    /// \brief luaLoadFromFile
    /// \param luaState
    /// STACK
    /// 2 fileName -1
    /// 1 ID       -2
    ///  \return
    static int luaLoadFromFile( lua_State* luaState );
    /// \brief luaRemoveTexture
    /// \param luaState
    /// STACK
    /// 1 ID -1
    static int luaRemoveTexture( lua_State* luaState );

    /// \brief luaSetIsSmooth
    /// \param luaState
    /// STACK
    /// 2 isSmooth -1
    /// 1 ID       -2
    ///  \return
    static int luaSetIsSmooth( lua_State* luaState );
    /// \brief luaSetIsRepeated
    /// \param luaState
    /// 2 isRepeated -1
    /// 1 isRepeated -2
    static int luaSetIsRepeated( lua_State* luaState );
    /// \brief luaRegister
    /// register all Texture Methods to lua
    /// \param luaState
    static int luaRegister( lua_State* luaState );
}
/// GlyphMan
/// Creates and manages everything that has to do with printing strings of text to the 
/// game screen.
namespace GlyphMan {
    static std::map<std::string, sf::Font*> fonts; // resource heavy base files for use with sf::Text
    static std::map<std::string, sf::Text*> glyphs; // the actual strings of text the user will create using the above fonts
    // transform interface

    /// \brief luaGetInverseTransform
    /// \param luaState
    /// \return
    /// returns a 4X4 matrix
    static int luaGetInverseTransform( lua_State* luaState );
    /// \brief luaGetTransform
    /// \param luaState
    /// \return
    /// returns a 4X4 matrix combining pos, rotation, scale, origin of asset
    static int luaGetTransform( lua_State* luaState );
    /// \brief luaSetOrigin
    /// The defualt origon for all objects is 0,0 (top-left corner)
    /// \param luaState
    /// \param X, Y
    /// The Cordinates for the new origin
    ///  \return
    static int luaSetOrigin( lua_State* luaState );
    /// \brief luaSetPosition
    /// \param luaState
    /// \param X, Y
    /// The new Position
    /// The ID of the shape or sprite being manipulated
    static int luaSetPosition( lua_State* luaState );
    /// \brief luaSetRotation
    /// \param luaState
    /// \param angle
    /// The new Angle about the origin. Range: 0 - 360
    static int luaSetRotation( lua_State* luaState );
    /// \brief luaSetScale
    /// \param luaState
    /// \param X, Y
    /// The new Scale factors for the asset
    static int luaSetScale( lua_State* luaState ); 
    // Font interface

    /// \brief luaLoadFromFile
    /// Load a font from file for use later with sf::Text
    ///  \param luaState
    /// STACK
    /// 2 fileName -1
    /// 1 ID       -2
    /// \return 
    /// the id of new font
    static int luaLoadFromFile( lua_State* luaState );
    // Text interface

    /// \brief luaSetCharSize
    /// STACK
    /// 2 size -1
    /// 1 ID   -2
    ///  \return 
    static int luaSetCharSize(lua_State*luaState);
    /// \brief luaSetTextColor
    /// STACK
    /// 5 Alpha -1
    /// 4 Blue  -2
    /// 3 Green -3
    /// 2 Red   -4
    /// 1 ID    -5
    static int luaSetTextColor( lua_State* luaState );
    /// \brief luaSetFont
    /// \param luaState
    /// STACK
    /// 2 FontID -1
    /// 1 ID     -2
    ///  \return 
    static int luaSetFont( lua_State* luaState );
    /// \brief luaSetString
    /// \param luaState
    /// STACK
    /// 2 newString -1
    /// 1 ID        -2
    static int luaSetString( lua_State* luaState );
    /// \brief luaSetStyle
    /// \param luaState
    /// STACK
    /// 2 style(enum) -1
    /// 1 ID          -2
    static int luaSetStyle( lua_State* luaState );
    /// \brief luaGetGlobalBounds
    /// Returns rect in terms of global coords (Whole screen)
    /// This is oppossed to getting local bounds which returns a rect relative to the
    /// shape's origin
    /// \param luaState
    /// \graphicsAssetId
    /// \return
    /// returns X, Y, Width, Height of rectangle
    static int luaGetGlobalBounds( lua_State* luaState );
    /// \brief luaGetLocalBounds
    /// Returns rect in terms of local coords
    /// This is oppossed to getting global bounds which returns a rect relative to the
    /// entire world, this returns a rect based on the Asset's coords
    /// \param luaState
    /// \graphicsAssetId
    /// \return
    /// returns X, Y, Width, Height of rectangle
    static int luaGetLocalBounds( lua_State* luaState );
    /// \brief luaRemoveGlyph
    /// \param luaState
    /// STACK
    /// 1 ID -1
    static int luaRemoveGlyph( lua_State* luaState );
    /// \brief luaCreateGlyph
    /// STACK
    /// 4 y      -1
    /// 3 x      -2
    /// 2 string -3
    /// 1 ID     -4
    ///  \param luaState
    static int luaCreateGlyph( lua_State* luaState );
    static int luaRegister( lua_State* luaState );
}
// GraphicsMan register Method
static int luaRegisterGraphicsMan( lua_State* luaState ) {
    // add graphics components to lua
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, ConvexShape::luaRegister ); // Convex Shape
        lua_setglobal( luaState, "register_convexShape" );
        lua_pushcfunction( luaState, Textures::luaRegister );    // Textures
        lua_setglobal( luaState, "register_texture" );
        lua_pushcfunction( luaState, GlyphMan::luaRegister );    // Glyphs
        lua_setglobal( luaState, "register_glyph" );
        alreadyRegistered = true;
    }
    return 0;
}
} // End of GraphicsMan namespace

#include "ConvexShape.inl"
#include "Textures.inl"
#include "GlyphMan.inl"
#endif // GRAPHICSMAN_H

