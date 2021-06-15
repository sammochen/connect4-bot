cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 14)

project(Connect4Solver)

set(CMAKE_CXX_FLAGS "-O3")
add_definitions(-DDEBUG)

# main
add_executable(Connect4Solver src/Main.cpp)

# link it to boost
set(BOOST_ROOT /Users/shihhaochen/Boost/boost_1_76_0/)
find_package(
  Boost
  COMPONENTS
  REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(Connect4Solver LINK_PUBLIC ${Boost_LIBRARIES})

# testing
enable_testing()

add_executable(Connect4Tests src/tests/MainTest.cpp)
target_link_libraries(Connect4Tests LINK_PUBLIC ${Boost_LIBRARIES})
# disable warning for macro redefined
target_compile_options(Connect4Tests PRIVATE -Wno-macro-redefined)
