# Simulation

A small C++ terrain-rendering prototype built with SFML 2.5.1 and FastNoiseLite. It explores generating a tile map from noise and displaying it in a desktop window.

The current program generates one 60 × 60 map with a fixed seed. Perlin fractal noise is classified into water, sand, and grass, then rendered using 16-pixel tiles. The map is drawn to a render texture once and displayed in the window loop. Closing the window exits the program.

## Project layout

- `VisualStudio/Simulation/Main.cpp`: window creation, map settings, and render loop.
- `TerrainGenerator.cpp`: noise sampling, terrain classification, and tile rendering.
- `AssetManager.cpp`: texture cache keyed by filename.
- `EventManager.cpp`: window-close event handling.
- `Prey.h` and `Prey.cpp`: unfinished entity scaffold; no movement, needs, or ecological interactions are implemented.
- `Textures/Environment/`: terrain images, including the three textures used by the program.
- `SFML-2.5.1/`: bundled headers, Windows libraries, and upstream documentation.

Source filenames above are under `VisualStudio/Simulation/` unless a directory is given.

## Build and run on Windows

Use Visual Studio 2022 with Desktop development with C++, the MSVC v143 toolset, and a Windows 10 SDK. The project has no package-manager setup or application CMake build.

1. Open `VisualStudio/Simulation/Simulation.sln`.
2. Select **Debug / x86** in the solution. This maps to the project's **Debug / Win32** configuration, which defines `SFML_STATIC` and lists the static debug libraries.
3. In that project's properties, replace the existing absolute SFML paths with:
   - **C/C++ → General → Additional Include Directories:** `$(ProjectDir)..\..\SFML-2.5.1\include`
   - **Linker → General → Additional Library Directories:** `$(ProjectDir)..\..\SFML-2.5.1\lib`
4. Ensure the SFML libraries match the selected x86 architecture and compiler/runtime. If the bundled binaries are incompatible, obtain or build a matching SFML 2.5.1 package and point these settings to it.
5. Set **Debugging → Working Directory** to `$(ProjectDir)..\..` so relative `Textures/Environment/...` paths resolve from the repository root.
6. Build and start the project in Visual Studio.

After correcting the paths, the equivalent build command from a Visual Studio Developer PowerShell at the repository root is:

```powershell
msbuild .\VisualStudio\Simulation\Simulation.sln /p:Configuration=Debug /p:Platform=x86
```

The project also links SFML audio/network and their listed dependencies, although the application code currently uses graphics/window/system functionality. The x64 configurations lack SFML settings; Release/Win32 lists static libraries but does not define `SFML_STATIC`, so those configurations need additional setup.

## Configuration and limitations

Change the map dimensions and seed in `Main.cpp` and rebuild to generate a different map. Keep the dimensions square: the noise-generation loops currently interchange width and height, so rectangular maps are unreliable. Render-texture dimensions are also passed in reversed window order, which can clip the terrain on some displays.

There are no runtime generation controls, camera controls, save/load functions, or active simulation entities. Texture-loading and render-texture creation failures are not handled. No automated test suite or CI workflow is included; a basic manual check is to launch the program from the repository root, confirm the terrain is visible, and close the window.

## Dependencies and licensing

SFML is third-party software by Laurent Gomila and contributors; retain its [license notice](SFML-2.5.1/license.md), including the external-library notices. FastNoiseLite is third-party noise-generation code by Jordan Peck and contributors, distributed under the MIT notice embedded in `VisualStudio/Simulation/FastNoiseLite.h`.

The repository does not include a project-wide license for the application code or explicit provenance/license documentation for the terrain textures. Dependency licenses should not be interpreted as licensing the rest of this repository.
