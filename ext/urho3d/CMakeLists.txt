cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(urho3d_builder C CXX)
include(ExternalProject)

ExternalProject_Add(urho3d
	GIT_REPOSITORY https://github.com/urho3d/Urho3D.git
	GIT_TAG 1.6
	CMAKE_ARGS -DURHO3D_ANGELSCRIPT=0
			   -DURHO3D_LUA=0
			   -DURHO3D_NETWORK=0
			   -DURHO3D_PHYSICS=0
			   -DURHO3D_NAVIGATION=0
			   -DURHO3D_URHO2D=0
			   -DURHO3D_SAMPLES=0
			   -DURHO3D_TOOLS=0
			   -DURHO3D_PCH=0
			   -DURHO3D_C++11=1
	#CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
	#           -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
	#           -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
	#           -Dgtest_force_shared_crt=ON
	#PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
# Disable install step
    INSTALL_COMMAND ""
)

# Specify MainTest's link libraries
ExternalProject_Get_Property(urho3d binary_dir)
#ExternalProject_Get_Property(urho3d source_dir)
if(WIN32)
	set(URHO3D_LIBRARIES ${binary_dir}/lib/libUrho3D.a PARENT_SCOPE)
else(WIN32)
	set(URHO3D_LIBRARIES ${binary_dir}/lib/libUrho3D.a PARENT_SCOPE)
endif(WIN32)
set(URHO3D_INCLUDE_DIR ${binary_dir}/include ${binary_dir}/include/Urho3D/ThirdParty PARENT_SCOPE)

