# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/client/main.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client/main.cpp.o: client/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/client/main.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/client/main.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/client/main.cpp

CMakeFiles/client.dir/client/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client/main.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/client/main.cpp > CMakeFiles/client.dir/client/main.cpp.i

CMakeFiles/client.dir/client/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client/main.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/client/main.cpp -o CMakeFiles/client.dir/client/main.cpp.s

CMakeFiles/client.dir/client/main.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/client/main.cpp.o.requires

CMakeFiles/client.dir/client/main.cpp.o.provides: CMakeFiles/client.dir/client/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client/main.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/client/main.cpp.o.provides

CMakeFiles/client.dir/client/main.cpp.o.provides.build: CMakeFiles/client.dir/client/main.cpp.o


CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o: shared/Etat/Joueur.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Joueur.cpp

CMakeFiles/client.dir/shared/Etat/Joueur.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Joueur.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Joueur.cpp > CMakeFiles/client.dir/shared/Etat/Joueur.cpp.i

CMakeFiles/client.dir/shared/Etat/Joueur.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Joueur.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Joueur.cpp -o CMakeFiles/client.dir/shared/Etat/Joueur.cpp.s

CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o


CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o: shared/Etat/ManaPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/ManaPool.cpp

CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/ManaPool.cpp > CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.i

CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/ManaPool.cpp -o CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.s

CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o


CMakeFiles/client.dir/shared/Etat/Active.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Active.cpp.o: shared/Etat/Active.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client.dir/shared/Etat/Active.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Active.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Active.cpp

CMakeFiles/client.dir/shared/Etat/Active.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Active.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Active.cpp > CMakeFiles/client.dir/shared/Etat/Active.cpp.i

CMakeFiles/client.dir/shared/Etat/Active.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Active.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Active.cpp -o CMakeFiles/client.dir/shared/Etat/Active.cpp.s

CMakeFiles/client.dir/shared/Etat/Active.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Active.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Active.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Active.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Active.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Active.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Active.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Active.cpp.o


CMakeFiles/client.dir/shared/Etat/Creature.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Creature.cpp.o: shared/Etat/Creature.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/client.dir/shared/Etat/Creature.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Creature.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Creature.cpp

CMakeFiles/client.dir/shared/Etat/Creature.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Creature.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Creature.cpp > CMakeFiles/client.dir/shared/Etat/Creature.cpp.i

CMakeFiles/client.dir/shared/Etat/Creature.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Creature.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Creature.cpp -o CMakeFiles/client.dir/shared/Etat/Creature.cpp.s

CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Creature.cpp.o


CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o: shared/Etat/Capacite.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Capacite.cpp

CMakeFiles/client.dir/shared/Etat/Capacite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Capacite.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Capacite.cpp > CMakeFiles/client.dir/shared/Etat/Capacite.cpp.i

CMakeFiles/client.dir/shared/Etat/Capacite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Capacite.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Capacite.cpp -o CMakeFiles/client.dir/shared/Etat/Capacite.cpp.s

CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o


CMakeFiles/client.dir/shared/Etat/State.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/State.cpp.o: shared/Etat/State.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/client.dir/shared/Etat/State.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/State.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/State.cpp

CMakeFiles/client.dir/shared/Etat/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/State.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/State.cpp > CMakeFiles/client.dir/shared/Etat/State.cpp.i

CMakeFiles/client.dir/shared/Etat/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/State.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/State.cpp -o CMakeFiles/client.dir/shared/Etat/State.cpp.s

CMakeFiles/client.dir/shared/Etat/State.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/State.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/State.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/State.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/State.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/State.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/State.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/State.cpp.o


CMakeFiles/client.dir/shared/Etat/Objet.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Objet.cpp.o: shared/Etat/Objet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/client.dir/shared/Etat/Objet.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Objet.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Objet.cpp

CMakeFiles/client.dir/shared/Etat/Objet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Objet.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Objet.cpp > CMakeFiles/client.dir/shared/Etat/Objet.cpp.i

CMakeFiles/client.dir/shared/Etat/Objet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Objet.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Objet.cpp -o CMakeFiles/client.dir/shared/Etat/Objet.cpp.s

CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Objet.cpp.o


CMakeFiles/client.dir/shared/Etat/Carte.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Carte.cpp.o: shared/Etat/Carte.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/client.dir/shared/Etat/Carte.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Carte.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Carte.cpp

CMakeFiles/client.dir/shared/Etat/Carte.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Carte.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Carte.cpp > CMakeFiles/client.dir/shared/Etat/Carte.cpp.i

CMakeFiles/client.dir/shared/Etat/Carte.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Carte.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Carte.cpp -o CMakeFiles/client.dir/shared/Etat/Carte.cpp.s

CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Carte.cpp.o


CMakeFiles/client.dir/shared/Etat/Cout.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Cout.cpp.o: shared/Etat/Cout.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/client.dir/shared/Etat/Cout.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Cout.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Cout.cpp

CMakeFiles/client.dir/shared/Etat/Cout.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Cout.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Cout.cpp > CMakeFiles/client.dir/shared/Etat/Cout.cpp.i

CMakeFiles/client.dir/shared/Etat/Cout.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Cout.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Cout.cpp -o CMakeFiles/client.dir/shared/Etat/Cout.cpp.s

CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Cout.cpp.o


CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o: shared/Etat/Declenchee.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Declenchee.cpp

CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Declenchee.cpp > CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.i

CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/shared/Etat/Declenchee.cpp -o CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.s

CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.requires

CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.provides: CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.provides

CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.provides.build: CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o


CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o: Test/Test/TestEtat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o -c /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/Test/Test/TestEtat.cpp

CMakeFiles/client.dir/Test/Test/TestEtat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Test/Test/TestEtat.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/Test/Test/TestEtat.cpp > CMakeFiles/client.dir/Test/Test/TestEtat.cpp.i

CMakeFiles/client.dir/Test/Test/TestEtat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Test/Test/TestEtat.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/Test/Test/TestEtat.cpp -o CMakeFiles/client.dir/Test/Test/TestEtat.cpp.s

CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.requires:

.PHONY : CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.requires

CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.provides: CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.provides.build
.PHONY : CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.provides

CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.provides.build: CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o


# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client/main.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Active.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Creature.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/State.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Objet.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Carte.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Cout.cpp.o" \
"CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o" \
"CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

../bin/client: CMakeFiles/client.dir/client/main.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Active.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Creature.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/State.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Objet.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Carte.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Cout.cpp.o
../bin/client: CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o
../bin/client: CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o
../bin/client: CMakeFiles/client.dir/build.make
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-window.so
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-system.so
../bin/client: /usr/lib/x86_64-linux-gnu/libsfml-network.so
../bin/client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable ../bin/client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: ../bin/client

.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/requires: CMakeFiles/client.dir/client/main.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Joueur.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/ManaPool.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Active.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Creature.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Capacite.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/State.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Objet.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Carte.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Cout.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/shared/Etat/Declenchee.cpp.o.requires
CMakeFiles/client.dir/requires: CMakeFiles/client.dir/Test/Test/TestEtat.cpp.o.requires

.PHONY : CMakeFiles/client.dir/requires

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src /home/sebachar/Documents/Projet3A/charrierpiquet/charrierpiquet/src/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

