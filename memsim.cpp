// Created by Erik Kronquist on 11/13/2025

#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
    using std::cout;
#include <set>
#include "memsim.h"

/// @brief Exectues the FIFO page replacement algorithm
/// @param frameSize Frame size specified by the user through the parameter list.
/// @param references All integer values that were provided through the input file provided by the user.
/// @param fout Output file to write to
void fifo(int frameSize, std::vector<int> references, std::ofstream& fout) {
    std::vector<double> pageFaultRates;
    std::list<int> currentPages;
    int pageFaults = 0;

    // cout << "Before FIFO for loop\n";

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
            // cout << "Segmentation Fault not yet occured!\n";
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
    pageFaultRates[4] << "\n";
}

/// @brief Least Recently Used algorithm
/// @param frameSize Frame size specified by the user through the parameter list
/// @param references All integer values that were provided through the input file
/// @param fout Output file to write to
void lru(int frameSize, std::vector<int> references, std::ofstream& fout) {
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

    fout << "LRU\t" << pageFaults << "\t" << 
    pageFaultRates[0] << "\t" <<
    pageFaultRates[1] << "\t" <<
    pageFaultRates[2] << "\t" <<
    pageFaultRates[3] << "\t" <<
    pageFaultRates[4] << "\n";
}

void optimal(int frameSize, std::vector<int> references, std::ofstream& fout) {
    std::vector<double> pageFaultRates;
    std::vector<int> currentPages;
    std::vector<int> temp(frameSize, -1);
    int pageFaults = 0;
    int positionToReplace = -1;
    bool noFutureReferenceFlag = false;

    // Start looping through all provided references
    for (int i = 0; i < references.size(); ++i) {
        // If the reference is not found in the list of pages in the table, page fault will occur
        if (std::find(currentPages.begin(), currentPages.end(), references[i]) == currentPages.end()) {
            // If the list is full, erase the item furthest away from the current index
            if (currentPages.size() >= frameSize) {
                // Find and store items which are present in currentPages and in the future references into a temp vector
                for (int j = 0; j < currentPages.size(); ++j) {
                    for (int k = i + 1; k < currentPages.size(); ++k) {
                        // Check if 
                        if (currentPages[j] == references[k]) {
                            temp[j] = k;
                        }
                    }
                }

                // If any item is in currentPages but not in future references, that item should be the one replaced
                for (int j = 0; j < frameSize; ++j) {
                    if (temp[j] == -1) {
                        positionToReplace = j;
                        noFutureReferenceFlag = true;
                        break;
                    }
                }

                // If all items have future refernces, find whichever one is furthest away and replace that one
                if(!noFutureReferenceFlag) {
                    // Default value is no further one is found
                    int max = temp[0];
                    positionToReplace = 0;
                    
                    // Find the value that is furthest away - defined by whichever "k" value is largest (index in references)
                    for (int j = 0; j < frameSize; ++j) {
                        if (temp[j] > max) {
                            max = temp[j];
                            positionToReplace = j;
                        }
                    }
                }

                currentPages[positionToReplace] = references[i];
            }
            // Add the new item to the back
            else {
                currentPages.push_back(references[i]);
            }
            pageFaults++;
        }

        // If i is evenly divisible by 2000, add the calculated page fault rate for all concurrent page faults to the page fault rate vector
        if (i > 0 && i % 2000 == 0 ) {
            pageFaultRates.push_back(static_cast<double>(pageFaults) / i);
        }
    }

    // Push the 10,000th page fault rate into the page fault rate vector
    pageFaultRates.push_back(static_cast<double>(pageFaults) / references.size());

    fout << "OPTIMAL\t" << pageFaults << "\t" << 
    pageFaultRates[0] << "\t" <<
    pageFaultRates[1] << "\t" <<
    pageFaultRates[2] << "\t" <<
    pageFaultRates[3] << "\t" <<
    pageFaultRates[4] << "\n";
}