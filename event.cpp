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

EventHandler::EventHandler() {
    total_events=0;
    queuesize=0;
    for(int & i : output){
        i = 0;
    }
}

void EventHandler::addgammaevents(NeuralNetwork &NNetwork){
    vector<array<int,2>> temp;
    temp = NNetwork.Getallclusters();
    //cout << temp.size();
    for(int i=0;i<temp.size();i++){
        eventqueue.push_back({MAXNEURON+i,get<1>(temp[i])});
    }
}

void EventHandler::handleEvents(NeuralNetwork &NNetwork, int current_time) {
    while (!eventqueue.empty()) {
        vector<tuple<int,STint>> temp;

        if (eventqueue.back().getdelay() != 0) {
            event temp = eventqueue.back();
            temp.lowerdelay();
            newqueue.push_back(temp);
            eventqueue.pop_back();
        }
        else {
            int eventnumber = eventqueue.back().getneuronNumber();
            if (eventnumber>=MAXNEURON){

                int cluster = eventnumber - MAXNEURON;
                NNetwork.GammaCycle(cluster);
                newqueue.push_back({eventnumber,NNetwork.GetGammafrequency(cluster)-1});
                eventqueue.pop_back();
                //cout << "Gammacycle event:\t" << cluster << "\ttime:\t" << current_time << endl;
            }
            else{
              event current_neuron = eventqueue.back();
              NNetwork.setfired(NNetwork.GetCluster(current_neuron.getneuronNumber()),current_neuron.getneuronNumber());
              for (int i = 0; i < eventqueue.size() - 1; i++) {
                  if ((current_neuron.getneuronNumber() == eventqueue[i].getneuronNumber()) &&current_neuron.getneuronNumber()>= 34*34*2) {
                      eventqueue.erase(eventqueue.begin() + i);
                      queuesize--;
                  }
               }

                temp = NNetwork.ActivateNeuron(current_neuron.getneuronNumber(), current_time);

                for (int i = 0; i < temp.size(); i++) {
                    queuesize++;
                    newqueue.push_back({get<0>(temp[i]), get<1>(temp[i]).get_int()});
                }
                total_events++;
                eventqueue.pop_back();
                queuesize--;

                if (current_neuron.getneuronNumber()>(34*34*2+512)){
//                    cout << "Neuron:\t" << current_neuron.getneuronNumber();
//                    cout << "\tin layer: " <<3<< " Fired\t";
//                    cout << queuesize << " events left" << endl;
                    output[current_neuron.getneuronNumber()-(34*34*2+512)]++;
                }
//                else if (current_neuron.getneuronNumber()>34*34*2){
//                    //cout << "Neuron:\t" << current_neuron.getneuronNumber();
//                    //cout << "\tin layer: " <<2<< " Fired\t";
//                    //cout << queuesize << " events left" << endl;
//                }
//                else {
//                    //cout << "\tin layer:" <<1<< " Fired\t" << endl;
//                }
//
//
//
//                if (total_events%100==0){
//                    //eventqueue.clear();
//                    //newqueue.clear();
//                    cout << "total events: " << total_events<< endl;
//                }
            }



        }
    }
}
void EventHandler::printqueuesize() {
    cout << "queue size:\t" << eventqueue.size() << endl;
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

void EventHandler::createevents(string filename, array<int,2> format) {
    TimeData TD = Read_Ndataset(filename);

    for(int i =0;i<TD.x.size();i++){
        event event_t = {(TD.x[i]+TD.y[i]*format[1])+((34*34)*(TD.p[i]-1)),static_cast<int>(TD.ts[i])};
        eventqueue.push_back(event_t);
        //cout << event_t.getneuronNumber() << endl;
        queuesize++;
        //std::cout << "X: "<< int(TD.x[i]) << "\tY: " << int(TD.y[i]) << "\tP: " << int(TD.p[i]) <<"\tT: " << static_cast<int>(TD.ts[i]) << std::endl;
    }
    //cout << "done loading the input data" << endl;
}

void EventHandler::printoutput(){
    for(int i = 0; i<output.size();i++){
        cout << "Output:\t" << output[i] << endl;
    }
}
int EventHandler::saveoutput(){
    int max = 0;
    int out = 0;
    for(int i = 0; i<output.size();i++){
        if (output[i] > max){
            max = output[i];
            out = i;
        }
    }
    return out;
}

bool EventHandler::isempty(){
    return eventqueue.empty();

}