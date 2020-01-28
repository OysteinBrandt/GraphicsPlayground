# Welcome! :space_invader:
* This is a hobby project for 2D and 3D graphics
* Current implementation is closely tied to [OpenGL](https://www.opengl.org/)
* The engine is platform independent
* I/O is partially implemented for Windows ([src](code/Editor/win32_Editor.cpp))
* I/O is not implemented for Linux

## Build
The project uses [CMake](https://cmake.org/ "CMake's homepage") as build tool. Once installed you can you can follow the [guide](https://cmake.org/runningcmake/) or run `cmake --help` to get started.

## Preprocessor Definitions

- define `ENGINE_DEBUG=1` if you want asserts enabled in engine
- define `ENGINE_DLL=1` if you want to build engine as a .dll
- define `ENGINE_DLL_EXPORT=1` if you want to _export_ functionality from engine .dll
  - Otherwise, if `ENGINE_DLL_EXPORT` is not defined and `ENGINE_DLL` is defined, _import_ will implicitly be defined

### Specified in CMake files
Note! These can be out of sync. Check `CmakeLists.txt` for actual value.
#### Engine (all build configs)
- `ENGINE_DEBUG=1` (default)
- `ENGINE_DLL=1` (default)
- `ENGINE_DLL_EXPORT=1` (default)

#### Editor (all build configs)
- `ENGINE_DEBUG=1` (default)
- `ENGINE_DLL=1` (default)

#### EngineTest (all build configs)
- `ENGINE_DLL=1` (default)