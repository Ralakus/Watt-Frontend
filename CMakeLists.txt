cmake_minimum_required(VERSION 3.1..3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)

    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

endif()

project(Watt VERSION 0.1.0
                  DESCRIPTION "A Labyrinth project"
                  LANGUAGES CXX)

file(GLOB_RECURSE all_c_src
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(WattFrontend ${all_c_src})

set_property(TARGET WattFrontend PROPERTY CXX_STANDARD 17)

set(CMAKE_C_FLAGS_RELEASE "-O3 -flto")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)     # 64 bit

    target_compile_definitions(WattFrontend PUBLIC WATT_64_BIT)

elseif(CMAKE_SIZEOF_VOID_P EQUAL 4) # 32 bit

    target_compile_definitions(WattFrontend PUBLIC WATT_32_BIT)

endif()