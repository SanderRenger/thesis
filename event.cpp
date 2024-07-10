//
// Created by sander on 22/10/2023.
//
#include <vector>
#include <array>
#include <tuple>
#include <iostream>
#include <set>

#include "event.h"
const int MAXNEURON = 20000000;
event::event(){
    delay=0;
    neuronNumber=0;
    strength=1;
}

event::event(int nn, int d) {
    delay = d;
    neuronNumber= nn;
    strength=1;
}

int event::getneuronNumber(){
    return neuronNumber;
}

int event::getdelay() {
    return delay;
}
int event::getstrength() {{
    return strength;
}}
void event::lowerdelay() {
    delay--;

}
void event::increasestrength(){
    strength++;
}
void EventHandler::addEvent(const event &event_t) {
    eventqueue.push_back(event_t);
}

EventHandler::EventHandler() {
    total_events=0;
    queuesize=0;
    newqueuesize=0;
    layer = 0;
    append = 0;
    for(int & i : output){
        i = 0;
    }
}

void EventHandler::addgammaevents(NeuralNetwork &NNetwork){
    vector<array<int,2>> temp;
    temp = NNetwork.Getallclusters();
    //cout << temp.size();
    for(int i=0;i<temp.size();i++){
        eventqueue.push_back({MAXNEURON+i,get<1>(temp[i])});
    }
}

void EventHandler::handleEvents(NeuralNetwork &NNetwork, int current_time) {
    vector<tuple<int,STint>> temp;
    while (!eventqueue.empty()) {
        if (eventqueue.back().getdelay() != 0) {
            event tempevent = eventqueue.back();
            tempevent.lowerdelay();
            newqueue.push_back(tempevent);
            eventqueue.pop_back();
        }
        else {
            int eventnumber = eventqueue.back().getneuronNumber();
            if (eventnumber>=MAXNEURON){
                cout << "oh no" << endl;
                int cluster = eventnumber - MAXNEURON;
                NNetwork.GammaCycle(cluster);
                newqueue.push_back({eventnumber,NNetwork.GetGammafrequency(cluster)-1});
                eventqueue.pop_back();
                //cout << "Gammacycle event:\t" << cluster << "\ttime:\t" << current_time << endl;
            }
            else {
                event current_neuron = eventqueue.back();
                int test = NNetwork.GetCluster(current_neuron.getneuronNumber());
                NNetwork.ActivateNeuron(current_neuron.getneuronNumber(),  current_time,current_neuron.getstrength());

                if (test!=-1){
                    NNetwork.setfired(test,current_neuron.getneuronNumber(), current_time);
                }
//                for (int i = 0; i < eventqueue.size() - 1; i++) {
//                    if ((current_neuron.getneuronNumber() == eventqueue[i].getneuronNumber()) &&
//                        current_neuron.getneuronNumber() >= 34 * 34 * 2) {
//                        eventqueue.erase(eventqueue.begin() + i);
//                        queuesize--;
//                    }
//                }
//                set<int> valid_values ={26672,26673,26674,26675,26800,26801,26802,26803,26928,26929,26930,26931,27056,27057,27058,27059};
//                if (valid_values.count(current_neuron.getneuronNumber())){
//                    output[0]++;
//                    cout <<"strength:\t" << current_neuron.getstrength() << "Neuron:\t" <<current_neuron.getneuronNumber()<<endl;
//                }
                if ( NNetwork.GetCluster(current_neuron.getneuronNumber())>(0)){
                        cout << "Neuron:\t" << current_neuron.getneuronNumber();
                        cout << "\tin layer: " <<0<< " Fired\t";
                        cout << queuesize << " events left" << endl;
                //    output[current_neuron.getneuronNumber()-(34*34*2+512)]++;
                }
                else if ( NNetwork.GetCluster(current_neuron.getneuronNumber())>(1)){
                   cout << "Neuron:\t" << current_neuron.getneuronNumber();
                   cout << "\tin layer: " <<1<< " Fired\t";
                   cout << queuesize << " events left" << endl;
                }
                else {
                    //cout << "\tin layer:" <<1<< " Fired\t" << endl;
                }
                if (append == layer){
                    append+=1;
                    std::ostringstream directory;
                    directory << "events";
                    namespace fs = std::filesystem;
                    fs::create_directories(directory.str());
                    ofstream file;
                    std::ostringstream filename;
                    filename << "events/Layer_"<<layer<<".txt";
                    file.open (filename.str());
                    file<< "Event:\t"<< current_neuron.getneuronNumber()<<"\t\tEvents Handled: " <<  total_events<<"\t\tQueuesize: " <<  queuesize<<"\t\tNewQueuesize: " <<  newqueuesize<< "\t\tcurrent_time: \t"<< current_time<<"\t\tLayer:\t"<< layer<<endl;
                    file.close();
                }
                else{
                    ofstream file;
                    std::ostringstream filename;
                    filename << "events/Layer_"<<layer<<".txt";
                    file.open (filename.str(),std::ios_base::app);
                    file<< "Event:\t"<< current_neuron.getneuronNumber()<<"\t\tEvents Handled: " <<  total_events<<"\t\tQueuesize: " <<  queuesize<<"\t\tNewQueuesize: " <<  newqueuesize<< "\t\tcurrent_time: \t"<< current_time<<"\t\tLayer:\t"<< layer<<endl;
                    file.close();
                }
                if (total_events%10000==0){
                    //eventqueue.clear();
                    //newqueue.clear();
                    cout << "Events Handled: " <<  total_events<<"\tQueuesize: " <<  queuesize<<"\tNewQueuesize: " <<  newqueuesize<< "\tcurrent_time: \t"<< current_time<<"\tLayer:\t"<< layer<<endl;
                }
                total_events++;
                eventqueue.pop_back();
                queuesize--;
            }
        }



    }
    temp = NNetwork.Output(current_time);
    for (int i = 0; i < temp.size(); i++) {
        newqueuesize++;
        newnewqueue.push_back({get<0>(temp[i]), get<1>(temp[i]).get_int()+current_time});
        if (get<0>(temp[i])>(34*34*2-1)){
           //cout << get<0>(temp[i]) << endl;
        }
    }
}


