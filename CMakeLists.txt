cmake_minimum_required(VERSION 3.20)

project(carimbo)

function(embed target file destination)
  get_filename_component(absolute_file ${file} ABSOLUTE)
  get_target_property(${target}_LINK_FLAGS ${target} LINK_FLAGS)
  if(NOT ${target}_LINK_FLAGS)
    set(${target}_LINK_FLAGS )
  endif()
  set_target_properties(${target} PROPERTIES LINK_FLAGS "${${target}_LINK_FLAGS} --embed-file ${absolute_file}@${destination}")
endfunction()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)



set(SDL2_MAIN SDL2::SDL2main)

# find_package(duktape CONFIG REQUIRED)
# find_package(ffmpeg CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(libavif CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
# find_package(mimalloc CONFIG REQUIRED)
# find_package(nlohmann_json CONFIG REQUIRED)
# find_package(openal CONFIG REQUIRED)
find_package(PhysFS CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
# find_package(SQLite3 CONFIG REQUIRED)
# find_package(zeromq CONFIG REQUIRED)
# find_package(zstd CONFIG REQUIRED)

file(GLOB HEADER_FILES "src/*.hpp")
file(GLOB SOURCE_FILES "src/*.cpp")

#include_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${HEADER_FILES})

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /Od /Zi) # /WX
  else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -O0 -g) # -Werror
  endif()
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
  if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /O2 /GL) # /WX
  else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -O2 -flto) # -Werror
  endif()
endif()

execute_process(
  COMMAND
    go run ${CMAKE_SOURCE_DIR}/assets/pack.go ${CMAKE_SOURCE_DIR}/assets/demo
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  embed(${PROJECT_NAME} "${CMAKE_BINARY_DIR}/bundle.zip" "/bundle.zip")
endif()

configure_file(${CMAKE_SOURCE_DIR}/assets/index.html ${CMAKE_BINARY_DIR}/index.html COPYONLY)

# target_link_libraries(${PROJECT_NAME} duktape::duktape)
# target_link_libraries(${PROJECT_NAME} ffmpeg::avcodec)
# target_link_libraries(${PROJECT_NAME} ffmpeg::avformat)
# target_link_libraries(${PROJECT_NAME} ffmpeg::avutil)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} avif)
target_link_libraries(${PROJECT_NAME} CURL::libcurl)
# target_link_libraries(${PROJECT_NAME} mimalloc-static)
# target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
# target_link_libraries(${PROJECT_NAME} OpenAL::OpenAL)
target_link_libraries(${PROJECT_NAME} physfs-static)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2main)
target_link_libraries(${PROJECT_NAME} sol2::sol2)
# target_link_libraries(${PROJECT_NAME} SQLite::SQLite3)
# target_link_libraries(${PROJECT_NAME} libzmq-static)
# target_link_libraries(${PROJECT_NAME} zstd::libzstd_static)
