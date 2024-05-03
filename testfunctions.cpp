//
// Created by sander on 04/04/2024.
//

#include "testfunctions.h"
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