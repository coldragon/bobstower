cmake_minimum_required(VERSION 3.7)
project(bobstower C)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_LIBRARY_ttf /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
set(SDL2_LIBRARY_image /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
set(SDL2_LIBRARY_mixer /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so)
include_directories(src/hdr)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..
        )

add_executable(bobstower
        src/main.c
        src/affichage.c
        src/attack.c
        src/basic.c
        src/collision.c
        src/event.c
        src/init.c
        src/map.c
        src/object_power.c
        src/other_screen.c
        src/texture.c
        src/hdr/affichage.h
        src/hdr/attack.h
        src/hdr/basic.h
        src/hdr/collision.h
        src/hdr/define.h
        src/hdr/event.h
        src/hdr/init.h
        src/hdr/map.h
        src/hdr/object_power.h
        src/hdr/other_screen.h
        src/hdr/struct.h
        src/hdr/texture.h
        src/hdr/tinyfiles.h)

target_link_libraries(bobstower
        ${SDL2_LIBRARY}
        ${SDL2_LIBRARY_image}
        ${SDL2_LIBRARY_mixer}
        ${SDL2_LIBRARY_ttf}
        m)