cmake_minimum_required(VERSION 3.5)

project(editor)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PATCH_VERSION 0.0.${PATCH_VERSION})
project(editor VERSION ${PATCH_VERSION})

add_executable(editor main.cpp)

target_include_directories(editor PRIVATE ${CMAKE_SOURCE_DIR}/src)

set_target_properties(editor PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(editor PROPERTIES COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
set_target_properties(editor PROPERTIES LINK_FLAGS "-fsanitize=address -fno-omit-frame-pointer")

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)