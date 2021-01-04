#include "dll.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <sstream>
//cant have enough libraries!
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



// ./Output dataSetA.csv dllInsert.csv dllSearch.csv

int main(int argc, char* argv[])
{
    DLL list;
 
    int inArr[10000];
    float insert[100];
    float search[100];

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




    //get clock times from inserting inArr to the DLL
    list.recInsert(inArr, insert, search);
    //Send array times to csvs
    //recOut(argv[2], insert);
    //recOut(argv[3], search);


    

    //prints times for averge insertion time
    /*cout << "Times: " << endl;
    cout << "Search || Insert" << endl;
    for(int i = 0; i < 100; i++){
        cout << (i+1) * 100 << " insertions" << endl;
        cout << search[i] << " || " << insert[i] << endl;
    }*/

    cout << endl << endl;

    list.display();

    
    return 0;

}