# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay

# Include any dependencies generated for this target.
include CMakeFiles/VoronoiApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VoronoiApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VoronoiApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VoronoiApp.dir/flags.make

CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o: CMakeFiles/VoronoiApp.dir/flags.make
CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o: src/SDL2_gfxPrimitives.c
CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o: CMakeFiles/VoronoiApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o -MF CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o.d -o CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o -c /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/SDL2_gfxPrimitives.c

CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/SDL2_gfxPrimitives.c > CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.i

CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/SDL2_gfxPrimitives.c -o CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.s

CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o: CMakeFiles/VoronoiApp.dir/flags.make
CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o: src/application_ui.cpp
CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o: CMakeFiles/VoronoiApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o -MF CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o.d -o CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o -c /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/application_ui.cpp

CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/application_ui.cpp > CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.i

CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/application_ui.cpp -o CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.s

CMakeFiles/VoronoiApp.dir/src/main.cpp.o: CMakeFiles/VoronoiApp.dir/flags.make
CMakeFiles/VoronoiApp.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/VoronoiApp.dir/src/main.cpp.o: CMakeFiles/VoronoiApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/VoronoiApp.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VoronoiApp.dir/src/main.cpp.o -MF CMakeFiles/VoronoiApp.dir/src/main.cpp.o.d -o CMakeFiles/VoronoiApp.dir/src/main.cpp.o -c /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/main.cpp

CMakeFiles/VoronoiApp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VoronoiApp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/main.cpp > CMakeFiles/VoronoiApp.dir/src/main.cpp.i

CMakeFiles/VoronoiApp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VoronoiApp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/src/main.cpp -o CMakeFiles/VoronoiApp.dir/src/main.cpp.s

# Object files for target VoronoiApp
VoronoiApp_OBJECTS = \
"CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o" \
"CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o" \
"CMakeFiles/VoronoiApp.dir/src/main.cpp.o"

# External object files for target VoronoiApp
VoronoiApp_EXTERNAL_OBJECTS =

bin/VoronoiApp: CMakeFiles/VoronoiApp.dir/src/SDL2_gfxPrimitives.c.o
bin/VoronoiApp: CMakeFiles/VoronoiApp.dir/src/application_ui.cpp.o
bin/VoronoiApp: CMakeFiles/VoronoiApp.dir/src/main.cpp.o
bin/VoronoiApp: CMakeFiles/VoronoiApp.dir/build.make
bin/VoronoiApp: CMakeFiles/VoronoiApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bin/VoronoiApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VoronoiApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VoronoiApp.dir/build: bin/VoronoiApp
.PHONY : CMakeFiles/VoronoiApp.dir/build

CMakeFiles/VoronoiApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VoronoiApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VoronoiApp.dir/clean

CMakeFiles/VoronoiApp.dir/depend:
	cd /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay /home/smooshiie/Documents/IMAC/2022-2023/S2/Prog_S2/Voronoi_delaunay/CMakeFiles/VoronoiApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VoronoiApp.dir/depend

