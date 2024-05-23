//
// Created by sander on 28/09/2023.
//

#ifndef THESIS_NEURONLIST_H
#define THESIS_NEURONLIST_H
#include "NeuronCluster.h"
#include <vector>
#include <tuple>
#include <array>
#include "npy.hpp"
inline extern const int DELAY = 1;
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
    void AddNeuron(int ClusterNumber,const Neuron& Neuron);
    bool AddNeuron(int ClusterNumber, int threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<int> outputConnections_t);
    bool UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<int> outputConnections_t);
    bool UpdateGammaFrequency(int ClusterNumber,int Gammafrequency);
    void UpdateThreshold(int NeuronNumber_t,double threshold_t);
    bool Printclusterinformation(int clusternumber);
    void Printneuroninformation(int NeuronNumber);
    void PrintNeuronList();
    void PrintNeuronList(int ClusterNumber);
    bool Addconnection(int NeuronNumber_1, int NeuronNumber_2, int Delay,double weight_t);
    void ActivateNeuron(int NeuronNumber, int current_time);
    vector<tuple<int,STint>> Output(int current_time);
    vector<NeuronCluster> GetSystem();
    int GetCluster(int Neuron);
    tuple<int, int,vector<int>,int> GetNeuron (int NeuronNumber);
    int GetGammafrequency(int ClusterNumber);
    void GammaCycle(int Cluster);
    void AddCluster();
    int TotalNeurons();
    vector<array<int,2>> Getallclusters();
    double GetWeight(int Cluster, int Neuron, int Input);
    vector<vector<vector<double>>> GetWeights();
    double GetThreshold(int Cluster, int Neuron);
    void UpdateWeightdataset(string filename1,string filename2);
    void PrintNeuronVoltagetofile(int Cluster);
    void setfired(int cluster, int neuron, int current_time);
    void MakeNeuronListFullConnected(vector<int> shape);


};



#endif //THESIS_NEURONLIST_H
