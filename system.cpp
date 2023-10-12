//
// Created by sander on 28/09/2023.
//
#include <vector>
#include <array>
#include "system.h"
NeuralNetwork::NeuralNetwork(){
    Neurons_total = 1;
    NeuronList.push_back({Neurons_total,0,{{0,0}}});
    NeuronCluster NeuronCluster;
    NeuronClusters.push_back(NeuronCluster);
}

bool NeuralNetwork::DeleteNeuron(int NeuronNumber){
    vector<int> temp;
    for(int i=0;i<NeuronList.size();i++){
        if(get<0>(NeuronList[i])==NeuronNumber){
            NeuronClusters[get<1>(NeuronList[i])].RemoveNeuron(NeuronNumber);
            NeuronList.erase(NeuronList.begin()+i);
            return true;
        };
    }
    return false;
};

bool NeuralNetwork::UpdateNeuron(int NeuronNumber_t,int threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<array<int,2>> outputConnections_t) {
    for(int i =0;i<NeuronList.size();i++){
        if (NeuronNumber_t==get<0>(NeuronList[i])){
            NeuronClusters[get<1>(NeuronList[i])].UpdateNeuron(NeuronNumber_t,threshold_t,inputConnections);
             get<2>(NeuronList[i])=outputConnections_t;
            return true;
        }
    }
    return false;
}

bool NeuralNetwork::DeleteNeuron(int NeuronNumber, int ClusterNumber){
    vector<int> temp;
        temp = NeuronClusters[ClusterNumber].GetNeurons();
        for(int j=0;j<NeuronClusters[ClusterNumber].Neuroncount();j++){
            if(temp[j] == NeuronNumber){
                NeuronClusters[ClusterNumber].RemoveNeuron(j);
                for(int k=0;k<NeuronList.size();k++){
                    if(get<0>(NeuronList[k])== NeuronNumber) {
                        NeuronList.erase(NeuronList.begin()+k);
                    }
                }
                return true;
            }

        }
    return false;
};

bool NeuralNetwork::AddNeuron(int ClusterNumber){
    if(NeuronClusters.size() >= ClusterNumber){
        Neurons_total +=1;
        NeuronList.push_back({Neurons_total,ClusterNumber,{{0,0}}});
        NeuronClusters[ClusterNumber].AddEmptyNeuron(Neurons_total);
        return true;
    }
    return false;
}

bool NeuralNetwork::AddNeuron(int ClusterNumber, int threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<array<int,2>> outputConnections_t){
    if(NeuronClusters.size() >= ClusterNumber){
        Neurons_total +=1;
        NeuronList.push_back({Neurons_total,ClusterNumber,{{0,0}}});
        NeuronClusters[ClusterNumber].AddEmptyNeuron(Neurons_total);
    }
    else {
        return false;
    }
    for(int i =0;i<NeuronList.size();i++){
        if (Neurons_total==get<0>(NeuronList[i])){
            NeuronClusters[get<1>(NeuronList[i])].UpdateNeuron(Neurons_total,threshold_t,inputConnections);
            get<2>(NeuronList[i])=outputConnections_t;
            return true;
        }
    }
    return false;
}
bool NeuralNetwork::UpdateGammaFrequency(int ClusterNumber,int Gammafrequency){
    if(NeuronClusters.size() >= ClusterNumber) {
        NeuronClusters[ClusterNumber].ChangeGammafrequency(Gammafrequency);
        return true;
    }
    return false;
};
// Output, Input, Delay
bool NeuralNetwork::Addconnection(int NeuronNumber_1, int NeuronNumber_2, int Delay,int weight_t) {
    int temp =0;
    bool temp2=false;
    int output;
    int input;
    int cluster;
    for(int i=0;i<NeuronList.size();i++){
        if (get<0>(NeuronList[i])==NeuronNumber_1){
            output = i;
            temp++;
            if (temp==2){
                temp2 = true;
                break;
            }
        }
        if (get<0>(NeuronList[i])==NeuronNumber_2){

            cluster = get<1>(NeuronList[i]);
            temp++;
            if (temp==2){
                temp2 = true;
                break;
            }
        }
    }
    get<2>(NeuronList[output]).push_back({NeuronNumber_2,Delay});
    NeuronClusters[cluster].AddNeuronInput(NeuronNumber_1, NeuronNumber_2, weight_t);
    return temp2;
}

bool NeuralNetwork::Printclusterinformation(int clusternumber){
    NeuronClusters[clusternumber].printAllNeuronInformation();
    return true;
}

bool NeuralNetwork::PrintNeuronList(){
    cout << "Neurons: \t\t\t\t\t" << NeuronList.size() << endl << endl;
    cout << "Highest Neuron Number: \t\t\t\t"<< Neurons_total<<endl <<endl;

    cout << "Neurons Information: \t" << endl;
    for (auto & i : NeuronList){
        cout << "Neuron:\t"<<get<0>(i)<<"\tCluster\t" << get<1>(i)<<endl;
        for(auto & j : get<2>(i)){
            cout << "\tOutput:\t" << (j[0]) << "\tDelay\t" << j[1] << endl;
        }
    }
    cout << endl;
    return true;
}