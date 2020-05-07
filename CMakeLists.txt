cmake_minimum_required(VERSION 3.10)
project(PA04)
set (EXE_NAME PA04)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

   set(input01 "graph_01.txt")
   set(input02 "graph_02.txt")
    set(input03 "graph_03.txt")
    set(input04 "graph_04.txt")
    set(input05 "graph_05.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04 input05)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)
add_executable(${EXE_NAME} main.cpp)
