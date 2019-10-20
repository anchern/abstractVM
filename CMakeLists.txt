cmake_minimum_required(VERSION 3.14)
project(abstractVM)

set(CMAKE_CXX_STANDARD 17)

add_definitions("-Wall -std=c++1y")

#set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
#set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
#set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
#
#FIND_PACKAGE( Boost 1.71.0 COMPONENTS date_time filesystem system )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
#
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
add_executable(abstractVM regexLearn.cpp src/Factory.cpp
        src/Factory.hpp
        src/IOperand.hpp
        src/Operand.cpp
        src/Operand.hpp
        src/VMLogic.cpp
        src/VMLogic.hpp
        src/Sign.cpp
        src/Sign.hpp src/Number.cpp src/Number.hpp src/SignOrNumber.hpp)

#
#TARGET_LINK_LIBRARIES( abstractVM LINK_PUBLIC ${Boost_LIBRARIES} )

#target_link_libraries(boost/lib/cmake/BoostDetectToolset-1.71.0.cmake)

#add_executable(abstractVM src/main.cpp src/Operand.hpp
#        src/Operand.cpp src/Factory.cpp src/Factory.hpp
#        test.cpp)

