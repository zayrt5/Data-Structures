#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

//working as of 10/14. needs 1 num text file to sort in cmd line


int addToArrayAsc(float sortedArray[], int numElements, float newValue){

        int i;
        for(i = numElements - 1; (i >= 0 && sortedArray[i] > newValue); i--){
            sortedArray[i + 1] = sortedArray[i];
        }
        sortedArray[i+1] = newValue;
        numElements++;
        return numElements;

}


int main(int argc, char* argv[]){
    int numElements = 0;
    float myArray[100];
    ifstream inNum(argv[1]);
    float newNum;
    string inString;
    if(inNum.is_open()){

        while(getline(inNum, inString)){
            newNum = stof(inString);
            numElements = addToArrayAsc(myArray, numElements, newNum);
            for(int i = 0; i < numElements - 1; i++){
                cout << myArray[i] << ",";
            }
            cout << myArray[numElements - 1] << endl;
            
        }
        
    }
    else{
        cout << "Failed to open the file." << endl;
        return 0;
    }
    

    inNum.close();

    
}



