#include <iostream>
#include <vector>
using namespace std;

class MaxPQ{

    private:
    vector<int> A;
 
    // don't call if i is already a root node
    int P(int i){ 
        return (i - 1) / 2; 
    }
 
    int L(int i){ 
        return (2 * i + 1); 
    }
 
    int R(int i){ 
        return (2 * i + 2); 
    }
 

    void downHeapify(int i){
        // get left and right child of node at index i
        int left = L(i);
        int right = R(i);
 
        int largest = i;
 
        // compare A[i] with L and R child and find largest value
        if (left < size() && A[left] > A[i]){
            largest = left;
        }
 
        if (right < size() && A[right] > A[largest]){
            largest = right;
        }
 
        //swap with child with greater value and heapify child
        if (largest != i){
            swap(A[i], A[largest]);
            downHeapify(largest);
        }
    }

    void upHeapify(int i)
    {
        // check if node exists at i and its parent values
        if (i && A[P(i)] < A[i]){
            //swap if child > parent
            swap(A[i], A[P(i)]);
            //call heapify on  parent
            upHeapify(P(i));
        }
    }
 
    
public:
    unsigned int size();
 
    bool empty();
    
    void push(int key);
 
    void pop();
 
    int top();

    void display();

    bool search(int key);
};
