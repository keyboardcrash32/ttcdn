# Version 3.28 is required for -S and -B command line arguments
cmake_minimum_required(VERSION 3.28)

project(ttcdn)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

set(SOURCE_FILES src/main.cpp
                 src/downloader.cpp
)

add_executable(ttcdn ${SOURCE_FILES})
include_directories(${CURL_INCLUDE_DIR})
include_directories(${JSON_INCLUDE_DIR})
target_link_libraries(ttcdn PRIVATE ${CURL_LIBRARIES})
target_link_libraries(ttcdn PRIVATE ${JSON_LIBRARIES})