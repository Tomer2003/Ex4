cmake_minimum_required(VERSION 3.0.0)
project(tester VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( Threads )


add_executable(tester main.cpp server.cpp client_operations.cpp)

target_link_libraries( tester ${CMAKE_THREAD_LIBS_INIT} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
