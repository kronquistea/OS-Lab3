// Created by Erik Kronquist on 11/13/2025

#pragma once

#include <array>
#include <vector>
#include <fstream>

void writeToFile(std::ofstream& fout, int pageFaults, std::vector<float> pageFaultRates);

void fifo(int frameSize, std::array<int, 10000> references, std::ofstream& fout);