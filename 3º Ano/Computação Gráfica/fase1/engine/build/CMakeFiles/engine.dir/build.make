# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build"

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/main.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/main.cpp.o -c "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/main.cpp"

CMakeFiles/engine.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/main.cpp" > CMakeFiles/engine.dir/main.cpp.i

CMakeFiles/engine.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/main.cpp" -o CMakeFiles/engine.dir/main.cpp.s

CMakeFiles/engine.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/engine.dir/main.cpp.o.requires

CMakeFiles/engine.dir/main.cpp.o.provides: CMakeFiles/engine.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/engine.dir/main.cpp.o.provides

CMakeFiles/engine.dir/main.cpp.o.provides.build: CMakeFiles/engine.dir/main.cpp.o


CMakeFiles/engine.dir/tinyxml2.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/tinyxml2.cpp.o: ../tinyxml2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/engine.dir/tinyxml2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/tinyxml2.cpp.o -c "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/tinyxml2.cpp"

CMakeFiles/engine.dir/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/tinyxml2.cpp" > CMakeFiles/engine.dir/tinyxml2.cpp.i

CMakeFiles/engine.dir/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/tinyxml2.cpp" -o CMakeFiles/engine.dir/tinyxml2.cpp.s

CMakeFiles/engine.dir/tinyxml2.cpp.o.requires:

.PHONY : CMakeFiles/engine.dir/tinyxml2.cpp.o.requires

CMakeFiles/engine.dir/tinyxml2.cpp.o.provides: CMakeFiles/engine.dir/tinyxml2.cpp.o.requires
	$(MAKE) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/tinyxml2.cpp.o.provides.build
.PHONY : CMakeFiles/engine.dir/tinyxml2.cpp.o.provides

CMakeFiles/engine.dir/tinyxml2.cpp.o.provides.build: CMakeFiles/engine.dir/tinyxml2.cpp.o


# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/main.cpp.o" \
"CMakeFiles/engine.dir/tinyxml2.cpp.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

engine: CMakeFiles/engine.dir/main.cpp.o
engine: CMakeFiles/engine.dir/tinyxml2.cpp.o
engine: CMakeFiles/engine.dir/build.make
engine: /usr/lib/x86_64-linux-gnu/libOpenGL.so
engine: /usr/lib/x86_64-linux-gnu/libGLX.so
engine: /usr/lib/x86_64-linux-gnu/libGLU.so
engine: /usr/lib/x86_64-linux-gnu/libglut.so
engine: /usr/lib/x86_64-linux-gnu/libXi.so
engine: CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine

.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/requires: CMakeFiles/engine.dir/main.cpp.o.requires
CMakeFiles/engine.dir/requires: CMakeFiles/engine.dir/tinyxml2.cpp.o.requires

.PHONY : CMakeFiles/engine.dir/requires

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine" "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine" "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build" "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build" "/home/carricossauro/Documents/LCC 3º ano/Projeto-CG/fase1/engine/build/CMakeFiles/engine.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/engine.dir/depend

