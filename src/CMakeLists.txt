enable_testing()

function(build_test TEST_NAME TEST_FILE)
  add_executable(${TEST_NAME} ${TEST_FILE})
  target_link_libraries(${TEST_NAME} PRIVATE project_warnings project_options)
  add_test(${TEST_NAME} ${TEST_NAME})
endfunction()

macro(copy_file FILE_NAME EXECUTABLE_NAME)
  add_custom_command(
    TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}
            ${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME})
endmacro()

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Sortari_Cautare_SDO/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Liste_Stive_Cozi_Hashuri/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Heapuri_BSTrees/)
