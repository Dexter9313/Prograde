# Additional target to perform clang-format/clang-tidy run
# Requires clang-format and clang-tidy

find_package(ClangFormat)

if(CLANG_FORMAT_FOUND)
        message("clang-format executable: ${CLANG_FORMAT_EXECUTABLE}")
        message("clang-format version: ${CLANG_FORMAT_VERSION}")
else()
        message("clang-format executable not found")
endif()

find_package(ClangTidy)

if(CLANG_FORMAT_FOUND)
	message("clang-tidy executable: ${CLANG_TIDY_EXECUTABLE}")
		message("clang-tidy version: ${CLANG_TIDY_VERSION}")
else()
        message("clang-tidy executable not found")
endif()

# Get all project files
file(GLOB_RECURSE ALL_SOURCE_FILES ${MAIN_SRC_FILES} ${TEST_FILES})

list(REMOVE_DUPLICATES ALL_SOURCE_FILES)

add_custom_target(
        clang-format
		COMMAND ${PROJECT_SOURCE_DIR}/dev/clang-format-report.sh
		${CLANG_FORMAT_EXECUTABLE}
        ${ALL_SOURCE_FILES}
)

set(SYSINC "")
foreach(INC ${SYSTEM_INCLUDES})
	list(APPEND SYSINC "-isystem"  "${INC}" "")
endforeach(INC)

add_custom_target(
        clang-tidy
		COMMAND ${PROJECT_SOURCE_DIR}/dev/clang-tidy-report.sh
		${CLANG_TIDY_EXECUTABLE}
		${ALL_SOURCE_FILES}
		config=''
		-system-headers=0
		--
		-std=gnu++11
		-I${COMMON_INCLUDES}
		${SYSINC}
)
