//
// Created by sander on 28/09/2023.
//

#ifndef THESIS_NEURONLIST_H
#define THESIS_NEURONLIST_H
#include "NeuronCluster.h"
#include <vector>
class NeuralNetwork {
private:
    int Neurons_total;
    vector<int> NeuronList;
    vector<NeuronCluster> NeuronClusters;
public:
    NeuralNetwork();
    bool DeleteNeuron(int NeuronNumber);
    bool Printclusterinformation(int clusternumber);
};


#endif //THESIS_NEURONLIST_H
