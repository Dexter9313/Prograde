#    Copyright (C) 2018 Florian Cabot <florian.cabot@hotmail.fr>
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with this program; if not, write to the Free Software Foundation, Inc.,
#    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#INIT
cmake_minimum_required(VERSION 3.2.3 FATAL_ERROR)

set(PROJECT_NAME prograde)
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
project(${PROJECT_NAME} C CXX)


#C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=gnu++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

if(MSVC)
	set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif()

#WARNINGS
#TODO put -fext-numeric-literals at right place
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g -Werror -fext-numeric-literals")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC") # Add this for Qt

#DEPENDENCIES
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
if(DEFINED USE_DIRECTX AND USE_DIRECTX)
	find_package(DirectX REQUIRED)
else()
	find_package(OpenGL REQUIRED)
endif()

find_package(Qt5Test REQUIRED)
message(STATUS "Qt5 include : ${Qt5Test_INCLUDE_DIRS}")
message(STATUS "Qt5 libs : ${Qt5Core_LIBRARIES} ${Qt5Test_LIBRARIES}")

#TODO put -fext-numeric-literals -lquadmath at right place
set(EXTERNAL_LIBS_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${Qt5Test_INCLUDE_DIRS})


#FILES/DIRECTORIES

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE HPP_FILES ${PROJECT_SOURCE_DIR}/test/*.hpp)

file(GLOB_RECURSE MAIN_SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

file(GLOB SRC_FILES ${MAIN_SRC_FILES})
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
list(APPEND TEST_FILES ${SRC_FILES})

set(EXT_PROJECT_DIR ${PROJECT_SOURCE_DIR}/ext)

	#URHO3D
	if( (NOT DEFINED URHO3D_LIBRARIES) OR (NOT DEFINED URHO3D_INCLUDE_DIR) )
		add_subdirectory(${EXT_PROJECT_DIR}/urho3d)
		set(BUILT_URHO3D true)
		MESSAGE(STATUS "Building URHO3D...")
	else()
		MESSAGE(STATUS "Using prebuilt URHO3D...")
	endif()
	MESSAGE(STATUS "Urho3D include dir : ${URHO3D_INCLUDE_DIR}")
	MESSAGE(STATUS "Urho3D libraries : ${URHO3D_LIBRARIES}")

#INCLUDE

set(SYSTEM_INCLUDES ${EXTERNAL_LIBS_INCLUDE_DIRS} ${URHO3D_INCLUDE_DIR})
include_directories(${COMMON_INCLUDES} SYSTEM ${SYSTEM_INCLUDES})

#LINKING SETUP
set(LD_LIBS ${URHO3D_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} -lquadmath ${Qt5Core_LIBRARIES} ${Qt5Test_LIBRARIES})
if(NOT WIN32)
	set(LD_LIBS ${LD_LIBS} -ldl)
endif()

#RUN MOC (FOR QT5)
qt5_wrap_cpp(MOC_FILES ${HPP_FILES})

#EXECUTABLE 1 : FreeOrbiter Test
add_executable(${PROJECT_TEST_NAME} ${TEST_FILES} ${MOC_FILES})
if(BUILT_URHO3D)
	add_dependencies(${PROJECT_TEST_NAME} urho3d)
endif(BUILT_URHO3D)

#TODO put -fext-numeric-literals -lquadmath at right place
target_link_libraries(${PROJECT_TEST_NAME} ${LD_LIBS})

#EXECUTABLE 2 : FreeOrbiter
add_executable(${PROJECT_NAME} ${MAIN_SRC_FILES})
if(BUILT_URHO3D)
	add_dependencies(${PROJECT_NAME} urho3d)
endif(BUILT_URHO3D)

#TODO put -fext-numeric-literals -lquadmath at right place
target_link_libraries(${PROJECT_NAME} ${LD_LIBS})

enable_testing ()
add_test (NAME FreeorbiterTests COMMAND ${PROJECT_TEST_NAME})


# Including extra cmake rules
include(cmake/clang-dev-tools.cmake)
include(cmake/doc.cmake)
