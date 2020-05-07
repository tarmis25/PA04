//
// Created by Travis Armistead on 5/6/20.
//

#ifndef PA04_GRAPH_H
#define PA04_GRAPH_H
#include<iostream>
#include <unordered_map>
#include <stack>
#include <queue>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

template <typename T>
class Vertex{  //My vertex class is pirated from my other project and then i changed  with there only being one child
    //and then to use later in the graph class instead of using an edge class to contain
public:
    T name;
    bool visited = false;
    bool queEd = false;
    //vector<Vertex<T>*> children;
    Vertex<T>* child = nullptr;
    Vertex(T nameIn){
        name = nameIn;
    }
    void addChild(Vertex<T>* childIn){
        //children.push_back(childIn);
        child = childIn;
    }
    void print(ofstream& outFile){
        outFile << name << ": " << "Children: ";
        if(child != nullptr){
            outFile << child->name;
        }
        outFile << endl;
    }

};


template <typename T>
class Graph{
public:
    int size;
    vector<Vertex<T>*> verticies;
    vector<pair<Vertex<T>*,Vertex<T>*>> edges;

    Graph(){ //initialixzing graph elements
        size = 0;
    }

    void addVertex(T nameIn){//this is adding all of the initial vertexes to later be manipulated for the algs
        Vertex<T>* temp = new Vertex<T>(nameIn);
        verticies.push_back(temp);
        size++;
    }

    void addEdge(T headIn, T tailIn){ // adding the edge to the vector but more importantly setting the vertex child
        Vertex<T>* head;
        Vertex<T>* tail;
        for(int i = 0; i < verticies.size(); i++){
            if(verticies[i]->name == headIn){
                head = verticies[i];
            }
        }
        for(int i = 0; i < verticies.size(); i++){
            if(verticies[i]->name == tailIn){
                tail = verticies[i];
            }
        }
        head->addChild(tail);
        edges.push_back(pair<Vertex<T>*,Vertex<T>*>(head,tail));
    }

    void print(ofstream& outFile){ //just used for testing the data set to make sure that I have the correct points
        for(int i = 0; i < verticies.size(); i++){
            verticies[i]->print(outFile);
        }
    }

    void FloydsAlg(ofstream& outFile){
        vector<Vertex<T>*> loners;
        Vertex<T>* tortise = nullptr;
        Vertex<T>* hare = nullptr;
        bool loopFound = false;
        bool isloner = true;
        for(int i = 0; i < verticies.size(); i ++){//this initial area is accounting for a graph that has seperated
            for(int x = 0 ; x < edges.size(); x++){//nodes that might have a loop imbedded in them
                if(edges[x].second->name == verticies[i]->name){
                    isloner = false;
                }
            }
            if(isloner){
                loners.push_back(verticies[i]);
            }
            isloner = true;
        }

        if(loners.size() == 0){ // here if there is only one grouping there will need to be something that can be the
            loners.push_back(verticies[0]);//start for the loop
        }
        for(int i = 0; i < loners.size(); i++){
            tortise = loners[i];//setting the tortise pointer to the start
            hare = tortise->child->child;
            while(hare != nullptr && hare->child != hare){ //making sure the hare has not reached the end of the graph
                if(tortise == hare){//if they are equal then there is definitly a loop
                    loopFound = true;
                    //outFile << "Broke after " << i << " itrs" << endl;
                    i = loners.size();
                    break;
                }else{ //else we want to iterate the tortise and the hare as long as not null ptr
                    tortise = tortise->child;
                    if(hare->child != nullptr){
                        hare = hare->child->child;
                    }else{
                        hare  = nullptr;
                    }

                }
            }
        }

        if(loopFound){ //print out to show weather or not loop found
            outFile << "FOUND LOOP" << endl;
        }else{
            outFile <<"NO LOOP FOUND" << endl;
        }



    }

    void trivAlg(ofstream& outFile){
        vector<Vertex<T>*> loners;
        unordered_map<T, Vertex<T>*> bookkeeping;
        Vertex<T>* curr = nullptr;
        bool loopFound = false;
        bool isloner = true;//same as before this section is to make sure that if there are multiple they are
        for(int i = 0; i < verticies.size(); i ++){//accounted for
            for(int x = 0 ; x < edges.size(); x++){
                if(edges[x].second->name == verticies[i]->name){
                    isloner = false;
                }
            }
            if(isloner){
                loners.push_back(verticies[i]);
            }
            isloner = true;
        }
//        outFile << "Loners: ";
//        for(int i = 0; i < loners.size(); i++){
//            outFile << loners[i]->name << " ";
//        }
//        outFile << endl;

        if(loners.size() == 0){ //same here showing that there needs to be a start point so pushing one back
            loners.push_back(verticies[0]);
        }
        for(int i = 0; i < loners.size(); i++){
            curr  = loners[i];
            //outFile << curr->name << endl;
            bookkeeping[curr->name] = loners[i]; //putting the start into the hash so that can be compared later
            while(curr->child != nullptr && curr->child != curr){ // as long as the curr is not at the end of the graph
                    if(bookkeeping.count(curr->child->name) > 0){ // then keep going and to check if in the map there
                        loopFound = true; // esxists the child which would indicate a loop found
                        //outFile << "Broke after " << i << " itrs" << endl;
                        i = loners.size();
                        break;
                    }else{ // if not to push the item into the map and move the curr along
                        bookkeeping[curr->child->name] = curr->child;
                        curr = curr->child;

                    }
            }
            bookkeeping.clear(); //clear the map becasue we are moving onto the next island and want clear map
        }

        if(loopFound){ // indicating if it is found a loop or not
            outFile << "FOUND LOOP" << endl;
        }else{
            outFile <<"NO LOOP FOUND" << endl;
        }
    }

    void clear(){ // clearing out in between different graphs
        size = 0;
        verticies.clear();
        edges.clear();
    }


};

#endif //PA04_GRAPH_H
