cmake_minimum_required(VERSION 3.29)
project(determinant)

set(CMAKE_CXX_STANDARD 20)


include_directories(include)

add_executable(determinant main.cpp determinant.cpp
        include/determinant.h)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

    message(NOTICE "Using GNU Multiple Precision Arithmetic Library")
    add_compile_definitions(__USE_GMP__)

    include_directories(gmp\\include\\)

    target_link_libraries(determinant  ${CMAKE_SOURCE_DIR}\\gmp\\libgmpxx.a)
    target_link_libraries(determinant  ${CMAKE_SOURCE_DIR}\\gmp\\libgmp.a)

endif ()
