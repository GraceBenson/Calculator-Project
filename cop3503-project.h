#ifndef COP3503PROJECT_H
#define COP3503PROJECT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

// method declarations for program
int factorial(int);
std::string processPostfix(std::string);
std::string shuntingYard(std::string);
std::string preProcess(std::string);
std::string compute(std::string, char);
std::string computeSingleNum(std::string, char);

// class Stack will declare all methods and variables for creating a stack
class Stack {
   
    private:
        //define vector to form basis of stack;
        std::vector<std::string> array;
    
    public:
        //constructor
        Stack();
    
        //push string to stack
        void push(std::string input);
        
        //pop string off stack
        std::string pop();
        
        //peek at stack contents
        std::string peek();
        
        //contains a string s
        bool contains(std::string s);
        
        //prints contents
        std::string print();
        
        //returns false if array contains at least one element
        bool isEmpty();
};
#endif // COP3503PROJECT_H
