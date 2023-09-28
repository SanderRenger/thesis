
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
    Network1.Printclusterinformation(0);

    return 0;
}