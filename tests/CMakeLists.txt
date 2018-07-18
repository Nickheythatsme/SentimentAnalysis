cmake_minimum_required(VERSION 3.5)
message("Including tests")

set(CXXTEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cxxtest")

# Check if the cxxtest director exists
if (EXISTS ${CXXTEST_DIR})

	# Include cxxtest and find cxxtestgen executable
	include_directories(${CXXTEST_DIR})
	set(CXXTESTGEN "${CXXTEST_DIR}/bin/./cxxtestgen")

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
    # Make parse test
	set (SOURCE "test_parse.h")
	set (TARGET "parse_test")

	# Find required packages
	find_package (Threads REQUIRED)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)

	cxx_test(${TARGET} ${SOURCE})
	target_link_libraries(
		${TARGET}
        Threads::Threads
		vectorize
		)

	#################
	# Make btree test
	set (SOURCE "test_btree.h")
	set (TARGET "btree")
	cxx_test(${TARGET} ${SOURCE})
	target_link_libraries(
		${TARGET}
		vectorize
		)

	#################
	# Make holder test
	set (SOURCE "test_holder.h")
	set (TARGET "holder")
	cxx_test(${TARGET} ${SOURCE})
	target_link_libraries(
		${TARGET}
		vectorize
		)
else()
	message(SEND_ERROR "
Cxxtest directory not found but is needed for testing. Clone and move it here:
git clone https://github.com/CxxTest/cxxtest 
mv cxxtest ${CMAKE_CURRENT_SOURCE_DIR}")
endif()
