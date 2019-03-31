/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.cpp
https://inversepalindrome.com/
*/


#include "MainWindow.hpp"
#include "ChessScene.hpp"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setVisible(false);
    ui->toolBar->addAction(QIcon(":/Resources/HomeIcon.png"), "Menu", [this](){ transitionToMenu(); });
    ui->chessView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->chessView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->chessView->setRenderHint(QPainter::Antialiasing);
    ui->chessView->setMouseTracking(true);
    ui->chessView->show();

    connect(ui->playButton, &QPushButton::clicked, [this](){ transitionToGame(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::transitionToMenu()
{
    ui->stackWidget->setCurrentIndex(0);
    ui->toolBar->setVisible(false);

    delete ui->chessView->scene();
    ui->chessView->setScene(nullptr);
}

void MainWindow::transitionToGame()
{
    ui->stackWidget->setCurrentIndex(1);
    ui->toolBar->setVisible(true);

    ui->chessView->setScene(new ChessScene());
}
