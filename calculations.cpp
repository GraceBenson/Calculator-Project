
/*
 Hints:

 The natural logarithm is base e.
 The common logarithm is base 10.
 The area of a circle is pi times the radius squared.
 The area of a triangle is one half the base times the height.
 Remember to use PEMDAS!
 Decimal numbers can't be used with the modulo operator.
 Don't use the negative sign for subtraction!
 The integral is the opposite operation of the derivative.
 The derivative returns the rate of change of a function at a point.
 Math is fun!

 The largest number that divides two numbers is the greatest common divisor.
 The square of a number is the number multiplied by itself.
 The cube of a number is the product of a number and its square.
 The natural logarithm of e is 1.
 The common logarithm of 10 is 1.
 e is equal to 2.71828...
 pi is equal to 3.14159.....
 Press CLEAR or ON to erase the screen.
 Keep up the hard work!
 X% of Y is Y% of X.

 You cannot take the logarithm of a negative number.
 You cannot use the factorial operation on a decimal.
 Some functions cannot be integrated.
 The calculator may take a long time to process some operations. Be patient!
 The problem with calculus jokes is that they're all derivative.


 */
#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <math.h>
#include <stack>
#include "cop3503-project.h"


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
        std::cout << s << " "; //comment out later
        ans += (s + " ");
    }
    std::cout << "\n"; //comment out later
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

