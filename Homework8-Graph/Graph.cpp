#include "Graph.hpp"
#include<vector>
#include<iostream>
#include <queue>
using namespace std;


//All functions working. No driver, none provided


void Graph::addEdge(string v1, string v2){
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
                }
            }
        }
    }
}

void Graph::addVertex(string name){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == name){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->name = name;
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    for(auto x : vertices){
        cout << x->name << " --> ";
        for(auto y : x->adj){
            cout << y.v->name << " ";
        }
        cout << endl;
    }
}




void Graph::breadthFirstTraverse(string sourceVertex){
    queue<vertex*> q;
    vertex* vStart;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == sourceVertex)
        {
            vStart = vertices[i];
        }
    }
    cout << "Starting vertex (root): " << vStart->name << "-> ";
    vStart->visited = true;
    q.push(vStart);
    vertex* n;
    while(!q.empty()){
        n = q.front();
        q.pop(); 
        for( int x = 0; x < n->adj.size(); x++ ){
            if(n->adj[x].v->visited == false){
                n->adj[x].v->distance = n->distance + 1;
                cout << n->adj[x].v->name << "(" << n->adj[x].v->distance << ")" << " ";
                n->adj[x].v->visited = true;
                q.push(n->adj[x].v);              
            }
        }
    }
  
    
}

void BFSnoprint(vertex* src){
    queue<vertex*> q;
    q.push(src);
    vertex* n;
    while(!q.empty()){
        n = q.front();
        q.pop(); 
        for( int x = 0; x < n->adj.size(); x++ ){
            if(n->adj[x].v->visited == false){
                n->adj[x].v->distance = n->distance + 1;
                n->adj[x].v->visited = true;
                q.push(n->adj[x].v);              
            }
        }
    }
  
    
}

int Graph::getConnectedBuildings(){
    for(auto x : vertices){
        x->visited = false;
        for(auto y : x->adj){
            y.v->visited = false;
        }
    }
    int count = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->visited == false){
            BFSnoprint(vertices[i]);
            count += 1;
        }
    }
    return count;

}


