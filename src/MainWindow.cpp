/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.cpp
https://inversepalindrome.com/
*/


#include "ChessScene.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QGraphicsView>


MainWindow::MainWindow(ChessBoard& chessBoard, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chessBoard(chessBoard)
{
    ui->setupUi(this);
    ui->toolBar->setVisible(false);
    ui->toolBar->addAction(QIcon(":/Resources/HomeIcon.png"), "Menu", [this](){ transitionToMenu(); });

    auto* scene = new ChessScene(chessBoard);

    auto* view = ui->chessView;
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);
    view->show();

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
}

void MainWindow::transitionToGame()
{
    ui->stackWidget->setCurrentIndex(1);
    ui->toolBar->setVisible(true);
}
