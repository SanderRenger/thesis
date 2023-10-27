
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "Neuron.h"
#include "event.h"
#include "NeuronCluster.h"
#include <bits/stdc++.h>
#include "global.h"
#include "system.h"
//int gammafrequency, double threshold,std::vector<double> inputs,std::vector<double> weights,std::vector<STint> inputspiketime
using namespace std;

void run_system(){

};

int main() {
    int simulationtime=0;
    vector<int> inputs(1,2);
    vector<double> weights(1,1);
    vector<STint> inputspiketime(1,{0,true});
    double threshold = 1;
    vector<Neuron> Neuron2(2);
    NeuralNetwork Network1;
    Network1.UpdateNeuron(1,1,{{}},{{2,0}});
    Network1.AddNeuron(0,1,{{1,0.5,{0,true}}},{});
    Network1.AddNeuron(0);
    Network1.Addconnection(3,2,0,0.5);
    Network1.Addconnection(2,1,0,1.01);
    Network1.Addconnection(2,3,0,1.01);
    //Network1.DeleteNeuron(1);
    EventHandler EventHandler1;
    EventHandler1.addEvent({1,0});
    EventHandler1.addEvent({3,0});
    while(!EventHandler1.empty()){
        Network1 = EventHandler1.handleEvents(Network1,simulationtime);
        EventHandler1.swapqueue();
           if (simulationtime==1000){break;
        }
        simulationtime++;
    }
    return 0;
}