cmake_minimum_required(VERSION 3.20)

project(carimbo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenAL CONFIG REQUIRED)
find_package(chipmunk2d CONFIG REQUIRED)
find_package(Ogg CONFIG REQUIRED)
find_package(PhysFS CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SPNG CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  # WebSocket++
endif()

file(GLOB HEADER_FILES "src/*.hpp")
file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${HEADER_FILES})

function(set_compile_options target)
  if (CMAKE_BUILD_TYPE MATCHES "Debug")
    if (MSVC)
      target_compile_options(${target} PRIVATE /W4 /Od /Zi)
    else()
      target_compile_options(${target} PRIVATE -Wall -Wextra -Werror -O0 -g)
    endif()
  elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    if (MSVC)
      target_compile_options(${target} PRIVATE /W4 /O2 /GL)
    else()
      target_compile_options(${target} PRIVATE -Wall -Wextra -Werror -pedantic -O3 -flto)
    endif()
  endif()
endfunction()

set_compile_options(${PROJECT_NAME})

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set(EMSCRIPTEN_OPTIONS
    "-s EVAL_CTORS=1"
    "-s WASM_BIGINT=1"
    "-s ALLOW_MEMORY_GROWTH=1"
    "-s PTHREAD_POOL_SIZE=4"
    "-s INITIAL_MEMORY=128MB"
    "-l websocket.js"
    "-s USE_SDL=2"
    "-s WEBSOCKET_SUBPROTOCOL=text"
    "-s EXPORTED_RUNTIME_METHODS=['callMain']"
    # Debugging
    "-s ASSERTIONS=2"
    # "-s RUNTIME_DEBUG"
    "-s NO_DISABLE_EXCEPTION_CATCHING"
  )

  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -O3 -flto)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${EMSCRIPTEN_OPTIONS})
endif()

option(SANDBOX "Use sandbox" OFF)
if(SANDBOX)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DSANDBOX)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
  chipmunk2d::chipmunk2d
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
  target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenAL::OpenAL
    # WebSocket++
  )
endif()

configure_file(${CMAKE_SOURCE_DIR}/assets/index.html ${CMAKE_BINARY_DIR}/index.html COPYONLY)
