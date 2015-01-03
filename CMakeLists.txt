cmake_minimum_required(VERSION 3.10)
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()
project(MiniDB VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/block_handle.cc
    src/block_info.cc
    src/buffer_manager.cc
    src/catalog_manager.cc
    src/file_handle.cc
    src/file_info.cc
    src/index_manager.cc
    src/interpreter.cc
    src/main.cc
    src/minidb_api.cc
    src/record_manager.cc
    src/sql_statement.cc
)

# Headers (optional for build, but helpful for IDEs)
set(HEADERS
    src/block_handle.h
    src/block_info.h
    src/buffer_manager.h
    src/catalog_manager.h
    src/commons.h
    src/exceptions.h
    src/file_handle.h
    src/file_info.h
    src/index_manager.h
    src/interpreter.h
    src/minidb_api.h
    src/record_manager.h
    src/sql_statement.h
)

# Define the executable
add_executable(minidb ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(minidb PRIVATE src)

# Boost dependencies
# The project uses: filesystem, serialization, and regex
find_package(Boost REQUIRED COMPONENTS filesystem serialization regex)
if(Boost_FOUND)
    target_include_directories(minidb PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(minidb PRIVATE ${Boost_LIBRARIES})
endif()

# Readline dependency
# CMake doesn't have a built-in FindReadline.cmake, so we look for it manually
find_path(READLINE_INCLUDE_DIR NAMES readline/readline.h)
find_library(READLINE_LIBRARY NAMES readline)

if(READLINE_INCLUDE_DIR AND READLINE_LIBRARY)
    target_include_directories(minidb PRIVATE ${READLINE_INCLUDE_DIR})
    target_link_libraries(minidb PRIVATE ${READLINE_LIBRARY})
else()
    message(FATAL_ERROR "Readline library or headers not found")
endif()

# Link the history library if it exists separately
find_library(HISTORY_LIBRARY NAMES history)
if(HISTORY_LIBRARY)
    target_link_libraries(minidb PRIVATE ${HISTORY_LIBRARY})
endif()
