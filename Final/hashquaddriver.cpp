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



void recOut(const char* fileName, float* times){
    ofstream outFile(fileName);
    if(!outFile.is_open()){
        cout << "Failed to open out file" << endl;
        return;
    }
    else{
        for(int i = 0; i < 100; i++){
            outFile << times[i] << endl;
        }
    }
}




// ./Output dataSetA.csv htInsert.csv htSearch.csv htCollisions.csv

int main(int argc, char* argv[]){
    int m = 40009;
    HashTable ht(m);

    int inArr[10000];
    float insert[100];
    float search[100];
    float collisions[100];

    const char* inFile = argv[1];

    ifstream inStream;
    inStream.open(inFile);
    if(!inStream.is_open()){
        cout << "Failed to open inFile" << endl;
        return 0;
    }
    else{
        //storing numbers from dataSetA into inArray
        string currIn;
        int inIndex = 0;
        while(getline(inStream, currIn, ',')){
            inArr[inIndex] = stoi(currIn);
            inIndex++;
        }
    }
    int added = 0;
    int insertIndex = 0;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++){
        ht.insertKey(inArr[i]);
        added++;
        if(added % 100 == 0){
            auto end = chrono::high_resolution_clock::now();
            double tt = 
                chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            tt *= 1e-9;
            float duration = float(tt) /100;
            insert[insertIndex] = duration;
            ht.recSearch(inArr, search, added);
            collisions[insertIndex] = ht.getNumOfCollision();
            insertIndex++;
            start = chrono::high_resolution_clock::now();
        }
    }
    /*cout << "Insert times: " << endl;
    for(int i = 0; i < 100; i++){
        cout << insert[i] << " (" << i << ")" << endl;
    }*/

    cout << "Collisions: " << ht.getNumOfCollision() << endl;

    //sends time arrays to csvs
    /*recOut(argv[2] , insert);
    recOut(argv[3], search);
    */recOut(argv[4], collisions);
    
    ht.printTable();
}