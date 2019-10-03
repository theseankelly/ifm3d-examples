cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0048 NEW)

project(ex-udp CXX)

set(CMAKE_BUILD_TYPE Release) # Release or Debug
set(CMAKE_CXX_EXTENSIONS OFF) # OFF -> -std=c++14, ON -> -std=gnu++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(OpenCV REQUIRED)

##############################################################
## finding the ifm3d lib.
##############################################################
find_package(ifm3d 0.16.0 CONFIG
  REQUIRED COMPONENTS camera framegrabber framegrabberudp image
  )

add_executable(ex-udp ex-udp.cpp)
target_link_libraries(ex-udp
                      ifm3d::camera
                      ifm3d::framegrabber
                      ifm3d::framegrabberudp
                      ifm3d::image
                      ${OpenCV_LIBS}
                      )
