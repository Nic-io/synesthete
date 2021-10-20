# Find Zephyr. This also loads Zephyr's build system.
set(BOARD nucleo_f446re)
cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr)
project(synesthete)

# Add your source file to the "app" target. This must come after
# find_package(Zephyr) which defines the target.
target_include_directories(app 
    PRIVATE
        src/gui)
        
target_sources(app 
    PRIVATE
        src/main.c
        src/gui/gui.c
        src/gui/gui.h)
