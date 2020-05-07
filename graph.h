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
class Vertex{
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

    Graph(){
        size = 0;
    }

    void addVertex(T nameIn){
        Vertex<T>* temp = new Vertex<T>(nameIn);
        verticies.push_back(temp);
        size++;
    }

    void addEdge(T headIn, T tailIn){
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

    void print(ofstream& outFile){
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
        for(int i = 0; i < verticies.size(); i ++){
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

        if(loners.size() == 0){
            loners.push_back(verticies[0]);
        }
        for(int i = 0; i < loners.size(); i++){
            tortise = loners[i];
            hare = tortise->child->child;
            while(hare != nullptr && hare->child != hare){
                if(tortise == hare){
                    loopFound = true;
                    //outFile << "Broke after " << i << " itrs" << endl;
                    i = loners.size();
                    break;
                }else{
                    tortise = tortise->child;
                    if(hare->child != nullptr){
                        hare = hare->child->child;
                    }else{
                        hare  = nullptr;
                    }

                }
            }
        }

        if(loopFound){
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
        bool isloner = true;
        for(int i = 0; i < verticies.size(); i ++){
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

        if(loners.size() == 0){
            loners.push_back(verticies[0]);
        }
        for(int i = 0; i < loners.size(); i++){
            curr  = loners[i];
            //outFile << curr->name << endl;
            bookkeeping[curr->name] = loners[i];
            while(curr->child != nullptr && curr->child != curr){
                    if(bookkeeping.count(curr->child->name) > 0){
                        loopFound = true;
                        //outFile << "Broke after " << i << " itrs" << endl;
                        i = loners.size();
                        break;
                    }else{
                        bookkeeping[curr->child->name] = curr->child;
                        curr = curr->child;

                    }
            }
            bookkeeping.clear();
        }

        if(loopFound){
            outFile << "FOUND LOOP" << endl;
        }else{
            outFile <<"NO LOOP FOUND" << endl;
        }
    }

    void clear(){
        size = 0;
        verticies.clear();
        edges.clear();
    }


};

#endif //PA04_GRAPH_H
