#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <cstdlib>
using namespace std;


// good file stream examples here



struct studentData {
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
    };

bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}


void addStudentData(studentData students[], string studentName, int homework, int recitation, 
    int quiz, int exam, int length) {

        //ii. Instantiate a struct and store thestudentName,homework,recitation,
            //quiz, and exam values in it.

    studentData Student;
    Student.studentName = studentName;
    Student.homework = homework;
    Student.recitation = recitation;
    Student.quiz = quiz;
    Student.exam = exam;
    Student.average = (homework + recitation + quiz+ exam) / 4.0;
    students[length] = Student;

}

char calcLetter(double avg){
    if (avg > 90)
    {
        return 'A';
    }
    else if(avg < 89.9 && avg > 80){
        return 'B';
    }
    else if(avg < 79.9 && avg > 70){
        return 'C';
    }
    else if(avg < 69.9 && avg > 60){
        return 'D';
    }
    else{
        return 'F';
    }
}

void printList(const studentData students[], int length){
    for(int i = 0; i < length; i++){
        char studChar = calcLetter(students[i].average);
        cout << students[i].studentName << " earned " << students[i].average 
            << " which is an "<< studChar << endl;
    }
}

int main(int argc, char* argv[]){
    char* lowBound = argv[3];
    char* upBound = argv[4];
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    studentData myStudents[100];
    int arrLength = 0;
    int inInt;
    string inLine;
    string inWord;
    int totalData = 0;
    if(inFile){
        while(getline(inFile, inLine, '\n')){
            stringstream ss(inLine);
            string newName;
            int inHW;
            int inExam;
            int inRec;
            int inQuiz;
            int stringIndex = totalData % 5;
            bool lineDone = false;
            while(getline(ss, inWord, ',')){
                switch(stringIndex){
                    case 0:{
                        newName = inWord;
                        stringIndex++;
                        totalData++;
                        break;
                    }
                    case 1:{
                        inHW = stoi(inWord);
                        stringIndex++;
                        totalData++;
                        break;
                    }
                    case 2:{
                        inExam = stoi(inWord);
                        stringIndex++;
                        totalData++;
                        break;
                    }
                    case 3:{
                        inQuiz = stoi(inWord);
                        stringIndex++;
                        totalData++;
                        break;
                    }
                    case 4:{
                        inRec = stoi(inWord);
                        stringIndex++;
                        totalData++;
                        lineDone = true;
                        break;
                    }
                }
                if(lineDone == true){
                    addStudentData(myStudents, newName, inHW, inRec, inQuiz, inExam, arrLength);
                    arrLength++;
                }
                
                

            }
            
        }
        
            inFile.close();
            
    }
    printList(myStudents, arrLength);
    

    if(outFile){
        for(int j = 0; j < arrLength; j++){
            char newLetter = calcLetter(myStudents[j].average);
            if(newLetter <= *lowBound && newLetter >= *upBound){
                outFile << myStudents[j].studentName << ',' << myStudents[j].average << ',' << newLetter
                    << endl;
            }
        }
        outFile.close();
    }
    
}
