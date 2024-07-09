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
void filereaderbinnew(string filename, NeuralNetwork& Simulation){
    std::string path {filename};
    npy::npy_data d = npy::read_npy<double>(path);

    std::vector<double> data = d.data;
    std::vector<unsigned long> shape = d.shape;
    if (d.data[0]<8){
        cout<< "wrongfileformat"<< endl;
        return;
    }
    vector<double> Neuron1;
    vector<array<int,5>> Layers;
    array<int,3> dimensions = {int(d.data[1]),int(d.data[1]),int(d.data[2])};
    int count = d.data[0];
    //cout << count << endl;
    int neurons_last_layer = 0;
    int input_neurons = dimensions[0]*dimensions[1]*dimensions[2];
    cout << input_neurons<< endl;
    for (int i=0; i< (d.data[0]-1)/5;i++){
        int count = 5*i;
        Layers.push_back({int(d.data[3+count]),int(d.data[4+count]),int(d.data[5+count]),int(d.data[6+count]),int(d.data[7+count])});
    }
    cout << "Layer: " << 0<< "\t\t\t\t" << "Dimensions: " << dimensions[0] << "*" << dimensions[1] << "\tPolarities: " << dimensions[2]<< endl;
    for (int i=0; i<Layers.size();i++){
        if (Layers[i][4] == 1){
            Simulation.AddCluster();
            int input_x = dimensions[0];
            int tensorsize = Layers[i][3];
            Simulation.MakeNeuronListPool({dimensions[0],dimensions[1],dimensions[2]},int(tensorsize),i);
            dimensions[0] = dimensions[0]/tensorsize;
            dimensions[1] = dimensions[0];
            dimensions[2] = dimensions[2];
            vector<tuple<int,double,STint,int>> temp;
            double weight = d.data[count];
            Neuron Neurontemp;
            int neurons=0;
            cout << "Layer: " << i+1 << " is of type Pool\t\t" << "Dimensions: " << dimensions[0] << "*" << dimensions[1] << "  \tPolarities: " << dimensions[2]<< endl;
            for (int l=0; l < dimensions[2];l++) { //polarities
                for (int j = 0; j < dimensions[0] * dimensions[1]; j++) { //output grid
                    for (int k = 0; k < Layers[i][2] * Layers[i][2]; k++) { //poolsize


                        int Neuron = neurons_last_layer + int(k / tensorsize) * input_x + (k % tensorsize) +
                                     l * input_x * input_x + tensorsize * (j % dimensions[0]) +
                                     input_x * tensorsize * (j / dimensions[0]);
                        if (input_x == 16){
                            //cout <<"input:\t" << Neuron <<"neuron:\t"<<neurons+input_neurons<< endl;
                        }
                        temp.push_back({Neuron, weight, {0, false}, -1});
                    }
                    Neuron Neurontemp = {input_neurons + neurons, 10, temp};
                    Simulation.AddNeuron(i, Neurontemp);
                    temp.clear();
                    neurons++;
                };
            }
            neurons_last_layer = input_neurons;
            input_neurons +=neurons;

            //cout << "total amount of neurons = " << input_neurons<< endl;
            count++;
        }
        else if (Layers[i][4] == 2){
            Simulation.AddCluster();
            int tensorsize = Layers[i][3];
            Simulation.MakeNeuronListConv({dimensions[0],dimensions[1],dimensions[2],Layers[i][0]}, tensorsize,i);
            dimensions[0] = dimensions[0];
            dimensions[1] = dimensions[0];
            int temp_tensor = dimensions[2];
            dimensions[2] = Layers[i][0];
            int neurons=0;
            cout << "Layer: " << i+1 << " is of type Convolution\t\t" << "Dimensions: " << dimensions[0] << "*" << dimensions[1] << "\tPolarities: " << dimensions[2]<< endl;
            vector<tuple<int,double,STint,int>> temp;
            for (int l=0; l < dimensions[2];l++) {
                    for (int j = 0; j < dimensions[0] * dimensions[1]; j++) {
                        double weight;
                        for (int k = 0; k < Layers[i][2] * Layers[i][2]* temp_tensor; k++) {
                            int m = int(k/(Layers[i][2] * Layers[i][2]));
                            int temp_x = -int(Layers[i][2] / 2) + j % dimensions[0] + k%Layers[i][2];
                            int temp_y = -int(Layers[i][2] / 2) + int(j / dimensions[0]) + int(k / Layers[i][2]) -m*Layers[i][2];

                            int temp_polarity = k % (Layers[i][2] * Layers[i][2]);
                            if (temp_x >= 0 && temp_y >= 0 && temp_x < dimensions[0] && temp_y < dimensions[1]) {

                                //cout << temp_y << "\t" << temp_x <<"\t" << m << endl;
                                weight = d.data[count + k + m*Layers[i][2]*Layers[i][2] + l*temp_tensor*Layers[i][2]*Layers[i][2]];
                                int Neuron = neurons_last_layer + temp_x + temp_y*dimensions[1] + m*dimensions[0] * dimensions[1];
                                //cout << "Neuron:\t" << Neuron << " Weight:\t" <<weight<<endl;
                                if(neurons==64){
                                    //cout << "X:\t" << temp_x << "Y:\t" << temp_y <<"K:\t"<<k<<"m:\t"<<m<<"j:\t"<<j<<endl;
                                    //cout << "Neuron:\t" << Neuron << endl;
                                }
                                temp.push_back({Neuron, weight, {0, false},-1});
                            }
                        }

                        Neuron Neurontemp = {input_neurons + neurons, 10, temp};
                        Simulation.AddNeuron(i, Neurontemp);
                        temp.clear();
                        neurons++;
                    };
            };
            neurons_last_layer = input_neurons;
            input_neurons +=neurons;

            //cout << "total amount of neurons = " << input_neurons<< endl;
            count+=Layers[i][2]*Layers[i][2]*temp_tensor*dimensions[2];
        }
        else if (Layers[i][4] == 3){
            Simulation.AddCluster();
            Simulation.MakeNeuronListFull({dimensions[0],dimensions[1],dimensions[2]},Layers[i][0],i);
            int temp_x = dimensions[0];
            int temp_y = dimensions[1];
            dimensions[0] = Layers[i][0];
            int temp_tensor = dimensions[2];
            dimensions[1] = 1;
            dimensions[2] = 1;
            double weight;
            int neurons=0;

            vector<tuple<int,double,STint,int>> temp;
            cout << "Layer: " << i+1 << " is of type Fullyconnected\t" << "Dimensions: " << dimensions[0] << "*" << dimensions[1] << "\tPolarities: " << dimensions[2]<< endl;
            for (int l=0; l < dimensions[0];l++) {
                for (int k=0; k < temp_tensor;k++) {
                    for (int j = 0; j < temp_x * temp_y; j++) {
                        weight = d.data[count + k*(temp_x * temp_y) + l*(temp_tensor*temp_x * temp_y) + j];
                        int Neuron = neurons_last_layer +  k*(temp_x * temp_y) + l*(temp_tensor*temp_x * temp_y) + j;
                        temp.push_back({Neuron, weight, {0, false},-1});
                    }
                }
                Neuron Neurontemp = {input_neurons + neurons, 10, temp};
                Simulation.AddNeuron(i, Neurontemp);
                //cout << "Neuron:\t" << neurons << " Weight:\t" <<weight<<" count\t"<< count <<endl;
                temp.clear();
                neurons++;
            }
            neurons_last_layer = input_neurons;
            input_neurons +=neurons;
            //cout << dimensions[0]*temp_x*temp_y*temp_tensor << endl;
            count+= dimensions[0]*temp_x*temp_y*temp_tensor;
            //cout << count << endl;
        }
    }
    Simulation.MakeNeuronListOutput({dimensions[0],dimensions[1],dimensions[2]},Layers.size()-1);
}
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
    NeuronCluster.push_back((Neuron1));
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
        vector<tuple<int,double,STint,int>> temp3;
        for(int j=0;j<d.shape[2];j++){
            temp3.push_back({j,network[0][i][j],{0,false},-1});
        }
        Neuron Neurontemp = {34*34*2-1+i,10,temp3};
        Simulation.AddNeuron(1,Neurontemp);
    }
    cout << "Second layer done" << endl;
    for(int i=0;i<temp2;i++){
        vector<tuple<int,double,STint,int>> temp3;
        for(int j=0;j<d.shape[1];j++){
            temp3.push_back({j+d.shape[2],network[1][i][j],{0,false},-1});
        }
        Neuron Neurontemp = {34*34*2+511+i,10,temp3};
        Simulation.AddNeuron(2,Neurontemp);
    }
    cout << "Third layer done" << endl;
    Simulation.MakeNeuronListFullConnected({34*34*2,512,10});
}