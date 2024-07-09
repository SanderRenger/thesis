//
// Created by sander on 12/03/2024.
//

#ifndef THESIS_TIMEDATA_H
#define THESIS_TIMEDATA_H
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "npy.hpp"
struct TimeData_bs2 {
    std::vector<unsigned char> x;
    std::vector<unsigned char> y;
    std::vector<unsigned char> p;
    std::vector<unsigned long long> ts1;
    std::vector<unsigned long long> ts2;
    std::vector<unsigned long long> ts3;
    std::vector<unsigned long long> ts;
};
struct TimeData_npy {
    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> p;
    std::vector<int> ts1;
    std::vector<int> ts2;
    std::vector<int> ts3;
    std::vector<int> ts;
};
TimeData_npy Read_Ndataset_bs2(const std::string& filename);
TimeData_npy Read_Ndataset_npy(const std::string& filename);
#endif //THESIS_TIMEDATA_H