//
// Created by sander on 12/03/2024.
//

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

    for (int i = 0; i < numEvents; ++i) {
        TD.x.push_back((evtStream[i * 5]) + 1);
        TD.y.push_back((evtStream[(i * 5) + 1]) + 1);
        TD.p.push_back((((evtStream[i * 5 + 2] >> 7) & 1) + 1));
        TD.ts.push_back((((evtStream[i * 5 + 2]) & 127) << 16));
        TD.ts.back() += ((evtStream[i * 5 + 3]) << 8);
        TD.ts.back() += (evtStream[i * 5 + 4]);
    }

    return TD;
}