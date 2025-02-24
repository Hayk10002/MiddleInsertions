# MiddleInsertions

## Table of Contents
- [Introduction](#introduction)
- [Build and Run](#build-and-run)
- [Possible Output](#possible-output)
- [What is Faster](#what-is-faster)

## Introduction
The purpose of this project is to provide a detailed comparison between finding the middle of and inserting an element in the middle of `std::vector` and `std::list` in C++.

## Build and Run
To clone and run this project, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/Hayk10002/MiddleInsertions

# Go into the repository
$ cd MiddleInsertions

# We need to generate the executable in Release configuration to be able to observe the time difference between std::list and std::vector

# Generate the build files
$ cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

# Build the project
$ cmake --build build --config Release
```

Then, run the executable generated in the `build` directory.

## Possible Output

```
Enter number count: 100000 

         |  Advance  |  Insert  |   Sum   
---------|-----------|----------|---------
Vector   |        2ms|     205ms|    207ms
---------|-----------|----------|---------
List     |    11783ms|      16ms|  11800ms
```

## What is Faster
In this project, we observe that finding the middle of `std::vector` is blazingly fast (well, it's one simple addition), compared to finding the middle of `std::list` where we need to jump from node to node until arriving at the spot. In contrast, inserting in `std::vector` is slower than inserting in `std::list` because the right half of the vector needs to be shifted every time, but inserting into a list is only two assignments (more or less). The main objective of this project is to show that the shifting process of `std::vector` far outperforms the cost of finding the right place in `std::list`, and so the overall time is very favorable towards `std::vector`.
