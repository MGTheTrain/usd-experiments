# usd-experiments

## Table of Contents

- [Summary](#summary)
- [References](#references)
- [Getting started](#getting-started)

## Summary

Experimenting with C++ libraries capable of parsing USD files

## References

- [USD file format](https://docs.fileformat.com/3d/usd/)
- [OpenUSD Github repository](https://github.com/PixarAnimationStudios/OpenUSD)
- [tinyusdz Github repository](https://github.com/lighttransport/tinyusdz/tree/dev)
- [OpenUSD - Converting Between Layer Formats](https://openusd.org/docs/Converting-Between-Layer-Formats.html#ConvertingBetweenLayerFormats-Convertingbetween.usdaand.usdcFiles)
- [Download Pre-Built OpenUSD Libraries and Tools](https://developer.nvidia.com/usd#section-getting-started)
- [A really small getting-started project for USD based projects](https://github.com/meshula/tinyusd)
- [OpenUSD sample files for download](https://openusd.org/release/dl_downloads.html)

## Getting started

### Preconditions

- Download and install [CMake from the official website](https://cmake.org/download/)  or trough a package manager
- Install a C++ compiler on your operating system. For example, on Ubuntu Linux use `sudo apt install -y build-essential` to install the `gcc` and `g++` compilers; on Windows, the `cl.exe` compiler is included with the [Visual Studio IDE](https://visualstudio.microsoft.com/vs/); and on macOS, `clang` and `clang++` compilers are installed with the Xcode IDE, which can be downloaded from the Apple Store
- Add git submodules: `git subdmodule update --init`

### Generating usda or usdc files from glTF files

To generate USD files from glTF files, you can either [download the pre-built OpenUSD libraries and tools](https://developer.nvidia.com/usd#section-getting-started) to use the `usdcat` CLI tool or build the project from GitHub. On macOS 12.0 (Monterey) and later, the pre-built OpenUSD CLI tools, including `usdcat`, should already be installed. The [data folder](data) can be utilized for storing usda or usdc files. Example usage os `usdcat`:

```sh
usdcat <path to gltf file> -o <path to usd file>
# e.g. usdcat third-party/glTF-Sample-Models/2.0/BrainStem/glTF/BrainStem.gltf -o data/BrainStem.usda
# e.g. usdcat third-party/glTF-Sample-Models/2.0/BrainStem/glTF/BrainStem.gltf -o data/BrainStem.usdc
```

### Building application binaries

#### Mac OS

Run: 

```sh
./third-party/vcpkg/bootstrap-vcpkg.sh
./third-party/vcpkg/vcpkg install --allow-unsupported # Initially building USD can be time-consuming and resource-intensive. Packages persist in the vcpkg git submodule
# Unable to use the `-DCMAKE_TOOLCHAIN_FILE` option because of build errors as the `--allow-unsupported` flag is not available in the subsequent `cmake` command
cmake -B build -DCMAKE_BUILD_TYPE=Release .
cmake --build build --parallel --config Release
./build/apps/openusd-parser/openusd-parser <path to usdc or usda file>
```

#### Windows OS

Run: 

```sh
.\third-party\vcpkg\bootstrap-vcpkg.bat
.\third-party\vcpkg\vcpkg install # Initially building USD can be time-consuming and resource-intensive. Packages persist in the vcpkg git submodule
cmake -B build -DCMAKE_BUILD_TYPE=Release . 
cmake --build build --parallel --config Release
.\build\apps\openusd-parser\Release\openusd-parser <path to usdc or usda file>
```

#### Linux Ubuntu OS

Run: 

```sh
./third-party/vcpkg/bootstrap-vcpkg.sh
./third-party/vcpkg/vcpkg install # Initially building USD can be time-consuming and resource-intensive. Packages persist in the vcpkg git submodule
cmake -B build -DCMAKE_BUILD_TYPE=Release .
cmake --build build --parallel --config Release
./build/apps/openusd-parser/openusd-parser <path to usdc or usda file>
```