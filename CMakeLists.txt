cmake_minimum_required(VERSION 3.20)

project(carimbo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL2_MAIN SDL2::SDL2main)

find_package(libavif CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Ogg CONFIG REQUIRED)
find_package(PhysFS CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(Vorbis REQUIRED)

file(GLOB HEADER_FILES "src/*.hpp")
file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${HEADER_FILES})

option(SANDBOX "Use sandbox" OFF)

if(SANDBOX)
  add_definitions(-DSANDBOX)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  target_link_libraries(${PROJECT_NAME} "--profiling")
  target_link_libraries(${PROJECT_NAME} "-s RUNTIME_DEBUG")
  target_link_libraries(${PROJECT_NAME} "-s ASSERTIONS=1")
  target_link_libraries(${PROJECT_NAME} "-s NO_DISABLE_EXCEPTION_CATCHING")

  target_link_libraries(${PROJECT_NAME} "-s ALLOW_MEMORY_GROWTH=1")
  # target_link_libraries(${PROJECT_NAME} "-s FORCE_FILESYSTEM=1")
  target_link_libraries(${PROJECT_NAME} "-s INITIAL_MEMORY=134217728")
  target_link_libraries(${PROJECT_NAME} "-s EXPORTED_RUNTIME_METHODS=['callMain']")

  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -Og -g)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
  if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /Od /Zi)
  else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -O0 -g)
  endif()
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
  if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /O3 /GL)
  else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -O3 -flto)
  endif()
endif()

configure_file(${CMAKE_SOURCE_DIR}/assets/index.html ${CMAKE_BINARY_DIR}/index.html COPYONLY)

target_link_libraries(${PROJECT_NAME} avif)
target_link_libraries(${PROJECT_NAME} CURL::libcurl)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} Ogg::ogg)
target_link_libraries(${PROJECT_NAME} physfs-static)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2main)
target_link_libraries(${PROJECT_NAME} sol2::sol2)
target_link_libraries(${PROJECT_NAME} vorbis::vorbis)
