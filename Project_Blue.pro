TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11
LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
LIBS += -L/usr/include/lua.hpp -llua

SOURCES += main.cpp \
    Application.cpp \
    CollisionMan.cpp \
    CollisionMan.inl \
    ConvexShape.inl \
    GlyphMan.inl \
    SystemMan.inl \
    Textures.inl

HEADERS += \
    Application.h \
    CollisionMan.h \
    GraphicsMan.h \
    LuaMan.h \
    ObjectMan.h \
    SystemMan.h

DISTFILES += \
    Animation.lua \
    Circle.lua \
    Clone.lua \
    config.lua \
    Game.lua \
    Glyph.lua \
    Keyboard.lua \
    Mouse.lua \
    Object.lua \
    ObjMan.lua \
    Rectangle.lua \
    Sprite.lua \
    Texture.lua
