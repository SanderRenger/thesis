//
// Created by sander on 28/09/2023.
//

#ifndef THESIS_NEURONCLUSTER_H
#define THESIS_NEURONCLUSTER_H
#include "Neuron.h"
#include <vector>

class NeuronCluster {
public:
    NeuronCluster(vector<Neuron> Neurons_t, int Gammafrequency_t);
    NeuronCluster();
    bool AddNeuron(Neuron Neuron);
    bool AddEmptyNeuron();
    bool RemoveNeuron(int NeuronNumber);
    bool ChangeGammafrequency(int Gammafrequency_t);
    bool RunCluster();
    bool printNeuronInformation(int NeuronNumber);
    bool printAllNeuronInformation();
    bool UpdateNeuronNumber(int NeuronNumber_t, int NeuronPosition);
    bool UpdateNeuron(int NeuronNumber_t,int threshold,vector<int>,vector<double>,vector<STint>);
    vector<int> GetNeurons();
    int Neuroncount();
private:
    int Neuroncount_cluster;
    int Gammafrequency;
    vector<array<int,2>> NeuronNumbers;
    vector<Neuron> Neurons;
};


#endif //THESIS_NEURONCLUSTER_H
