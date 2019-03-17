/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <QMainWindow>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
