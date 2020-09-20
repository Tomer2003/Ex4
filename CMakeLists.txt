cmake_minimum_required(VERSION 3.0.0)
project(tester VERSION 0.1.0)

set(C_STANDARD C99)
add_compile_options(-Wall -Wextra -pedantic -Werror)

include(CTest)
enable_testing()

find_package( Threads )


#get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
# Add the libmatrix file to the include path - so that
#   we can include it as without explicitly specifying 
#   the files directory.
include_directories(matrix)
# Link directories - tells the linker to look for .so files
#   in these directories. We want libmatrix.so which is under 
#the matrix directory. Note that a full path is required.
link_directories(matrix)
add_executable(tester main.cpp server.cpp client_operations.cpp solver_tasks.cpp matrix/MatrixExceptions.cpp matrix/ClassMatrix.cpp) 
# Links out executable with matrix. ld (the linker) will automatically
#   add the 'lib' prefix and 'so' suffix, which will result in libmatrix.so
target_link_libraries(tester matrix)



target_link_libraries( tester ${CMAKE_THREAD_LIBS_INIT} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
