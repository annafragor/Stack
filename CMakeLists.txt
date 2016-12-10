cmake_minimum_required(VERSION 2.8.7)

project(Stack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(BUILD_TESTS "Build tests for moskanka" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include /tests)
add_library(Stack STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/stack.cpp tests/main.cpp)

add_executable(Examples ${CMAKE_CURRENT_SOURCE_DIR} examples/main.cpp)

add_executable(length ${CMAKE_CURRENT_SOURCE_DIR}/tests/length.cpp)
target_link_libraries(length ${PROJECT_NAME} ${DEPENDS_LIBRARIES})

add_executable(pop ${CMAKE_CURRENT_SOURCE_DIR}/tests/pop.cpp)
target_link_libraries(pop ${PROJECT_NAME} ${DEPENDS_LIBRARIES})

add_executable(push_back ${CMAKE_CURRENT_SOURCE_DIR}/tests/push_back.cpp)
target_link_libraries(push_back ${PROJECT_NAME} ${DEPENDS_LIBRARIES})

add_executable(empty ${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.cpp)
target_link_libraries(empty ${PROJECT_NAME} ${DEPENDS_LIBRARIES})