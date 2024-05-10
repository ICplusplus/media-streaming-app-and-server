cmake_minimum_required(VERSION 3.0.0)
project(MediaStreamer VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(MediaStreamerClient Client/src/main.cpp)
set_target_properties(MediaStreamerClient PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../Client/bin)

add_executable(MediaStreamerServer Server/src/main.cpp)
set_target_properties(MediaStreamerServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../Server/bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
