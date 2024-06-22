cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

project(LHTS-ERTC)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_compile_options(-Wall -fuse-ld=gold)

aux_source_directory("src" ERTC_SRC)
add_library(ERTC STATIC ${ERTC_SRC})

add_executable(main_test "test/main_test.cpp")
target_link_libraries(main_test ERTC)
