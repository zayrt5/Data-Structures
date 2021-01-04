#include <iostream>
#include "StackCalculator.hpp"


//Code is fully functional with driver. All edge cases handled


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
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

StackCalculator::StackCalculator()
{
  //TODO:
  stackHead = nullptr;

}

StackCalculator::~StackCalculator()
{
  //TODO:
  while(!isEmpty()){
    pop();
  }
  

}

bool StackCalculator::isEmpty()
{
	//TODO:
  if(stackHead == NULL){
    return true;
  }
  else{
    return false;
  }

}

void StackCalculator::push(float number)
{
  //TODO:
  Operand* newNode = new Operand;
  newNode->number = number;
  newNode->next = nullptr;
  newNode->next = stackHead;
  stackHead = newNode;

}

void StackCalculator::pop()
{
	//TODO:
  if(isEmpty()){
    cout << "Stack empty, cannot pop an item." << endl;
    return;
  }
  else{
    Operand* temp = stackHead;
    if(stackHead->next == NULL){
      temp = stackHead;
      delete temp;
      stackHead = NULL;
    }
    else{
      temp = stackHead;
      stackHead = stackHead->next;
      delete temp;
    }
  }


}

Operand* StackCalculator::peek()
{
	//TODO:
  if(isEmpty()){
    cout << "Stack empty, cannot peek." << endl;
    return NULL;
  }
  else{
    return stackHead;
  }

}

bool StackCalculator:: evaluate(string* s, int size)
{
    /*TODO: 1.scan the array from the end
            2.Use isNumber function to check if the input is an operand
            3.push all operands to the stack
            4.If operator take two element of from the stack,
              compute and put the result back in stack
            5.Handle the boundery cases as required.
            6.Read the writeup for more details
    */
  float num1;
  float num2;
  for(int i = size - 1; i >= 0; i--){
    if(isNumber(s[i])){
      float pushing = stof(s[i]);
      push(pushing);
    }
    else{
      if(s[i] == "+"){
        if(stackHead == NULL || stackHead->next == NULL){
          cout << "err: not enough operands" << endl;
          return false;
        }
        else{
          num1 = stackHead->number;
          num2 = stackHead->next->number;
          pop();
          stackHead->number = num1 + num2;
        }

      } 
      else if(s[i] == "*"){
        if(stackHead == NULL || stackHead->next == NULL){
          cout << "err: not enough operands" << endl;
          return false;
        }
        else{
          num1 = stackHead->number;
          num2 = stackHead->next->number;
          pop();
          stackHead->number = num1 * num2;
        }

      }

      else{
        cout << "err: invalid operation" << endl;
        return false;
      }
    }
  }
   




		return true;
}
