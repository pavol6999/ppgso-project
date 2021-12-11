# This CMake script is designed for CLion IDE and QTCreator projects on Windows
# It should find bundled binary dependencies automatically when using MinGW compiler
# On Linux and Mac the dependencies (glm, glew, glfw) need to be installed manually

cmake_minimum_required(VERSION 3.1)
project(ppgso CXX)

#
# CONFIGURATION
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)

# Use add_resources function to convert .glsl to a .cpp files which will be compiled into a separate static library
include(add_resources)

#
# DEPENDENCIES
#

# Set up external dependencies for Windows users
if (MINGW)
  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/mingw")
elseif (MSVC)
  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/vc2015")
  set(USE_STRICT_COMPILE_WARNINGS OFF CACHE BOOL "" FORCE)
endif ()

# Warnings for Debug mode
option(USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON)
# These compile flags should apply for GCC and Clang compilers
set(STRICT_COMPILE_FLAGS "-Wpedantic -Wall -Wno-c++98-compat -Wextra -Wno-sign-conversion -Wno-unused-parameter")
if (USE_STRICT_COMPILE_WARNINGS)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_FLAGS}")
endif ()

# Find required packages
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

# Optional packages
find_package(OpenMP)
if(OPENMP_FOUND)
  list(APPEND CMAKE_CXX_FLAGS ${OpenMP_CXX_FLAGS})
endif()

# Set default installation destination
if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

#
# Shaders / Materials
#

set(PPGSO_SHADER_SRC
        shader/color_vert.glsl shader/color_frag.glsl
        shader/convolution_vert.glsl shader/convolution_frag.glsl
        shader/diffuse_vert.glsl shader/diffuse_frag.glsl
        shader/texture_vert.glsl shader/texture_frag.glsl
        shader/test_vert.glsl shader/test_frag.glsl
        shader/depth_vert.glsl shader/depth_frag.glsl
        shader/phongo_frag.glsl)

add_resources(shaders ${PPGSO_SHADER_SRC})

# PPGSO library
add_library(ppgso STATIC
        ppgso/mesh.cpp
        ppgso/tiny_obj_loader.cpp
        ppgso/shader.cpp
        ppgso/image.cpp
        ppgso/image_bmp.cpp
        ppgso/image_raw.cpp
        ppgso/texture.cpp
        ppgso/window.cpp
        src/interior_objects/slot_machine/slot_machine.h src/interior_objects/slot_machine/screen.h src/interior_objects/slot_machine/slot_machine.cpp src/interior_objects/slot_machine/screen.cpp src/interior_objects/roulette/roulette_table.h src/interior_objects/roulette/roulette_wheel.h src/interior_objects/roulette/roulette_moving.h src/interior_objects/roulette/roulette_table.cpp src/interior_objects/roulette/roulette_wheel.cpp src/interior_objects/roulette/roulette_moving.cpp)

# Make sure GLM uses radians and GLEW is a static library
target_compile_definitions(ppgso PUBLIC -DGLM_FORCE_RADIANS -DGLEW_STATIC)

# Link to GLFW, GLEW and OpenGL
target_link_libraries(ppgso PUBLIC ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
# Pass on include directories
target_include_directories(ppgso PUBLIC
        ppgso
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})

#
# TARGETS

add_executable(skalican_krajkovic_project src/utilities/utils.cpp src/main.cpp src/scene_window.cpp src/scene.cpp src/staticObject.cpp src/camera.cpp  src/terrain_desert.cpp src/object.cpp src/outside_objects/skybox.cpp src/outside_objects/skybox.h src/outside_objects/building.h src/outside_objects/building.cpp src/outside_objects/tumbleweed.h src/outside_objects/tumbleweed.cpp src/outside_objects/doors/doors.h src/outside_objects/doors/doors.cpp src/outside_objects/doors/double_doors.h src/outside_objects/doors/double_doors.cpp src/animated_object.h src/animated_object.cpp src/interior_objects/human/human.cpp src/interior_objects/human/human.h src/interior_objects/human/arm.cpp src/interior_objects/human/arm.h)

target_link_libraries(skalican_krajkovic_project ppgso shaders)
install (TARGETS skalican_krajkovic_project DESTINATION .)
add_custom_command(TARGET skalican_krajkovic_project POST_BUILD COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR})


#
# INSTALLATION
#

file(COPY "data/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(DIRECTORY data/ DESTINATION .)
