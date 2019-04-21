/*
Copyright (c) 2019 Inverse Palindrome
Chess - MainWindow.cpp
https://inversepalindrome.com/
*/


#include "MainWindow.hpp"
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

	auto* chessScene = new ChessScene();
	ui->chessView->setScene(chessScene);

	ui->toolBar->addAction(QIcon(":/Resources/HomeIcon.png"), "Menu", [this, chessScene]()
	{
		transitionToMenu(chessScene);
	});
;
	connect(chessScene, &ChessScene::openPromotionDialog, [this](auto & piece)
	{
		auto* dialog = new PromotionDialog(piece, this);
		dialog->exec();
	});
	connect(chessScene, &ChessScene::gameEnded, [this, chessScene](auto result)
	{
		auto* dialog = new GameOverDialog(result, this);
		connect(dialog, &GameOverDialog::transitionToMenu, [this, chessScene]()
		{ 
			transitionToMenu(chessScene); 
		});
		connect(dialog, &GameOverDialog::playAgain, [this, chessScene]()
		{ 
			chessScene->clearScene();
			transitionToGame(chessScene);
		});
		dialog->exec();
	});
    connect(ui->playButton, &QPushButton::clicked, [this, chessScene]()
	{ 
		transitionToGame(chessScene);
	});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::transitionToMenu(ChessScene* chessScene)
{
	chessScene->clearScene();

    ui->stackWidget->setCurrentIndex(0);
    ui->toolBar->setVisible(false);
}

void MainWindow::transitionToGame(ChessScene* chessScene)
{
	chessScene->populateScene();

    ui->stackWidget->setCurrentIndex(1);
    ui->toolBar->setVisible(true);
}