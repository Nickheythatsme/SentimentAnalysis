cmake_minimum_required(VERSION 3.5)
message("Including tests")

# Check if the cxxtest director exists
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3)

	# Include cxxtest and find cxxtestgen executable
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3)
	set(CXXTESTGEN "${CMAKE_CURRENT_SOURCE_DIR}/cxxtest-4.3/bin/./cxxtestgen")

	# Function to add cxxtest
	function(cxx_test target source)
		set(H_FULL_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
		string(REGEX REPLACE ".h$" ".cpp" CPP ${source} )
		set(CPP_FULL_NAME "${CMAKE_CURRENT_BINARY_DIR}/${CPP}")
		add_custom_command(
			OUTPUT "${CPP_FULL_NAME}"
			COMMAND ${CXXTESTGEN} --error-printer --output "${CPP_FULL_NAME}" "${H_FULL_NAME}" 
			DEPENDS "${H_FULL_NAME}"
			)
		add_executable(${target} ${CPP_FULL_NAME})
		add_test("${target}" ${CMAKE_CURRENT_BINARY_DIR}/${target})
		message(STATUS "executable made: " ${CMAKE_CURRENT_BINARY_DIR}/${target})
	endfunction(cxx_test)

	#################
	# Make Parse test
	set (SOURCE "test_parse.h")
	set (TARGET "parse_test")

	# Find required packages
	find_package (Threads REQUIRED)

	cxx_test(${TARGET} ${SOURCE})
	target_link_libraries(
		${TARGET}
		${CMAKE_THREAD_LIBS_INIT}
		vectorize
		)

	#################
	#Make window test
	set (SOURCE "test_window.h")
	set (TARGET "window_test")
	cxx_test(${TARGET} ${SOURCE})
	target_link_libraries(
		${TARGET}
		vectorize
		)
else()
	message(SEND_ERROR "cxxtest directory not found.
	It can be downloaded here: https://cxxtest.com/
	Then placed in the directory: ${CMAKE_CURRENT_SOURCE_DIR}")
endif()
