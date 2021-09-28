# HydrusCXXPatch [![Release](https://github.com/KJNeko/HydrusCXXPatch/actions/workflows/cmake.yml/badge.svg)](https://github.com/KJNeko/HydrusCXXPatch/actions/workflows/cmake.yml)
A Patch for Hydrus to accelerate the program using CBindings in python.

# ***I am not responsible for any lost data or damage to your database***
 - ***Patch will always be non-distructive and can be removed at any time*** 
 - ***Currently will only work with the raw hydrus source. Fix for that sometime soon***

The patch will be expected to work on any system and follow my specification for writing code with my compile flags. Throughly tested and punched in the face a bunch of times in order to ensure it sticks with the expected working parameters of hydrus. Deviation from the expected working parameters of hydrus is **NOT** an option.



## Modes of the patch
  - Mode 1: Speeds up existing code
  - Mode 2: Speeds up exsiting code and adds other features.

## Patch goals:
  - [ ] Accelerates file import times by speeding up the Mime data generation
  - [ ] PTR import
  - [ ] Thumbnail Generation
  - [ ] Duplicate Detection (Rather fast, Low on the priority list)
  
## Additional features
  - [ ] Adding a histogram method for the duplicate detection

## How to build
##### Requirements:
  1. CMake
  2. GCC Compiler
  3. Make
  4. Python

##### Source:
 Run cmake from the root directory and move the contents of *patch* into the hydrus root directory next to client.py. Run PatchedClient.py through python

##### Binary (Windows only due to pyinstaller issues with linux and cbindings)
 Same as source but rename PatchedClient.py to client.py and build with pyinstaller (Follow the hydrus guide for this, I recomend running from source though)
