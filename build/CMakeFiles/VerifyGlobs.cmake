# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# SOURCES_FILES at CMakeLists.txt:57 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/tanya/Cours/Projet/Voronoi_delaunay/src/*")
set(OLD_GLOB
  "/home/tanya/Cours/Projet/Voronoi_delaunay/src/SDL2_gfxPrimitives.c"
  "/home/tanya/Cours/Projet/Voronoi_delaunay/src/SDL2_gfxPrimitives.h"
  "/home/tanya/Cours/Projet/Voronoi_delaunay/src/application_ui.cpp"
  "/home/tanya/Cours/Projet/Voronoi_delaunay/src/application_ui.h"
  "/home/tanya/Cours/Projet/Voronoi_delaunay/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/tanya/Cours/Projet/Voronoi_delaunay/build/CMakeFiles/cmake.verify_globs")
endif()