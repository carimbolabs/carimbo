cmake_minimum_required(VERSION 3.20)

project(carimbo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL2_MAIN SDL2::SDL2main)

find_package(CURL CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Ogg CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(PhysFS CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SPNG CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
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
  target_link_libraries(${PROJECT_NAME} PRIVATE "-s EVAL_CTORS=1")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-s WASM_BIGINT=1")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-s DISABLE_EXCEPTION_CATCHING=1")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-s ALLOW_MEMORY_GROWTH=1")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-s INITIAL_MEMORY=134217728")
  target_link_libraries(${PROJECT_NAME} PRIVATE "-s EXPORTED_RUNTIME_METHODS=['callMain']")
  # target_link_libraries(${PROJECT_NAME} PRIVATE "-s USE_PTHREADS=1" "-pthread")

  # target_link_libraries(${PROJECT_NAME} PRIVATE "--profiling")
  # target_link_libraries(${PROJECT_NAME} PRIVATE "-s RUNTIME_DEBUG")
  # target_link_libraries(${PROJECT_NAME} PRIVATE "-s ASSERTIONS=1")
  # target_link_libraries(${PROJECT_NAME} PRIVATE "-s NO_DISABLE_EXCEPTION_CATCHING")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -O3 -flto)
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

target_link_libraries(${PROJECT_NAME} PRIVATE
  CURL::libcurl
  fmt::fmt
  Ogg::ogg
  physfs-static
  SDL2::SDL2-static
  SDL2::SDL2main
  spng::spng_static
  sol2::sol2
  nlohmann_json::nlohmann_json
  vorbis::vorbis
)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenAL::OpenAL)
endif()
