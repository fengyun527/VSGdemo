cmake_minimum_required(VERSION 3.7)

project(vsgDemos
        VERSION 0.0.0
        DESCRIPTION "use vsg to implement learnOpengl demos"
        LANGUAGES CXX C
)

# build all demos into the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Change the default build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# find the vsg
if (VULKAN_SDK)
    set(ENV{VULKAN_SDK} ${VULKAN_SDK})
endif()

find_package(vsg 1.1.0)

vsg_setup_dir_vars()
vsg_setup_build_vars()

# find the optional vsgXchange that can be used for reading a range of image and 3d model formats and shader compilation
find_package(vsgXchange 1.0.5 QUIET)

# find the optional vsgImGui that can be used for GUI elements added into graphics windows.
find_package(vsgImGui QUIET)

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(demos/Getting_started)