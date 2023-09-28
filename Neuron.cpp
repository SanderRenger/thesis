//
// Created by sander on 27/09/2023.
//

#include "Neuron.h"
#include "global.h"
Neuron::Neuron(int gammafrequency_t, double threshold_t, vector<tuple<int,double,STint>> Connections_t){
    NeuronNumber = 1;
    gammafrequency = gammafrequency_t;
    threshold = threshold_t;
    Numinputs = Connections_t.size();
    Connections = Connections_t;
    outputspiketime = {0, true};
}
bool Neuron::UpdateNeuronNumber(int NeuronNumber_t) {
    NeuronNumber = NeuronNumber_t;
    return true;
}


int Neuron::GetNeuronNumber(){
    return NeuronNumber;
}
Neuron::Neuron(){
    NeuronNumber = 1;
    gammafrequency = 100;
    threshold = 1;
    Numinputs =1;
    Connections.push_back({1,1,{0,true}});
    outputspiketime = {0,true};
}

bool Neuron::output() {
    double temp=0;
    for (int local_time; local_time< gammafrequency;local_time++) {
        for (int i = 0; i < Numinputs; i++) {
            if (get<2>(Connections[i]).get_bool() != true){
                int temp1 = get<2>(Connections[i]).get_int();
                if ((local_time - temp + 100 > 0) && temp1 >= local_time) {
                    temp += get<1>(Connections[i]) / 100;
                } else if (local_time > temp1) {
                    temp -= get<1>(Connections[i]) / (gammafrequency - temp);
                }
            }
        }
        if (temp > threshold) {
            outputspiketime = {local_time, false};
            return true;
        } else {
            outputspiketime = {0, true};
        }
    }
    return false;
}

bool Neuron::UpdateNeuronInputSpiketime(int Neuronnumber, STint spiketime){
    for(int i=0; i<Numinputs;i++){
        if (Neuronnumber == get<0>(Connections[i]) ){
            get<2>(Connections[i])  = spiketime;
            return true;
        }
    }
    return false;
};

void Neuron::AddNeuronInput(int Neuronnumber){
    Numinputs += 1;
    Connections.push_back({Neuronnumber,1,{0,true}});
};

bool Neuron::RemoveNeuronInput(int Neuronnumber){

    for(int i=0; i<Numinputs+1;i++){
        if (Neuronnumber == get<0>(Connections[i])) {
            Numinputs -= 1;
            Connections.erase(Connections.begin()+i);
            return true;
        }
    }
    return false;
};

bool Neuron::UpdateNeuronInputWeight(int Neuronnumber,int Weights){
    for(int i=0; i<Numinputs;i++){
        if (Neuronnumber == get<0>(Connections[i])){
            get<1>(Connections[i]) = Weights;
            return true;
        }
    }
    return false;
};

bool Neuron::printNeuronInformation(){
    cout << "Neuron: \t\t\t" << NeuronNumber << endl << endl;
    cout << "Gamma Frequency: \t\t"<< gammafrequency << endl <<endl;
    cout << "Threshold: \t\t\t"<< threshold<<endl <<endl;
    cout << "Numinputs: \t\t\t"<<Numinputs<<endl<<endl;
    if ( outputspiketime.get_bool()==true){
        cout << "output spike time: \t\tNo Spike" << endl;
    }
    else {
        cout << "output spike time: \t\t"<<(int) outputspiketime.get_int()  << endl;
    }
    cout << "Input Neurons Infornmation: \t";
    for (int i=0;i<Numinputs;i++){
        cout << get<0>(Connections[i])<<"\t" << get<1>(Connections[i])<<"\t" ;
        if (get<2>(Connections[i]).get_bool()){
            cout << "No Spike" << endl << "\t\t\t\t";
        }
        else{
            cout << (int) get<2>(Connections[i]).get_int()<< endl<< "\t\t\t\t";
        }
    }
    cout << endl;
return true;
};