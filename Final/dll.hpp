#include <iostream>
using namespace std;

struct Node{
    int key;
    Node* next;
    Node* prev;
};

class DLL{
    private:
        Node* head;

    public:

        DLL();
        bool isEmpty();
        void addNode(int key);
        Node* nodeSearch(int key);
        void display();
        void recInsert(int* inArray, float* insert, float* search);
        void recSearch(int* inArray, float* search, int numEntries);
};




    