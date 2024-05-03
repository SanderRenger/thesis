
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
#include "testfunctions.h"
#include "npy.hpp"
//int gammafrequency, double threshold,std::vector<double> inputs,std::vector<double> weights,std::vector<STint> inputspiketime
using namespace std;



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

int Run(NeuralNetwork &Simulation, EventHandler &EventHandler){
    int simulationtime=0;
    //EventHandler.printoutput();
    //EventHandler.addgammaevents(Simulation);
    while(!EventHandler.empty()){
        EventHandler.handleEvents(Simulation,simulationtime);
        EventHandler.swapqueue();
           if (simulationtime==600||EventHandler.isempty()) {
               break;
           }
        simulationtime++;
    }
    //EventHandler.printoutput();
    return EventHandler.saveoutput();
}
int main() {



//    Simulation.Printclusterinformation(1);
//   EventHandler.printqueue();
// EventHandler.printqueue();
//    Simulation.Printclusterinformation(1);
    //Simulation.Printneuroninformation(2312);
    vector<int> outputs;
    for (int i =60001; i<60101; i++){
        NeuralNetwork Simulation;
        EventHandler EventHandler;
        string filename = "input2.txt";

        parsefile(Simulation,filename);
        string path1 { "layer1.npy"};
        string path2 {"layer2.npy"};
        Simulation.UpdateWeightdataset(path1, path2);
        std::ostringstream filename2;
        filename2 << "NMNISTsmall/"<< i << ".bs2";
        EventHandler.createevents(filename2.str(), {34,34});
        int temp = Run(Simulation,EventHandler);
        outputs.push_back(temp);
        cout <<i <<"\t"<<  outputs.back() << endl;
    }
    for(int i=0; i<outputs.size();i++){
        cout <<60001+i <<"\t"<<  outputs[i] << endl;
    }

    //Simulation.PrintNeuronVoltagetofile(1);
    //Simulation.PrintNeuronVoltagetofile(2);
    //filewriter(Simulation,"output.txt");
   return 0;
}