# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.4.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.4.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/msmith/git/omush/proving_grounds

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/msmith/git/omush/proving_grounds/build

# Include any dependencies generated for this target.
include test/testomushnetwork/CMakeFiles/testomushnetwork.dir/depend.make

# Include the progress variables for this target.
include test/testomushnetwork/CMakeFiles/testomushnetwork.dir/progress.make

# Include the compile flags for this target's objects.
include test/testomushnetwork/CMakeFiles/testomushnetwork.dir/flags.make

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/flags.make
test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o: ../test/testomushnetwork/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/msmith/git/omush/proving_grounds/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o"
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testomushnetwork.dir/main.cc.o -c /Users/msmith/git/omush/proving_grounds/test/testomushnetwork/main.cc

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testomushnetwork.dir/main.cc.i"
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/msmith/git/omush/proving_grounds/test/testomushnetwork/main.cc > CMakeFiles/testomushnetwork.dir/main.cc.i

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testomushnetwork.dir/main.cc.s"
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/msmith/git/omush/proving_grounds/test/testomushnetwork/main.cc -o CMakeFiles/testomushnetwork.dir/main.cc.s

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.requires:

.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.requires

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.provides: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.requires
	$(MAKE) -f test/testomushnetwork/CMakeFiles/testomushnetwork.dir/build.make test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.provides.build
.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.provides

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.provides.build: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o


test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/flags.make
test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o: ../test/testomushnetwork/test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/msmith/git/omush/proving_grounds/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o"
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && /usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testomushnetwork.dir/test.cc.o -c /Users/msmith/git/omush/proving_grounds/test/testomushnetwork/test.cc

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testomushnetwork.dir/test.cc.i"
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/msmith/git/omush/proving_grounds/test/testomushnetwork/test.cc > CMakeFiles/testomushnetwork.dir/test.cc.i

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testomushnetwork.dir/test.cc.s"
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/msmith/git/omush/proving_grounds/test/testomushnetwork/test.cc -o CMakeFiles/testomushnetwork.dir/test.cc.s

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.requires:

.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.requires

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.provides: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.requires
	$(MAKE) -f test/testomushnetwork/CMakeFiles/testomushnetwork.dir/build.make test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.provides.build
.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.provides

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.provides.build: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o


# Object files for target testomushnetwork
testomushnetwork_OBJECTS = \
"CMakeFiles/testomushnetwork.dir/main.cc.o" \
"CMakeFiles/testomushnetwork.dir/test.cc.o"

# External object files for target testomushnetwork
testomushnetwork_EXTERNAL_OBJECTS =

bin/testomushnetwork: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o
bin/testomushnetwork: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o
bin/testomushnetwork: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/build.make
bin/testomushnetwork: lib/libomushnetwork/liblibomushnetwork.a
bin/testomushnetwork: test/gtest/src/gtest-build/libgtest.a
bin/testomushnetwork: test/gmock/src/gmock-build/libgmock.a
bin/testomushnetwork: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/msmith/git/omush/proving_grounds/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/testomushnetwork"
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testomushnetwork.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/testomushnetwork/CMakeFiles/testomushnetwork.dir/build: bin/testomushnetwork

.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/build

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/requires: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/main.cc.o.requires
test/testomushnetwork/CMakeFiles/testomushnetwork.dir/requires: test/testomushnetwork/CMakeFiles/testomushnetwork.dir/test.cc.o.requires

.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/requires

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/clean:
	cd /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork && $(CMAKE_COMMAND) -P CMakeFiles/testomushnetwork.dir/cmake_clean.cmake
.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/clean

test/testomushnetwork/CMakeFiles/testomushnetwork.dir/depend:
	cd /Users/msmith/git/omush/proving_grounds/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/msmith/git/omush/proving_grounds /Users/msmith/git/omush/proving_grounds/test/testomushnetwork /Users/msmith/git/omush/proving_grounds/build /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork /Users/msmith/git/omush/proving_grounds/build/test/testomushnetwork/CMakeFiles/testomushnetwork.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/testomushnetwork/CMakeFiles/testomushnetwork.dir/depend

