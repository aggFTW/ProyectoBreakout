# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = "/Applications/CMake 2.8-10.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-10.app/Contents/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-10.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alexgg/Desktop/SFML-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexgg/Desktop/SFML-debug

# Include any dependencies generated for this target.
include examples/ftp/CMakeFiles/ftp.dir/depend.make

# Include the progress variables for this target.
include examples/ftp/CMakeFiles/ftp.dir/progress.make

# Include the compile flags for this target's objects.
include examples/ftp/CMakeFiles/ftp.dir/flags.make

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o: examples/ftp/CMakeFiles/ftp.dir/flags.make
examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o: /Users/alexgg/Desktop/SFML-master/examples/ftp/Ftp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexgg/Desktop/SFML-debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o"
	cd /Users/alexgg/Desktop/SFML-debug/examples/ftp && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ftp.dir/Ftp.cpp.o -c /Users/alexgg/Desktop/SFML-master/examples/ftp/Ftp.cpp

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftp.dir/Ftp.cpp.i"
	cd /Users/alexgg/Desktop/SFML-debug/examples/ftp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexgg/Desktop/SFML-master/examples/ftp/Ftp.cpp > CMakeFiles/ftp.dir/Ftp.cpp.i

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftp.dir/Ftp.cpp.s"
	cd /Users/alexgg/Desktop/SFML-debug/examples/ftp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexgg/Desktop/SFML-master/examples/ftp/Ftp.cpp -o CMakeFiles/ftp.dir/Ftp.cpp.s

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.requires:
.PHONY : examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.requires

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.provides: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.requires
	$(MAKE) -f examples/ftp/CMakeFiles/ftp.dir/build.make examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.provides.build
.PHONY : examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.provides

examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.provides.build: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o

# Object files for target ftp
ftp_OBJECTS = \
"CMakeFiles/ftp.dir/Ftp.cpp.o"

# External object files for target ftp
ftp_EXTERNAL_OBJECTS =

examples/ftp/ftp: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o
examples/ftp/ftp: examples/ftp/CMakeFiles/ftp.dir/build.make
examples/ftp/ftp: lib/sfml-network.framework/Versions/2.0.0/sfml-network
examples/ftp/ftp: lib/sfml-system.framework/Versions/2.0.0/sfml-system
examples/ftp/ftp: examples/ftp/CMakeFiles/ftp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ftp"
	cd /Users/alexgg/Desktop/SFML-debug/examples/ftp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/ftp/CMakeFiles/ftp.dir/build: examples/ftp/ftp
.PHONY : examples/ftp/CMakeFiles/ftp.dir/build

examples/ftp/CMakeFiles/ftp.dir/requires: examples/ftp/CMakeFiles/ftp.dir/Ftp.cpp.o.requires
.PHONY : examples/ftp/CMakeFiles/ftp.dir/requires

examples/ftp/CMakeFiles/ftp.dir/clean:
	cd /Users/alexgg/Desktop/SFML-debug/examples/ftp && $(CMAKE_COMMAND) -P CMakeFiles/ftp.dir/cmake_clean.cmake
.PHONY : examples/ftp/CMakeFiles/ftp.dir/clean

examples/ftp/CMakeFiles/ftp.dir/depend:
	cd /Users/alexgg/Desktop/SFML-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexgg/Desktop/SFML-master /Users/alexgg/Desktop/SFML-master/examples/ftp /Users/alexgg/Desktop/SFML-debug /Users/alexgg/Desktop/SFML-debug/examples/ftp /Users/alexgg/Desktop/SFML-debug/examples/ftp/CMakeFiles/ftp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/ftp/CMakeFiles/ftp.dir/depend

