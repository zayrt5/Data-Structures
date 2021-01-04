#include "bubblesort.hpp"
#include <iostream>
#include <vector>
using namespace std;

unsigned int bSort::size(){
    return A.size();
}


void bSort::sort(){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i < size(); i++){
            if(A[i] > A[i + 1]){
                int temp = A[i + 1];
                A[i + 1] = A[i];
                A[i] = temp;
                sorted = false;
            }
        }
    }
}

void bSort::insert(int key){
    A.push_back(key);
}

bool bSort::search(int key){
    for(int i = 0; i < size(); i++){
        if(A[i] == key){
            return true;
        }
    }
    return false;
}

void bSort::display(){
    cout << "Printing array: " << endl;
    for(int i = 0; i < size(); i++){
        cout << A[i] << " ";
    }
    cout << endl;
}