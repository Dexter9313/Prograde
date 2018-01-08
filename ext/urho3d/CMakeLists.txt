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
	set(URHO3D_LIBRARIES ${binary_dir}/lib/libUrho3D.dll.a PARENT_SCOPE)
else(WIN32)
	set(URHO3D_LIBRARIES ${binary_dir}/lib/libUrho3D.a PARENT_SCOPE)
endif(WIN32)
set(URHO3D_INCLUDE_DIR ${binary_dir}/include ${binary_dir}/include/Urho3D/ThirdParty PARENT_SCOPE)

