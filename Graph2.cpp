#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


//dijsktra no worky. everything else good

void addWeight(vertex* v1, vertex* v2, int num){
    for(int i = 0; i < v1->adj.size(); i++){
        if(v1->adj[i].v == v2){
            for(int j = 0; j < v2->adj.size(); j++){
                if(v2->adj[j].v == v1){
                    v1->adj[i].weight = num;
                    v2->adj[j].weight = num;
                }
            }
        }
    }
}

void Graph::createEdge(string v1, string v2, int num){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == v2 && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                    addWeight(av.v, av2.v, num);
                }
            }
        }
    }

}

void Graph::insertVertex(string n){

}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    // cout<<"here"<<vertices.size()<<endl;
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<endl;
        for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
            cout<<" --> "<< vertices[i]->adj[j].v->name << " "<<vertices[i]->adj[j].weight<<endl;
        }
        cout<<endl;
    }
}




void Graph::traverseWithDijkstra(string start){
    vertex* vStart;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == start)
        {
            vStart = vertices[i];
        }
    }

    /*src: geeksforgeeks with their priority queue implementation of dijkstra. who knows
    if this will even work. I dont. a 75 is solid
    */
    priority_queue < vertex*, vector <vertex*> , greater<vertex*> > pq;
    pq.push(vStart);
    while(!pq.empty()){
        vertex* n = pq.top();
        pq.pop();

        for(int i = 0; i < n->adj.size(); i++){
            vertex* v = n->adj[i].v;
            v->distance = n->distance + n->adj[i].weight;
            if(n->distance > v->distance){
                pq.push(v);
            }
        }
    }


    
}




void dftHelper(vertex* n){
    n->visited = true;
    cout << n->name << " -> ";

    for(int x = 0; x < n->adj.size(); x++ )
    {
        if(n->adj[x].v->visited == false){
            dftHelper(n->adj[x].v);
        }
    }
}

void Graph::depthFirstTraversal(string sourceVertex)
{
    vertex* n;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == sourceVertex)
        {
            n = vertices[i];
        }
    }
    dftHelper(n);
    cout << "DONE";

}

void Graph::minDistPath(string source, string destination) {
    vertex* vEnd;
    vertex* vStart;
    traverseWithDijkstra(source);
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == destination){
            vEnd = vertices[i];
        }
    }
    vector<vertex*> shortPath;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == source){
            vStart = vertices[i];
        }
        vertices[i]->visited = false;
    }

    vertex* vCurrent = vEnd;
    
    
    //cout << "Dij Traversed" << endl;

    shortPath.push_back(vEnd);
    while(vCurrent->pred != NULL && vCurrent->pred->visited == false){
        vCurrent->pred->visited = true;
        //cout << "Adding pred of " << vCurrent->name << " to vector... " << vCurrent->pred->name << endl;
        shortPath.push_back(vCurrent->pred);
        vCurrent = vCurrent->pred;
        if(vCurrent->name == source)
            break;
    }
    //cout << "All preds added" << endl;

    for(int i = shortPath.size() - 1; i >= 0; i--){
        cout << shortPath[i]->name << " -> ";
    }

    cout << "DONE " << "[" << vEnd->distance << "]" << endl;
}
