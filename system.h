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
    vector<tuple<int, int,vector<int>,int>> NeuronList; //NeuronNumber,ClusterNumber,Outputs(NeuronNumber)
    vector<NeuronCluster> NeuronClusters;
public:
    NeuralNetwork();
    vector<tuple<int, int,vector<int>,int>> getNeuronList();
    bool DeleteNeuron(int NeuronNumber);
    bool DeleteNeuron(int NeuronNumber, int ClusterNumber);
    bool AddNeuron(int ClusterNumber);
    bool AddNeuron(int ClusterNumber, int threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<int> outputConnections_t);
    bool UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<int> outputConnections_t);
    bool UpdateGammaFrequency(int ClusterNumber,int Gammafrequency);
    void UpdateThreshold(int NeuronNumber_t,double threshold_t);
    bool Printclusterinformation(int clusternumber);
    bool PrintNeuronList();
    bool Addconnection(int NeuronNumber_1, int NeuronNumber_2, int Delay,double weight_t);
    vector<tuple<int,STint>> ActivateNeuron(int NeuronNumber, int current_time);
    vector<NeuronCluster> GetSystem();
    int GetCluster(int Neuron);
    tuple<int, int,vector<int>,int> GetNeuron (int NeuronNumber);
    int GetGammafrequency(int ClusterNumber);
    void GammaCycle(int Cluster);
    void AddCluster();
    int TotalNeurons();
    vector<array<int,2>> Getallclusters();
    double GetWeight(int Cluster, int Neuron, int Input);
};


#endif //THESIS_NEURONLIST_H
