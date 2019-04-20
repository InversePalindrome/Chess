/*
Copyright (c) 2019 Inverse Palindrome
Chess - GameOverDialog.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessConstants.hpp"

#include <QDialog>


class GameOverDialog : public QDialog
{
	Q_OBJECT

public:
	explicit GameOverDialog(Chess::EndResult result, QWidget* parent = nullptr);

signals:
	void transitionToMenu();
	void playAgain();
};