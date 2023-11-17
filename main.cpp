
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
void loopsimulation(NeuralNetwork &Simulation){

    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.AddNeuron(0);
    Simulation.UpdateNeuron(4,1.5,{},{});
    Simulation.Addconnection(1,2,0,1);
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
int main() {
   int simulationtime=0;
    //Network1.DeleteNeuron(1);
    NeuralNetwork Simulation = simulation(3);
    EventHandler EventHandler;
    EventHandler.addEvent({1,0});
    EventHandler.addgammaevents(Simulation);
    while(!EventHandler.empty()){
        EventHandler.handleEvents(Simulation,simulationtime);
        EventHandler.swapqueue();
           if (simulationtime==110) {
               break;
           }
        simulationtime++;
    }
    return 0;


}