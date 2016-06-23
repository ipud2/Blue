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
