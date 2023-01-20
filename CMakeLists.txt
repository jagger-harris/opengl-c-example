# Project definitions
cmake_minimum_required(VERSION 3.1)
project(executable)

# Project options
add_definitions(-std=c11)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Get all sources
file(GLOB_RECURSE SOURCES "src/*.c" main.c)

# Get all libs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# Get all resources
set (source "${CMAKE_SOURCE_DIR}/data")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/data")

# Get all resources
set (source "${CMAKE_SOURCE_DIR}/data")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/data")

add_custom_target(data)

file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/data" source)
file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/data" destination)

if (WIN32)
  add_custom_command(
    TARGET data POST_BUILD
    COMMAND mklink /D ${destination} ${source}
    DEPENDS ${destination}
    COMMENT "symbolic link data folder from ${source} => ${destination}"
  )
else()
  add_custom_command(
    TARGET data POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "symbolic link data folder from ${source} => ${destination}"
  )
endif()

# Create executable and add dependencies
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_dependencies(${PROJECT_NAME} data)
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

# GLFW compile fix
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target" FORCE)
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# Glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/gl.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# GLM
set(CGLM_DIR "${LIB_DIR}/cglm")
target_include_directories(${PROJECT_NAME} PRIVATE "${CGLM_DIR}")

# STB
set(STB_DIR "${LIB_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_DIR}")