//computes the given numbers using the given operation
std::string compute(std::vector<std::string> singleOperation, char operation){
    double x = 0.0;
    double y = 0.0;
    double ans = 0.0;
    std::string::size_type sz;

    x = std::stod (singleOperation.at(0), &sz);
    y = std::stod (singleOperation.at(1));

    //std::cout << singleOperation.at(0) << " " << operation << " " << singleOperation.at(1) <<   std::endl;
    switch(operation)
    {
        case ('^'): {
            ans = pow (y, x);
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
        case ('%'):
        {
            //casts doubles as ints and computes
            //results in loss of data, but users are expected to enter ints when computing
            int a = x;
            int b = y;
            ans = a % b;
            break;
        }
        default:
            break;

    }
    //std::cout << "ans = " << ans << std::endl;

    return std::to_string(ans);

}

std::string computeSingleNum(std::vector<std::string> singleOperation, char operation)
{
    double x = 0.0;
    double ans = 0.0;
    std::string::size_type sz;

    x = std::stod (singleOperation.at(0), &sz);
    switch(operation)
    {
        case ('s'): {
            //sin
            ans = sin (x);
            break;
        }
        case ('c'): {
            //cos
            ans = cos (x);
            break;
        }
        case ('t'): {
            //tan
            ans = tan (x);
            break;
        }
        case ('n'): {
            //natural log
            ans = log (x);
            break;
        }
        default:
            break;
    }
    return std::to_string(ans);
}


std::string processPostfix (std::string postfix)
{
    Stack * numbers = new Stack();
    std::vector <std::string> singleOperation;
    std::string singleOperationAnswer;

    //place the items onto the stack
    int i = 0;
    int digitLength = 0;

    while((unsigned) i < postfix.length())
    {
        //TODO make sure only one period and no negatives in the middle of the number
        if(isdigit(postfix.at(i)) || postfix.at(i) == '.' || postfix.at(i) == '~')  //if an element is a number, see how many digits it is and add that number to a stack.
        {
            digitLength++;
            if (postfix.at(i) == '~')
            {
                postfix.at(i) = '-';
            }
        }
        else if (postfix.at(i) == ' ' && digitLength > 0)  //spaces should be separating each number
        {
            //push the number onto the numbers stack
            numbers->push(postfix.substr(i - digitLength, digitLength));
            //std::cout << numbers.top() << std::endl;
            digitLength = 0;
        }
        //check for operators
        //if the next element is not a space or a digit, then it is an operator. Should stop numbers here.
        else if (postfix.at(i) == '+' || postfix.at(i) == '-' || postfix.at(i) == '*' || postfix.at(i) == '/'
                 || postfix.at(i) == '^' || postfix.at(i) == '%')
        {
            singleOperation.push_back(numbers->peek());
            //std::cout << "top of numbers: " << numbers.top() << std::endl;
            numbers->pop();

            singleOperation.push_back(numbers->peek());
            //std::cout << "top of numbers: " << numbers.top() << std::endl;
            numbers->pop();

            singleOperationAnswer = compute(singleOperation, postfix.at(i));
            numbers->push(singleOperationAnswer);
            singleOperation.clear();
        }
      else if (postfix.at(i) == 's' || postfix.at(i) == 'c'|| postfix.at(i) == 't' || postfix.at(i) == 'n')
       {
           // sin cos tan natural log
           singleOperation.push_back(numbers->peek());
           numbers->pop();
           singleOperationAnswer = computeSingleNum(singleOperation, postfix.at(i));
           numbers->push(singleOperationAnswer);
           singleOperation.clear();
       }
        i++;
        //if(!numbers.empty())
        //  std::cout << "stack top: " << numbers.top() << std::endl;
    }
    //erasing trailing zeroes
    singleOperationAnswer.erase(singleOperationAnswer.find_last_not_of('0') + 1);
    //erasing the period if it's the last character
    if (singleOperationAnswer.at(singleOperationAnswer.length() - 1) == '.')
    {
        singleOperationAnswer.erase(singleOperationAnswer.length() - 1, 1);
    }
    //returns a string of double
    return singleOperationAnswer;
}



std::string shuntingYard(std::string input) {
    Stack * output = new Stack();
    Stack * operators = new Stack();

    std::map<string, int> precedence;
    precedence["("] = 0;
    precedence[")"] = 0;
    precedence["^"] = 4;
    precedence["s"] = 3; //sin
    precedence["n"] = 3; //natural log
    precedence["!"] = 3; //factorial
    precedence["c"] = 3; //cos
    precedence["t"] = 3; //tan
    precedence["*"] = 2;
    precedence["/"] = 2;
    precedence["+"] = 1;
    precedence["-"] = 1;


    int index = 0;
    for (int x = 0; (unsigned) x < input.length(); x++) {


        //extract digits
        if (isdigit(input[x]) || input[x] == '~') {
            index = x++;

            while (isdigit(input[x]) || input[x] == '.') {
                x++;
            }

            output->push(input.substr(index, x - index));
        }

        //handle operators
        std::string operatorList[] = {"-", "/", "*", "+", "%", "(", ")", "^", "s", "c", "t", "!", "n"};
        //list of operators for find method

        //extract operators



        //std::string a = input.substr(x,1);
        //std::string b = end(operatorList);

        //if (find(begin(operatorList), end(operatorList), input.substr(x, 1)) != end(operatorList)) {

//        std::string c = input.substr(x, 1);
//        std::string *a = find(begin(operatorList), end(operatorList), c);
//        std::string *b = end(operatorList);
//        bool isEqual = false;
//        for(auto i: operatorList) {
//            if(i == c) {
//                isEqual = true;
//                break;
//            }
//        }
//        if(isEqual) {
        if(std::find(begin(operatorList), end(operatorList), input.substr(x, 1)) != end(operatorList)) {
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
    return output->print();
}

std::string preProcess(std::string input) {
    std::string newString;
    for (int x = 0; (unsigned) x < input.length(); x++) {

        if(input[x] == 'e') {
            std::string prev = input.substr(0, x);
            std::string after = input.substr(x + 1);
            newString = prev + "2.71828" + after;
        }

        if(input[x] == 'p' && input[x + 1] == 'i')
        {
            std::string prev = input.substr(0, x);
            std::string after = input.substr(x + 2);
            newString = prev + "3.14159" + after;
        }

        if(input[x] == 'l') { //n for natural log, l for common
            int end = x;
            std::string digit;
            std::string prev = input.substr(0, x);


            if (isdigit(input[x + 1])) {
                end = x++;

                while (isdigit(input[x]) || input[x] == '.') {
                    x++;
                }
                digit = input.substr(end + 1, x - end - 1);
            }
            std::string after = input.substr(x);
            newString = prev + "((n" + digit + ")/(n10))" + after;
        }

    }
    return newString;
}

//int main(){

//    //TO DO: derivative, sin cos tan, ln

//    cout << processPostfix(shuntingYard(preProcess("3! + 5 + 8")));

//}
