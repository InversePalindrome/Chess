/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"

#include <QMainWindow>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ChessBoard& chessBoard, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void transitionToGame();

private:
    Ui::MainWindow *ui;

    ChessBoard& chessBoard;
};
