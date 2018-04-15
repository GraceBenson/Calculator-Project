#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <stack>
#include "parsecode.h"

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
