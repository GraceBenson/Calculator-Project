#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "random"
#include "QInputDialog"
#include "QMessageBox"
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <math.h>
#include <stack>
#include "COP3503-Project.h"

using namespace std;

QString labelNumber;
string str;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("MainWindow {background-image: url(:/blank.png);}");

     connect(ui->zero, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button1, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button2, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button3, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button4, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button5, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button6, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button7, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button8, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->button9, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->dot, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->negative, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->tan, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->cos, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->sin, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->derivative, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->sqrt, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->log, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->ln, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->leftparen, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->rightparen, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->e, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->function, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->multiply, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->divide, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->minus, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->plus, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->pi, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->factorial, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->exponent, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->question, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->modulo, SIGNAL(released()), this, SLOT(digit_pressed()));
     connect(ui->on, SIGNAL(released()), this, SLOT(digit_pressed()));

     ui->equals->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    if(ui->label->text() == "0")
    {
        ui->equals->setChecked(false);
        labelNumber = button->text();
        if(button->text() == "!")
        {
            labelNumber= ui->label->text() + button->text();
        }
    }
    else if(ui->equals->isChecked() && ui->label->text() != "0")
    {
        labelNumber = button->text();
        ui->equals->setChecked(false);
    }
    else
    {
        labelNumber= ui->label->text() + button->text();
    }

    ui->label->setText(labelNumber);
}

void MainWindow::on_clearbutton_released()
{
    labelNumber= "0";
    ui->label->setText(labelNumber);
}

void MainWindow::on_equals_released()
{
    str = labelNumber.toStdString();

    if (str.find('d') != 0) 
    {
        str = str.substr(6);
        cout << str;
        str = derive(str);
    }
    else if (str.find('a') != 0) 
    {
        str = integrate(str);
    }
    else
    {
        str = processPostfix(shuntingYard(preProcess(str)));
    }

    labelNumber = QString::fromStdString(str);
    ui->label->setText(labelNumber);
}

// Stack constructor - initialize empty array
Stack::Stack() 
{
    array = {};
}

// push method - push value onto stack
void Stack::push(std::string input) 
{
    array.push_back(input);
}

// pop method - pops the top value off the stack
std::string Stack::pop() 
{
    std::string container;
    container = array.back();
    array.pop_back();
    return container;
}

// peek method - returns the top value of the stack without removing it
std::string Stack::peek() 
{
    if(isEmpty()) 
    {
        return "";
    }
    return array.back();
}

// contains method - returns true if the stack contains a certain value s
bool Stack::contains(std::string s) 
{
    for (std::string &value : array) 
    {
        if (value == s) 
        {
            return true;
        }
    }
    return false;
}

//print method - prints out contents of stack
std::string Stack::print() 
{
    std::string ans = "";
    for (std::string s : array) 
    {
        std::cout << s << " "; // add spaces in between strings
        ans += (s + " ");
    }
    std::cout << "\n"; // go to next line
    return ans;
}

