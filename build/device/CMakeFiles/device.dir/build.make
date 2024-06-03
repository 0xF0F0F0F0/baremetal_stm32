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
CMAKE_SOURCE_DIR = /home/ayush/git_files/baremetal_stm32

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ayush/git_files/baremetal_stm32/build

# Include any dependencies generated for this target.
include device/CMakeFiles/device.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include device/CMakeFiles/device.dir/compiler_depend.make

# Include the progress variables for this target.
include device/CMakeFiles/device.dir/progress.make

# Include the compile flags for this target's objects.
include device/CMakeFiles/device.dir/flags.make

device/CMakeFiles/device.dir/startup_stm32f429.c.o: device/CMakeFiles/device.dir/flags.make
device/CMakeFiles/device.dir/startup_stm32f429.c.o: ../device/startup_stm32f429.c
device/CMakeFiles/device.dir/startup_stm32f429.c.o: device/CMakeFiles/device.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ayush/git_files/baremetal_stm32/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object device/CMakeFiles/device.dir/startup_stm32f429.c.o"
	cd /home/ayush/git_files/baremetal_stm32/build/device && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT device/CMakeFiles/device.dir/startup_stm32f429.c.o -MF CMakeFiles/device.dir/startup_stm32f429.c.o.d -o CMakeFiles/device.dir/startup_stm32f429.c.o -c /home/ayush/git_files/baremetal_stm32/device/startup_stm32f429.c

device/CMakeFiles/device.dir/startup_stm32f429.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/device.dir/startup_stm32f429.c.i"
	cd /home/ayush/git_files/baremetal_stm32/build/device && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ayush/git_files/baremetal_stm32/device/startup_stm32f429.c > CMakeFiles/device.dir/startup_stm32f429.c.i

device/CMakeFiles/device.dir/startup_stm32f429.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/device.dir/startup_stm32f429.c.s"
	cd /home/ayush/git_files/baremetal_stm32/build/device && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ayush/git_files/baremetal_stm32/device/startup_stm32f429.c -o CMakeFiles/device.dir/startup_stm32f429.c.s

device/CMakeFiles/device.dir/system_stm32f4xx.c.o: device/CMakeFiles/device.dir/flags.make
device/CMakeFiles/device.dir/system_stm32f4xx.c.o: ../device/system_stm32f4xx.c
device/CMakeFiles/device.dir/system_stm32f4xx.c.o: device/CMakeFiles/device.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ayush/git_files/baremetal_stm32/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object device/CMakeFiles/device.dir/system_stm32f4xx.c.o"
	cd /home/ayush/git_files/baremetal_stm32/build/device && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT device/CMakeFiles/device.dir/system_stm32f4xx.c.o -MF CMakeFiles/device.dir/system_stm32f4xx.c.o.d -o CMakeFiles/device.dir/system_stm32f4xx.c.o -c /home/ayush/git_files/baremetal_stm32/device/system_stm32f4xx.c

device/CMakeFiles/device.dir/system_stm32f4xx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/device.dir/system_stm32f4xx.c.i"
	cd /home/ayush/git_files/baremetal_stm32/build/device && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ayush/git_files/baremetal_stm32/device/system_stm32f4xx.c > CMakeFiles/device.dir/system_stm32f4xx.c.i

device/CMakeFiles/device.dir/system_stm32f4xx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/device.dir/system_stm32f4xx.c.s"
	cd /home/ayush/git_files/baremetal_stm32/build/device && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ayush/git_files/baremetal_stm32/device/system_stm32f4xx.c -o CMakeFiles/device.dir/system_stm32f4xx.c.s

device: device/CMakeFiles/device.dir/startup_stm32f429.c.o
device: device/CMakeFiles/device.dir/system_stm32f4xx.c.o
device: device/CMakeFiles/device.dir/build.make
.PHONY : device

# Rule to build all files generated by this target.
device/CMakeFiles/device.dir/build: device
.PHONY : device/CMakeFiles/device.dir/build

device/CMakeFiles/device.dir/clean:
	cd /home/ayush/git_files/baremetal_stm32/build/device && $(CMAKE_COMMAND) -P CMakeFiles/device.dir/cmake_clean.cmake
.PHONY : device/CMakeFiles/device.dir/clean

device/CMakeFiles/device.dir/depend:
	cd /home/ayush/git_files/baremetal_stm32/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ayush/git_files/baremetal_stm32 /home/ayush/git_files/baremetal_stm32/device /home/ayush/git_files/baremetal_stm32/build /home/ayush/git_files/baremetal_stm32/build/device /home/ayush/git_files/baremetal_stm32/build/device/CMakeFiles/device.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : device/CMakeFiles/device.dir/depend
