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
    Neuron(int NeuronNumber_t, double threshold_t,vector<tuple<int,double,STint>> inputConnections_t);
    Neuron();
    void spike(int current_time,int Gammafrequency,int neuroninput);
    STint output(int current_time);
    int UpdateNeuronInputSpiketime(int Neuronnumber, int current_time);
    bool UpdateNeuronInputWeight(int Neuronnumber,double Weights);
    void AddNeuronInput(int Neuronnumber, double weight);
    bool RemoveNeuronInput(int Neuronnumber);
    void UpdateNeuronThreshold(double threshold_t);
    void UpdateNeuronInputs(vector<tuple<int,double,STint>> inputConnections_t);
    void UpdateNeuronOutputs(vector<array<int,2>> outputConnections_t);
    bool printNeuronInformation();
    bool UpdateNeuronNumber(int NeuronNumber_t);
    int GetNeuronNumber();
    double GetWeight(int Input);
    vector<double> GetWeights();
    double GetThreshold();
    int InputconnectionsSize();
    int OutputconnectionsSize();
    void GammaCycle(bool Gammareset,int Gammafrequency);
    void GetVoltage(const string& filename);
    void setfired(int current_time);

private:
    vector<double> spiketrains;
    int has_fired{};
    bool out{};
    int NeuronNumber;
    STint outputspiketime;
    double threshold;
    vector<tuple<int,double,STint>> inputConnections; //Neuronnumber,weights,inputspiketime
};


#endif //THESIS_NEURON_H
