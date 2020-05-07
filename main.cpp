//
// Created by Travis Armistead on 5/6/20.
//
#include<iostream>
#include "graph.h"
#include <chrono>
#include <fstream>


using namespace std;
int main(){

    Graph<int> joe;

    ofstream outFile;
    outFile.open("output.txt");
    if (!outFile.is_open()) {
        throw runtime_error("Failed opening output File");
    }
    for(int x = 0; x < 5; x++) { //iterating through all of the different graph files
        outFile << "Graph #" << x << ": \n";

        ifstream inFile;
        string start = "graph_0";
        string toadd = to_string(x+1); //making a name for each one using the loop counter
        string end = ".txt";
        string filename = start + toadd + end;
        inFile.open(filename);
        if (!inFile.is_open()) {
            throw runtime_error("Failed opening graph File");
        }

        int count;
        inFile >> count;
        for (int i = 0; i < count; i++) { // adding each vertex into the graph class
            int temp;
            inFile >> temp;
            joe.addVertex(temp);
        }

        char brak;
        inFile >> brak;
        inFile >> count;
        inFile >> brak;

        for (int i = 0; i < count; i++) {//adding each edge to the graph class
            int temp;
            int temp2;
            inFile >> temp;
            inFile >> temp2;
            joe.addEdge(temp, temp2);
        }


        auto start_time = std::chrono::high_resolution_clock::now();//running and mecuring the time for the trivial
        joe.trivAlg(outFile);
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = current_time - start_time;
        outFile << "Trivial elapsed time: " << elapsed_seconds.count()*1000.00 << "ms\n";

        start_time = std::chrono::high_resolution_clock::now();//running and mecuring the time for the floyds
        joe.FloydsAlg(outFile);
        current_time = std::chrono::high_resolution_clock::now();
        elapsed_seconds = current_time - start_time;
        outFile << "Floyds elapsed time: " << elapsed_seconds.count()*1000.00 << "ms\n";
        joe.clear();//my apologies on the video i forgot to add the *1000 to the second so it apears the gap is way
        outFile << "\n\n";//biggere which had supprised me, which the trivial is still slower it is much closer now
        //which makes alot more sense, again my apologies
    }
}

