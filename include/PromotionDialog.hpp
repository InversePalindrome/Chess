/*
Copyright (c) 2019 Inverse Palindrome
Chess - PromotionDialog.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessConstants.hpp"

#include <QDialog>


class PromotionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PromotionDialog(Chess::Color color, QWidget* parent = nullptr);
};