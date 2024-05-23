//
// Created by sander on 28/09/2023.
//

#ifndef THESIS_NEURONCLUSTER_H
#define THESIS_NEURONCLUSTER_H
#include "Neuron.h"
#include <format>
#include <vector>
#include <sstream>
#include <filesystem>

class NeuronCluster {
public:
    NeuronCluster(vector<Neuron> Neurons_t, int Gammafrequency_t);
    NeuronCluster();
    bool AddNeuron(Neuron Neuron, int NeuronNumber);
    bool AddEmptyNeuron(int NeuronNumber);
    bool RemoveNeuron(int NeuronNumber);
    bool ChangeGammafrequency(int Gammafrequency_t);
    bool printNeuronInformation(int NeuronNumber);
    bool printAllNeuronInformation();
    bool AddNeuronInput(int NeuronNumber_1, int NeuronNumber_2, double weight_t);
    bool UpdateNeuronNumber(int NeuronNumber_t, int NeuronPosition);
    bool UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint>> inputConnections);
    void UpdateThreshold(int NeuronNumber_t,double threshold_t);
    void setfired(int Neuron, int current_time);
    void ActivateNeuronInput(int NeuronNumber, int NeuronInput, int current_time);
    STint Output(int NeuronNumber, int current_time);
    vector<int> GetNeurons();
    int Neuroncount();
    int GetGammafrequency();
    void DoGammaCycle();
    int GetNeuroncount();
    double GetWeight(int Neuron, int Input);
    vector<vector<double>> GetWeights();
    double GetThreshold(int Neuron);
    void GetVoltage(int Cluster);
    void UpdateWeightDataset(int Neuron_in, int Neuron_out,double Weight);
private:
    int Neuroncount_cluster;
    int Gammafrequency;
    vector<int> NeuronNumbers;
    vector<Neuron> Neurons;
    bool Gammareset;
};


#endif //THESIS_NEURONCLUSTER_H
