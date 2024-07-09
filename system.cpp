//
// Created by sander on 28/09/2023.
//
#include <vector>
#include <array>
#include <iostream>
#include "system.h"
NeuralNetwork::NeuralNetwork(){
    Neurons_total = 0;
    NeuronList;
    NeuronClusters;
}

void NeuralNetwork::AddCluster(){
    NeuronCluster temp;
    NeuronClusters.push_back(temp);
}

vector<tuple<int, int, vector<int>,int>> NeuralNetwork::getNeuronList() {
    return NeuronList;
}

void NeuralNetwork::ActivateNeuron(int NeuronNumber, int current_time, int strength) {
    STint temp1;
    vector<tuple<int, STint>> temp2;
    int Neuroncluster = get<1>(NeuronList[NeuronNumber]);
    vector<int> Outputs = get<2>(NeuronList[NeuronNumber]);
    //cout<< "test2\t" << NeuronNumber<< endl;
    //cout << Outputs.size() << endl;
    int delay = get<3>(NeuronList[NeuronNumber]);
    NeuronClusters[get<1>(NeuronList[Outputs[0]])].ActivateNeuronInput(Outputs, NeuronNumber, current_time, strength);
}

vector<tuple<int,STint>> NeuralNetwork::Output(int current_time) {
    STint temp1;
    vector<tuple<int, STint>> temp2;
    int temp = NeuronClusters[0].GetNeuroncount();

    for (int i =NeuronClusters[0].Neuroncount()-1; i <NeuronList.size(); i++) {
       temp1 = NeuronClusters[get<1>(NeuronList[i])].Output(i, current_time);
        if (!temp1.get_bool()) {
            temp2.push_back({i, temp1});
        }
    }
    if (!temp2.empty()){
        return temp2;
    }
        return {};
}
vector<array<int,2>> NeuralNetwork::Getallclusters(){
    vector<array<int,2>> temp;
    for(int i=0; i<NeuronClusters.size();i++){
        temp.push_back({i,NeuronClusters[i].GetGammafrequency()});
    }
    return temp;
}

bool NeuralNetwork::DeleteNeuron(int NeuronNumber){
    vector<int> temp;
    for(int i=0;i<NeuronList.size();i++){
        if(get<0>(NeuronList[i])==NeuronNumber){
            NeuronClusters[get<1>(NeuronList[i])].RemoveNeuron(NeuronNumber);
            NeuronList.erase(NeuronList.begin()+i);
            return true;
        };
    }
    return false;
};

bool NeuralNetwork::UpdateNeuron(int NeuronNumber_t,double threshold_t,vector<tuple<int,double,STint,int>> inputConnections,vector<int> outputConnections_t) {
    for(int i =0;i<NeuronList.size();i++){
        if (NeuronNumber_t==get<0>(NeuronList[i])){
            NeuronClusters[get<1>(NeuronList[i])].UpdateNeuron(NeuronNumber_t,threshold_t,inputConnections);
             get<2>(NeuronList[i])=outputConnections_t;
            return true;
        }
    }
    return false;
}


void NeuralNetwork::UpdateThreshold(int NeuronNumber_t, double threshold_t) {

    for(int i =0;i<NeuronList.size();i++){
        if (NeuronNumber_t==get<0>(NeuronList[i])){
            NeuronClusters[get<1>(NeuronList[i])].UpdateThreshold(NeuronNumber_t,threshold_t);
        }
    }
}
bool NeuralNetwork::DeleteNeuron(int NeuronNumber, int ClusterNumber){
    vector<int> temp;
        temp = NeuronClusters[ClusterNumber].GetNeurons();
        for(int j=0;j<NeuronClusters[ClusterNumber].Neuroncount();j++){
            if(temp[j] == NeuronNumber){
                NeuronClusters[ClusterNumber].RemoveNeuron(j);
                for(int k=0;k<NeuronList.size();k++){
                    if(get<0>(NeuronList[k])== NeuronNumber) {
                        NeuronList.erase(NeuronList.begin()+k);
                    }
                }
                return true;
            }

        }
    return false;
};

