cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
cmake_policy(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake/")

project("Vulkan Examples")


include_directories("include")
include_directories("ExampleCommon/include")


file(GLOB COMMON_SRC ExampleCommon/source/*.cpp)

# Find required libraries
if(WIN32)
else()
    find_package(ASSIMP REQUIRED)
    find_package(SDL2 REQUIRED)
    find_package(Vulkan REQUIRED)
    find_package(Threads REQUIRED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_XLIB_KHR")
endif()


# Function for building single example
function(BuildExample EXAMPLE_NAME)
    file(GLOB EXAMPLE_SRC ${COMMON_SRC} source/*.cpp source/${EXAMPLE_NAME}/*.cpp)
    if(WIN32)
        add_executable(${EXAMPLE_NAME} WIN32 ${EXAMPLE_SRC})
        target_include_directories(${EXAMPLE_NAME} PUBLIC "include/${EXAMPLE_NAME}")
        target_link_libraries(${EXAMPLE_NAME} ${VULKAN_LIB})
    else()
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC})
        target_include_directories(${EXAMPLE_NAME} PUBLIC "include/${EXAMPLE_NAME}")
        target_link_libraries(${EXAMPLE_NAME} ${VULKAN_LIBRARY} ${SDL2_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
    endif()
endfunction()

# Build all examples
function(BuildExamples)
    foreach(EXAMPLE ${EXAMPLES})
        BuildExample(${EXAMPLE})
    endforeach()
endfunction()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(EXAMPLES
    triangle
    model)

BuildExamples()
