//
// Created by sander on 27/09/2023.
//

#include "Neuron.h"
#include "global.h"
#include "event.h"
#include <iostream>
#include <fstream>

Neuron::Neuron(int NeuronNumber_t, double threshold_t,vector<tuple<int,double,STint>> inputConnections_t){
    out = false;
    has_fired=0;
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
    out = false;
    has_fired=0;
    NeuronNumber = 1;
    threshold = 0.99;
    inputConnections;
    outputspiketime = {0,true};
    //outputConnections.push_back({0,0});
    vector<double> temp(300,0);
    spiketrains = temp;
}

void Neuron::spike(int current_time,int Gammafrequency,int neuroninput) {
   bool firstspike = false;
   int samplesize=300;
   while(spiketrains.size() < samplesize){
       spiketrains.push_back(0);
   }
   bool temp= false;
   int temp2=0;
   double output=0;
   float slope=0;
   float total_spike_prev = 0;
   float total_spike = 0;
   double weights_t;
   STint Spiketime_t;
   int Taus = 10;
   // ofstream myfile;
   //if (NeuronNumber == 4){
   //   myfile.open ("log1.txt");
   //}
   //cout << inputConnections.size() << endl;
   //cout << "neuron\t"<< neuroninput<< "time\t"<< get<2>(inputConnections[neuroninput]).get_int() << endl;
   //if (!has_fired){
       for (int i = current_time; i < samplesize; i++) {
           if (current_time != get<2>(inputConnections[neuroninput]).get_int()){ cout <<"hey that shouldn't happen\t Neuron:"<< NeuronNumber << "\tInput:" << neuroninput << endl;}

           weights_t = get<1>(inputConnections[neuroninput]);

           if (neuroninput >1155 && neuroninput <2311){
               //weights_t = weights_t*-1;
           }
           Spiketime_t = get<2>(inputConnections[neuroninput]);
           if (!Spiketime_t.get_bool()) {
               if (i >= Spiketime_t.get_int()) {
                   total_spike_prev = total_spike;
                   double timestep = (double) (i - Spiketime_t.get_int()) / (double) (Taus);
                   if ((i < samplesize)) {
                       total_spike = weights_t * timestep * exp(1 - timestep);
                   } else {
                       break;
                   }
               }
               slope = total_spike - total_spike_prev;
               output += slope;

               spiketrains[i] = spiketrains[i] + output;
               //if (NeuronNumber==2+34*34*2){cout << spiketrains[i] << endl;}
               //cout << "spiketrain:\t"<< spiketrains[i] << endl;
           }

           if (spiketrains[i] >= threshold) {
                   temp2=i;
                   temp = true;
           }

       }
    if (temp){
        if(has_fired+2 <= temp2) {
        //    has_fired = temp2;
        //cout << "Neuron: \t" << NeuronNumber << "fired" << endl;
        //return {temp2,false};
        }
    }
    //return {0,true};
}

int Neuron::UpdateNeuronInputSpiketime(int Neuronnumber_t, int current_time){

    //cout <<NeuronNumber<<"\t" <<Neuronnumber_t<< endl;
    for(int i=0; i<inputConnections.size();i++){
        if (Neuronnumber_t == get<0>(inputConnections[i]) ){
            //cout <<"updated\t" << Neuronnumber_t << endl;
            get<2>(inputConnections[i])  = {current_time,false};
            //cout << "test\t" << get<2>(inputConnections[i]).get_int() << "index\t" << i<<  endl;

            return i;
        }
    }
    return 0;
};

void Neuron::AddNeuronInput(int Neuronnumber,double weight){
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

void Neuron::GammaCycle(bool Gammareset,int Gammafrequency) {
    has_fired=false;
    //fill(spiketrains.begin(),spiketrains.end(),0);
    //    for (int i =0;i<inputConnections.size();i++){
    //        if (!get<2>(inputConnections[i]).get_bool()){
    //            if (Gammareset){ //reset or put old spike in negative gammacycle time
    //                get<2>(inputConnections[i]) = {0,true};
    //            }
    //            else{
    //                    get<2>(inputConnections[i]) = {get<2>(inputConnections[i]).get_int()-Gammafrequency,false};
    //            }
    //            if (!outputspiketime.get_bool()) {
    //                if (outputspiketime.get_int() >
    //                    get<2>(inputConnections[i]).get_int()) { //update weights based on spiketime close to threshhold
    //                    get<1>(inputConnections[i]) += 0;
    //                } else {
    //                    get<1>(inputConnections[i]) -= 0;
    //                }
    //            }
    //        }
    //    }
}
bool Neuron::UpdateNeuronInputWeight(int Neuronnumber,double Weights){
    for(int i=0; i<inputConnections.size();i++){
        if (Neuronnumber == get<0>(inputConnections[i])){
            get<1>(inputConnections[i]) = Weights;
            return true;
        }
    }
    cout << "oops" << endl;
    return false;
};

bool Neuron::printNeuronInformation(){
    if (NeuronNumber > 2823) {cout << "Neuron: \t\t\t" << NeuronNumber%2824 << endl << endl;}
    else if (NeuronNumber >2312 ) {cout << "Neuron: \t\t\t" << NeuronNumber%2312 << endl << endl;}
    else {cout << "Neuron: \t\t\t" << NeuronNumber << endl << endl;}
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
        if (get<0>(inputConnections[i]) > 2823) { cout << get<0>(inputConnections[i])%2824<<"\t" << get<1>(inputConnections[i])<<"\t" ;}
        else if (get<0>(inputConnections[i]) > 2311) { cout << get<0>(inputConnections[i])%2312<<"\t" << get<1>(inputConnections[i])<<"\t" ;}
        else { cout << get<0>(inputConnections[i])<<"\t" << get<1>(inputConnections[i])<<"\t" ;}
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



double Neuron::GetWeight(int Input){
    //cout << "Neuron:\t"<< NeuronNumber << endl;
    for(int i =0; i < inputConnections.size(); i++){
        if (Input == get<0>(inputConnections[i])){
            //cout <<"weight:\t"<<get<1>(inputConnections[i])<< endl;
            return get<1>(inputConnections[i]);
        }
    }
    return 0;
}

vector<double> Neuron::GetWeights(){
    //cout << "Neuron:\t"<< NeuronNumber << endl;
    vector<double> temp;
    for(int i =0; i < inputConnections.size(); i++){
            temp.push_back(get<1>(inputConnections[i]));
            //cout << temp.back() << endl;
    }
    return temp;
}

double Neuron::GetThreshold() {
    return threshold;
}

void Neuron::GetVoltage(const string& filename) {
    //cout << NeuronNumber << "\t" << filename << endl;
    npy::npy_data_ptr<double> d;
    d.data_ptr = spiketrains.data();
    d.shape = {1,300};
    d.fortran_order = false; // optional
    npy::write_npy(filename, d);
}

void Neuron::setfired(int current_time) {
    has_fired = current_time;
}

STint Neuron::output(int current_time){
    while(spiketrains.size() < 300){
        spiketrains.push_back(0);
    }
    //cout << spiketrains[current_time+1]<<endl;
double temp;
    if (current_time -has_fired>8){
        temp =0;
    }
    else{
        temp = double(2*exp(double(1)-double((current_time -has_fired))/double(10)));
        temp = 2*(2.7-1.95*(double((current_time -has_fired))/double(2)));
        if (temp<0){
            temp=0;
        }
    }
    if (spiketrains[current_time+1]> threshold + 10*temp){
        has_fired = current_time+1;
        return {current_time+1, false};

    }
    return {0,true};
}