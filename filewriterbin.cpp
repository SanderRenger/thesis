//
// Created by sander on 19/05/2024.
//

#include "filewriterbin.h"

#include <utility>
void filewriterbin(string filename, NeuralNetwork& Simulation){
    vector<vector<vector<double>>> network =Simulation.GetWeights();
    vector<NeuronCluster> Clusters = Simulation.GetSystem();
    int SizeLayer1=Clusters[0].Neuroncount();
    int SizeLayer2=Clusters[1].Neuroncount();
    int SizeLayer3=Clusters[2].Neuroncount();

    cout << "SizeLayer1:\t" << SizeLayer1 << "SizeLayer2:\t" << SizeLayer2 << "SizeLayer3:\t" << SizeLayer3 << endl;
    vector<double> data(SizeLayer1*SizeLayer2*2,0);
    int temp = 0;
    for(int k=1;k<(network.size());k++){
        for(int j =0; j<network[k].size();j++){
            if (k==2){
                cout << "Network k:\t" << network[k].size() << endl;
                cout << "Network kj:\t" << network[k][j].size() << endl;
            }
            for(int i=0;i<network[k][j].size();i++){
                data[SizeLayer2*SizeLayer1*(k-1)+j*SizeLayer1+i] = network[k][j][i];
                temp++;
                if (temp%100 ==0){
                    //cout << network[k][j][i] << endl;
                    cout << "connections written:\t" << temp << endl;
                }

            }
        }
    }
    npy::npy_data<double> d;
    d.data = data;
    d.shape = {2, 512, 34*34*2};
    d.fortran_order = false; // optional

    const std::string path{std::move(filename)};
    npy::write_npy(path, d);

};

void filereaderbin(string filename, NeuralNetwork& Simulation){
    std::string path {filename};
    npy::npy_data d = npy::read_npy<double>(path);

    std::vector<double> data = d.data;
    std::vector<unsigned long> shape = d.shape;
    //d.shape[0] = 2
    //d.shape[1] = 512
    //d.shape[2] = 34*34*2
    // Layer 1 = {512,34*34*2}
    // Layer 2 = {10,512}
    vector<vector<vector<double>>> network;
    vector<double> Neuron1;
    vector<vector<double>> NeuronCluster;
    bool empty= false;
    int temp2=0;
    int size_layer = d.shape[1]*d.shape[2];
    for(int i =0;i<size_layer;i++){
        if (i%d.shape[2]==0 &&i!=0){
            NeuronCluster.push_back(Neuron1);
            Neuron1.clear();
        }
        Neuron1.push_back(d.data[i]);
        //layer1 512//34*34*2
    }
    NeuronCluster.push_back(Neuron1);

    network.push_back(NeuronCluster);
    NeuronCluster.clear();
    Neuron1.clear();
    int count=0;
    for(int i=0;i<size_layer;i++){
        if(i%(d.shape[1])==d.shape[2]){
            i+=(34*34*2)-512;
        }
        if(d.data[i+size_layer]!=0){

            if (count==512 &&i!=0){
                count=0;
                NeuronCluster.push_back(Neuron1);
                Neuron1.clear();
            }
            count++;
            Neuron1.push_back(d.data[i+size_layer]);

            //layer2 10/512
        }
        else if(!empty){
            empty = true;
            temp2 = i/(34*34*2);
        }

    }
    temp2 = NeuronCluster.size();
    //cout << temp2 << endl;

    network.push_back((NeuronCluster));
    cout << "File Read" << endl;
    //cout << network[1][0][511] << endl;
    int Total_Neurons = d.shape[1]+d.shape[0]+temp2;
    for(int i=0;i<network.size()+1;i++){
        Simulation.AddCluster();
    };
    for(int i=0;i<d.shape[2];i++){
        Neuron Neurontemp = {i,10, {}};
        Simulation.AddNeuron(0, Neurontemp);
    }
    cout << "First layer done" << endl;

    for(int i=0;i<d.shape[1];i++){
        vector<tuple<int,double,STint>> temp3;
        for(int j=0;j<d.shape[2];j++){
            temp3.push_back({j,network[0][i][j],{0,false}});
        }
        Neuron Neurontemp = {34*34*2-1+i,10,temp3};
        Simulation.AddNeuron(1,Neurontemp);
    }
    cout << "Second layer done" << endl;

    for(int i=0;i<temp2;i++){
        vector<tuple<int,double,STint>> temp3;
        for(int j=0;j<d.shape[1];j++){
            temp3.push_back({j+d.shape[2],network[1][i][j],{0,false}});
        }
        Neuron Neurontemp = {34*34*2+511+i,10,temp3};
        Simulation.AddNeuron(2,Neurontemp);
    }
    cout << "Third layer done" << endl;
    Simulation.MakeNeuronListFullConnected({34*34*2,512,10});
}