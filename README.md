# C++ Modules Example
This repository is meant as an example on how to dynamically load a variable number of dynamic libs in C++ and use them as modules.
It is not to be used as a example on how to secure loading and handling of the modules. This aspect was not regarded while implementing this quick example.

## Building
Required tools:
- CMake
- Make
- C++ compiler supporting C++ 17 or higher

If you have those, run the following command after `cd`ing into root of this project:
```bash
mkdir build && cd build
cmake ..
make -j8
```

## Usage
Simply enter yout build folder and run the cppmods executable.
```bash
./cppmods
```
You will be prompted with an option of two commands:
- "update" (u)
- "quit" (q)
