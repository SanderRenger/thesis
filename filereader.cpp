//
// Created by sander on 09/11/2023.
//

#include "filereader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

void parsefile(NeuralNetwork &Simulation,string filename){
    srand ( time(NULL) );
    std::ifstream file(filename);
    if (!file.is_open()){
        cerr << "Failed to open file." << endl;
        return;
    }
    vector<tuple<int, float>> neuronData;
    string line;
    vector<tuple<int, bool,vector<tuple<int,vector<tuple<int,double>>>>>> clusterData;
    vector<tuple<int,bool,int>> clusterDataRandom;
    int current_cluster=-1;
    int current_neuron=-1;
    int neurons_total=0;
    bool mode = false;
    while (getline(file,line)) {
        std::istringstream iss(line);
        std::string key;
        std::string value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            if (key == "Mode") {
                size_t startPos = line.find("Mode:")+ 7;
                string data = line.substr(startPos);
                istringstream iss(data);
                string package;
                getline(iss, package, '}');
                package = package.substr(package.find('{') + 1); // Remove '{'
                size_t BracketPos = package.find('}');
                mode = std::stoi(package.substr(0, BracketPos));
            }
            if (mode==1){
                if (key == "Cluster") {
                    current_cluster +=1;
                    size_t startPos = line.find("Cluster:") + 8;
                    string data = line.substr(startPos);
                    istringstream iss(data);
                    string package;
                    // Split into individual packages
                    while (std::getline(iss, package, '}')) {
                        if (package.size() > 1) {
                            package = package.substr(package.find('{') + 1); // Remove '{'
                            size_t commaPos = package.find(',');
                            // Extract the integer and float values

                            int first = std::stoi(package.substr(0, commaPos));
                            bool second = std::stoi(package.substr(commaPos + 1));
                            clusterData.push_back({first, second, {}});
                        }
                        if (iss.peek() == ',') {
                            iss.ignore(); // Ignore the comma after '}'
                        }
                    }
                }  else if (key == "Neuron") {
                    current_neuron +=1;
                    size_t startPos = line.find("Neuron:") + 8;
                    string data = line.substr(startPos);
                    istringstream iss(data);
                    string package;
                    int first;
                    int delay;
                    double second;
                    vector<tuple<int,double>> temp;
                    neurons_total+=1;
                    while (std::getline(iss, package, '}')) {
                        if (package.size() > 1) {

                            package = package.substr(package.find('{') + 1);
                            package = package.substr(package.find('{') + 1);// Remove '{'
                            size_t commaPos = package.find(',');
                            // Extract the integer and float values
                                if (package.substr(0, commaPos).empty()) {
                                    delay = std::stoi(package.substr(commaPos + 1));
                                }
                                else {
                                    second = std::stof(package.substr(commaPos + 1));
                                    first = std::stoi(package.substr(0, commaPos));
                                    temp.push_back({first,second});
                                }


                        }
                    }
                    get<2>(clusterData[current_cluster]).push_back({delay,temp});
                }
                else{

                }
            } else {
                if (key == "Cluster") {
                    current_cluster +=1;
                    size_t startPos = line.find("Cluster:") + 8;
                    string data = line.substr(startPos);
                    istringstream iss(data);
                    string package;
                    int first;
                    int Neurons;
                    bool second;
                    vector<tuple<int,bool,int>> temp;
                    // Split into individual packages
                    while (std::getline(iss, package, '}')) {
                        if (package.size() > 1) {
                            package = package.substr(package.find('{') + 1); // Remove '{'
                            package = package.substr(package.find('{') + 1); // Remove '{'
                            size_t commaPos = package.find(',');
                            // Extract the integer and float values
                            if (package.substr(0, commaPos).empty()) {
                                Neurons = std::stoi(package.substr(commaPos + 1));
                            }
                            else {
                                second = std::stof(package.substr(commaPos + 1));
                                first = std::stoi(package.substr(0, commaPos));

                            }
                        }
                    }
                    neurons_total += Neurons;
                    clusterDataRandom.push_back({first,second,Neurons});
                } else{

                }
            }

        }

    }
    if(mode == 0){
        for(int i=0;i<clusterDataRandom.size();i++){
            Simulation.AddCluster();
            Simulation.UpdateGammaFrequency(i,get<0>(clusterDataRandom[i]));
            for(int j=0;j<get<2>(clusterDataRandom[i]);j++){
                Simulation.AddNeuron(i);
                Simulation.UpdateThreshold(j,(double)(rand()%100)/100);
            }
        }
        current_neuron = 0;
        for(int i=0;i<clusterDataRandom.size();i++){
            for(int j=0;j<get<2>(clusterDataRandom[i]);j++){
                int connections =rand()%(neurons_total-1)+1;

                vector<int> temp;
                for(int k=0;k<connections;k++) {
                    int randomOutput = j;
                    while (randomOutput == j) {
                        randomOutput = rand() % neurons_total;
                        for (int l : temp){
                            if (l == randomOutput){
                                randomOutput = j;
                                break;
                            }
                        }
                    }
                    double randomweight = (double) (rand() % 100) / 100;
                    int randomdelay = rand() % 100;
                    temp.push_back(randomOutput);
                    Simulation.Addconnection(j, randomOutput, randomdelay, randomweight);
                }
            }
        }
    }
    else {
        for(int i=0;i<clusterData.size();i++){
            Simulation.AddCluster();
            Simulation.UpdateGammaFrequency(i,get<0>(clusterData[i]));
            for(int j=0;j<get<2>(clusterData[i]).size();j++){
                Simulation.AddNeuron(i);
            }
        }
        current_neuron =0;
        for(int i=0;i<clusterData.size();i++){

            for(int j=0;j<get<2>(clusterData[i]).size();j++){

                for(int k=0; k<get<1>(get<2>(clusterData[i])[j]).size();k++){
                    //cout << current_neuron<<" \t" <<get<0>(get<1>(get<2>(clusterData[i])[j])[k])<<" \t" <<get<0>(get<2>(clusterData[i])[j])<<" \t" <<get<1>(get<1>(get<2>(clusterData[i])[j])[k])<<endl;
                    Simulation.Addconnection(current_neuron,get<0>(get<1>(get<2>(clusterData[i])[j])[k]),get<0>(get<2>(clusterData[i])[j]),get<1>(get<1>(get<2>(clusterData[i])[j])[k]));
                }
                current_neuron+=1;
            }
        }
    }


}

