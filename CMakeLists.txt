#INIT
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

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
#TODO put -fext-numeric-literals -lquadmath at right place
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g -Werror -fext-numeric-literals")
endif()


#DEPENDENCIES
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenGL REQUIRED)

#TODO put -fext-numeric-literals -lquadmath at right place
set(EXTERNAL_LIBS_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})


#FILES/DIRECTORIES

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE MAIN_SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

file(GLOB SRC_FILES ${MAIN_SRC_FILES})
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
list(APPEND TEST_FILES ${SRC_FILES})

set(EXT_PROJECT_DIR ${PROJECT_SOURCE_DIR}/ext)

	#GMOCK
	add_subdirectory(${EXT_PROJECT_DIR}/google-test)
	add_definitions(${MSVC_COMPILER_DEFS})

	#URHO3D
	if(NOT URHO3D_LIBRARIES or NOT URHO3D_INCLUDE_DIR)
		add_subdirectory(${EXT_PROJECT_DIR}/urho3d)
		MESSAGE(STATUS "Building URHO3D...")
	else()
		MESSAGE(STATUS "Using prebuilt URHO3D...")
	endif()
	MESSAGE(STATUS "Urho3D libraries : ${URHO3D_LIBRARIES}")
	MESSAGE(STATUS "Urho3D include dir : ${URHO3D_INCLUDE_DIR}")

#INCLUDE

set(SYSTEM_INCLUDES ${EXTERNAL_LIBS_INCLUDE_DIRS} ${GOOGLE_TEST_INCLUDE_DIRS} ${URHO3D_INCLUDE_DIR})
include_directories(${COMMON_INCLUDES} SYSTEM ${SYSTEM_INCLUDES})

#EXECUTABLE 1 : FreeOrbiter Test
add_executable(${PROJECT_TEST_NAME} ${TEST_FILES})
add_dependencies(${PROJECT_TEST_NAME} google-test urho3d)

if(NOT WIN32)
    target_link_libraries(${PROJECT_TEST_NAME} ${GOOGLE_TEST_LIBRARIES})
else()
    target_link_libraries(${PROJECT_TEST_NAME}
    debug ${GMOCK_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES}
    optimized ${GMOCK_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES}
       )
    target_link_libraries(${PROJECT_TEST_NAME}
	    debug ${GMOCK_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	    optimized ${GMOCK_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	)
endif()
#TODO put -fext-numeric-literals -lquadmath at right place
target_link_libraries(${PROJECT_TEST_NAME} ${URHO3D_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} dl ${OPENGL_LIBRARIES} -lquadmath)

#EXECUTABLE 2 : FreeOrbiter
add_executable(${PROJECT_NAME} ${MAIN_SRC_FILES})
add_dependencies(${PROJECT_NAME} urho3d)
#TODO put -fext-numeric-literals -lquadmath at right place
target_link_libraries(${PROJECT_NAME} ${URHO3D_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} dl ${OPENGL_LIBRARIES} -lquadmath)

enable_testing ()
add_test (NAME FreeorbiterTests COMMAND ${PROJECT_TEST_NAME})


# Including extra cmake rules
include(cmake/clang-dev-tools.cmake)
include(cmake/doc.cmake)
