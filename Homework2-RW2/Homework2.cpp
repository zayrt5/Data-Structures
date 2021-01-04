#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iomanip> //found this one for the decimal places?

// Reads in text file and ignores certain words, while maintaining word count and array doubling


// code is operational
// 3 inputs, [1] is int, [2] and [3] are filenames for file being read and ignore words file respectively

using std::cout;
using std::string;

struct wordRecord{
    int count;
    string word;

};

void getIgnoreWords(const char* ignoreWordFileName, string ignoreWords[]){
    std::ifstream inStream;
    inStream.open(ignoreWordFileName);
    if(!inStream.is_open()){
        cout << "Failed to open" << ignoreWordFileName << std::endl;
    }
    string word;
    int i = 0;
    while(inStream >> word){
        ignoreWords[i] = word;
        i++;
    }
    inStream.close();
}

bool isIgnoreWord(string word, string ignoreWords[]){
    bool isWord = false;
    for(int i = 0; i < 50; i++){
        if(ignoreWords[i] == word){
            isWord = true;
            break;
        }
    }
    if(isWord){
        return true;
    }
    else{
        return false;
    }
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length){
    int count = 0;
    for(int i = 0; i < length; i++){
        count = count + distinctWords[i].count;
    }
    return count;
}


void sortArray(wordRecord distinctWords[], int length){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i < length; i++){
            if(distinctWords[i].count < distinctWords[i + 1].count){
                wordRecord temp = distinctWords[i];
                distinctWords[i] = distinctWords[i + 1];
                distinctWords[i + 1] = temp;
                sorted = false;
            }
            else if( distinctWords[i].count == distinctWords[i + 1].count){
                if(distinctWords[i].word > distinctWords[i + 1].word){
                    wordRecord temp = distinctWords[i];
                    distinctWords[i] = distinctWords[i + 1];
                    distinctWords[i + 1] = temp;
                    sorted = false;
                }
            }
            else{
                continue;
            }
        }
    }
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords){
    float wordChance;
    for(int i = 0; i < 10; i++){
        wordChance = ((float)distinctWords[i + N].count / totalNumWords);
        cout << std::fixed << std::setprecision(5) << wordChance << " - ";
        cout << distinctWords[N+i].word << std::endl;
    }
}

int main(int argc, char* argv[]){
    if(argc != 4){
        cout << "Invalid number of arguments" << std::endl;
        return 0;
    }
    string inN = argv[1];
    int N = std::stoi(inN);
    string uniqueFile = argv[2];
    int maxArray = 100;
    wordRecord *unqWords = new wordRecord[maxArray];
    string ignoreWords[50];
    int totalUnqWords = 0;
    int totalWords = 0;
    int arrayDoubles = 0;
    getIgnoreWords(argv[3], ignoreWords);
    std::ifstream inUnique;
    inUnique.open(argv[2]);
    if(!inUnique.is_open()){
        cout << "Failed to open " << argv[3] << std::endl;
        return 0;
    }
    else{
        string currentWord;
        while(inUnique >> currentWord){
            bool isRepeat = false;
            if(!isIgnoreWord(currentWord, ignoreWords)){
                for(int i = 0; i < totalUnqWords; i++){
                    if(unqWords[i].word == currentWord){
                        unqWords[i].count++; 
                        totalWords++;                         //add count to repeat words
                        isRepeat = true;
                        break;
                    }
                }

                if(!isRepeat){
                    unqWords[totalUnqWords].word = currentWord;       //Add unique word to array
                    unqWords[totalUnqWords].count = 1;
                    totalUnqWords++;
                    totalWords++;
                }

            }
            if(totalUnqWords == maxArray){         //array doubling without outside function
                arrayDoubles++;
                maxArray = maxArray * 2;
                wordRecord *temp = new wordRecord[maxArray];                      
                for(int j = 0; j < totalUnqWords; j++){
                    temp[j] = unqWords[j];
                }
                delete [] unqWords;
                unqWords = temp;
            }
            else{
                continue;
            }
                
        }
        inUnique.close();
        sortArray(unqWords, totalUnqWords);
    }
    

    totalWords = getTotalNumberNonIgnoreWords(unqWords, totalUnqWords);
    cout << "Array doubled: " <<  arrayDoubles << std::endl;
    cout << "Distinct non-common words: " << totalUnqWords << std::endl;
    cout << "Total non-common words: " << totalWords << std::endl;
    cout << "Probability of next 10 words from rank " << N << std::endl << "---------------------------------------" << std::endl;
    printTenFromN(unqWords, N, totalWords);

    delete [] unqWords;
    
}