// Created by Erik Kronquist on 11/13/2025

#pragma once

#include <vector>
#include <fstream>

void fifo(int frameSize, std::vector<int> references, std::ofstream& fout);

void lru(int frameSize, std::vector<int> references, std::ofstream& fout);

void optimal(int framesize, std::vector<int> references, std::ofstream& fout);