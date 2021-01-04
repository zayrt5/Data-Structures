
#include "hashquad.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <chrono> 
#include <time.h>
#include <sstream>
#include <random>
using namespace std;



HashTable::HashTable(int bsize){
    this->tableSize= bsize;
    table = new int[bsize];
}

bool HashTable::insertKey(int key){
    int index = hashFunction(key);
    if(table[index] == 0){
        //cout << "No collision hash: " << index << endl;
        table[index] = key;
        return true;
    }
    else{
        int q = 0;
        while(table[index] != 0){
            index = (index + (q * q)) % tableSize;
            q++; numOfcolision++;
        }
        table[index] = key;
        return true;
        
        
    }
    return false;
}

unsigned int HashTable::hashFunction(int key){
    return (key % tableSize);
}

void HashTable::recSearch(int* inArray, float* search, int numEntries){
    int index[100];
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, numEntries);
    for(int i = 0; i < 100; i++){
        index[i] =  uni(rng);
    }

    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    for(int i = 0; i < 100; i++){
        int searched = inArray[index[i]];
        int n = searchKey(searched);
    }
    auto end = chrono::high_resolution_clock::now();
    double tt = 
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    tt *= 1e-9;
    float duration = float(tt) /100;
    search[(numEntries / 100) - 1] = duration;
}



void HashTable::printTable(){
    int total = 0;
    cout  << "Table: " << endl;
    for(int i = 0; i < 40009; i++){
        cout << table[i] << " ";
        if(table[i] != 0){
            total++;
        }
    }
    cout << endl <<  "Total items: " << total << endl;
}

int HashTable::getNumOfCollision(){
    return numOfcolision;
}

int HashTable::searchKey(int key){
    int index = hashFunction(key);
    if(table[index] == key){
        return index;
    }

    return 0;
}