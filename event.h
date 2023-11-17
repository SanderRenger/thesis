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

class event {
private:
    int neuronNumber;
    int delay;
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
public:
    void addgammaevents(NeuralNetwork &NNetwork);
    void addEvent(const event& event_t);
    void handleEvents(NeuralNetwork &NNetwork,int current_time);
    void printqueue();
    void printnewqueue();
    void swapqueue();
    bool empty();


};


#endif //THESIS_EVENT_H