bool NeuralNetwork::AddNeuron(int ClusterNumber){
    if(NeuronClusters.size() >= ClusterNumber){
        Neurons_total +=1;
        //NeuronList.push_back({Neurons_total-1,ClusterNumber,{},0});
        NeuronClusters[ClusterNumber].AddEmptyNeuron(Neurons_total-1);
        return true;
    }
    return false;
}

void NeuralNetwork::AddNeuron(int ClusterNumber, Neuron& Neuron){
    if(NeuronClusters.size() >= ClusterNumber){
        Neurons_total +=1;
        //NeuronList.push_back({Neurons_total-1,ClusterNumber,{},0});
        NeuronClusters[ClusterNumber].AddNeuron(Neuron,Neuron.GetNeuronNumber());
    }

}

bool NeuralNetwork::AddNeuron(int ClusterNumber, int threshold_t,vector<tuple<int,double,STint,int>> inputConnections,vector<int> outputConnections_t){
    if(NeuronClusters.size() >= ClusterNumber){
        Neurons_total +=1;
        NeuronList.push_back({Neurons_total,ClusterNumber,{0},-1});
        NeuronClusters[ClusterNumber].AddEmptyNeuron(Neurons_total);
    }
    else {
        return false;
    }
    for(int i =0;i<NeuronList.size();i++){
        if (Neurons_total==get<0>(NeuronList[i])){
            NeuronClusters[get<1>(NeuronList[i])].UpdateNeuron(Neurons_total,threshold_t,inputConnections);
            get<2>(NeuronList[i])=outputConnections_t;
            return true;
        }
    }
    return false;
}
bool NeuralNetwork::UpdateGammaFrequency(int ClusterNumber,int Gammafrequency){
    if(NeuronClusters.size() >= ClusterNumber) {
        NeuronClusters[ClusterNumber].ChangeGammafrequency(Gammafrequency);
        return true;
    }
    return false;
};

int NeuralNetwork::GetGammafrequency(int ClusterNumber) {
    if(NeuronClusters.size() >= ClusterNumber) {
        int temp = NeuronClusters[ClusterNumber].GetGammafrequency();
        return temp;
    }
    return 0;
};

void NeuralNetwork::GammaCycle(int Cluster) {
    if(NeuronClusters.size() >= Cluster) {
        NeuronClusters[Cluster].DoGammaCycle();
    }

};
// Output, Input, Delay,weight
bool NeuralNetwork::Addconnection(int NeuronNumber_1, int NeuronNumber_2, int Delay,double weight_t) {
    int temp =0;
    bool temp2=false;
    int output;
    int input;
    int cluster;
    for(int i=0;i<NeuronList.size();i++){
        if (get<0>(NeuronList[i])==NeuronNumber_1){
            output = i;
            temp++;
            if (temp==2){
                temp2 = true;
                break;
            }
        }
        if (get<0>(NeuronList[i])==NeuronNumber_2){

            cluster = get<1>(NeuronList[i]);
            temp++;
            if (temp==2){
                temp2 = true;
                break;
            }
        }

    }
    get<2>(NeuronList[output]).push_back(NeuronNumber_2);
    get<3>(NeuronList[output]) = Delay;
    NeuronClusters[cluster].AddNeuronInput(NeuronNumber_1, NeuronNumber_2, weight_t);
    return temp2;
}

bool NeuralNetwork::Printclusterinformation(int clusternumber){
    NeuronClusters[clusternumber].printAllNeuronInformation();
    return true;
}

void NeuralNetwork::Printneuroninformation(int clusternumber, int neuronnumber){
    NeuronClusters[clusternumber].printNeuronInformation(neuronnumber);
}

