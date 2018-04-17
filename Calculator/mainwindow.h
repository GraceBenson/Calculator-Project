#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void digit_pressed();
//    void on_pushButton_decimal_released();
//    void unary_operation_pressed();
    void on_pushButton_clear_released();
    void on_pushButton_equal_released();
//    void binary_operation_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
