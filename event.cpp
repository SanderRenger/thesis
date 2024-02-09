//
// Created by sander on 22/10/2023.
//
#include <vector>
#include <array>
#include <tuple>
#include <iostream>

#include "event.h"
const int MAXNEURON = 20000;
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

void EventHandler::addgammaevents(NeuralNetwork &NNetwork){
    vector<array<int,2>> temp;
    temp = NNetwork.Getallclusters();
    //cout << temp.size();
    for(int i=0;i<temp.size();i++){
        eventqueue.push_back({MAXNEURON+i,get<1>(temp[i])-2});
    }
}

void EventHandler::handleEvents(NeuralNetwork &NNetwork, int current_time) {
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
            int eventnumber = eventqueue.back().getneuronNumber();
            if (eventnumber>=MAXNEURON){

                int cluster = eventnumber - MAXNEURON;
                NNetwork.GammaCycle(cluster);
                newqueue.push_back({eventnumber,NNetwork.GetGammafrequency(cluster)});
                eventqueue.pop_back();
                cout << "Gammacycle event:\t" << cluster << "\ttime:\t" << current_time << endl;
            }
            else{event current_neuron = eventqueue.back();
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
                eventqueue.pop_back();}


        }
    }
    if (fired){
        cout<<endl;
    }
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