void NeuralNetwork::Printneuroninformation(int NeuronNumber){
    for( int i=0; i< NeuronClusters.size(); i++){
        NeuronClusters[i].printNeuronInformation(NeuronNumber);
    }
}
void NeuralNetwork::PrintneuroninformationInputs(int NeuronNumber){
    for( int i=0; i< NeuronClusters.size(); i++){
        NeuronClusters[i].printNeuronInformation(NeuronNumber);
    }
}

void NeuralNetwork::PrintNeuronList(){
    cout << "Neurons: \t\t\t\t\t" << NeuronList.size() << endl << endl;
    cout << "Highest Neuron Number: \t\t\t\t"<< Neurons_total<<endl <<endl;

    cout << "Neurons Information: \t" << endl;
    for (auto & i : NeuronList){
        cout << "Neuron:\t"<<get<0>(i)<<"\tCluster\t" << get<1>(i)<<endl;
        for(auto & j : get<2>(i)){
            cout << "\tOutput:\t" << (j) << endl;
        }
    }
    cout << endl;
};

void NeuralNetwork::PrintNeuronList(int NeuronCluster){
    cout << "Neurons: \t\t\t\t\t" << NeuronList.size() << endl << endl;
    cout << "Highest Neuron Number: \t\t\t\t"<< Neurons_total<<endl <<endl;

    cout << "Neurons Information: \t" << endl;
    for (auto & i : NeuronList){
        if(NeuronCluster==get<1>(i)){
            cout << "Neuron:\t"<<get<0>(i)<<"\tCluster\t" << get<1>(i)<<endl;
            for(auto & j : get<2>(i)){
                cout << "\tOutput:\t" << (j) << endl;
            }
        }

    }
    cout << endl;
};

void NeuralNetwork::PrintNeuronListNeuron(int NeuronNumber){
    cout << "Neurons Information: \t" << endl;
    for (auto & i : NeuronList){
        if(NeuronNumber==get<0>(i)){
            cout << "Neuron:\t"<<get<0>(i)<<"\tCluster\t" << get<1>(i)<<endl;
            for(auto & j : get<2>(i)){
                cout << "\tOutput:\t" << (j) << endl;
            }
            return;
        }

    }
    cout << endl;
};

void NeuralNetwork::PrintNeuronListNeuronOutput(int NeuronNumber){
    cout << "Neurons Information: \t" << endl;
    for (auto & i : NeuronList){
        for(int j=0; j< get<2>(i).size();j++){
            if(NeuronNumber==get<2>(i)[j]){
                cout << "Neuron:\t"<<get<0>(i)<<"\tCluster\t" << get<1>(i)<<endl;
                for(auto & j : get<2>(i)){
                    cout << "\tOutput:\t" << (j) << endl;
                }
            }
        }
    }
    cout << endl;
};


vector<NeuronCluster> NeuralNetwork::GetSystem() {
        return NeuronClusters;
};
int NeuralNetwork::TotalNeurons() {
    return Neurons_total;
}

tuple<int, int,vector<int>,int> NeuralNetwork::GetNeuron(int NeuronNumber) {
    for (int i=0; i < Neurons_total; i++){
        if (NeuronNumber == get<0>(NeuronList[i])) {
            return NeuronList[i];
        }
    }
}
double NeuralNetwork::GetWeight(int Cluster, int Neuron, int Input) {
    return NeuronClusters[Cluster].GetWeight(Neuron, Input);
}

vector<vector<vector<double>>> NeuralNetwork::GetWeights() {
    vector<vector<vector<double>>> temp;
    for(int i=0;i<NeuronClusters.size();i++){
        temp.push_back(NeuronClusters[i].GetWeights());
    }
    return temp;
}

double NeuralNetwork::GetThreshold(int Cluster, int Neuron) {
    return NeuronClusters[Cluster].GetThreshold(Neuron);
}
int NeuralNetwork::GetCluster(int Neuron){
    return get<1>(NeuronList[Neuron]);
}

