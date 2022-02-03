message(STATUS "Psi-context testing")

file(GLOB TEST_SOURCES "./*.cpp")

add_executable(psi_context_test ${TEST_SOURCES})
target_link_libraries(psi_context_test psi-context)