cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Example|Scope LANGUAGES CXX VERSION 1.0.0)
include(ScopeStatus)

# Look for sugar.cmake files in the plugin src directory
sugar_include("src")

# The plugin is a static library that Scope will be linked with
add_library(example_scope OBJECT ${example_SOURCES} ${example_CUDA_SOURCES} )
target_include_directories(example_scope PRIVATE 
    ${SCOPE_SRC_DIR}
    ${THIRDPARTY_DIR}
    ${TOP_DIR}/include
    ${CUDA_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}/src
    "src"
)

# Get the git version
git_get_head_revision(GIT_REFSPEC GIT_HASH)
git_local_changes(GIT_LOCAL_CHANGES)
scope_status(GIT_REFSPEC=${GIT_REFSPEC})
scope_status(GIT_HASH=${GIT_HASH})
scope_status(GIT_LOCAL_CHANGES=${GIT_LOCAL_CHANGES})

target_compile_features(example_scope PUBLIC cxx_std_11)
set_property(TARGET example_scope PROPERTY CUDA_STANDARD 11)
target_link_libraries(example_scope PRIVATE benchmark::benchmark)

scope_status("${PROJECT_SOURCE_DIR}/src/config.hpp.in -> ${PROJECT_BINARY_DIR}/src/config.hpp")
configure_file (
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
    "${PROJECT_BINARY_DIR}/src/config.hpp"
)