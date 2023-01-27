cmake_minimum_required(VERSION 3.23)
project(Library_Manage_System)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
add_executable(Library_Manage_System main.c menu.c data_lists.c data_list.h menu.h option.c option.h book.c book.h catagory_management.c catagory_management.h data_io.c data_io.h)