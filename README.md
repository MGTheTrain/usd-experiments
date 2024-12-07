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

## Getting started

### Preconditions

- Download and install [CMake from the official website](https://cmake.org/download/)  or trough a package manager
- Install a C++ compiler on your operating system. For example, on Ubuntu Linux use `sudo apt install -y build-essential` to install the `gcc` and `g++` compilers; on Windows, the `cl.exe` compiler is included with the [Visual Studio IDE](https://visualstudio.microsoft.com/vs/); and on macOS, `clang` and `clang++` compilers are installed with the Xcode IDE, which can be downloaded from the Apple Store
- For Windows and Linux systems, it is recommended to [download the pre-built libraries and tools of OpenUSD](https://developer.nvidia.com/usd#section-getting-started) due to time-consuming and resource-intensive [OpenUSD CMake builds](https://github.com/PixarAnimationStudios/OpenUSD). 
Unzip the folder, e.g. `usd.py311.windows-x86_64.usdview.release-0.24.11-4d81dd85`, rename it to `OpenUSD` and move it to the [third-party folder](./third-party/). On macOS 12.0 (Monterey) and greater versions pre-built OpenUSD CLI tools (e.g. `usdcat`)  should already be pre-installed
- Add git submodules: `git subdmodule update --init`

### Generating usda or usdc files from glTF files

The [data folder](data) can be utilized for storing USD/A/C/Z files. Run:

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
./third-party/vcpkg/vcpkg install --allow-unsupported
# Unable to use the `-DCMAKE_TOOLCHAIN_FILE` option because of build errors as the `--allow-unsupported` flag is not available in the subsequent `cmake` command
cmake -B build -DCMAKE_BUILD_TYPE=Release .
cmake --build build --parallel --config Release
./build/apps/openusd-parser/openusd-parser <path to usdc or usda file>
```

#### Windows OS

Run: 

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release .
cmake --build build --parallel --config Release
```

#### Linux Ubuntu OS

Run: 

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release .
cmake --build build --parallel --config Release
```