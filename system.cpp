//
// Created by sander on 28/09/2023.
//
#include <vector>
#include <array>
#include "system.h"
NeuralNetwork::NeuralNetwork(){
    Neurons_total = 1;
    NeuronList.push_back(Neurons_total);
    NeuronCluster NeuronCluster;
    NeuronClusters.push_back(NeuronCluster);
}

bool NeuralNetwork::DeleteNeuron(int NeuronNumber){
    vector<int> temp;
    for(int i=0;i<NeuronClusters.size();i++){
        temp = NeuronClusters[i].GetNeurons();
        for(int j=0;j<NeuronClusters[i].Neuroncount();j++){
            if(temp[j] == NeuronNumber){
                NeuronClusters[i].RemoveNeuron(j);
                for(int k=0;k<NeuronList.size();k++){
                    if(NeuronList[k]== NeuronNumber) {
                        NeuronList.erase(NeuronList.begin()+k);
                    }
                }
                return true;
            }

        }
    }
    return false;
};

bool NeuralNetwork::Printclusterinformation(int clusternumber){
    NeuronClusters[clusternumber].printAllNeuronInformation();
    return true;
}