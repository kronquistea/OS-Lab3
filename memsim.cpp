// Created by Erik Kronquist on 11/13/2025

#include <array>
#include <vector>
#include <list>
#include <algorithm>

/// @brief Exectues the FIFO page replacement algorithm
/// @param frameSize Frame size specified by the user through the parameter list.
/// @param references All integer values that were provided through the input file provided by the user.
/// @return array<float, 5> pageFaultRates
std::vector<float> fifo(int frameSize, std::array<int, 10000> references) {
    std::vector<float> pageFaultRates;
    std::list<int> currentPages;
    int enteredPages = 0;
    int pageFaults = 0;

    // Start looping through all provided references
    for (int i = 0; i < references.size(); ++i) {
        // If the reference is not found in the list of pages in the table, page fault will occur
        if (std::find(currentPages.begin(), currentPages.end(), references[i]) != currentPages.end()) {
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
        if (i % 2000 == 0 && i > 0) {
            pageFaultRates.push_back(pageFaults / (float)i);

        }
    }

    // Push the 10,000th page fault rate into the page fault rate vector
    pageFaultRates.push_back(pageFaults / references.size());

    return pageFaultRates;
}