# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.3.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.3.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src

# Include any dependencies generated for this target.
include exec/CMakeFiles/theia_extract_features.dir/depend.make

# Include the progress variables for this target.
include exec/CMakeFiles/theia_extract_features.dir/progress.make

# Include the compile flags for this target's objects.
include exec/CMakeFiles/theia_extract_features.dir/flags.make

exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o: exec/CMakeFiles/theia_extract_features.dir/flags.make
exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o: ../exec/theia_extract_features/extract_features.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o"
	cd /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/exec && /Library/Developer/CommandLineTools/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o -c /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/exec/theia_extract_features/extract_features.cpp

exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.i"
	cd /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/exec && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/exec/theia_extract_features/extract_features.cpp > CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.i

exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.s"
	cd /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/exec && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/exec/theia_extract_features/extract_features.cpp -o CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.s

exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.requires:

.PHONY : exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.requires

exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.provides: exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.requires
	$(MAKE) -f exec/CMakeFiles/theia_extract_features.dir/build.make exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.provides.build
.PHONY : exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.provides

exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.provides.build: exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o


# Object files for target theia_extract_features
theia_extract_features_OBJECTS = \
"CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o"

# External object files for target theia_extract_features
theia_extract_features_EXTERNAL_OBJECTS =

../bin/theia_extract_features: exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o
../bin/theia_extract_features: exec/CMakeFiles/theia_extract_features.dir/build.make
../bin/theia_extract_features: libberkeley_sfm.a
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_videostab.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_ts.a
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_superres.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_stitching.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_contrib.2.4.8.dylib
../bin/theia_extract_features: /usr/local/lib/libtheia.a
../bin/theia_extract_features: /usr/local/lib/libgflags.2.1.2.dylib
../bin/theia_extract_features: /usr/local/lib/libglog.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_nonfree.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_ocl.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_gpu.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_photo.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_objdetect.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_legacy.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_video.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_ml.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_calib3d.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_features2d.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_highgui.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_imgproc.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_flann.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libopencv_core.2.4.8.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libpng.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libz.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libjpeg.dylib
../bin/theia_extract_features: /Users/davidfridovichkeil/anaconda/lib/libtiff.dylib
../bin/theia_extract_features: /usr/local/lib/libeasyexif.dylib
../bin/theia_extract_features: /usr/local/lib/libstatx.a
../bin/theia_extract_features: /usr/local/lib/libceres.1.10.0.dylib
../bin/theia_extract_features: /usr/local/lib/libstlplus3.dylib
../bin/theia_extract_features: /usr/local/lib/libvlfeat.dylib
../bin/theia_extract_features: /usr/local/lib/libglog.dylib
../bin/theia_extract_features: exec/CMakeFiles/theia_extract_features.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/theia_extract_features"
	cd /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/exec && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/theia_extract_features.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
exec/CMakeFiles/theia_extract_features.dir/build: ../bin/theia_extract_features

.PHONY : exec/CMakeFiles/theia_extract_features.dir/build

exec/CMakeFiles/theia_extract_features.dir/requires: exec/CMakeFiles/theia_extract_features.dir/theia_extract_features/extract_features.cpp.o.requires

.PHONY : exec/CMakeFiles/theia_extract_features.dir/requires

exec/CMakeFiles/theia_extract_features.dir/clean:
	cd /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/exec && $(CMAKE_COMMAND) -P CMakeFiles/theia_extract_features.dir/cmake_clean.cmake
.PHONY : exec/CMakeFiles/theia_extract_features.dir/clean

exec/CMakeFiles/theia_extract_features.dir/depend:
	cd /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/exec /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/exec /Users/davidfridovichkeil/Documents/Developer/berkeley_sfm/src/exec/CMakeFiles/theia_extract_features.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : exec/CMakeFiles/theia_extract_features.dir/depend

