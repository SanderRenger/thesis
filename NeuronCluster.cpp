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
    NeuronNumbers.push_back(1);
    Neuron Neuron;
    Neurons.push_back(Neuron);
}

NeuronCluster::NeuronCluster(vector<Neuron> Neurons_t, int Gammafrequency_t){
    Neuroncount_cluster += Neurons_t.size();
    Gammafrequency = Gammafrequency_t;
    for(int i =0; i<Neurons_t.size();i++){
        NeuronNumbers.push_back(i);
        Neurons.push_back(Neurons_t[i]);
    }
}
int NeuronCluster::Neuroncount(){
    return Neuroncount_cluster;
}
vector<int> NeuronCluster::GetNeurons(){
    vector<int> temp;
    for(int i =0;i<Neuroncount_cluster;i++){
        temp.push_back(NeuronNumbers[i]);
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
bool NeuronCluster::AddEmptyNeuron(int NeuronNumber){
    Neuroncount_cluster +=1;
    NeuronNumbers.push_back(NeuronNumber);
    Neuron temp;
    Neurons.push_back(temp);
    Neurons[Neuroncount_cluster-1].UpdateNeuronNumber(NeuronNumber);
    return true;
}

bool NeuronCluster::RemoveNeuron(int NeuronNumber){
    bool temp = false;
    for(int i=0; i<Neuroncount_cluster;i++){
        if (NeuronNumbers[i] == NeuronNumber){
            Neurons.erase(Neurons.begin()+i);
            temp = true;
        };
    };
    Neuroncount_cluster -=1;
    return temp;
}
// NeuronNumber, threshold,
bool NeuronCluster::UpdateNeuron(int NeuronNumber_t,int threshold_t,vector<tuple<int,double,STint>> inputConnections){
    for(int i=0; i<Neuroncount_cluster;i++){
        if (NeuronNumbers[i] == NeuronNumber_t){

            Neurons[i].UpdateNeuronInputs(inputConnections);
            //Neurons[i].UpdateNeuronOutputs(outputConnections_t);
            Neurons[i].UpdateNeuronThreshold(threshold_t);
            return true;
            };
    };
    return false;
};


bool NeuronCluster::ChangeGammafrequency(int Gammafrequency_t){
    Gammafrequency = Gammafrequency;
    return true;
};

bool NeuronCluster::RunCluster(){
    bool temp= false;
    for (int i=0;i<Neuroncount_cluster;i++){
        temp = Neurons[i].output();
    }
    return temp;
};

bool NeuronCluster::AddNeuronInput(int NeuronNumber_1, int NeuronNumber_2, int weight_t) {
    for(int i=0; i<Neuroncount_cluster;i++){
        if (NeuronNumbers[i] == NeuronNumber_2){
            Neurons[i].AddNeuronInput(NeuronNumber_1, weight_t);
            return true;
        };
    };
    return false;
}
bool NeuronCluster::printNeuronInformation(int NeuronNumber){
        for(int i=0; i<Neuroncount_cluster;i++){
            if (NeuronNumbers[i] == NeuronNumber){
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