
#include <math.h>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Neuron.h"
#include "event.h"
#include "NeuronCluster.h"
#include <bits/stdc++.h>
#include "global.h"
#include "system.h"
#include "filereader.h"
#include "filewriter.h"
#include "TimeData.h"

#include "npy.hpp"
//int gammafrequency, double threshold,std::vector<double> inputs,std::vector<double> weights,std::vector<STint> inputspiketime
using namespace std;

void loopsimulation(NeuralNetwork &Simulation){

    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.UpdateNeuron(4,1.5,{},{});
    Simulation.Addconnection(1,2,5,1);
    Simulation.Addconnection(1,3,0,0);
    Simulation.Addconnection(3,4,0,1);
    Simulation.Addconnection(2,4,0,1);
    Simulation.Addconnection(5,1,0,1);
    Simulation.Addconnection(4,5,0,1);
}
void treesimulation(NeuralNetwork &Simulation){
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);

    Simulation.Addconnection(1,2,0,1);
    Simulation.Addconnection(1,3,0,1);
    Simulation.Addconnection(2,4,0,1);
    Simulation.Addconnection(3,5,0,1);
    Simulation.Addconnection(3,6,0,1);

}

void delayedactivationsimulation(NeuralNetwork &Simulation){
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);

    Simulation.Addconnection(1,2,0,1);
    Simulation.Addconnection(2,3,0,1);
    Simulation.Addconnection(2,4,0,0.5);
    Simulation.Addconnection(4,6,0,1);
    Simulation.Addconnection(3,5,0,1);
    Simulation.Addconnection(5,4,0,0);
}

NeuralNetwork simulation(int simulationnumber){
    NeuralNetwork Simulation;
    switch (simulationnumber){
        case 1:
            treesimulation( Simulation);
            break;
        case 2:
            loopsimulation(Simulation);
            break;
        case 3:
            delayedactivationsimulation(Simulation);
            break;
        default:
            cout << "non valid simulation number" << endl;
            break;
    }
    return Simulation;
};

void Run(NeuralNetwork &Simulation, EventHandler &EventHandler){
    int simulationtime=0;

    EventHandler.addgammaevents(Simulation);
    while(!EventHandler.empty()){
        EventHandler.handleEvents(Simulation,simulationtime);
         EventHandler.swapqueue();
           if (simulationtime==1000000) {
               break;
           }
        simulationtime++;
    }
}
int main() {
    NeuralNetwork Simulation;
    string filename = "input4.txt";
    parsefile(Simulation,filename);

//    string path1 { "layer1.npy"};
//    string path2 {"layer2.npy"};
//    Simulation.UpdateWeightdataset(path1, path2);
    //Simulation.Printclusterinformation(1);
   EventHandler EventHandler;
   EventHandler.createevents("60001.bs2", {34,34});
//   EventHandler.printqueue();
//Simulation.Printclusterinformation(2);
   //filewriter(Simulation,"output.txt");
   Run(Simulation,EventHandler);

   return 0;
}