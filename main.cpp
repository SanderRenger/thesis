
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
#include "filereaderbin.h"
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

void Loop(const string& Network){
    vector<int> outputs;
    for (int i =60001; i<60102; i++){
        EventHandler EventHandler;
        NeuralNetwork Simulation;
        filereaderbin(Network,Simulation);
        //Simulation.Printclusterinformation(2);
        std::ostringstream filename;
        filename << "NMNISTsmall/"<< i << ".bs2";
        EventHandler.createevents(filename.str(), {34,34});
        int temp = Run(Simulation,EventHandler);
        outputs.push_back(temp);
        cout <<i <<"\t"<<  outputs.back() << endl;
        Simulation.PrintNeuronVoltagetofile(1);
        Simulation.PrintNeuronVoltagetofile(2);
    }
    for(int i=0; i<outputs.size();i++){
        cout <<60001+i <<"\t"<<  outputs[i] << endl;
    }
}
int main() {
    //NeuralNetwork Simulation;
    //string filename = "input2.txt";
    //parsefile(Simulation,filename);
    //string path1 { "layer1.npy"};
    //string path2 {"layer2.npy"};
    //Simulation.UpdateWeightdataset(path1, path2);
    //filewriterbin("outbin.npy", Simulation);
    NeuralNetwork Simulation;
    string filename {"outbin.npy"};

    //filereaderbin(filename,Simulation);
    //Simulation.PrintNeuronList(2);
    //Simulation.Printclusterinformation(2);
    //filereaderbin("outbin.npy",Simulation);
    //Simulation2.Printclusterinformation(2);
    Loop(filename);

//    Simulation.Printclusterinformation(1);
//   EventHandler.printqueue();
// EventHandler.printqueue();
//    Simulation.Printclusterinformation(1);
    //Simulation.Printneuroninformation(2312);


     //filewriter(Simulation,"output.txt");
   return 0;
}