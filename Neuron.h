//
// Created by sander on 27/09/2023.
//

#ifndef THESIS_NEURON_H
#define THESIS_NEURON_H
using namespace std;
#include <iostream>
#include "STint.h"
#include <vector>
#include <array>

class Neuron {
public:
    Neuron(int NeuronNumber_t,int gammafrequency_t, double threshold_t,vector<tuple<int,double,STint>> inputConnections_t);
    Neuron();
    STint output(int Gammafrequency);
    bool UpdateNeuronInputSpiketime(int Neuronnumber, int current_time);
    bool UpdateNeuronInputWeight(int Neuronnumber,int Weights);
    void AddNeuronInput(int Neuronnumber, double weight);
    bool RemoveNeuronInput(int Neuronnumber);
    void UpdateNeuronThreshold(double threshold_t);
    void UpdateNeuronInputs(vector<tuple<int,double,STint>> inputConnections_t);
    void UpdateNeuronOutputs(vector<array<int,2>> outputConnections_t);
    bool printNeuronInformation();
    bool UpdateNeuronNumber(int NeuronNumber_t);
    int GetNeuronNumber();
    double GetWeight(int Input);
    int InputconnectionsSize();
    int OutputconnectionsSize();
    void GammaCycle(bool Gammareset,int Gammafrequency);
private:
    int NeuronNumber;
    STint outputspiketime;
    double threshold;
    vector<tuple<int,double,STint>> inputConnections; //Neuronnumber,weights,inputspiketime
};


#endif //THESIS_NEURON_H
