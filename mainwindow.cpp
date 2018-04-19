#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random"
#include "QTextStream"
#include "QMessageBox"
#include "QInputDialog"


QString labelNumber;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("MainWindow {background-image: url(:/blank.png);}");

     connect(ui->on, SIGNAL(released()), this, SLOT(digit_pressed()));
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    if(ui->label->text() == "0"){
        labelNumber = button->text();
    }
    else{
        labelNumber= ui->label->text() + button->text();
    }
    ui->label->setText(labelNumber);
}

void MainWindow::on_clearbutton_released()
{
    labelNumber= "0";
    ui->label->setText(labelNumber);
}

//NEW METHOD OF CODE :
void MainWindow::on_on_released()
{
    labelNumber= "0";
    ui->label->setText(labelNumber);
}

void MainWindow::on_question_released()
{

    int hintNumber = rand() % 10;
    std::string hints[3] = {"the natural log is base e", "the area of a circle if pi times", "trial 3"};


    std::string ChosenString = hints[hintNumber];

    QMessageBox::information(
            this,
            tr("Helpful Hints"),
            tr("Hints:"
               "\nThe natural logarithm is base e."
               "\nThe common logarithm is base 10."
               "\nThe area of a circle is pi times the radius squared."
               "\nThe area of a triangle is one half the base times the height."
               "\nRemember to use PEMDAS!"
               "\nDecimal numbers can't be used with the modulo operator."
               "\nDon't use the negative sign for subtraction!"
               "\nThe integral is the opposite operation of the derivative."
               "\nThe derivative returns the rate of change of a function at a point."
               "\nMath is fun!"
               "\n"
               "\nThe largest number that divides two numbers is the greatest common divisor."
               "\nThe square of a number is the number multiplied by itself."
               "\nThe cube of a number is the product of a number and its square."
               "\nThe natural logarithm of e is 1."
               "\nThe common logarithm of 10 is 1."
               "\ne is equal to 2.71828..."
               "\npi is equal to 3.14159....."
               "\nPress CLEAR or ON to erase the screen."
               "\nKeep up the hard work!"
               "\nX% of Y is Y% of X."
               "\n"
               "\nYou cannot take the logarithm of a negative number."
               "\nYou cannot use the factorial operation on a decimal."
               "\nSome functions cannot be integrated."
               "\nThe calculator may take a long time to process some operations. Be patient!"
               "\nThe problem with calculus jokes is that they're all derivative")
               );
}

void MainWindow::on_equals_released(){
    QMessageBox::information(
            this,
            tr("Application Name"),
            tr(labelNumber.toLocal8Bit().constData()) //converting the QString to a string

               );
}

