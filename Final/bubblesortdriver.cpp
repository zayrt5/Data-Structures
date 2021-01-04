#include "bubblesort.hpp"
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


// ./Output dataSetA.csv bubblesort.csv

int main(int argc, char* argv[]){

    int inArr[10000];
    float sort[100];

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
    double tt;
    for(int i = 0; i < 100; i++){
        bSort bubble;
        int currSize = (i + 1) * 100;
        int tempArr[currSize];
        for (int j = 0; j < currSize; j++){
            bubble.insert(inArr[j]);
        }
        cout << "Sorting " << currSize << " entries" << endl;

        auto start = chrono::high_resolution_clock::now();
        bubble.sort();
        auto end = chrono::high_resolution_clock::now();

        tt = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        tt *= 1e-9;
        float duration = float(tt) /100;
        sort[i] = duration;

        cout << "Loop " << i + 1 << ": " << duration << " (seconds)" << endl;

        
    }
    
    //recOut(argv[2], sort);

}