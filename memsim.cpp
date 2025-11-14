// Created by Erik Kronquist on 11/13/2025

#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include "memsim.h"

/// @brief Exectues the FIFO page replacement algorithm
/// @param frameSize Frame size specified by the user through the parameter list.
/// @param references All integer values that were provided through the input file provided by the user.
/// @param fout Output file to write to
void fifo(int frameSize, std::array<int, 10000> references, std::ofstream& fout) {
    std::vector<double> pageFaultRates;
    std::list<int> currentPages;
    int pageFaults = 0; 

    // Start looping through all provided references
    for (int i = 0; i < references.size(); ++i) {
        // If the reference is not found in the list of pages in the table, page fault will occur
        if (std::find(currentPages.begin(), currentPages.end(), references[i]) == currentPages.end()) {
            // If all the pages are full, the oldest one needs to be popped out
            if (currentPages.size() >= frameSize) {
                currentPages.pop_front();
            }
            
            // Push the new page into the table/lists
            currentPages.push_back(references[i]);
            
            pageFaults++;
        }

        // If i is evenly divisible by 2000, add the calculated page fault rate for all concurrent page faults to the page fault rate vector
        if (i > 0 && i % 2000 == 0 ) {
            pageFaultRates.push_back(static_cast<double>(pageFaults) / i);
        }
    }

    // Push the 10,000th page fault rate into the page fault rate vector
    pageFaultRates.push_back(static_cast<double>(pageFaults) / references.size());

    fout << "FIFO\t" << pageFaults << "\t" << 
    pageFaultRates[0] << "\t" <<
    pageFaultRates[1] << "\t" <<
    pageFaultRates[2] << "\t" <<
    pageFaultRates[3] << "\t" <<
    pageFaultRates[4] << std::endl;
}

/// @brief Least Recently Used algorithm
/// @param frameSize Frame size specified by the user through the parameter list
/// @param references All integer values that were provided through the input file
/// @param fout Output file to write to
void lru(int frameSize, std::array<int, 10000> references, std::ofstream& fout) {
    std::vector<double> pageFaultRates;
    std::list<int> currentPages;
    int pageFaults = 0;

    // Start looping through all provided references
    for (int i = 0; i < references.size(); ++i) {
        // If the reference is not found in the list of pages in the table, page fault will occur
        if (std::find(currentPages.begin(), currentPages.end(), references[i]) == currentPages.end()) {
            // If the list is full, pop the front item (least recently used)
            if (currentPages.size() >= frameSize) {
                currentPages.pop_front();
            }

            // Add the new item to the back
            currentPages.push_back(references[i]);
            pageFaults++;
        }
        else {
            // Remove the page from the list
            currentPages.erase(std::find(currentPages.begin(), currentPages.end(), references[i]));
            // Put the page back into the list at the back (so at the end of the day, the least recently used item will be in the front)
            currentPages.push_back(references[i]);
        }

        // If i is evenly divisible by 2000, add the calculated page fault rate for all concurrent page faults to the page fault rate vector
        if (i > 0 && i % 2000 == 0 ) {
            pageFaultRates.push_back(static_cast<double>(pageFaults) / i);
        }
    }

    // Push the 10,000th page fault rate into the page fault rate vector
    pageFaultRates.push_back(static_cast<double>(pageFaults) / references.size());

    fout << "LRU\t\t" << pageFaults << "\t" << 
    pageFaultRates[0] << "\t" <<
    pageFaultRates[1] << "\t" <<
    pageFaultRates[2] << "\t" <<
    pageFaultRates[3] << "\t\t" <<
    pageFaultRates[4] << std::endl;
}