//
// Created by sander on 09/11/2023.
//

#include "filereader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void parsefile(NeuralNetwork &Simulation, std::ifstream file){
    if (!file.is_open()){
        cerr << "Failed to open file." << endl;
        return;
    }
    vector<std::pair<int, float>> neuronData;
    string line;
    while (getline(file,line)) {
        std::istringstream iss(line);
        std::string key;
        std::string value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            if (key == "Neuron") {
                size_t startPos = line.find("Neuron:") + 8;
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
                        float second = std::stof(package.substr(commaPos + 1));

                        neuronData.emplace_back(first, second);
                    }

                    if (iss.peek() == ',') {
                        iss.ignore(); // Ignore the comma after '}'
                    }
                }
            } else if (key == "Cluster") {
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
                        float second = std::stof(package.substr(commaPos + 1));

                        neuronData.emplace_back(first, second);
                    }

                    if (iss.peek() == ',') {
                        iss.ignore(); // Ignore the comma after '}'
                    }
                }
            } else if (key == "Mode") {
                size_t startPos = line.find("Mode:") + 8;
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
                        float second = std::stof(package.substr(commaPos + 1));

                        neuronData.emplace_back(first, second);
                    }

                    if (iss.peek() == ',') {
                        iss.ignore(); // Ignore the comma after '}'
                    }
                }
            }
        }

    }
}

vector<tuple<int, float>> parseNeuronConnections(const std::string& neuronData) {
    vector<tuple<int, float>> connections;
    istringstream iss(neuronData);
    string package;

    while (getline(iss, package, '}')) {
        if (package.size() > 1) {
            package = package.substr(package.find('{') + 1); // Remove '{'
            size_t commaPos = package.find(',');

            int first = std::stoi(package.substr(0, commaPos));
            float second = std::stof(package.substr(commaPos + 1));

            connections.emplace_back(first, second);
        }

        if (iss.peek() == ',') {
            iss.ignore(); // Ignore the comma after '}'
        }
    }
    return connections;
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
}/