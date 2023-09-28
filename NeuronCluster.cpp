//
// Created by sander on 28/09/2023.
//
#include <vector>
#include <array>
#include "NeuronCluster.h"
#include "global.h"
NeuronCluster::NeuronCluster(){
    Neuroncount_cluster = 1;
    Gammafrequency =100;
    NeuronNumbers.push_back({1,0});
    Neuron Neuron;
    Neurons.push_back(Neuron);
}

NeuronCluster::NeuronCluster(vector<Neuron> Neurons_t, int Gammafrequency_t){
    Neuroncount_cluster += Neurons_t.size();
    Gammafrequency = Gammafrequency_t;
    for(int i =0; i<Neurons_t.size();i++){
        NeuronNumbers.push_back({i,0});
        Neurons.push_back(Neurons_t[i]);
    }
}
int NeuronCluster::Neuroncount(){
    return Neuroncount_cluster;
}
vector<int> NeuronCluster::GetNeurons(){
    vector<int> temp;
    for(int i =0;i<Neuroncount_cluster;i++){
        temp.push_back(NeuronNumbers[i][0]);
    }
    return temp;
}



bool NeuronCluster::UpdateNeuronNumber(int NeuronNumber_t, int NeuronPosition){
    for(int i=0; i<Neuroncount_cluster+1;i++){
        if (Neurons[i].GetNeuronNumber()==NeuronNumber_t){
            return false;
        }
    }
    Neurons[NeuronPosition].UpdateNeuronNumber(NeuronNumber_t);
    return true;
}
bool NeuronCluster::AddEmptyNeuron(){
    Neuroncount_cluster +=1;
    NeuronNumbers.push_back({Neuroncount_cluster,0});
    Neuron temp;
    Neurons.push_back(temp);
    Neurons[Neuroncount_cluster-1].UpdateNeuronNumber(Neuroncount_cluster);
    return true;
}

bool NeuronCluster::RemoveNeuron(int NeuronNumber){
    bool temp = false;
    Neuroncount_cluster -=1;
    for(int i=0; i<Neuroncount_cluster;i++){
        if (NeuronNumbers[i][0] == NeuronNumber){
            Neurons.erase(Neurons.begin()+i);
            temp = true;
        }
    }
    return temp;
}

bool NeuronCluster::ChangeGammafrequency(int Gammafrequency_t){
    Gammafrequency = Gammafrequency;
    return true;
}

bool NeuronCluster::RunCluster(){
    bool temp= false;
    for (int i=0;i<Neuroncount_cluster;i++){
        temp = Neurons[i].output();
    }
    return temp;
}

bool NeuronCluster::printNeuronInformation(int NeuronNumber){
        for(int i=0; i<Neuroncount_cluster;i++){
            if (NeuronNumbers[i][0] == NeuronNumber){
                Neurons[i].printNeuronInformation();
                return true;
            }
        }
        return false;
};

bool NeuronCluster::printAllNeuronInformation(){
    for(int i=0; i<Neuroncount_cluster;i++){
            Neurons[i].printNeuronInformation();
            cout <<"--------------------------------------------------------" << endl;
    }
    return true;
};

//bool NeuronCluster::StandardCluster9Neurons(){};