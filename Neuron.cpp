//
// Created by sander on 27/09/2023.
//

#include "Neuron.h"
#include "global.h"

Neuron::Neuron(int NeuronNumber_t,int gammafrequency_t, double threshold_t,vector<tuple<int,double,STint>> inputConnections_t){
    NeuronNumber = NeuronNumber_t;
    threshold = threshold_t;
    inputConnections = inputConnections_t;
    //outputConnections = outputConnections_t;
    outputspiketime = {0, true};
}
bool Neuron::UpdateNeuronNumber(int NeuronNumber_t) {
    NeuronNumber = NeuronNumber_t;
    return true;
}


int Neuron::GetNeuronNumber(){
    return NeuronNumber;
}

int Neuron::InputconnectionsSize(){
    return inputConnections.size();
}

//int Neuron::OutputconnectionsSize(){
//    return outputConnections.size();
//}
Neuron::Neuron(){
    NeuronNumber = 1;
    threshold = 1;
    inputConnections.push_back({0,0,{0,true}});
    outputspiketime = {0,true};
    //outputConnections.push_back({0,0});
}

bool Neuron::output() {
return true;
}

bool Neuron::UpdateNeuronInputSpiketime(int Neuronnumber, STint spiketime){
    for(int i=0; i<inputConnections.size();i++){
        if (Neuronnumber == get<0>(inputConnections[i]) ){
            get<2>(inputConnections[i])  = spiketime;
            return true;
        }
    }
    return false;
};

void Neuron::AddNeuronInput(int Neuronnumber,int weight){
    inputConnections.push_back({Neuronnumber,weight,{0,true}});
};

void Neuron::UpdateNeuronInputs(vector<tuple<int,double,STint>> inputConnections_t){
    inputConnections = inputConnections_t;
};
//void Neuron::UpdateNeuronOutputs(vector<array<int,2>> outputConnections_t){
//    outputConnections = outputConnections_t;
//};

void Neuron::UpdateNeuronThreshold(double threshold_t) {
    threshold= threshold_t;
};
bool Neuron::RemoveNeuronInput(int Neuronnumber){

    for(int i=0; i<inputConnections.size()+1;i++){
        if (Neuronnumber == get<0>(inputConnections[i])) {
            inputConnections.erase(inputConnections.begin()+i);
            return true;
        }
    }
    return false;
};

bool Neuron::UpdateNeuronInputWeight(int Neuronnumber,int Weights){
    for(int i=0; i<inputConnections.size();i++){
        if (Neuronnumber == get<0>(inputConnections[i])){
            get<1>(inputConnections[i]) = Weights;
            return true;
        }
    }
    return false;
};

bool Neuron::printNeuronInformation(){
    cout << "Neuron: \t\t\t" << NeuronNumber << endl << endl;
    cout << "Threshold: \t\t\t"<< threshold<<endl <<endl;
    cout << "Numinputs: \t\t\t"<<inputConnections.size()<<endl<<endl;
    if (outputspiketime.get_bool()){
        cout << "output spike time: \t\tNo Spike" << endl;
    }
    else {
        cout << "output spike time: \t\t"<<(int) outputspiketime.get_int()  << endl;
    }
    cout << "Input Neurons Information: \t";
    for (int i=0;i<inputConnections.size();i++){
        cout << get<0>(inputConnections[i])<<"\t" << get<1>(inputConnections[i])<<"\t" ;
        if (get<2>(inputConnections[i]).get_bool()){
            cout << "No Spike" << endl << "\t\t\t\t";
        }
        else{
            cout << (int) get<2>(inputConnections[i]).get_int()<< endl<< "\t\t\t\t";
        }
    }
    cout << endl;

return true;
}

