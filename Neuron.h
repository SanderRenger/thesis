//
// Created by sander on 27/09/2023.
//

#ifndef THESIS_NEURON_H
#define THESIS_NEURON_H
using namespace std;
#include <iostream>
#include "STint.h"
#include <vector>

class Neuron {
public:
    Neuron(int gammafrequency_t, double threshold_t,vector<tuple<int,double,STint>> Connections_t);
    Neuron();
    bool output();
    bool UpdateNeuronInputSpiketime(int Neuronnumber, STint spiketime);
    bool UpdateNeuronInputWeight(int Neuronnumber,int Weights);
    void AddNeuronInput(int Neuronnumber);
    bool RemoveNeuronInput(int Neuronnumber);
    bool printNeuronInformation();
    bool UpdateNeuronNumber(int NeuronNumber_t);
    int GetNeuronNumber();
private:
    int NeuronNumber;
    STint outputspiketime;
    int gammafrequency;
    double threshold;
    int Numinputs;
    vector<tuple<int,double,STint>> Connections; //Neuronnumber,weights,inputspiketime

};


#endif //THESIS_NEURON_H
