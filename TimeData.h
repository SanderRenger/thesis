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
struct TimeData {
    std::vector<unsigned char> x;
    std::vector<unsigned char> y;
    std::vector<unsigned char> p;
    std::vector<unsigned long long> ts1;
    std::vector<unsigned long long> ts2;
    std::vector<unsigned long long> ts3;
    std::vector<unsigned long long> ts;
};
TimeData Read_Ndataset(const std::string& filename);
#endif //THESIS_TIMEDATA_H