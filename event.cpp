//
// Created by sander on 22/10/2023.
//
#include <vector>
#include <array>
#include <tuple>
#include <iostream>

#include "event.h"

event::event(){
    delay=0;
    neuronNumber=0;
}

event::event(int nn, int d) {
    delay = d;
    neuronNumber= nn;
}

int event::getneuronNumber(){
    return neuronNumber;
}

int event::getdelay() {
    return delay;
}
void event::lowerdelay() {
    delay--;

}

void EventHandler::addEvent(const event &event_t) {
    eventqueue.push_back(event_t);
}

NeuralNetwork EventHandler::handleEvents(NeuralNetwork NNetwork, int current_time) {
    bool fired= false;
    while (!eventqueue.empty()) {
        vector<tuple<int,STint>> temp;
        if (eventqueue.back().getdelay() != 0) {
            event temp = eventqueue.back();
            temp.lowerdelay();
            newqueue.push_back(temp);
            eventqueue.pop_back();
        }
        else {
            fired = true;
            event current_neuron = eventqueue.back();
            for (int i = 0; i < eventqueue.size() - 1; i++) {
                if (current_neuron.getneuronNumber() == eventqueue[i].getneuronNumber()) {
                    eventqueue.erase(eventqueue.begin() + i);
                }
            }
            cout << "Neuron event:\t" << current_neuron.getneuronNumber() << "\ttime:\t" << current_time << endl;
            temp = NNetwork.ActivateNeuron(current_neuron.getneuronNumber(), current_time);
            for (int i = 0; i < temp.size(); i++) {
                newqueue.push_back({get<0>(temp[i]), get<1>(temp[i]).get_int()});
            }
            eventqueue.pop_back();
        }
    }
    if (fired){
        cout<<endl;
    }
    return NNetwork;
}

void EventHandler::printqueue() {
    cout << "queue:" <<endl;
    for (int i=0; i<eventqueue.size();i++){
        cout << "Neuron:\t"<<(eventqueue[i].getneuronNumber()) <<"\tDelay:\t" <<eventqueue[i].getdelay()<< endl;

    }
    cout << endl;
};

void EventHandler::printnewqueue() {
    cout << "new queue:" <<endl;
    for (int i=0; i<newqueue.size();i++){
        cout << "Neuron:\t"<<(newqueue[i].getneuronNumber()) <<"\tDelay:\t" <<newqueue[i].getdelay()<< endl;

    }
    cout << endl;
};
void EventHandler::swapqueue() {
    eventqueue = newqueue;
    newqueue.clear();
}

bool EventHandler::empty() {
    return eventqueue.empty();
}