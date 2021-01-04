#include "heapsort.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <chrono> 
#include <time.h>
#include <sstream>
#include <random>
using namespace std;


unsigned int MaxPQ::size(){
    return A.size();
}


bool MaxPQ::empty(){
    return size() == 0;
}


void MaxPQ::push(int key){
    //new element to the end of the vector
    A.push_back(key);
 
    //get index and heapify-up
    int index = size() - 1;
    upHeapify(index);
}

void MaxPQ::pop(){
    if (size() == 0){
        cout << "No elements in Heap to pop." << endl;
        return;
    }
 
    //swap root with last node of tree
    A[0] = A.back();
    A.pop_back();
 
    // call heapify on root node
    downHeapify(0);
}

int MaxPQ::top(){

    return A.at(0);

}


void MaxPQ::display(){
    cout << "Printing heap..." << endl << endl;
    for(int i = 0; i < A.size(); i++){
        cout << A[i] << " ";
    }
    cout << endl;
}

bool MaxPQ::search(int key){
    for(int i = 0; i < A.size(); i++){
        if(A[i] == key){
            cout << "Found " << key << " at index " << i << endl;
            return true;
        }
    }
    cout << "Did not find " << key << endl;
    return false;
}