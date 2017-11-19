# C++ libsift {#mainpage}

## Requirements

- C++11 compatible compiler (GCC 4.8.4+, Clang 3.3+, MSVC2015+).
- OpenImageIO
- Boost (for binaries and test).

Travis CI is used to automatically build on Linux and Mac OSX. I assume Windows can work with little to no modifications.

### Ubuntu 14.04+ Setup

- apt-get install libboost-all-dev
- apt-get install openimageio libopenimageio-dev

### Mac OSX Setup  (Homebrew)

- brew install homebrew/science/openimageio
- brew install boost

## Compilation and Installation

Compilation and installation is done using CMake.

```
    mkdir build
    cd build
    cmake ../
    make -jX
    make install
```
### CMake Configuration Options

- BUILD_BINARIES=ON/OFF: Build the executables in the 'src' directory. Default: ON.
- BUILD_TESTS=ON/OFF: Build the tests in the 'tests' directory. Default: ON.
- BUILD_DOCS=ON/OFF: Build the docs with Doxygen. Default: ON.

## Library Usage

## Executable Usage
