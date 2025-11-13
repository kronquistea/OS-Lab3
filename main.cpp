// Created by Erik Kronquist on 11/13/2025

#include <iostream>
    using std::cout;
#include <fstream>

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

    fin.close();

    return 0;
}