/*Mode: true
Cluster: {100,true}
Neuron: {{3,0.5},{4,1.0},{2,1.5},100}
Neuron: {{3,0.5},{5,1.0},{3,1.5},50}
Cluster: {110,true}
Neuron: {{1,0.4},{2,1.0},{7,1.5},0}
*/

/*Mode: false
Cluster: {100,true}
Neuron: 100
Cluster: {110,true}
Neuron: 150
*/

/*{
    "simulator": "pyNN.nest",
    "threads": 1,
    "populations": {
        "A": {
            "n": 10000,
            "celltype": "IF_cond_exp",
            "params": {
                "i_offset": 1.0 }},
        "B": {
            "n": 10000,
            "celltype": "IF_cond_exp",
            "params": {
                "i_offset": 0.5 }}},
    "sim_time": 100.0,
    "recording": {
        "A": {
            "v": 10,
            "spikes": 1000},
        "B": {
            "v": 10,
            "spikes": 1000}},
    "projections": {
        "AB": {
            "pre": "A",
            "post": "B",
            "connector": {
                "type": "AllToAllConnector",
                "params": {}},
            "synapse_type": {
                "type": "StaticSynapse",
                "params": {
                    "weight": 0.000001,
                    "delay": 1.5}},
            "receptor_type": "excitatory"}}
}*/

/*{
    "simulator": "pyNN.nest",
    "populations": {
        "A": {
            "n": 10000,
            "celltype": "IF_cond_exp",
            "params": {
                "i_offset": 1.0 }},
        "B": {
            "n": 10000,
            "celltype": "IF_cond_exp",
            "params": {
                "i_offset": 0.5 }}},
    "sim_time": 100.0,
    "recording": {
        "A": {
            "v": 100,
            "spikes": 1000},
        "B": {
            "v": 100,
            "spikes": 1000}}
}*/