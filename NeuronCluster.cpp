//
// Created by sander on 28/09/2023.
//
#include <vector>
#include <array>
#include <format>
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

bool NeuronCluster::AddNeuron(Neuron Neuron, int NeuronNumber){
    Neuroncount_cluster +=1;
    NeuronNumbers.push_back(NeuronNumber);
    Neurons.push_back(Neuron);
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
bool NeuronCluster::UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint,int>> inputConnections){
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
        for(int j=0; j<Neurons[i].InputconnectionsSize();j++){
            if (Neurons[i].GetNeuronNumber() == NeuronNumber){
                Neurons[i].printNeuronInformation();
                return true;
            }
        }
    };
    return false;
}
void NeuronCluster::printNeuronInformationInputs(int NeuronNumber){
    for(int i=0; i<Neuroncount_cluster;i++){
        if (Neurons[i].hasConnection(NeuronNumber)){
            Neurons[i].printNeuronInformation();
        }
    }
};

bool NeuronCluster::printAllNeuronInformation(){
    for(int i=0; i<Neuroncount_cluster;i++){
            Neurons[i].printNeuronInformation();
            cout <<"--------------------------------------------------------" << endl;
    }
    return true;
};

void NeuronCluster::printAllNeuronInformation(int neuronnumber){
        Neurons[neuronnumber].printNeuronInformation();
        cout <<"--------------------------------------------------------" << endl;
};

void NeuronCluster::ActivateNeuronInput(vector<int> NeuronNumbers_temp, int Neuroninput, int current_time, int strength) {
    int temp;

    for (int i=0; i<NeuronNumbers.size();i++) {
       for(int j=0; j<NeuronNumbers_temp.size();j++){
            if (NeuronNumbers[i] == NeuronNumbers_temp[j]){
                //cout << "Neuroninput:\t" << Neuroninput << endl;
                temp =Neurons[i].UpdateNeuronInputSpiketime(Neuroninput,current_time,strength);
                //cout << "temp:\t" << temp << endl;
                Neurons[i].spike(current_time, 10,temp);
            }
        }
    }
};

STint NeuronCluster::Output(int NeuronNumber, int current_time) {
    STint temp1;
    for (int i=0; i<Neurons.size();i++) {
        //cout << NeuronNumber<< endl;
        if (NeuronNumbers[i] == NeuronNumber){
            //cout << "time"<< current_time%Gammafrequency << endl;

            temp1= Neurons[i].output(current_time);
            if (!temp1.get_bool()){
                temp1 = {(temp1.get_int()-current_time),false};
                //cout << "hi" << endl;
            }
            return temp1;
        }
    }
    return {0,true};
};

//bool NeuronCluster::StandardCluster9Neurons(){};

double NeuronCluster::GetWeight(int Neuron, int Input) {
    for(int i =0; i < Neuroncount_cluster; i++){
        if (Neuron == NeuronNumbers[i]){
            return Neurons[i].GetWeight(Input);
        }
    }
    return 0;
}

vector<vector<double>> NeuronCluster::GetWeights() {
    vector<vector<double>> temp;
    for(int i =0; i < Neuroncount_cluster; i++){
            temp.push_back(Neurons[i].GetWeights());
    }
    return temp;
}

double NeuronCluster::GetThreshold(int Neuron) {
    for(int i =0; i < Neuroncount_cluster; i++){
        if (Neuron == NeuronNumbers[i]){
            return Neurons[i].GetThreshold();
        }
    }
    return 0;
}

void NeuronCluster::GetVoltage(int Cluster) {
    std::ostringstream directory;
    directory << "test2/Cluster"<<Cluster;
    namespace fs = std::filesystem;
    fs::create_directories(directory.str());
    //cout << Neuroncount_cluster<<endl;
    for(int i =0; i < Neuroncount_cluster; i++){
        std::ostringstream filename;
        filename << "test2/Cluster"<<Cluster<<"/"<<"Neuron"<<i<<".npy";
        Neurons[i].GetVoltage(filename.str());
        }
    }


void NeuronCluster::setfired(int Neuron,int current_time) {
    for(int i =0; i < Neuroncount_cluster; i++){
        if (Neuron == NeuronNumbers[i]){
            Neurons[i].setfired(current_time);
        }
    }
}
void NeuronCluster::UpdateWeightDataset(int Neuron_in, int Neuron_out,double Weight){
            Neurons[Neuron_in].UpdateNeuronInputWeight(Neuron_out,Weight);
}

int NeuronCluster::GetNeuroncount() {
    return NeuronNumbers.size();
}

