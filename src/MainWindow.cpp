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

    auto* scene = new ChessScene(chessBoard, ui->ChessBoard);

    auto* view = ui->chessView;
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);
    view->fitInView(scene->sceneRect());
    view->show();
}
