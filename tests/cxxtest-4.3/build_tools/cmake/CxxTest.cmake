
include("${CMAKE_CURRENT_LIST_DIR}/FindCxxTest.cmake")

function(cxx_test target source)
    set(CPP_FULL_NAME "${CMAKE_CURRENT_BINARY_DIR}/${source}.cpp")
    set(H_FULL_NAME "${CMAKE_CURRENT_SOURCE_DIR}/${source}.h")
    add_custom_command(
        OUTPUT "${CPP_FULL_NAME}"
        COMMAND ${CXXTESTGEN} --error-printer --output "${CPP_FULL_NAME}" "${H_FULL_NAME}" 
        DEPENDS "${H_FULL_NAME}"
        )
    add_executable(${target} ${CPP_FULL_NAME})
	# TODO check windows vs linux
    #set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-Wno-effc++") 
    add_test("${target}" ${RUNTIME_OUTPUT_DIRECTORY}/${target})
endfunction(cxx_test)
