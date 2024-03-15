//
// Created by sander on 27/09/2023.
//

#include "Neuron.h"
#include "global.h"
#include "event.h"
#include <iostream>
#include <fstream>

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
    threshold = 0.99;
    inputConnections;
    outputspiketime = {0,true};
    //outputConnections.push_back({0,0});
}

STint Neuron::output(int Gammafrequency,int neuroninput) {
   bool firstspike = false;
   if(spiketrains.size() != Gammafrequency){
       firstspike = true;
       spiketrains.resize(Gammafrequency);
       fill(spiketrains.begin(),spiketrains.end(),0);
   }
   bool out = false;
   int temp2;
   double output=0;
   double slope=0;
   double weights_t;
   STint Spiketime_t;
   // ofstream myfile;
   //if (NeuronNumber == 4){
   //   myfile.open ("log1.txt");
   //}
   //cout << inputConnections.size() << endl;
   //cout << "neuron\t"<< neuroninput<< "time\t"<< get<2>(inputConnections[neuroninput]).get_int() << endl;
   for(int i=0;i< Gammafrequency;i++){
       if (NeuronNumber==2312&&spiketrains[i]>0){
           //cout <<"output of Neuron: " << NeuronNumber <<" = "<<spiketrains[i] << "\ttime:"<<i<<endl;
       }

           weights_t =get<1>(inputConnections[neuroninput]);
           Spiketime_t =get<2>(inputConnections[neuroninput]);
           if (!Spiketime_t.get_bool()){
               if (i >= Spiketime_t.get_int()){
                   if(i< Spiketime_t.get_int()+1){
                       slope = ((double)1/(double)1)*weights_t;
                   }
                   else if(i< Spiketime_t.get_int()+3000){
                       slope = 0;
                   }
                   else if((i<Spiketime_t.get_int()+4000)){
                       slope =-((double)1/(double)1000)*weights_t;;
                   }
                   else {
                       slope = 0;
                   }

               }
               output += slope;
               spiketrains[i] = spiketrains[i] + output;
               //cout << "spiketrain:\t"<< spiketrains[i] << endl;
           }
       if (spiketrains[i] >= threshold){

           out= true;
           temp2 = i;
       }
   }
   //cout << output << endl;
    //if (NeuronNumber==4){
    //    myfile.close();
    //}
    if (out){
        //cout << "Neuron: \t" << NeuronNumber << "fired" << endl;
        return {temp2,false};
    }
    return {0,true};
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
    fill(spiketrains.begin(),spiketrains.end(),0);
    for (int i =0;i<inputConnections.size();i++){
        if (!get<2>(inputConnections[i]).get_bool()){
            if (Gammareset){ //reset or put old spike in negative gammacycle time
                get<2>(inputConnections[i]) = {0,true};
            }
            else{
                    get<2>(inputConnections[i]) = {get<2>(inputConnections[i]).get_int()-Gammafrequency,false};
            }
            if (!outputspiketime.get_bool()) {
                if (outputspiketime.get_int() >
                    get<2>(inputConnections[i]).get_int()) { //update weights based on spiketime close to threshhold
                    get<1>(inputConnections[i]) += 0;
                } else {
                    get<1>(inputConnections[i]) -= 0;
                }
            }
        }
    }
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

double Neuron::GetThreshold() {
    return threshold;
}