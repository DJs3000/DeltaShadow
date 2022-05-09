TEMPLATE = app
CONFIG += c++11
CONFIG -= qt
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    SdlDotNetCompat/Audio/Sound.cpp \
    SdlDotNetCompat/Audio/Music.cpp \
    SdlDotNetCompat/Graphics/Video.cpp \
    SdlDotNetCompat/Graphics/Surface.cpp \
    SdlDotNetCompat/Core/TickEventArgs.cpp \
    SdlDotNetCompat/Core/Events.cpp \
    SdlDotNetCompat/Input/Joysticks.cpp \
    SdlDotNetCompat/Input/Mouse.cpp \
    SdlDotNetCompat/Input/Joystick.cpp \
    SdlDotNetCompat/Audio/MusicPlayer.cpp \
    SdlDotNetCompat/Input/KeyboardEventArgs.cpp \
    SdlDotNetCompat/Input/Keyboard.cpp \
    SdlDotNetCompat/Graphics/VideoInfo.cpp \
    SdlDotNetCompat/Core/BaseSdlResource.cpp \
    SdlDotNetCompat/Core/EventHandler.cpp \
    SdlDotNetCompat/Graphics/VideoResizeEventArgs.cpp \
    SdlDotNetCompat/Input/ActiveEventArgs.cpp \
    SdlDotNetCompat/Input/MouseMotionEventArgs.cpp \
    SdlDotNetCompat/Input/MouseButtonEventArgs.cpp \
    SdlDotNetCompat/Core/QuitEventArgs.cpp \
    SdlDotNetCompat/Audio/Mixer.cpp \
    Util/BinaryStreamReader.cpp \
    DeltaShadow.Program.cpp \
    SdlDotNetCompat/Core/SdlEventArgs.cpp \
    SdlDotNetCompat/Graphics/VideoExposeEventArgs.cpp \
    SdlDotNetCompat/Core/UserEventArgs.cpp \
    Environment/SpecialFolder.cpp \
    Util/BinaryStreamWriter.cpp \
    Util/File.cpp \
    Util/Random.cpp \
    SdlDotNetCompat/Drawing/Rectangle.cpp \
    SdlDotNetCompat/Drawing/Color.cpp \
    Environment/PrimaryScreen.cpp \
    SdlDotNetCompat/Core/SdlException.cpp \
    program_main.cpp

HEADERS += \
    DeltaShadow.Program.h \
    AnimTile.h \
    RoomLayers.h \
    Program.h \
    SdlDotNetCompat/Audio/Sound.h \
    SdlDotNetCompat/Audio/Music.h \
    SdlDotNetCompat/Graphics/Video.h \
    SdlDotNetCompat/Graphics/Surface.h \
    SdlDotNetCompat/Core/TickEventArgs.h \
    SdlDotNetCompat/Core/Events.h \
    SdlDotNetCompat/Input/Joysticks.h \
    SdlDotNetCompat/Input/Mouse.h \
    SdlDotNetCompat/Input/Joystick.h \
    SdlDotNetCompat/Audio/MusicPlayer.h \
    SdlDotNetCompat/Input/KeyboardEventArgs.h \
    SdlDotNetCompat/Input/Keyboard.h \
    SdlDotNetCompat/Graphics/VideoInfo.h \
    SdlDotNetCompat/Core/BaseSdlResource.h \
    SdlDotNetCompat/Core/EventHandler.h \
    SdlDotNetCompat/Graphics/VideoResizeEventArgs.h \
    SdlDotNetCompat/Input/ActiveEventArgs.h \
    SdlDotNetCompat/Input/MouseMotionEventArgs.h \
    SdlDotNetCompat/Input/MouseButtonEventArgs.h \
    SdlDotNetCompat/Core/QuitEventArgs.h \
    SdlDotNetCompat/Audio/Mixer.h \
    Util/BinaryStreamReader.h \
    SdlDotNetCompat/Core/SdlEventArgs.h \
    SdlDotNetCompat/Graphics/VideoExposeEventArgs.h \
    SdlDotNetCompat/Core/UserEventArgs.h \
    Environment/SpecialFolder.h \
    Util/BinaryStreamWriter.h \
    Util/File.h \
    Util/Random.h \
    SdlDotNetCompat/Drawing/Size.h \
    SdlDotNetCompat/Drawing/Rectangle.h \
    SdlDotNetCompat/Drawing/Point.h \
    SdlDotNetCompat/Drawing/Color.h \
    Environment/PrimaryScreen.h \
    SdlDotNetCompat/Core/SdlException.h

FORMS +=

unix:!macx {
    INCLUDEPATH += /usr/include/SDL
    LIBS += -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -lX11
}

