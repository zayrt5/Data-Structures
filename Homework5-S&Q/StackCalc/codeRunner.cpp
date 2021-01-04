#include<iostream>
#include<cmath>
#include<iomanip>
#include "StackCalculator.hpp"

using namespace std;

int main(){
    StackCalculator calc;
    string *s = new string[50];
    s[0] = "+";
    calc.evaluate(s, 1);

}