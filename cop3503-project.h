#ifndef COP3503PROJECT_H
#define COP3503PROJECT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

class Stack {
    private:
        //define vector to form basis of stack;
        std::vector<std::string> array;
    public:
        Stack();
        //constructor
        void push(std::string input);
        //push string to stack
        std::string pop();
        //pop string off stack
        std::string peek();
        //peek at stack contents
        bool contains(std::string s);
        //contains a string s
        std::string print();
        //prints contents
        bool isEmpty();
        //returns false if array contains at least one element

};


#endif // COP3503PROJECT_H
