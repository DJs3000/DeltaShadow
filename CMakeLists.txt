cmake_minimum_required(VERSION 3.16)
project(DeltaShadow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Использовать стандарт C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Инициализация зависимостей.
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)

add_executable(${PROJECT_NAME}
    AnimTile.h
    DeltaShadow.Program.cpp DeltaShadow.Program.h
    Environment/PrimaryScreen.cpp Environment/PrimaryScreen.h
    Environment/SpecialFolder.cpp Environment/SpecialFolder.h
    Program.h
    RoomLayers.h
    SdlDotNetCompat/Audio/Mixer.cpp SdlDotNetCompat/Audio/Mixer.h
    SdlDotNetCompat/Audio/Music.cpp SdlDotNetCompat/Audio/Music.h
    SdlDotNetCompat/Audio/MusicPlayer.cpp SdlDotNetCompat/Audio/MusicPlayer.h
    SdlDotNetCompat/Audio/Sound.cpp SdlDotNetCompat/Audio/Sound.h
    SdlDotNetCompat/Core/BaseSdlResource.cpp SdlDotNetCompat/Core/BaseSdlResource.h
    SdlDotNetCompat/Core/EventHandler.cpp SdlDotNetCompat/Core/EventHandler.h
    SdlDotNetCompat/Core/Events.cpp SdlDotNetCompat/Core/Events.h
    SdlDotNetCompat/Core/QuitEventArgs.cpp SdlDotNetCompat/Core/QuitEventArgs.h
    SdlDotNetCompat/Core/SdlEventArgs.cpp SdlDotNetCompat/Core/SdlEventArgs.h
    SdlDotNetCompat/Core/SdlException.cpp SdlDotNetCompat/Core/SdlException.h
    SdlDotNetCompat/Core/TickEventArgs.cpp SdlDotNetCompat/Core/TickEventArgs.h
    SdlDotNetCompat/Core/UserEventArgs.cpp SdlDotNetCompat/Core/UserEventArgs.h
    SdlDotNetCompat/Drawing/Color.cpp SdlDotNetCompat/Drawing/Color.h
    SdlDotNetCompat/Drawing/Point.h
    SdlDotNetCompat/Drawing/Rectangle.cpp SdlDotNetCompat/Drawing/Rectangle.h
    SdlDotNetCompat/Drawing/Size.h
    SdlDotNetCompat/Graphics/Surface.cpp SdlDotNetCompat/Graphics/Surface.h
    SdlDotNetCompat/Graphics/Video.cpp SdlDotNetCompat/Graphics/Video.h
    SdlDotNetCompat/Graphics/VideoExposeEventArgs.cpp SdlDotNetCompat/Graphics/VideoExposeEventArgs.h
    SdlDotNetCompat/Graphics/VideoInfo.cpp SdlDotNetCompat/Graphics/VideoInfo.h
    SdlDotNetCompat/Graphics/VideoResizeEventArgs.cpp SdlDotNetCompat/Graphics/VideoResizeEventArgs.h
    SdlDotNetCompat/Input/ActiveEventArgs.cpp SdlDotNetCompat/Input/ActiveEventArgs.h
    SdlDotNetCompat/Input/Joystick.cpp SdlDotNetCompat/Input/Joystick.h
    SdlDotNetCompat/Input/Joysticks.cpp SdlDotNetCompat/Input/Joysticks.h
    SdlDotNetCompat/Input/Keyboard.cpp SdlDotNetCompat/Input/Keyboard.h
    SdlDotNetCompat/Input/KeyboardEventArgs.cpp SdlDotNetCompat/Input/KeyboardEventArgs.h
    SdlDotNetCompat/Input/Mouse.cpp SdlDotNetCompat/Input/Mouse.h
    SdlDotNetCompat/Input/MouseButtonEventArgs.cpp SdlDotNetCompat/Input/MouseButtonEventArgs.h
    SdlDotNetCompat/Input/MouseMotionEventArgs.cpp SdlDotNetCompat/Input/MouseMotionEventArgs.h
    Util/BinaryStreamReader.cpp Util/BinaryStreamReader.h
    Util/BinaryStreamWriter.cpp Util/BinaryStreamWriter.h
    Util/File.cpp Util/File.h
    Util/Random.cpp Util/Random.h
    program_main.cpp
)

# Сборка для Linux/Unix
if(UNIX AND NOT MACOS)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL_INCLUDE_DIR}
        ${SDL_IMAGE_INCLUDE_DIR}
        ${SDL_MIXER_INCLUDE_DIR}
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL_LIBRARY}
        ${SDL_IMAGE_LIBRARIES}
        ${SDL_MIXER_LIBRARY}
        SDL_gfx
    )
endif()

# Копирует папку res из корня проекта в папку сборки если они отличаются.
if(NOT "${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res)
endif()

# Установка.
#install(TARGETS DeltaShadow
#    BUNDLE DESTINATION .
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
