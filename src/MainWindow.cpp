/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.cpp
https://inversepalindrome.com/
*/


#include "MainWindow.hpp"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->singlePlayerButton, &QPushButton::clicked, [this](){ transitionToGame(); });
    connect(ui->multiPlayerButton, &QPushButton::clicked, [this](){ transitionToGame(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::transitionToGame()
{
    ui->stackWidget->setCurrentIndex(1);
}
