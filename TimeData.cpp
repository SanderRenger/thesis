//
// Created by sander on 12/03/2024.
//
#include <iostream>
#include "TimeData.h"
TimeData Read_Ndataset(const std::string& filename) {
    TimeData TD;
    std::ifstream eventData(filename, std::ios::binary);
    if (!eventData.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return TD;
    }

    eventData.seekg(0, std::ios::end);
    std::streampos fileSize = eventData.tellg();
    eventData.seekg(0, std::ios::beg);

    std::vector<char> evtStream(fileSize);
    eventData.read(evtStream.data(), fileSize);
    eventData.close();

    int numEvents = fileSize / 5; // Assuming each event is 5 bytes
    //numEvents=1;
    for (int i = 0; i <numEvents; ++i) {
        TD.x.push_back((evtStream[i * 5]));
        TD.y.push_back((evtStream[i * 5 + 1]));
        unsigned char p = evtStream[i*5+2];
        TD.p.push_back((p>>7)+1);
        unsigned char ts1=evtStream[i*5+2];
        unsigned char ts2=evtStream[i*5+3];
        unsigned char ts3=evtStream[i*5+4];
        TD.ts1.push_back(((ts1)&127)<<16);
        TD.ts2.push_back((ts2)<<8);
        TD.ts3.push_back(ts3);
        TD.ts.push_back((TD.ts1.back()+TD.ts2.back()+TD.ts3.back())/1000);
        //std::cout << sizeof(evtStream[i]) << std::endl;
        //std::cout << "X: "<< int(TD.x[i]) << "\tY: " << int(TD.y[i]) << "\tP: " << int(TD.p[i]) << std::endl;
    };

    return TD;
}