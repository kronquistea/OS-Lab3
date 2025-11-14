// Created by Erik Kronquist on 11/13/2025

#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "memsim.h"

/// @brief Writes the analysis to the screen.
/// @param outputFile Output file name
/// @param pageFaults Amount of page faults
/// @param pageFaultRates Page fault rates for the 5 intervals
void writeToFile(std::ofstream& fout, int pageFaults, std::vector<double> pageFaultRates) {
    fout << "FIFO\t" << pageFaults << "\t" << 
    pageFaultRates[0] << "\t" <<
    pageFaultRates[1] << "\t" <<
    pageFaultRates[2] << "\t" <<
    pageFaultRates[3] << "\t" <<
    pageFaultRates[4] << "\n";
}

/// @brief Exectues the FIFO page replacement algorithm
/// @param frameSize Frame size specified by the user through the parameter list.
/// @param references All integer values that were provided through the input file provided by the user.
/// @param outputFile Output file name to write analysis to
/// @return nothing
void fifo(int frameSize, std::array<int, 10000> references, std::ofstream& fout) {
    std::vector<double> pageFaultRates;
    std::list<int> currentPages;
    int enteredPages = 0;
    int pageFaults = 0; 

    // Start looping through all provided references
    for (int i = 0; i < references.size(); ++i) {
        // If the reference is not found in the list of pages in the table, page fault will occur
        if (std::find(currentPages.begin(), currentPages.end(), references[i]) == currentPages.end()) {
            // If all the pages are full, the oldest one needs to be popped out
            if (enteredPages >= frameSize) {
                currentPages.pop_back();
            }
            
            // Push the new page into the table/lists
            currentPages.push_front(references[i]);
            
            // Increase page fault tracker
            pageFaults++;
        }

        // If i is evenly divisible by 2000, add the calculated page fault rate for all concurrent page faults to the page fault rate vector
        if (i > 0 && i % 2000 == 0 ) {
            pageFaultRates.push_back(static_cast<double>(pageFaults) / i);
        }
    }

    // Push the 10,000th page fault rate into the page fault rate vector
    pageFaultRates.push_back(static_cast<double>(pageFaults) / references.size());

    for (int i = 0; i < pageFaultRates.size(); ++i) {
        std::cout << "pageFaultRates[" << i << "]: " << pageFaultRates[i] << "\n";
    }

    writeToFile(fout, pageFaults, pageFaultRates);
}