void NeuralNetwork::UpdateWeightdataset(string filename1,string filename2) {
    std::string path {filename1};
    npy::npy_data d = npy::read_npy<double>(path);

    std::vector<double> data = d.data;
    std::vector<unsigned long> shape = d.shape;
    int rows = d.shape[1];
    //cout << d.data[514]<< endl;
    int sizelayer1 = rows;
    //cout << sizelayer1 << endl;
       for (int i=0;i<data.size();i++){
            NeuronClusters[1].UpdateWeightDataset(int(i/rows),i%rows,data[i]);
    }
    path = filename2;
    d = npy::read_npy<double>(path);

    data = d.data;
       rows = d.shape[1];
    //cout << rows << endl;
    //cout << data.size() << endl;
    for (int i=0;i<data.size();i++){
        NeuronClusters[2].UpdateWeightDataset(int(i/rows),i%rows+sizelayer1,data[i]);
    }
}

void NeuralNetwork::PrintNeuronVoltagetofile(int Cluster){
    NeuronClusters[Cluster].GetVoltage(Cluster);
};
void NeuralNetwork::setfired(int cluster, int Neuron, int current_time){
    NeuronClusters[cluster].setfired(Neuron, current_time);
}

void NeuralNetwork::MakeNeuronListFullConnected(vector<int> shape){
    vector<tuple<int, int,vector<int>,int>> temp;
    int count=0;
    //cout << shape.size()<< endl;
    for(int k =0;k < shape.size()-1;k++){
        vector<int> outputs;
        count+=shape[k];
        //cout << count << endl;
        for(int i=0;i<shape[k+1];i++){
            //cout << count+i << endl;
            outputs.push_back(count+i);
        }
        for(int i=0;i<shape[k];i++){
            NeuronList.push_back({(i+count-shape[k]),k,outputs,0});
        }
    }
    for(int i=0;i<shape.back();i++){
        NeuronList.push_back({(i+count),shape.size()-1,{},0});
    }

};

void NeuralNetwork::MakeNeuronListPool(array<int,3> shapein,int poolsize,int clusternumber){
    int x_axis = shapein[0];
    int y_axis = shapein[1];
    int polarity = shapein[2];
    int neuron = NeuronList.size();
    //cout << x_axis << "\t" << y_axis << "\t" << polarity << "\t"<< clusternumber-1<< endl;
    tuple<int, int,vector<int>,int> temp;
    for (int k=0; k<polarity;k++){
        for (int j=0; j<y_axis;j++) {
            for(int i=0;i<x_axis;i++) {
                get<0>(temp) = neuron;
                get<1>(temp) = clusternumber - 1;
                int x_temp = int(i/poolsize);
                int y_temp = int(j/poolsize);
                int neuronnumber = (x_axis/poolsize)*(y_axis/poolsize)*k+x_temp +y_temp*x_axis/poolsize;
                neuronnumber +=x_axis*y_axis*polarity;
                get<2>(temp).push_back(neuronnumber);
                get<3>(temp)=0;
                neuron++;
                NeuronList.push_back(temp);
                get<2>(temp).clear();
            }
        }
    }
    //cout << "Neuronlist size:\t" << NeuronList.size() << endl;
    return;
};

