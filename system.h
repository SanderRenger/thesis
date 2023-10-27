//
// Created by sander on 28/09/2023.
//

#ifndef THESIS_NEURONLIST_H
#define THESIS_NEURONLIST_H
#include "NeuronCluster.h"
#include <vector>
#include <tuple>
#include <array>
class NeuralNetwork {
private:
    int Neurons_total;
    vector<tuple<int, int,vector<array<int,2>>>> NeuronList; //NeuronNumber,ClusterNumber,Outputs(NeuronNumber,Delay)
    vector<NeuronCluster> NeuronClusters;
public:
    NeuralNetwork();
    vector<tuple<int, int,vector<array<int,2>>>> getNeuronList();
    bool DeleteNeuron(int NeuronNumber);
    bool DeleteNeuron(int NeuronNumber, int ClusterNumber);
    bool AddNeuron(int ClusterNumber);
    bool AddNeuron(int ClusterNumber, int threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<array<int,2>> outputConnections_t);
    bool UpdateNeuron(int NeuronNumber_t,int threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<array<int,2>> outputConnections_t);
    bool UpdateGammaFrequency(int ClusterNumber,int Gammafrequency);
    bool Printclusterinformation(int clusternumber);
    bool PrintNeuronList();
    bool Addconnection(int NeuronNumber_1, int NeuronNumber_2, int Delay,double weight_t);
    vector<tuple<int,STint>> ActivateNeuron(int NeuronNumber, int current_time);
};


#endif //THESIS_NEURONLIST_H
