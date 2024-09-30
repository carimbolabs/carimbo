# Carimbo

Carimbo is a simple 2D game engine, scriptable in Lua, created during the spare time of [@skhaz](https://github.com/skhaz).

It is a transcendental descendant of the [Wintermoon](https://github.com/wintermoon/wintermoon) engine, a project by the same author. It runs on Linux, Windows, macOS, and the Web (WebAssembly).

### Build

Python & virtualenv

```shell
uv venv
source .venv/bin/activate
```

Conan & pre-commit hooks

```shell
uv pip install -r requirements.txt
pre-commit install
conan install . --output-folder=build --build=missing
```

CMake build

```shell
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release -DSANDBOX=ON
cmake --build . --parallel 8
```

Run

```shell
# if not in build directory, cd build
./carimbo
```
