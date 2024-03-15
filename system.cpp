//
// Created by sander on 28/09/2023.
//
#include <vector>
#include <array>
#include <iostream>
#include "system.h"
NeuralNetwork::NeuralNetwork(){
    Neurons_total = 0;
    NeuronList;
    NeuronClusters;
}

void NeuralNetwork::AddCluster(){
    NeuronCluster temp;
    NeuronClusters.push_back(temp);
}

vector<tuple<int, int, vector<int>,int>> NeuralNetwork::getNeuronList() {
    return NeuronList;
}

vector<tuple<int,STint>> NeuralNetwork::ActivateNeuron(int NeuronNumber, int current_time) {
    STint temp1;
    vector<tuple<int,STint>> temp2;
    int Neuroncluster = get<1>(NeuronList[NeuronNumber]);
    vector<int> Outputs = get<2>(NeuronList[NeuronNumber]);
    int delay = get<3>(NeuronList[NeuronNumber]);
    for (int i =0; i < Outputs.size();i++) {
        //cout << "cluster\t" << i << endl;
        temp1= NeuronClusters[get<1>(NeuronList[Outputs[i]])].ActivateNeuronInput(Outputs[i],NeuronNumber,current_time);
        if (!temp1.get_bool()){
            //cout << "outputs\t=" << Outputs[i] << "delay\t"<< delay << endl;
               temp2.push_back({Outputs[i],temp1.add_constant(delay)});
        }
    }
    return temp2;
}
vector<array<int,2>> NeuralNetwork::Getallclusters(){
    vector<array<int,2>> temp;
    for(int i=0; i<NeuronClusters.size();i++){
        temp.push_back({i,NeuronClusters[i].GetGammafrequency()});
    }
    return temp;
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

bool NeuralNetwork::UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<int> outputConnections_t) {
    for(int i =0;i<NeuronList.size();i++){
        if (NeuronNumber_t==get<0>(NeuronList[i])){
            NeuronClusters[get<1>(NeuronList[i])].UpdateNeuron(NeuronNumber_t,threshold_t,inputConnections);
             get<2>(NeuronList[i])=outputConnections_t;
            return true;
        }
    }
    return false;
}


void NeuralNetwork::UpdateThreshold(int NeuronNumber_t, double threshold_t) {

    for(int i =0;i<NeuronList.size();i++){
        if (NeuronNumber_t==get<0>(NeuronList[i])){
            NeuronClusters[get<1>(NeuronList[i])].UpdateThreshold(NeuronNumber_t,threshold_t);
        }
    }
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
        NeuronList.push_back({Neurons_total-1,ClusterNumber,{},0});
        NeuronClusters[ClusterNumber].AddEmptyNeuron(Neurons_total-1);
        return true;
    }
    return false;
}

bool NeuralNetwork::AddNeuron(int ClusterNumber, int threshold_t,vector<tuple<int,double,STint>> inputConnections,vector<int> outputConnections_t){
    if(NeuronClusters.size() >= ClusterNumber){
        Neurons_total +=1;
        NeuronList.push_back({Neurons_total,ClusterNumber,{0},0});
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

int NeuralNetwork::GetGammafrequency(int ClusterNumber) {
    if(NeuronClusters.size() >= ClusterNumber) {
        int temp = NeuronClusters[ClusterNumber].GetGammafrequency();
        return temp;
    }
    return 0;
};

void NeuralNetwork::GammaCycle(int Cluster) {
    if(NeuronClusters.size() >= Cluster) {
        NeuronClusters[Cluster].DoGammaCycle();
    }

};
// Output, Input, Delay,weight
bool NeuralNetwork::Addconnection(int NeuronNumber_1, int NeuronNumber_2, int Delay,double weight_t) {
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
    get<2>(NeuronList[output]).push_back(NeuronNumber_2);
    get<3>(NeuronList[output]) = Delay;
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
            cout << "\tOutput:\t" << (j) << endl;
        }
    }
    cout << endl;
    return true;
};

vector<NeuronCluster> NeuralNetwork::GetSystem() {
        return NeuronClusters;
};
int NeuralNetwork::TotalNeurons() {
    return Neurons_total;
}

tuple<int, int,vector<int>,int> NeuralNetwork::GetNeuron(int NeuronNumber) {
    for (int i=0; i < Neurons_total; i++){
        if (NeuronNumber == get<0>(NeuronList[i])) {
            return NeuronList[i];
        }
    }
}
double NeuralNetwork::GetWeight(int Cluster, int Neuron, int Input) {
    return NeuronClusters[Cluster].GetWeight(Neuron, Input);
}

double NeuralNetwork::GetThreshold(int Cluster, int Neuron) {
    return NeuronClusters[Cluster].GetThreshold(Neuron);
}
int NeuralNetwork::GetCluster(int Neuron){
    return get<1>(NeuronList[Neuron]);
}

void NeuralNetwork::UpdateWeightdataset(string filename1,string filename2) {
    std::string path {filename1};
    npy::npy_data d = npy::read_npy<double>(path);

    std::vector<double> data = d.data;
    std::vector<unsigned long> shape = d.shape;
    int rows = d.shape[1];
    int sizelayer1 = rows;
    cout << sizelayer1 << endl;
       for (int i=0;i<data.size();i++){
            NeuronClusters[1].UpdateWeightDataset(int(i/rows),i%rows,data[i]);
    }
    path = filename2;
    d = npy::read_npy<double>(path);

    data = d.data;
       rows = d.shape[1];
    cout << rows << endl;
    cout << data.size() << endl;
    for (int i=0;i<data.size();i++){
        NeuronClusters[2].UpdateWeightDataset(int(i/rows),i%rows+sizelayer1,data[i]);
    }
}
