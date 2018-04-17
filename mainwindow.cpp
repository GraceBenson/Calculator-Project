#include "mainwindow.h"
#include "ui_mainwindow.h"

QString labelNumber;

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
//    if(ui->pushButton_add->isChecked() || ui->pushButton_minus->isChecked()
//            || ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()
//            || ui->pushButton_exponent->isChecked())
//    {
//        labelNumber = button->text().toDouble();
//    }
//    else{
//        labelNumber = (ui->label->text() + button->text()).toDouble();
//    }
 //   QString numLabel = QString::number(labelNumber, 'g', 15);
    ui->label->setText(labelNumber);
}

void MainWindow::on_clearbutton_released()
{
    labelNumber= "0";
    ui->label->setText(labelNumber);
}