void NeuralNetwork::MakeNeuronListConv(array<int,4> shapein,int poolsize,int clusternumber){
    int x_axis = shapein[0];
    int y_axis = shapein[1];
    int polarity_in = shapein[2];
    int polarity_out = shapein[3];
    int neuron = NeuronList.size();
    int neuron_start = neuron;
    //cout << x_axis << "\t" << y_axis << "\t" << polarity_in << "\t"<< clusternumber-1<< endl;
    tuple<int, int,vector<int>,int> temp;

    for (int k=0; k<polarity_in;k++) {
        for (int j = 0; j < y_axis; j++) {
            for (int i = 0; i < x_axis; i++) {
                get<0>(temp) = neuron;
                get<1>(temp) = clusternumber - 1;
                int neuronnumber;
                for (int m = 0; m < polarity_out; m++) {
                    for (int y_temp = -int(poolsize / 2); y_temp < int(poolsize / 2) + 1; y_temp++) {
                        for (int x_temp = -int(poolsize / 2); x_temp < int(poolsize / 2) + 1; x_temp++) {
                            if (x_temp + i >= 0 && x_temp + i < x_axis && y_temp + j >= 0 && y_temp + j < x_axis) {
                                neuronnumber = x_temp + i + (y_temp + j) * x_axis + y_axis * x_axis * k + x_axis * y_axis * polarity_in * m + neuron_start +x_axis*y_axis*polarity_in;
                                get<2>(temp).push_back(neuronnumber);
                            }
                        }
                    }
                }
                get<2>(temp).push_back(neuronnumber);
                get<3>(temp) = 0;
                neuron++;
                NeuronList.push_back(temp);
                get<2>(temp).clear();
            }
        }
    }
    //cout << "Neuronlist size:\t" << NeuronList.size() << endl;
}

void NeuralNetwork::MakeNeuronListFull(array<int,3> shapein,int neuronsout,int clusternumber){
    int x_axis = shapein[0];
    int y_axis = shapein[1];
    int polarity_in = shapein[2];
    int neuron = NeuronList.size();
    int neuron_start = neuron;
    //cout << x_axis << "\t" << y_axis << "\t" << polarity_in << "\t"<< clusternumber-1<< endl;
    tuple<int, int,vector<int>,int> temp;
    for (int k = 0; k < polarity_in; k++) {
        for (int j = 0; j < y_axis; j++) {
            for (int i = 0; i < x_axis; i++) {
                get<0>(temp) = neuron;
                get<1>(temp) = clusternumber - 1;
                for (int l=0; l<neuronsout;l++) {
                    int neuronnumber = neuron_start + x_axis * y_axis * polarity_in +l;
                    get<2>(temp).push_back(neuronnumber);
                }
                get<3>(temp) = 0;
                neuron++;
                NeuronList.push_back(temp);
                get<2>(temp).clear();
            }
        }
    }
    //cout << "Neuronlist size:\t" << NeuronList.size() << endl;
}

void NeuralNetwork::MakeNeuronListOutput(array<int,3> shapein,int clusternumber){
    int x_axis = shapein[0];
    int y_axis = shapein[1];
    int polarity_in = shapein[2];
    int neuron = NeuronList.size();
    int neuron_start = neuron;
    //cout << x_axis << "\t" << y_axis << "\t" << polarity_in << "\t"<< clusternumber-1<< endl;
    tuple<int, int,vector<int>,int> temp;
    for (int k = 0; k < polarity_in; k++) {
        for (int j = 0; j < y_axis; j++) {
            for (int i = 0; i < x_axis; i++) {
                get<0>(temp) = neuron;
                get<1>(temp) = clusternumber - 1;
                get<3>(temp) = 0;
                neuron++;
                NeuronList.push_back(temp);
            }
        }
    }
    //cout << "Neuronlist size:\t" << NeuronList.size() << endl;
}

void NeuralNetwork::DeleteConnectionRandom(int NeuralCluster, int connections){
    srand ( time(NULL) );
    int temp;
    int size = NeuronClusters[NeuralCluster].GetNeuroncount();
    for(int i=0; i<Neurons_total;i++){
        if(get<1>(NeuronList[i])==NeuralCluster){
            temp = i;
            break;
        }
    }
    //cout << "Layer: " << NeuralCluster << "\t Starts at: " << temp << endl;
    for(int i=0; i<connections;i++){
        int random = temp +rand()%size;
        int cluster = get<1>(NeuronList[random]);
        int vectorsize = get<2>(NeuronList[random]).size();
        if (vectorsize != 0){
            int deletedconnection = rand()%vectorsize;
            get<2>(NeuronList[random]).erase(get<2>(NeuronList[random]).begin()+deletedconnection);
        }
        else{
            i--;
        }
    }
    cout << "Deleted connections: " << connections << endl;
}