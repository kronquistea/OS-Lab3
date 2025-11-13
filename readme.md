## Overview
This is a project containing one program. This program is called memsim. It will run all three page replacement algorithms (FIFO, LRU, OPT) and output their results into the supplied output file.

## Compilation and Usage
### Compilation
Run `make` to compile the program.
 - The compiled files will be compiled into `memsim`.

Run `make clean` to remove the executable file.
### Usage
Run `./memsim [page/frame size] [input file name] [output file name]`.

Full usage example: `./memsim 128 pg-reference pg-output`.