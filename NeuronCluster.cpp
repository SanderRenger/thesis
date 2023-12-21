//
// Created by sander on 28/09/2023.
//
#include <vector>
#include <array>
#include "NeuronCluster.h"
NeuronCluster::NeuronCluster(){
    Neuroncount_cluster = 0;
    Gammafrequency =100;
    NeuronNumbers;
    Neuron Neuron;
    Neurons;
    Gammareset = true;
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

int NeuronCluster::GetGammafrequency() {
    return Gammafrequency;
}

void NeuronCluster::DoGammaCycle(){
    for(int i =0;i<Neurons.size();i++){
        Neurons[i].GammaCycle(Gammareset,Gammafrequency);
    }
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
bool NeuronCluster::UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint>> inputConnections){
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

void NeuronCluster::UpdateThreshold(int NeuronNumber_t, double threshold_t) {
    for(int i=0; i<Neuroncount_cluster;i++){
        if (NeuronNumbers[i] == NeuronNumber_t){
            Neurons[i].UpdateNeuronThreshold(threshold_t);
        };
    };
};

bool NeuronCluster::ChangeGammafrequency(int Gammafrequency_t){
    Gammafrequency = Gammafrequency_t;
    return true;
};

bool NeuronCluster::AddNeuronInput(int NeuronNumber_1, int NeuronNumber_2, double weight_t) {
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

STint NeuronCluster::ActivateNeuronInput(int NeuronNumber, int Neuroninput, int current_time) {
    STint temp1;
    cout << "Neuroncount in cluster:\t " <<Neuroncount_cluster << endl;
    for (int i=0; i<Neuroncount_cluster;i++) {
        if (NeuronNumbers[i] == NeuronNumber){
            Neurons[i].UpdateNeuronInputSpiketime(Neuroninput,current_time%Gammafrequency);
            temp1= Neurons[i].output(Gammafrequency);
            if (!temp1.get_bool()){
                temp1 = {(temp1.get_int()-current_time%Gammafrequency),false};
            }
            return temp1;
        }
    }
    return {0,true};
};

//bool NeuronCluster::StandardCluster9Neurons(){};