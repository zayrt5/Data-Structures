#include <iostream>
#include <vector>
using namespace std;

class bSort{

    private:

        vector<int> A;
    
    public:

        unsigned int size();

        void sort();

        void insert(int key);

        bool search(int key);

        void display();


};