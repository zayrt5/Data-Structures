#include "dll.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <chrono> 
#include <time.h>
#include <sstream>
#include <random>
using namespace std;


DLL::DLL(){
    head = NULL;
}

bool DLL::isEmpty(){
    return (head == NULL);

}

void DLL::recInsert(int* inArr, float* insert, float* search){
    int total = 0;
    int insertIndex = 0;

    //https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/?ref=lbp
    //Everyone shits on srand()
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < 10000; i++){
        addNode(inArr[i]);
        total++;
        //if the structure currently has a multiple of 100 elements
        if(total % 100 == 0){
            auto end = chrono::high_resolution_clock::now();
            double tt = 
                chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            tt *= 1e-9; //nanoseconds to seconds. Using seconds directly breaks things
            float duration = float(tt) /100; //taking the time of 100 inserts and /100 to get average per
            recSearch(inArr, search, total); //run same thing but for search
            insert[insertIndex] = duration;
            insertIndex++;
            start = chrono::high_resolution_clock::now();
        }
    }

}

void DLL::recSearch(int* inArray, float* search, int numEntries){
    int index[100];
    //https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    //EVEN DISTRIBUTION FLEX TOWN
    //Creates random distribution of 100 searchable indeces
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, numEntries);
    for(int i = 0; i < 100; i++){
        index[i] =  uni(rng);
    }

    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < 100; i++){
        int searchKey = inArray[index[i]];
        Node* n = nodeSearch(searchKey);
    }
    auto end = chrono::high_resolution_clock::now();
    double tt = 
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    tt *= 1e-9;
    float duration = float(tt) /100;
    search[(numEntries / 100) - 1] = duration;

}

void DLL::addNode(int key){
    if(isEmpty()){
        head = new Node;
        head->key = key;
        head->next = NULL;
        head->prev = NULL;
    }

    else{
        //cout << key << endl;
        Node* nn = new Node;
        nn->key = key;
        nn->next = head;
        head->prev = nn;
        head = nn;
        nn->prev = NULL;

    }
}


Node* DLL::nodeSearch(int key){
    //cout << "Searching for " << key << endl;
    Node* crawler = head;
    while(crawler != NULL && crawler->key != key){
        crawler = crawler->next;
    }
    /*if(crawler != NULL){
        cout << "Found" << endl;
    }
    else{
        cout << "Not found" << endl;
    }*/
    return crawler;
}


void DLL::display(){
    cout << "Printing DLL: " << endl << endl;
    if(isEmpty()){
        cout << "Nothing in list" << endl;
    }
    else{
        Node* crawler = head;
        while (crawler->next != NULL){
            cout << crawler->key << " -> ";
            crawler = crawler->next;
        }
        cout << crawler->key << endl;
    }

}