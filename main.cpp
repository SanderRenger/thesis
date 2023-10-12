
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "Neuron.h"
#include "NeuronCluster.h"
#include <bits/stdc++.h>
#include "global.h"
#include "system.h"
//int gammafrequency, double threshold,std::vector<double> inputs,std::vector<double> weights,std::vector<STint> inputspiketime
using namespace std;

void run_system(){

};

int main() {
    vector<int> inputs(1,2);
    vector<double> weights(1,1);
    vector<STint> inputspiketime(1,{0,true});
    double threshold = 1;
    vector<Neuron> Neuron2(2);
    NeuralNetwork Network1;
    Network1.UpdateNeuron(1,1,{{4,0.5,{200,false}}},{{0,0}});
    Network1.AddNeuron(0,1,{{4,0.5,{200,false}},{2,1,{0,true}}},{{3,0}});
    Network1.UpdateNeuron(2,4,{{4,0.5,{200,false}}},{{0,0}});
    //Network1.DeleteNeuron(1);
    Network1.Addconnection(1,2,0,1);
    Network1.Printclusterinformation(0);
    Network1.PrintNeuronList();
    return 0;
}