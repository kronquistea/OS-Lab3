// Created by Erik Kronquist on 11/13/2025

#include <iostream>
    using std::cout;
#include <fstream>
#include <array>
#include <algorithm>
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

    // cout << "Received arguments\n";

    int frameSize = atoi(argv[1]);
    // cout << "Processed frame size parameter\n";

    const char* inputFile = argv[2];
    // cout << "Processed input file\n";

    const char* outputFile = argv[3];
    // cout << "Processed output file\n";

    std::ifstream fin(inputFile);
    if(!fin) {
        cout << "Error: cannot open input file.\n";
        return 1;
    }

    // cout << "Before processing references\n";
    std::vector<int> references;
    int value;
    int i = 0;
    while(fin >> value) {
        references.push_back(value);
        i++;
    }
    // cout << "After processing references: references.size() =" << references.size() << "\n";

    fin.close();
    
    std::ofstream fout(outputFile);
    fout << "===============================\n";
    fout << "\tPage Replacement Algorithm Simulation (Frame Size = " << frameSize << ")\n";
    fout << "===============================\n";
    fout << "\t\t\tPage Fault Rates\n";
    fout << "Algorithm\tTotal Page Faults\t2000\t4000\t6000\t8000\t10000\n";
    fout << "-------------------------------\n";

    // Test set
    // references = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    // cout << "Before calling fifO()\n";

    fifo(frameSize, references, fout);
    lru(frameSize, references, fout);
    optimal(frameSize, references, fout);

    fout.close();

    return 0;
}   