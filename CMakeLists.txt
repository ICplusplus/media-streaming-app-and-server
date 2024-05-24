cmake_minimum_required(VERSION 3.0.0)
project(MediaStreamingApp VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(MediaStreamingClient Client/src/main.cpp)
set_target_properties(MediaStreamingClient PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../Client/bin/)
if(WIN32)
    target_link_libraries(MediaStreamingClient wsock32 ws2_32)
endif()

add_executable(MediaStreamingServer Server/src/main.cpp)
set_target_properties(MediaStreamingServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../Server/bin/)
if(WIN32)
    target_link_libraries(MediaStreamingServer wsock32 ws2_32)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
