/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.cpp
https://inversepalindrome.com/
*/


#include "MainWindow.hpp"
#include "ChessScene.hpp"
#include "ui_MainWindow.h"
#include "GameOverDialog.hpp"
#include "PromotionDialog.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setVisible(false);
    ui->chessView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->chessView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->chessView->setRenderHint(QPainter::Antialiasing);
    ui->chessView->setMouseTracking(true);
    ui->chessView->show();
	ui->toolBar->addAction(QIcon(":/Resources/HomeIcon.png"), "Menu", [this]()
	{
		transitionToMenu();
	});
    connect(ui->playButton, &QPushButton::clicked, [this]()
    {
       transitionToGame();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::transitionToMenu()
{
    ui->chessView->scene()->deleteLater();

    ui->stackWidget->setCurrentIndex(0);
    ui->toolBar->setVisible(false);
}

void MainWindow::transitionToGame()
{
    auto* chessScene = new ChessScene();
    ui->chessView->setScene(chessScene);

    connect(chessScene, &ChessScene::openPromotionDialog, [this](auto & piece)
    {
        auto* dialog = new PromotionDialog(piece, this);
        dialog->exec();
    });
    connect(chessScene, &ChessScene::gameEnded, [this](auto result)
    {
        auto* dialog = new GameOverDialog(result, this);
        connect(dialog, &GameOverDialog::transitionToMenu, [this]()
        {
             transitionToMenu();
        });
        connect(dialog, &GameOverDialog::playAgain, [this]()
        {
              transitionToGame();
        });
        dialog->exec();
    });

    ui->stackWidget->setCurrentIndex(1);
    ui->toolBar->setVisible(true);
}