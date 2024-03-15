//
// Created by sander on 22/10/2023.
//

#ifndef THESIS_EVENT_H
#define THESIS_EVENT_H
#include "NeuronCluster.h"
#include "system.h"
#include <vector>
#include <tuple>
#include <array>
#include "TimeData.h"
#include "TimeData.h"
class event {
private:
    int neuronNumber;
    double delay;
public:
    int getneuronNumber();
    int getdelay();
    void lowerdelay();
    event();
    event(int nn,int d);
};

class EventHandler{
private:
    vector<event> eventqueue;
    vector<event> newqueue;
    int total_events;
    int queuesize;
public:
    EventHandler();
    void addgammaevents(NeuralNetwork &NNetwork);
    void addEvent(const event& event_t);
    void handleEvents(NeuralNetwork &NNetwork,int current_time);
    void printqueue();
    void printnewqueue();
    void swapqueue();
    bool empty();
    void createevents(string filename, array<int,2> format);

};


#endif //THESIS_EVENT_H
