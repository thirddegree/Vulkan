cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
cmake_policy(VERSION 3.5)

project("Vulkan Examples")


include_directories("include")
include_directories("ExampleCommon/include")


file(GLOB COMMON_SRC ExampleCommon/source/*.cpp)

# Function for building single example
function(BuildExample EXAMPLE_NAME)
    include_directories("include/${EXAMPLE_NAME}")
    file(GLOB EXAMPLE_SRC ${COMMON_SRC} source/${EXAMPLE_NAME}/*.cpp)
    if(WIN32)
        add_executable(${EXAMPLE_NAME} WIN32 ${EXAMPLE_SRC})
        target_link_libraries(${EXAMPLE_NAME} ${VULKAN_LIB})
    else()
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC})
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
    triangle)

BuildExamples()
