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
    bool AddEmptyNeuron(int NeuronNumber);
    bool AddEmptyNeuron(int NeuronNumber, double threshold);
    bool RemoveNeuron(int NeuronNumber);
    bool ChangeGammafrequency(int Gammafrequency_t);
    bool printNeuronInformation(int NeuronNumber);
    bool printAllNeuronInformation();
    bool AddNeuronInput(int NeuronNumber_1, int NeuronNumber_2, double weight_t);
    bool UpdateNeuronNumber(int NeuronNumber_t, int NeuronPosition);
    bool UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint>> inputConnections);
    void UpdateThreshold(int NeuronNumber_t,double threshold_t);
    STint ActivateNeuronInput(int NeuronNumber, int NeuronInput, int current_time);
    vector<int> GetNeurons();
    int Neuroncount();
    int GetGammafrequency();
    void DoGammaCycle();
    double GetWeight(int Neuron, int Input);
    double GetThreshold(int Neuron);
private:
    int Neuroncount_cluster;
    int Gammafrequency;
    vector<int> NeuronNumbers;
    vector<Neuron> Neurons;
    bool Gammareset;
};


#endif //THESIS_NEURONCLUSTER_H
