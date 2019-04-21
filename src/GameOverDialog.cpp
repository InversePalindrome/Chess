/*
Copyright (c) 2019 Inverse Palindrome
Chess - GameOverDialog.cpp
https://inversepalindrome.com/
*/


#include "GameOverDialog.hpp"

#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QApplication>


GameOverDialog::GameOverDialog(Chess::EndResult endResult, QWidget* parent) :
	QDialog(parent, Qt::WindowTitleHint)
{
	setFixedSize(600, 600);
	setWindowTitle("Game Over");
	setAttribute(Qt::WA_DeleteOnClose);

	auto* layout = new QVBoxLayout(this);

	auto* resultLabel = new QLabel(this);
	resultLabel->setFont(QFont("Bebas", 24, QFont::Bold));
	resultLabel->setAlignment(Qt::AlignCenter);
	switch (endResult)
	{
	case Chess::EndResult::LightWon:
		resultLabel->setText("Light side won!");
		break;
	case Chess::EndResult::DarkWon:
		resultLabel->setText("Dark side won!");
		break;
	case Chess::EndResult::Stalemate:
		resultLabel->setText("Stalemate");
		break;
	}

	auto* playAgainButton = new QPushButton("Play Again", this);
	playAgainButton->setFont(QFont("Bebas", 24, QFont::Bold));
	connect(playAgainButton, &QPushButton::clicked, [this]()
	{
		emit playAgain();
		close();
	});

	auto* menuButton = new QPushButton("Menu", this);
	menuButton->setFont(QFont("Bebas", 24, QFont::Bold));
	connect(menuButton, &QPushButton::clicked, [this]()
	{
		emit transitionToMenu();
		close();
	});

	auto* quitButton = new QPushButton("Quit", this);
	quitButton->setFont(QFont("Bebas", 24, QFont::Bold));
	connect(quitButton, &QPushButton::clicked, []()
	{
		QApplication::quit();
	});

	layout->addWidget(resultLabel);
	layout->addWidget(playAgainButton);
	layout->addWidget(menuButton);
	layout->addWidget(quitButton);
}