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
include examples/sound_capture/CMakeFiles/sound-capture.dir/depend.make

# Include the progress variables for this target.
include examples/sound_capture/CMakeFiles/sound-capture.dir/progress.make

# Include the compile flags for this target's objects.
include examples/sound_capture/CMakeFiles/sound-capture.dir/flags.make

examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o: examples/sound_capture/CMakeFiles/sound-capture.dir/flags.make
examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o: /Users/alexgg/Desktop/SFML-master/examples/sound_capture/SoundCapture.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alexgg/Desktop/SFML-debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o"
	cd /Users/alexgg/Desktop/SFML-debug/examples/sound_capture && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sound-capture.dir/SoundCapture.cpp.o -c /Users/alexgg/Desktop/SFML-master/examples/sound_capture/SoundCapture.cpp

examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-capture.dir/SoundCapture.cpp.i"
	cd /Users/alexgg/Desktop/SFML-debug/examples/sound_capture && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alexgg/Desktop/SFML-master/examples/sound_capture/SoundCapture.cpp > CMakeFiles/sound-capture.dir/SoundCapture.cpp.i

examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-capture.dir/SoundCapture.cpp.s"
	cd /Users/alexgg/Desktop/SFML-debug/examples/sound_capture && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alexgg/Desktop/SFML-master/examples/sound_capture/SoundCapture.cpp -o CMakeFiles/sound-capture.dir/SoundCapture.cpp.s

examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.requires:
.PHONY : examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.requires

examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.provides: examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.requires
	$(MAKE) -f examples/sound_capture/CMakeFiles/sound-capture.dir/build.make examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.provides.build
.PHONY : examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.provides

examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.provides.build: examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o

# Object files for target sound-capture
sound__capture_OBJECTS = \
"CMakeFiles/sound-capture.dir/SoundCapture.cpp.o"

# External object files for target sound-capture
sound__capture_EXTERNAL_OBJECTS =

examples/sound_capture/sound-capture: examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o
examples/sound_capture/sound-capture: examples/sound_capture/CMakeFiles/sound-capture.dir/build.make
examples/sound_capture/sound-capture: lib/sfml-audio.framework/Versions/2.0.0/sfml-audio
examples/sound_capture/sound-capture: lib/sfml-system.framework/Versions/2.0.0/sfml-system
examples/sound_capture/sound-capture: examples/sound_capture/CMakeFiles/sound-capture.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sound-capture"
	cd /Users/alexgg/Desktop/SFML-debug/examples/sound_capture && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sound-capture.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/sound_capture/CMakeFiles/sound-capture.dir/build: examples/sound_capture/sound-capture
.PHONY : examples/sound_capture/CMakeFiles/sound-capture.dir/build

examples/sound_capture/CMakeFiles/sound-capture.dir/requires: examples/sound_capture/CMakeFiles/sound-capture.dir/SoundCapture.cpp.o.requires
.PHONY : examples/sound_capture/CMakeFiles/sound-capture.dir/requires

examples/sound_capture/CMakeFiles/sound-capture.dir/clean:
	cd /Users/alexgg/Desktop/SFML-debug/examples/sound_capture && $(CMAKE_COMMAND) -P CMakeFiles/sound-capture.dir/cmake_clean.cmake
.PHONY : examples/sound_capture/CMakeFiles/sound-capture.dir/clean

examples/sound_capture/CMakeFiles/sound-capture.dir/depend:
	cd /Users/alexgg/Desktop/SFML-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexgg/Desktop/SFML-master /Users/alexgg/Desktop/SFML-master/examples/sound_capture /Users/alexgg/Desktop/SFML-debug /Users/alexgg/Desktop/SFML-debug/examples/sound_capture /Users/alexgg/Desktop/SFML-debug/examples/sound_capture/CMakeFiles/sound-capture.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/sound_capture/CMakeFiles/sound-capture.dir/depend

