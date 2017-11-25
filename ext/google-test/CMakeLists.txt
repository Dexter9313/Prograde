cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(google-test_builder C CXX)
include(ExternalProject)

ExternalProject_Add(google-test
	GIT_REPOSITORY https://github.com/google/googletest.git
	#CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
	#           -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
	#           -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
	#           -Dgtest_force_shared_crt=ON
	#PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
# Disable install step
    INSTALL_COMMAND ""
)

# Specify include dir
ExternalProject_Get_Property(google-test source_dir)
set(GOOGLE_TEST_INCLUDE_DIRS ${source_dir}/googletest/include ${source_dir}/googlemock/include PARENT_SCOPE)

# Specify MainTest's link libraries
ExternalProject_Get_Property(google-test binary_dir)
set(GOOGLE_TEST_LIBRARIES ${binary_dir}/googlemock/gtest/libgtest.a ${binary_dir}/googlemock/gtest/libgtest_main.a ${binary_dir}/googlemock/libgmock.a  ${binary_dir}/googlemock/libgmock_main.a PARENT_SCOPE)