// isEmpty method - returns true if stack is empty
bool Stack::isEmpty() 
{
    if (array.empty()) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//compute method - computes the given numbers using the given operation
std::string compute(std::vector<std::string> singleOperation, char operation)
{
    // initialize variables for method
    double x = 0.0;
    double y = 0.0;
    double ans = 0.0;
    std::string::size_type sz;

    x = std::stod (singleOperation.at(0), &sz);
    y = std::stod (singleOperation.at(1));

    switch(operation)
    {
        case ('^'): 
        {
            ans = pow (y, x);
            break;
        }
        case ('*'): 
        {
            ans = (x * y);
            break;
        }
        case ('/') : 
        {
            ans = (y / x);
            break;
        }
        case ('+'):  
        {
            ans = (x + y);
            break;
        }
        case ('-'): 
        {
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
    return std::to_string(ans);
}

// factorial method - calculates factorial sequence
int factorial(int x)
{
    // base case
    if (x == 0 || x == 1)
    {
        return 1;
    }
    // all other cases
    else 
    {
        return (x * factorial(x - 1));
    }
}

// computeSingleNum method - chooses and calculates which function to use
std::string computeSingleNum(std::vector<std::string> singleOperation, char operation)
{
    // initialize variables for method
    double x = 0.0;
    double ans = 0.0;
    std::string::size_type sz;

    x = std::stod (singleOperation.at(0), &sz);
    switch(operation)
    {
        case ('s'): 
        {
            //sin
            ans = sin (x);
            break;
        }
        case ('c'): 
        {
            //cos
            ans = cos (x);
            break;
        }
        case ('t'): 
        {
            //tan
            ans = tan (x);
            break;
        }
        case ('n'): 
        {
            //natural log
            ans = log (x);
            break;
        }
        case ('!') :
        {
            //factorial
            int a = x;
            if (a < 0)
            {
                std::cout << "Factorial of a negative number cannot be computed" << std::endl;
            }
            else if (a < 13)
            {
                ans = factorial(a);
            } 
	    else
            {
                //handle big factorials
                std::cout << "The number is too large to be computed" << std::endl;
            }
            break;
        }
        default:
            break;
    }
    return std::to_string(ans);
}

// processPostFix method - puts post fix notation into useable form
std::string processPostfix (std::string postfix)
{
    Stack * numbers = new Stack();
    std::vector <std::string> singleOperation;
    std::string singleOperationAnswer;

    //place the items onto the stack
    int i = 0;
    int digitLength = 0;

    while(i < postfix.length())
    {
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
            digitLength = 0;
        }
        //check for operators
        //if the next element is not a space or a digit, then it is an operator. Should stop numbers here.
        else if (postfix.at(i) == '+' || postfix.at(i) == '-' || postfix.at(i) == '*' || postfix.at(i) == '/'
                 || postfix.at(i) == '^' || postfix.at(i) == '%' )
        {
            singleOperation.push_back(numbers->peek());
            numbers->pop();

            singleOperation.push_back(numbers->peek());
            numbers->pop();

            singleOperationAnswer = compute(singleOperation, postfix.at(i));
            numbers->push(singleOperationAnswer);
            singleOperation.clear();
        }
        else if (postfix.at(i) == 's' || postfix.at(i) == 'c'|| postfix.at(i) == 't' || postfix.at(i) == 'n' || postfix.at(i) == '!')
         {
           // sin cos tan natural log
           singleOperation.push_back(numbers->peek());
           numbers->pop();
           singleOperationAnswer = computeSingleNum(singleOperation, postfix.at(i));
           numbers->push(singleOperationAnswer);
           singleOperation.clear();
        }
        i++;
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

// shuntingYard method - takes input and processes it into post fix notation
std::string shuntingYard(std::string input) 
{
    // initialize stacks for method
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

    int openParenCount = 0;
    int closeParenCount = 0;

    // counts parenthesis
    for (int i = 0; i < input.length(); i++) 
    {
        if (input[i] == '(') 
        {
            openParenCount++;
        }
        if (input[i] == ')') 
        {
            closeParenCount++;
        }
    }

    // if parenthesis do not match then throw exception
    if (openParenCount != closeParenCount) 
    {
       throw std::exception();
    }

    int index = 0;
    for (int x = 0; x < input.length(); x++) 
    {
        //extract digits
        if (isdigit(input[x]) || input[x] == '~') 
        {
            index = x++;
            while (isdigit(input[x]) || input[x] == '.') 
            {
                x++;
            }
            output->push(input.substr(index, x - index));
        }

        //handle operators
        std::string operatorList[] = {"-", "/", "*", "+", "%", "(", ")", "^", "s", "c", "t", "!", "n"};

        //extract operators
        if (find(begin(operatorList), end(operatorList), input.substr(x, 1)) != end(operatorList)) 
        {
            string op = input.substr(x, 1);
            while (((precedence[operators->peek()] > precedence[op]) || (operators->peek() == "^")) && operators->peek() != "(" && op != "(") 
            {
                output->push(operators->pop());
            }
            if(op != ")") 
            {
                operators->push(op);
            }
            else 
            {
                while(operators->peek() != "(") 
                {
                    output->push(operators->pop());
                }
                operators->pop();
            }
        }
    }
    while(!operators->isEmpty()) 
    {
        output->push(operators->pop());
    }
    return output->print();
}

// preProcess method - processes calculator functions
std::string preProcess(std::string input) 
{
    std::cout << "got to preProcess" <<std::endl;
    std::string newString = input;
    int digitNum = 0;
    int digitStart = 0;
    for (int x = 0; x < input.length(); x++) 
    {
        if(input[x] == 'e') 
        {
            std::string prev = input.substr(0, x);
            std::string after = input.substr(x + 1);
            newString = prev + "2.71828" + after;
        } 
        else if(input[x] == 'p' && input[x + 1] == 'i')
        {
            std::string prev = input.substr(0, x);
            std::string after = input.substr(x + 2);
            newString = prev + "3.14159" + after;
        }
        else if (input[x] == 'q')
        {
            std::string prev = input.substr(0, x);
            for (int i = x + 1; i < input.length(); i++)
            {
                if (isdigit(input[i]))
                {
                    if (digitNum == 0)
                    {
                        digitStart = i;
                    }
                    digitNum++;
                }
                if (digitNum > 0 && input[x] == ' ')
                {
                    break;
                }
            }
            newString = prev;
            newString += input.substr(digitStart, digitNum) + " ^ 0.5 " + input.substr(digitStart + digitNum);
            cout << "q test: " << newString << endl;
        }
        else if(input[x] == 'l') //n for natural log, l for common
        { 
            int end = x;
            std::string digit;
            std::string prev = input.substr(0, x);

            if (input[x + 1] == ' ')
            {
                x++;
            }
            if (input[x + 1] == '(')
            {
                prev += "(";
                x++;
            }
            if (isdigit(input[x + 1])) 
            {
                end = x++;
                while (isdigit(input[x]) || input[x] == '.') 
                {
                    x++;
                }
                digit = input.substr(end + 1, x - end - 1);
                cout << "digit is " << digit << endl;
            }
            std::string after = input.substr(x);
            newString = prev + "n " + digit + " / n 10" + after;
            std::cout << "newString test: " << newString << std::endl;
        }
        else if (x == 1 && input[x] == 'd')
        {
            //send to derive
            newString = input.substr(6);
            //send newString
        }
        else if (x == 1 && input[x] == 'a')
        {
            //send to integrate
            newString = input.substr(6);
            //send newString
        }
    }
    return newString;
}

// isOperator method - checks to see if input is an operator
bool isOperator(char a)
{
    if(a == '*' || a == '/' || a == '*' || a == '(' || a == ')' || a == '+' || a == '-' || a == '^')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// fixSpacing method - add spaces to the given string
std::string fixSpacing (std::string str)
{
    //Variables
    std::string s;
    //an intermediary string used to hold str without spaces.
    s = str;
    s += " ";
    //str is converted to not have spaces to it is easier to parse through it.
    std::string ans = "";
    //ans is the string that will eventually be returned. It is added to throughout the method.

    for(int i = 0; i < s.length() - 1; i ++)
    {
        ans += s.substr(i,1);
        //AN: this additional loop is needed to make sure that digits of a single number are not separated during
        //this process. A space should only be added after all of the digits have been found and added.
        while(!isOperator(s.at(i)) && isdigit(s.at(i + 1)))
        {
            i++;
            //counter is incremented inside so that the counter does repeat through the digits it is finding and adding
            ans += s.substr(i,1);
        }
        ans += " ";
    }
    return ans;
}

//stringToVector method - converting string to vector for easy use
std::vector<std::string> stringToVector(std::string stringInput)
{
    stringInput = fixSpacing(stringInput);
    std::vector<std::string> vectorInput;
    int charCount = 0;
    int modTest = 0;

    for (int i = 0; i < stringInput.length(); i++)
    {
        if (stringInput.at(i) != ' ')
        {
            charCount++;
        }
        else
        {
            vectorInput.push_back(stringInput.substr(i - charCount, charCount));
            charCount = 0;
        }
    }

    //check to make sure everything is in the right place
    for (int j = 0; j < vectorInput.size(); j++)
    {
        modTest = j % 6;
        switch (modTest) {
            case 0:
            {		
                if (!isdigit(vectorInput.at(j).at(0)))
                {
                    vectorInput.insert(vectorInput.begin() + j, "1");
                    vectorInput.insert(vectorInput.begin() + j + 1, "*");
                }
                if (j + 1 == vectorInput.size())
                {
                    vectorInput.insert(vectorInput.begin() + j + 1, "*");
                    vectorInput.insert(vectorInput.begin() + j + 2, "x");
                    vectorInput.insert(vectorInput.begin() + j + 3, "^");
                    vectorInput.insert(vectorInput.begin() + j + 4, "0");
                }
                break;
	        }
            case 1:
	        {
                if (vectorInput[j] != "*") {
                    vectorInput.insert(vectorInput.begin() + j, "*");
                    vectorInput.insert(vectorInput.begin() + j + 1, "x");
                    vectorInput.insert(vectorInput.begin() + j + 2, "^");
                    vectorInput.insert(vectorInput.begin() + j + 3, "0");
                }
                break;
	         }
            case 2:
	         {
                //x
                if (j + 1 == vectorInput.size())
                {
                    vectorInput.insert(vectorInput.begin() + j + 1, "^");
                    vectorInput.insert(vectorInput.begin() + j + 2, "1");
                }
                break;
	        }
            case 3:
	        {
                //^
                if (vectorInput[j] != "^") {
                    //v.insert(v.begin() + i, valueToInsert);
                    vectorInput.insert(vectorInput.begin() + j, "^");
                    vectorInput.insert(vectorInput.begin() + j + 1, "1");
                }
                break;
	        }
            case 4:
	        {
                //exponent
                break;
	        }
            case 5:
	        {
                //+ or -
                break;
	         }
            default:
                std::cout << "something happened" << std::endl;
                break;
        }
    }
    return vectorInput;
}

//vectorToString method - convert string to vector
std::string vectorToString (std::vector <std::string> vec) {
    std::string ans;
    std::string ans_ = "";
    std::string temp;
    //go thru vector
    for (int i = 0; i < vec.size(); i++) {
        //if an exponent (thing after ^ is...)
        temp = vec[i];

        if (temp == "+" || temp == "-") {
            ans += vec[i];
        } else if (temp == "^") {
            if (vec[i + 1] == "-1") {
                ans += "0";
            } else if (vec[i + 1] == "1") {
                ans += vec[i - 3];
                ans += vec[i - 2];
                ans += vec[i - 1];
            } else if (vec[i + 1] == "0") {
                ans += vec[i - 3];
            } else {

                ans += vec[i - 3];
                ans += vec[i - 2];
                ans += vec[i - 1];
                ans += vec[i];
                ans += vec[i + 1];
            }
        }
        //-1 , then don't need entire thing (is 0)
        //0, then is only constant
        //1, then is constant * x
        if (ans.find("0")) {
            for (int i = 0; i < ans.length(); i++) {

                if (ans.at(i) == '0') {

                    if (i + 1 < ans.length() && (ans.at(i + 1) == '+' || ans.at(i + 1) == '-')) {
                        continue;
                    } else if (i - 1 > 0 && (ans.at(i - 1) == '+' || ans.at(i - 1) == '-')) {
                        ans_ = ans_.substr(0, i - 1);
                    }
                } else
                    ans_ += ans.at(i);
            }

            if (ans.length() == 0) {
                ans_ = "0";
            }
        } else
            return ans;
    }
}


// integrate method - calculate and integrate input
std::string integrate (std::string stringInput)
{
    std::vector<std::string> vectorInput;
    std::string answer;
    std::string temp;
    int modTest = 0;
    double coefficient = 0.0;
    double exponent = 0.0;
    std::string::size_type sz;
    
    vectorInput = stringToVector(stringInput);
    for (int j = vectorInput.size() - 1; j >= 0;  j--)
    {
        modTest = j % 6;
        switch (modTest)
        {
            case 0:
            {
                //coefficienet
                coefficient = std::stod (vectorInput[j], &sz);
                coefficient /= exponent;
                temp = std::to_string(coefficient);
                //erasing trailing zeroes
                temp.erase(temp.find_last_not_of('0') + 1);
                //erasing the period if it's the last character
                if (temp.at(temp.length() - 1) == '.')
                {
                    temp.erase(temp.length() - 1, 1);
                }
                vectorInput[j] = temp;
                break;
            }
            case 1:
            {
                //*
                //do nothing
                break;
            }
            case 2:
            {
                //x
                //do nothing
                break;
            }
            case 3:
            {
                //^
                //do nothing
                break;
            }
            case 4:
            {
                //exponent
                exponent = std::stod (vectorInput[j], &sz);
                exponent += 1.0;
                temp = std::to_string(exponent);
                //erasing trailing zeroes
                temp.erase(temp.find_last_not_of('0') + 1);
                //erasing the period if it's the last character
                if (temp.at(temp.length() - 1) == '.')
                {
                    temp.erase(temp.length() - 1, 1);
                }
                vectorInput[j] = temp;
                break;
            }
            case 5:
            {
                //+ or -
                break;
            }
            default:
                std::cout << "something happened" << std::endl;
                break;
        }
    }
    //to convert from vector to string
    answer = vectorToString(vectorInput);
    return answer;
}

// derive method - calculate and take derivative of input
std::string derive (std::string stringInput)
{
    std::vector<std::string> vectorInput;
    std::string answer;
    std::string temp;
    int modTest = 0;
    double coefficient = 0.0;
    double exponent = 0.0;
    std::string::size_type sz;

    vectorInput = stringToVector(stringInput);
    for (int j = vectorInput.size() - 1; j >= 0;  j--)
    {
        modTest = j % 6;
        switch (modTest)
        {
            case 0:
            {
                //coefficienet
                coefficient = std::stod (vectorInput[j], &sz);
                coefficient *= (exponent + 1.0);
                temp = std::to_string(coefficient);
                //erasing trailing zeroes
                temp.erase(temp.find_last_not_of('0') + 1);
                //erasing the period if it's the last character
                if (temp.at(temp.length() - 1) == '.')
                {
                    temp.erase(temp.length() - 1, 1);
                }
                vectorInput[j] = temp;
                break;
            }
            case 1:
            {
                //*
                //do nothing
                break;
            }
            case 2:
            {
                //x
                //do nothing
                break;
            }
            case 3:
            {
                //^
                //do nothing
                break;
            }
            case 4:
            {
                //exponent
                exponent = std::stod (vectorInput[j], &sz);
                exponent -= 1.0;
                temp = std::to_string(exponent);
                //erasing trailing zeroes
                temp.erase(temp.find_last_not_of('0') + 1);
                //erasing the period if it's the last character
                if (temp.at(temp.length() - 1) == '.')
                {
                    temp.erase(temp.length() - 1, 1);
                }
                vectorInput[j] = temp;
                break;
            }
            case 5:
            {
                //+ or -
                break;
            }
            default:
                std::cout << "something happened" << std::endl;
                break;
        }
    }
    //to convert from vector to string
    answer = vectorToString(vectorInput);
    return answer;
}

// HINT function - allows user to display random "hint" or fun fact when hint button pressed
void MainWindow::on_question_released()
{
	// chooses random number for random hint
    int caseNumber = rand() % 25 + 1;

    //needed to do switch statements because QMessageBox doesn't work with variable strings
    switch (caseNumber) 
    {
        case 1:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The natural logarithm is base e.") );
                break;
        }
        case 2:
        {
            QMessageBox::information(
                        this,
                        tr("Helpful Hints"),
                        tr("The common logarithm is base 10.") );
                break;
        }
        case 3:
        {
            QMessageBox::information(
                        this,
                        tr("Helpful Hints"),
                        tr("The area of a circle is pi times the radius squared.") );
                break;
        } 
        case 4:
        {
            QMessageBox::information(
                        this,
                        tr("Helpful Hints"),
                        tr("The area of a triangle is one half the base times the height.") );
                    break;
        }
        case 5:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Remember to use PEMDAS!") );
                break;
        }
        case 6:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Decimal numbers can't be used with the modulo operator.") );
                break;
        }
        case 7:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Don't use the negative sign for subtraction!") );
                break;
        }
        case 8:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The integral is the opposite operation of the derivative.") );
                break;
        }
        case 9:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The derivative returns the rate of change of a function at a point.") );
                break;
        }
        case 10:
        {  
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Math is fun!") );
                break;
        }
        case 11:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The largest number that divides two numbers is the greatest common divisor.") );
                break;
        }
        case 12:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The square of a number is the number multiplied by itself.") );
                break;
        }
        case 13:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The cube of a number is the product of a number and its square.") );
                break;
        }
        case 14:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The natural logarithm of e is 1.") );
                break;
        }
        case 15:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The common logarithm of 10 is 1.") );
                break;
        }
        case 16:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("e is equal to 2.71828...") );
                break;
        }
        case 17:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("pi is equal to 3.14159...") );
                break;
        }
        case 18:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Press CLEAR or ON to erase the screen.") );
                break;
        }
        case 19:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Keep up the hard work!") );
                break;
        }
        case 20:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("X% of Y is Y% of X.") );
                break;
        }
        case 21:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("You cannot take the logarithm of a negative number.") );
                break;
        }
        case 22:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("You cannot use the factorial operation on a decimal.") );
                break;
        }
        case 23:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Some functions cannot be integrated. Sorry!") );
                break;
        }
        case 24:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The calculator may take a long time to process some operations. Be patient!") );
                break;
        }
        case 25:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("The problem with calculus jokes is that they're all derivative") );
                break;
        }
        default:
        {
                QMessageBox::information(
                            this,
                            tr("Helpful Hints"),
                            tr("Oops! This happens sometimes. Please try again.")
                            );
        }
    }
}
