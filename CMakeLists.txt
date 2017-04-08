cmake_minimum_required(VERSION 3.7)
project(tsh)

set(CMAKE_CXX_STANDARD 11)

set(SRC_TSH tsh.c utils.h)
set(SRC_FIN fin.c)
set(SRC_LIST list.c)
set(SRC_NEW new.c)
set(SRC_NEWDIR newdir.c)
set(SRC_RMALL rmall.c)
set(SRC_SIZE size.c)

set(BIN_DIR inf3172/bin/)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${BIN_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_executable(fin ${SRC_FIN})
add_executable(list ${SRC_LIST})
add_executable(new ${SRC_NEW})
add_executable(newdir ${SRC_NEWDIR})
add_executable(rmall ${SRC_RMALL})
add_executable(size ${SRC_SIZE})
add_executable(tsh ${SRC_TSH})
add_executable(inf3172_tp2 ${SRC_TSH})