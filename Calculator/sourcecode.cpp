#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <stack>

using namespace std;
Stack::Stack() {
    //initialize empty array
    array = {};
}

void Stack::push(std::string input) {
    //push value onto stack
    array.push_back(input);
}

std::string Stack::pop() {
    //pops the top value off the stock
    std::string container;
    container = array.back();
    array.pop_back();
    return container;
}

std::string Stack::peek() {
    //returns the top value of the stack without removing it
    if(isEmpty()) {
        return "";
    }
    return array.back();
}

bool Stack::contains(std::string s) {
    //returns true if the stack contains a certain value s
    for (std::string &value : array) {
        if (value == s) {
            return true;
        }
    }
    return false;
}

std::string Stack::print() {
    //prints out contents of stack
    std::string ans = "";
    for (std::string s : array) {
        std::cout << s << " ";
        ans += (s + " ");
    }
    std::cout << "\n";
    return ans;
}

bool Stack::isEmpty() {
    //returns true if stack is empty
    if (array.empty()) {
        return true;
    }
    else {
        return false;
    }
}

int main(){

    Stack * output = new Stack();
    Stack * operators = new Stack(); //convert to char?

    std::map<string, int> precedence;
    precedence["("] = 0;
    precedence[")"] = 0;
    precedence["^"] = 3;
    precedence["*"] = 2;
    precedence["/"] = 2;
    precedence["+"] = 1;
    precedence["-"] = 1;

    string input ="3+4+2-12/2"; //fix handling of +!

    int index = 0;
    for (int x = 0; x < input.length(); x++) {


        //extract digits
        if (isdigit(input[x])) {
            index = x++;

            while (isdigit(input[x]) || input[x] == '.') {
                x++;
            }

            output->push(input.substr(index, x - index));
        }

        //handle operators
        std::string operatorList[] = {"-", "/", "*", "+", "%", "(", ")"};
        //list of operators for find method

        //extract operators
        if (find(begin(operatorList), end(operatorList), input.substr(x, 1)) != end(operatorList)) {
            string op = input.substr(x, 1);
            while (((precedence[operators->peek()] > precedence[op]) || (operators->peek() == "^")) && operators->peek() != "(" && op != "(") {
                output->push(operators->pop());
            }
            if(op != ")") {
                operators->push(op);
            }
            else {
                while(operators->peek() != "(") {
                    output->push(operators->pop());
                }
                operators->pop();
            }

        }

    }
    while(!operators->isEmpty()) {
        output->push(operators->pop());
    }

    output->print();

}



//
//  COP3503-Project.h
//  COP3503-Project.h
//
//  Created by Ben Goldstein on 3/19/18.

#ifndef COP3503-Project_h
#define COP3503-Project_h

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

std::string compute(std::vector<std::string> singleOperation, char operation){
    int x = 0;
    int y = 0;
    int ans = 0;

    std::cout << singleOperation.at(0) << " " << operation << " " << singleOperation.at(1) <<   std::endl;

    std::stringstream convertX(singleOperation.at(0));
    convertX >> x;
    // std::cout << x << std::endl;

    std::stringstream convertY(singleOperation.at(1));
    convertY >> y;
    // std::cout << y << std::endl;

    switch(operation){

        case ('^'): {
            ans = (y ^ x);      //TODO: Double check operation order for first and second round stuff
            break;
        }
        case ('*'): {
            ans = (x * y);
            break;
        }

        case ('/') : {
            ans = (y / x);
            break;
        }

        case ('+'):  {
            ans = (x + y);
            break;
        }

        case ('-'): {
            ans = (y - x);
            break;
        }
        default:
            break;

    }
    std::cout << "ans = " << ans << std::endl;

    return std::to_string(ans);

}
//singleOperation.front()

int processPostfix (std::string postfix)
{
    std::stack <std::string> numbers;
    std::vector <std::string> singleOperation;
    std::string singleOperationAnswer;

    //place the items onto the stack
    int i = 0;
    int digitLength = 0;

    while(i < postfix.length()){

        if(isdigit(postfix.at(i)))  //if an element is a number, see how many digits it is and add that number to a stack.
        {
            digitLength++;
        }
        else if (postfix.at(i) == ' ' && digitLength > 0)  //spaces should be separating each number
        {
            numbers.push(postfix.substr(i - digitLength, digitLength));
            //std::cout << postfix.substr(i - digitLength, digitLength) << std::endl;     //test
            std::cout << numbers.top() << std::endl;
            digitLength = 0;
        }

        else if (postfix.at(i) == '+' || postfix.at(i) == '-' || postfix.at(i) == '*' || postfix.at(i) == '/'
                 || postfix.at(i) == '^')       //if the next element is not a space or a digit, then it is an operator. Should stop numbers here.
        {
            singleOperation.push_back(numbers.top());
            std::cout << "top of numbers: " << numbers.top() << std::endl;
            numbers.pop();

            singleOperation.push_back(numbers.top());
            std::cout << "top of numbers: " << numbers.top() << std::endl;
            numbers.pop();

            singleOperationAnswer = compute(singleOperation, postfix.at(i));
            numbers.push(singleOperationAnswer);
            singleOperation.clear();


            //std::cout << "i is " << i << " top number: " << numbers.top() << std::endl;
        }
        i++;
        if(!numbers.empty())
            std::cout << "stack top: " << numbers.top() << std::endl;
    }

    std::cout << "all done folks" << std::endl;

    return 0;

}


#endif /* COP3503-Project_h */
