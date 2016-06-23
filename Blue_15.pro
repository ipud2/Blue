TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11
LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
LIBS += -L/usr/include/lua.hpp -llua

SOURCES += main.cpp \
    Application.cpp \
    CameraMan.inl \
    CollisionMan.cpp \
    CollisionMan.inl \
    ConvexShape.inl \
    GlyphMan.inl \
    SystemMan.inl \
    Textures.inl

HEADERS += \
    Application.h \
    CameraMan.h \
    CollisionMan.h \
    GraphicsMan.h \
    SystemMan.h \
    Window.h \
    Ai.h

DISTFILES += \
    Ai.lua \
    AnimatedSprite.lua \
    Animation.lua \
    Button.lua \
    Camera.lua \
    Circle.lua \
    Clone.lua \
    config.lua \
    ControlMap.lua \
    FSM.lua \
    Game.lua \
    GlobalState.lua \
    Glyph.lua \
    Link.lua \
    MapManager.lua \
    MenuState.lua \
    Mouse.lua \
    MovingObj.lua \
    npc.lua \
    Object.lua \
    ObjMan.lua \
    PauseState.lua \
    Rectangle.lua \
    RunState.lua \
    Sprite.lua \
    State.lua \
    test2.lua \
    Texture.lua \
    World.lua
