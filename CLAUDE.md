# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a C++ game development project called "SuperStar" - a 2D shooting game built with a custom engine architecture. The project uses a modular plugin system with the HobbyEngine core and various HobbyPlugin modules.

## Architecture

### Core Components
- **HobbyEngine**: Core engine providing fundamental systems (math, memory, tasks, modules)
- **HobbyPlugin**: Modular plugin system with specialized functionality:
  - Platform: SDL2-based platform abstraction
  - Render: Rendering system
  - Actor: Entity/actor management
  - AssetManager: Asset loading (JSON, TOML, XML, binary)
  - Level: Level/scene management
  - Localization: Multi-language support
  - EnhancedInput: Input handling
  - Event: Event system
  - Lua: Lua scripting integration
  - RHI: Render Hardware Interface
- **Game**: Application-specific game logic

### Build System
Uses CMake with a hierarchical configuration system. Each plugin has its own Config.cmake that gets included in the main CMakeLists.txt.

## Common Commands

### Building
```bash
# Generate Visual Studio 2022 project
ProjBuild.bat

# Clean build artifacts
ProjClean.bat
```
After running ProjBuild.bat, open `Build/ProjMSVC2022_x64_mt/SuperStar.sln` in Visual Studio 2022.

### Testing
Tests use Google Test framework. Unit test executables are built alongside main projects.
Test executables are output to `Bin/Test/[CONFIG]/` directory.

### Code Formatting
```bash
# Format all code in the project
CodeCleanup.bat

# Format specific directory
HobbyEngine\Script\CodeCleanup\CodeCleanup.bat [directory_path]
```
Uses clang-format with project-specific rules. Excludes ThirdParty directories to avoid license issues.

### Module Creation
```bash
# Create new plugin module
HobbyEngine\Script\Generater\CreateModule\CreateModule.bat
```
New modules should be created in the HobbyPlugin directory.

## Coding Conventions

### Naming
- Files/directories: PascalCase (e.g., TaskManager.cpp)
- Classes: PascalCase with HE:: namespace for engine types
- Methods: PascalCase, private/protected methods prefixed with `_`
- Virtual methods: Prefixed with `V` (e.g., VProcess())
- Enums: Prefixed with `E`, elements prefixed with enum name (e.g., EState_Active)
- Macros: ALL_CAPS, engine macros prefixed with `HE_`

### Hungarian Notation
Variable prefixes indicate type:
- `i`/`u`: signed/unsigned 32-bit integers
- `il`/`ul`: signed/unsigned 64-bit integers
- `f`/`d`: float/double
- `b`: boolean
- `sz`: strings
- `p`: pointers
- `a`: arrays
- `v`: vectors
- `m`: maps
- `_`: class member variables

### Class Rules
- Always use virtual destructors for base classes
- Mark non-inheritable classes as `final`
- Override methods must call parent implementation
- Use `this->` for member variable access
- Never manually call destructors

### File Organization
- Third-party code goes in ThirdParty directories (excluded from formatting)
- Each plugin has Inc/, Src/, and Test/ subdirectories
- Header files should not include third-party headers (include in .cpp only)

## Development Environment
- Windows with Visual Studio 2022
- CMake 3.26+
- vcpkg for dependency management
- C++17 standard