# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = "/home/tomer/Advanced Programmin 1/Ex4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/tomer/Advanced Programmin 1/Ex4/build"

# Include any dependencies generated for this target.
include CMakeFiles/tester.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tester.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tester.dir/flags.make

CMakeFiles/tester.dir/main.cpp.o: CMakeFiles/tester.dir/flags.make
CMakeFiles/tester.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tester.dir/main.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/main.cpp.o -c "/home/tomer/Advanced Programmin 1/Ex4/main.cpp"

CMakeFiles/tester.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/main.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tomer/Advanced Programmin 1/Ex4/main.cpp" > CMakeFiles/tester.dir/main.cpp.i

CMakeFiles/tester.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/main.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tomer/Advanced Programmin 1/Ex4/main.cpp" -o CMakeFiles/tester.dir/main.cpp.s

CMakeFiles/tester.dir/exceptions.cpp.o: CMakeFiles/tester.dir/flags.make
CMakeFiles/tester.dir/exceptions.cpp.o: ../exceptions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tester.dir/exceptions.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/exceptions.cpp.o -c "/home/tomer/Advanced Programmin 1/Ex4/exceptions.cpp"

CMakeFiles/tester.dir/exceptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/exceptions.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tomer/Advanced Programmin 1/Ex4/exceptions.cpp" > CMakeFiles/tester.dir/exceptions.cpp.i

CMakeFiles/tester.dir/exceptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/exceptions.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tomer/Advanced Programmin 1/Ex4/exceptions.cpp" -o CMakeFiles/tester.dir/exceptions.cpp.s

CMakeFiles/tester.dir/server.cpp.o: CMakeFiles/tester.dir/flags.make
CMakeFiles/tester.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tester.dir/server.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/server.cpp.o -c "/home/tomer/Advanced Programmin 1/Ex4/server.cpp"

CMakeFiles/tester.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/server.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tomer/Advanced Programmin 1/Ex4/server.cpp" > CMakeFiles/tester.dir/server.cpp.i

CMakeFiles/tester.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/server.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tomer/Advanced Programmin 1/Ex4/server.cpp" -o CMakeFiles/tester.dir/server.cpp.s

CMakeFiles/tester.dir/client_operations.cpp.o: CMakeFiles/tester.dir/flags.make
CMakeFiles/tester.dir/client_operations.cpp.o: ../client_operations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/tester.dir/client_operations.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/client_operations.cpp.o -c "/home/tomer/Advanced Programmin 1/Ex4/client_operations.cpp"

CMakeFiles/tester.dir/client_operations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/client_operations.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tomer/Advanced Programmin 1/Ex4/client_operations.cpp" > CMakeFiles/tester.dir/client_operations.cpp.i

CMakeFiles/tester.dir/client_operations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/client_operations.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tomer/Advanced Programmin 1/Ex4/client_operations.cpp" -o CMakeFiles/tester.dir/client_operations.cpp.s

CMakeFiles/tester.dir/solver_tasks.cpp.o: CMakeFiles/tester.dir/flags.make
CMakeFiles/tester.dir/solver_tasks.cpp.o: ../solver_tasks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/tester.dir/solver_tasks.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/solver_tasks.cpp.o -c "/home/tomer/Advanced Programmin 1/Ex4/solver_tasks.cpp"

CMakeFiles/tester.dir/solver_tasks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/solver_tasks.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tomer/Advanced Programmin 1/Ex4/solver_tasks.cpp" > CMakeFiles/tester.dir/solver_tasks.cpp.i

CMakeFiles/tester.dir/solver_tasks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/solver_tasks.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tomer/Advanced Programmin 1/Ex4/solver_tasks.cpp" -o CMakeFiles/tester.dir/solver_tasks.cpp.s

CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.o: CMakeFiles/tester.dir/flags.make
CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.o: ../matrix/MatrixExceptions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.o -c "/home/tomer/Advanced Programmin 1/Ex4/matrix/MatrixExceptions.cpp"

CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tomer/Advanced Programmin 1/Ex4/matrix/MatrixExceptions.cpp" > CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.i

CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tomer/Advanced Programmin 1/Ex4/matrix/MatrixExceptions.cpp" -o CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.s

CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.o: CMakeFiles/tester.dir/flags.make
CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.o: ../matrix/ClassMatrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.o -c "/home/tomer/Advanced Programmin 1/Ex4/matrix/ClassMatrix.cpp"

CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tomer/Advanced Programmin 1/Ex4/matrix/ClassMatrix.cpp" > CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.i

CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tomer/Advanced Programmin 1/Ex4/matrix/ClassMatrix.cpp" -o CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.s

# Object files for target tester
tester_OBJECTS = \
"CMakeFiles/tester.dir/main.cpp.o" \
"CMakeFiles/tester.dir/exceptions.cpp.o" \
"CMakeFiles/tester.dir/server.cpp.o" \
"CMakeFiles/tester.dir/client_operations.cpp.o" \
"CMakeFiles/tester.dir/solver_tasks.cpp.o" \
"CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.o" \
"CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.o"

# External object files for target tester
tester_EXTERNAL_OBJECTS =

tester: CMakeFiles/tester.dir/main.cpp.o
tester: CMakeFiles/tester.dir/exceptions.cpp.o
tester: CMakeFiles/tester.dir/server.cpp.o
tester: CMakeFiles/tester.dir/client_operations.cpp.o
tester: CMakeFiles/tester.dir/solver_tasks.cpp.o
tester: CMakeFiles/tester.dir/matrix/MatrixExceptions.cpp.o
tester: CMakeFiles/tester.dir/matrix/ClassMatrix.cpp.o
tester: CMakeFiles/tester.dir/build.make
tester: CMakeFiles/tester.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable tester"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tester.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tester.dir/build: tester

.PHONY : CMakeFiles/tester.dir/build

CMakeFiles/tester.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tester.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tester.dir/clean

CMakeFiles/tester.dir/depend:
	cd "/home/tomer/Advanced Programmin 1/Ex4/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/tomer/Advanced Programmin 1/Ex4" "/home/tomer/Advanced Programmin 1/Ex4" "/home/tomer/Advanced Programmin 1/Ex4/build" "/home/tomer/Advanced Programmin 1/Ex4/build" "/home/tomer/Advanced Programmin 1/Ex4/build/CMakeFiles/tester.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/tester.dir/depend

