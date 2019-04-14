/*
Copyright (c) 2019 Inverse Palindrome
Chess - PromotionDialog.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"

#include <QDialog>


class PromotionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PromotionDialog(ChessPiece& promotedPiece, QWidget* parent = nullptr);
};