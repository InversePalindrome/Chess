/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessScene.hpp"

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

public slots:
    void transitionToMenu(ChessScene* chessScene);
    void transitionToGame(ChessScene* chessScene);

private:
    Ui::MainWindow *ui;
};
