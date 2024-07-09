//
// Created by sander on 19/05/2024.
//

#ifndef THESIS_FILEREADERBIN_H
#define THESIS_FILEREADERBIN_H
#include <iostream>
#include <fstream>
#include <string>
#include "system.h"
#include "npy.hpp"
void filewriterbin(string filename, NeuralNetwork& Simulation);
void filereaderbin(string filename, NeuralNetwork& Simulation);
void filereaderbinnew(string filename, NeuralNetwork& Simulation);
#endif //THESIS_FILEREADERBIN_H
