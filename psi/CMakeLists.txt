find_package(Threads REQUIRED)

get_filename_component(LIB_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(LIB_PATH "." ABSOLUTE)

file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.hpp)
file(GLOB_RECURSE LIB_ASM_SOURCES ${LIB_PATH}/*.S)

enable_language(ASM)

add_library(psi-context STATIC ${LIB_CXX_SOURCES} ${LIB_ASM_SOURCES} ${LIB_HEADERS})
target_include_directories(psi-context PUBLIC ${LIB_INCLUDE_PATH})
target_link_libraries(psi-context PUBLIC ${CMAKE_THREAD_LIBS_INIT})