void EventHandler::printqueuesize() {
    cout << "queue size:\t" << eventqueue.size() << endl;
}
void EventHandler::printqueue() {
    cout << "queue:" <<endl;
    for (int i=0; i<eventqueue.size();i++){
        cout << "Neuron:\t"<<(eventqueue[i].getneuronNumber()) <<"\tDelay:\t" <<eventqueue[i].getdelay()<< endl;

    }
    cout << endl;
};

void EventHandler::printqueuetofiletxt(string filename) {
    ofstream file;
    file.open (filename);
    for (int i=0; i<eventqueue.size();i++){
        file  << "Neuron:\t"<<(eventqueue[i].getneuronNumber()) <<"\tDelay:\t" <<eventqueue[i].getdelay()<< endl;

    }
    file << endl;
    file.close();
};
void EventHandler::printqueuetofilenpy(string filename) {
    ofstream file;
    file.open (filename);
    vector<int> queue;
    for (int i=0; i<eventqueue.size();i++){
        queue.push_back(eventqueue[i].getneuronNumber());
        queue.push_back(eventqueue[i].getdelay());
        queue.push_back(eventqueue[i].getstrength());
    }
    npy::npy_data_ptr<int> d;
    d.data_ptr = queue.data();
    d.shape =  {3,unsigned(queue.size())/3};
    d.fortran_order = false; // optional
    npy::write_npy(filename, d);
    file << endl;
    file.close();
};

void EventHandler::printnewqueue() {
    cout << "new queue:" <<endl;
    for (int i=0; i<newqueue.size();i++){
        cout << "Neuron:\t"<<(newqueue[i].getneuronNumber()) <<"\tDelay:\t" <<newqueue[i].getdelay()<< endl;

    }
    cout << endl;
};
void EventHandler::swapqueue() {
    eventqueue = newqueue;
    newqueue.clear();
}


void EventHandler::swapnewqueue() {
    eventqueue = newnewqueue;
    newnewqueue.clear();
    newqueuesize=0;
    queuesize = eventqueue.size();
    layer += 1;

}

bool EventHandler::empty() {
    return eventqueue.empty();
}

void EventHandler::createevents(string filename, array<int,2> format) {
    //cout << filename.back() << endl;
    if (filename.back()=='2'){
        TimeData_npy TD = Read_Ndataset_bs2(filename);
    }
    else if (filename.back()=='y'){
        TimeData_npy TD = Read_Ndataset_npy(filename);
        //cout << "test"<<  TD.x.size()<< endl;
        int lastNeuronNewDelay=0;
        int delay=0;
        double Scale = 400/double(TD.ts.back());
        cout << TD.ts.size() << endl;
        for(int i =0;i<TD.x.size();i++){

            event event_t = {(TD.x[i]+TD.y[i]*format[1])+((format[1]*format[0])*(TD.p[i])),int(round(double((TD.ts[i]))*Scale))};
            //cout <<"Delay:\t" << event_t.getdelay()<< endl;
            if (delay <int(round(double((TD.ts[i]))*Scale))){
                delay =int(round(double((TD.ts[i]))*Scale));
                lastNeuronNewDelay =eventqueue.size();

            }
            int size = eventqueue.size();
            bool duplicate = false;
            for(int j=lastNeuronNewDelay;j<size;j++) {
                if (eventqueue[j].getneuronNumber() == event_t.getneuronNumber() &&eventqueue[j].getdelay() == event_t.getdelay()) {
                    //eventqueue[j].increasestrength();
                    duplicate = true;
                    //cout << "delete" << endl;
                }
            }
            if(!duplicate){            queuesize++;    eventqueue.push_back(event_t);}
            //cout << event_t.getneuronNumber() << endl;

            //std::cout << "X: "<< int(TD.x[i]) << "\tY: " << int(TD.y[i]) << "\tP: " << int(TD.p[i]) <<"\tT: " << static_cast<int>(TD.ts[i]) << std::endl;
        }
    }

    else{
        return;
    }
    cout << queuesize << endl;

    //cout << "done loading the input data" << endl;
}

void EventHandler::printoutput(){
    for(int i = 0; i<output.size();i++){
        cout << "Output:\t" << output[i] << endl;
    }
}
int EventHandler::saveoutput(){
    int max = 0;
    int out = 0;
    for(int i = 0; i<output.size();i++){
        if (output[i] > max){
            max = output[i];
            out = i;
        }
    }
    return out;
}

bool EventHandler::isempty(){
    return eventqueue.empty();

}