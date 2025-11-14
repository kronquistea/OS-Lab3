// Created by Erik Kronquist on 11/13/2025

#include <iostream>
    using std::cout;
#include <fstream>
#include <array>
#include "memsim.h"

/// @brief Sets up and executes required functionality for the entire program but not for the actual page replacement algorithms.
/// @param argc Number of parameters
/// @param argv Parameters
/// @return Exit Code 0 if success, exit code 1 if failure
int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage:\n./memsim <page/frame size> <input file> <output file>\n";
        return 1;
    }

    int frameSize = atoi(argv[1]);
    const char* inputFile = argv[2];
    const char* outputFile = argv[3];

    std::ifstream fin(inputFile);
    if(!fin) {
        cout << "Error: cannot open input file.\n";
        return 1;
    }

    /** Next Steps
     *  1. Call FIFO page replacement algorithm - do this for the specified frame size that was sent in by the user.
     *      a. Receive the page fault rates as an array of floats.
     *      b. There will be 5 total entires in this returned array, where the first entry (index 0) is the page fault rate for the first 2000 references, and so on.
     *      c. These 5 entries will be extracted and written into the specified output file that was given by the user.
     *  2. Call LRU page replacement algorithm - do this for the specified frame size that was sent in by the user.
     *      a. Do the same thing as for FIFO but now with LRU
     *  3. Call OPT page replacement algorithm - do this for the specified frame size that was sent in by the user.
     *      a. Do the same thing as for FIFO but now with OPT
     */

    std::array<int, 10000> references;
    int value;
    int i = 0;
    while(fin >> value) {
        references[i] = value;
        i++;
    }

    fin.close();
    
    std::ofstream fout(outputFile);
    fout << "===============================\n";
    fout << "\tPage Replacement Algorithm Simulation (Frame Size = " << frameSize << ")\n";
    fout << "===============================\n";
    fout << "\t\t\tPage Fault Rates\n";
    fout << "Algorithm\tTotal Page Faults\t2000\t4000\t6000\t8000\t10000\n";
    fout << "-------------------------------\n";

    fifo(frameSize, references, fout);

    fout.close();

    return 0;
}   