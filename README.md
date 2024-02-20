# OpenGL C Example

OpenGL C Example is a simple program demonstrating basic modern, core OpenGL 3.3 with CMake 3.5 using the C89 programming language.

This program contains commonly used libraries GLFW, GLAD, and STB.

Requires git and CMake 3.5 or later to build.

<img alt="opengl-c-example.gif" src="https://github.com/jagger-harris/opengl-c-example/assets/78388435/fe03cc18-cf6e-4fdf-87ed-2fa5580d4aa0" width="640" height="360">

## Dependencies
* CMake 3.5 or greater
* OpenGL 3.3 or higher supported graphics card and drivers
* C89 compiler

## Compiling and Running
Clone the repository:
```shell
git clone https://github.com/jagger-harris/opengl-c-example.git
cd opengl-c-example
git submodule init
git submodule update
```

Using provided build script:
```shell
./build.sh build run
```

Without build script:
```shell
mkdir build
cd build
cmake ..
make
./executable
```

## Contributing
See the contributing guidelines [here](docs/CONTRIBUTING.md).

## License
- [ISC](https://choosealicense.com/licenses/isc/)
