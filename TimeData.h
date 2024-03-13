//
// Created by sander on 12/03/2024.
//

#ifndef THESIS_TIMEDATA_H
#define THESIS_TIMEDATA_H
#include <iostream>
#include <fstream>
#include <vector>

struct TimeData {
    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> p;
    std::vector<long long> ts;
};
TimeData Read_Ndataset(const std::string& filename);
#endif //THESIS_TIMEDATA_H