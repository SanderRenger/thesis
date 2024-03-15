//
// Created by sander on 18/01/2024.
//

#include "filewriter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

void filewriter(NeuralNetwork &Simulation, string filename){
    int count = 0;
    vector<NeuronCluster> system = Simulation.GetSystem();
    ofstream file;
    file.open (filename);
    if (!file.is_open()){
        cerr << "Failed to open file." << endl;
        return;
    }
    file << "Mode: {1}" << endl;
    for(int i =0; i< system.size(); i++) {
        file << "Cluster: {" << system[i].GetGammafrequency() << ",1}" << endl;
        vector<int> temp = system[i].GetNeurons();
        for (int j = 0; j < system[i].Neuroncount(); j++) {
            tuple<int, int, vector<int>, int> Neuron = Simulation.GetNeuron(count);
            if (j%100==0&&j!=0) {
                cout << "Neurons written to file:\t" << j << endl;
            }
            file << "Neuron: {{";

            for (int k =0; k < get<2>(Neuron).size();k++) {
                if (k!=0){
                    file <<",{";
                }
                int temp2 = get<1>(Simulation.GetNeuron(get<2>(Neuron)[k]));
                //cout << "test:\t" << get<2>(Neuron)[k]<<endl;
                //cout << "Cluster:\t" << i << "\tNeuron:\t" << j << "\tInput:\t" << get<2>(Neuron)[k]<<endl;
                double temp3 = Simulation.GetWeight(Simulation.GetCluster(get<2>(Neuron)[k]),get<2>(Neuron)[k],count);
                //cout << temp3<< endl;

                file <<get<2>(Neuron)[k]<<","<<temp3<<"}";

            }
            if (get<2>(Neuron).empty()){
                file <<"}";
            }
            double temp4 = Simulation.GetThreshold(Simulation.GetCluster(count),count);
            //cout << temp4 << endl;
            file <<","<< get<3>(Neuron)<<","<<temp4<<"}"<<endl;
            count++;

        }
    }
    cout << "Done writing the file "<<endl;
}
