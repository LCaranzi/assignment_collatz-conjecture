# Copyright: (C) 2009 RobotCub Consortium
# Author: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

# Make sure that YARP_DIR is set in your environment to wherever you 
# compiled YARP.

cmake_minimum_required(VERSION 2.8.9)

project(collatz-client)

find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/..)
add_executable(${PROJECT_NAME} client.cpp)
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES})
