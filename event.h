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
#include <math.h>
#include "TimeData.h"
#include "TimeData.h"
class event {
private:
    int neuronNumber;
    double delay;
    int strength;
public:
    int getneuronNumber();
    int getdelay();
    void lowerdelay();
    event();
    event(int nn,int d);
    int geteventid();
    void increasestrength();
    int getstrength();
};

class EventHandler{
private:
    vector<event> eventqueue;
    vector<event> newqueue;
    vector<event> newnewqueue;
    int total_events;
    int newqueuesize;
    int queuesize;
    array<int,10> output;
    int layer;
    int append;
public:
    EventHandler();
    void printqueuesize();
    void addgammaevents(NeuralNetwork &NNetwork);
    void addEvent(const event& event_t);
    void handleEvents(NeuralNetwork &NNetwork,int current_time);
    void printqueue();
    void printqueuetofiletxt(string filename);
    void printqueuetofilenpy(string filename);
    void printnewqueue();
    void swapqueue();
    void swapnewqueue();
    bool empty();
    void createevents(string filename, array<int,2> format);
    void printoutput();
    bool isempty();
    int saveoutput();

};


#endif //THESIS_EVENT_H
