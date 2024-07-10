
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
        simulationtime++;
        if(EventHandler.isempty()){
            EventHandler.swapnewqueue();
            EventHandler.printqueuetofilenpy("queue.npy");
            simulationtime=0;
        }
        if (EventHandler.isempty()||simulationtime==1305) {
            break;
        }
    }
    //EventHandler.printoutput();
    return EventHandler.saveoutput();
}

void Loop(const string& Network){
    vector<int> outputs;
    for (int i =60001; i<60002; i++){
        EventHandler EventHandler;
        NeuralNetwork Simulation;
        filereaderbin(Network,Simulation);
        //Simulation.PrintNeuronList(1);
        //Simulation.Printclusterinformation(2);
        std::ostringstream filename;
        filename << "NMNISTsmall/"<< i << ".bs2";
        EventHandler.createevents(filename.str(), {34,34});
        Simulation.DeleteConnectionRandom(0,300000);
        //Simulation.DeleteConnectionRandom(1,1000);
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
//dvs 128


int main() {
    EventHandler EventHandler;
    NeuralNetwork Simulation;
    string filename {"connections.npy"};

    filereaderbinnew(filename,Simulation);
    std::ostringstream filename2;
    filename2 << "DVSGesturedataset/user01_fluorescent/0"<<".npy";
    EventHandler.createevents(filename2.str(), {128,128});
//    EventHandler.printqueuetofile("testqueue2.txt");
    Simulation.PrintNeuronListNeuron(26929);
   Simulation.Printneuroninformation(34444);
    //Simulation.PrintneuroninformationInputs(0);
    //Simulation.Printclusterinformation(1);
//    EventHandler.printqueuetofiletxt("testqueue.txt");

    int temp = Run(Simulation,EventHandler);
//    vector<int> outputs;
//    outputs.push_back(temp);
//    cout << outputs[0] << endl;
//    Simulation.PrintNeuronVoltagetofile(0);
//    Simulation.PrintNeuronVoltagetofile(1);
//    Simulation.Printneuroninformation(-1,0);
//    Simulation.Printclusterinformation(1);
//    Loop(filename);

//    Simulation.Printclusterinformation(1);

// EventHandler.printqueue();
//    Simulation.Printclusterinformation(1);
    //Simulation.Printneuroninformation(2312);


     //filewriter(Simulation,"output.txt");
   return 0;
}