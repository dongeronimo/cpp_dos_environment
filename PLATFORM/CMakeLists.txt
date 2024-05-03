cmake_minimum_required(VERSION 3.7)
project(dos-app)

set(CMAKE_GENERATOR Ninja)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
add_compile_options(-Wall -std=gnu99 -save-temps )

# file(GLOB sources CONFIGURE_DEPENDS "src/*.c" "src/*.cpp" "src/*.h" "src/**/*.c" "src/**/*.cpp" "src/**/*.h" )
set (sources 
    "inc/asstload/assetld.h"
    "inc/asstload/pcxload.h"
    "inc/image/image.h"
    "inc/input/input.h"
    "inc/utils/logger.h"
    "inc/video/video.h"
    "inc/types.h"
    "src/asstload/assetld.c"
    "src/asstload/pcxload.c"
    "src/input/input.c"
    "src/utils/logger.c"
    "src/video/video.c"
    "src/gdbstub.h"
    )
set (main_source "src/main.c")
set (elf_asset_generator_source "src/assetgen/elf.c")
add_executable(main ${sources} ${main_source})
add_executable(elf ${sources} ${elf_asset_generator_source})

add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)
add_dependencies(main assets)
target_include_directories(main PRIVATE inc)
target_include_directories(elf PRIVATE inc)

target_compile_definitions(main PRIVATE USING_6_BITS_COLORS)

