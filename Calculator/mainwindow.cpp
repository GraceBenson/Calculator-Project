#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "sourcecode.cpp"

//double x;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->pushButton_plusminus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_exponent, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

//    ui->pushButton_add->setCheckable(true);
//    ui->pushButton_minus->setCheckable(true);
//    ui->pushButton_multiply->setCheckable(true);
//    ui->pushButton_divide->setCheckable(true);
//    ui->pushButton_exponent->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    double labelNumber = (ui->label->text() + button->text()).toDouble();
    QString numLabel = QString::number(labelNumber, 'g', 15);
    ui->label->setText(numLabel);
}

void MainWindow::on_pushButton_decimal_released()
{
    if(!(ui->label->text().contains('.'))){
        ui->label->setText(ui->label->text() + ".");
    }
}

void MainWindow::unary_operation_pressed(){
    // for +/- and %
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString numLabel;
    if (button->text() == "+/-"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        numLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(numLabel);
    }
    else{
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        numLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(numLabel);
        }
}

void MainWindow::on_pushButton_equal_released()
{
//    double labelNumber, y;
//    y = ui->label->text().toDouble();
//    QString numLabel;

//    if (ui->pushButton_exponent->isChecked()) {
//        labelNumber = x ^ y;      //TODO: Double check operation order for first and second round stuff
//        numLabel = QString::number(labelNumber, 'g', 15);
//        ui->label->setText(numLabel);
//        ui->pushButton_exponent->setChecked(false);
//    }
//   else if (ui->pushButton_multiply->isChecked()) {
//        labelNumber = x * y;
//        numLabel = QString::number(labelNumber, 'g', 15);
//        ui->label->setText(numLabel);
//        ui->pushButton_multiply->setChecked(false);
//    }

//    else if (ui->pushButton_divide->isChecked()) {
//        labelNumber = x / y;
//        numLabel = QString::number(labelNumber, 'g', 15);
//        ui->label->setText(numLabel);
//        ui->pushButton_divide->setChecked(false);
//    }

//    else if (ui->pushButton_add->isChecked()) {
//        labelNumber = x + y;
//        numLabel = QString::number(labelNumber, 'g', 15);
//        ui->label->setText(numLabel);
//        ui->pushButton_add->setChecked(false);
//    }

//    else if (ui->pushButton_minus->isChecked()) {
//        labelNumber = x - y;
//        numLabel = QString::number(labelNumber, 'g', 15);
//        ui->label->setText(numLabel);
//        ui->pushButton_minus->setChecked(false);
//    }
}

void MainWindow::binary_operation_pressed(){
    // *, /, +, -, ^
    QPushButton * button = (QPushButton*) sender();
    x = ui->label->text().toDouble();   // first num
    button->setChecked(true);
}

void MainWindow::on_pushButton_clear_released()
{

}

