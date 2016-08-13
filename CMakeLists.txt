
SET(PROJECT_NAME "test")
project(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

#INCLUDE_DIRECTORIES($ENV{HOME}/workspace/libcurl/curl-7.49.1/include)  
#LINK_DIRECTORIES($ENV{HOME}/workspace/libcurl/curl-7.49.1/lib/.libs)  

aux_source_directory(src DIR_SRCS)
aux_source_directory(src/public DIR_SRCS)

set(CMAKE_EXE_LINKER_FLAGS "-lpthread") 
add_executable(${PROJECT_NAME} ${DIR_SRCS})
