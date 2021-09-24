# HydrusCXXPatch
A Patch for Hydrus to accelerate the program using CBindings in python.

***Currently will only work with the raw hydrus source. Fix for that sometime soon***

The patch will be expected to work on any system and follow my specification for writing code with my compile flags. Throughly tested and punched in the face a bunch of times in order to ensure it sticks with the expected working parameters of hydrus. Deviation from the expected working parameters of hydrus is **NOT** an option.

# ***Patch will always be non-distructive and can be removed at any time*** 


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
 
 Run cmake from the root directory and move the contents of build into the hydrus root directory next to client.py
