/*
Copyright (c) 2019 Inverse Palindrome
Chess - PromotionDialog.cpp
https://inversepalindrome.com/
*/


#include "ChessResources.hpp"
#include "PromotionDialog.hpp"

#include <QBoxLayout>
#include <QPushButton>


PromotionDialog::PromotionDialog(Chess::Color color, QWidget* parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowStaysOnTopHint)
{
	setFixedSize(400, 100);
	setWindowTitle("Pawn Promotion");
	setAttribute(Qt::WA_DeleteOnClose);

	auto* layout = new QHBoxLayout(this);

	auto* knightButton = new QPushButton(this);
	knightButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Knight, color }))));

	auto* bishopButton = new QPushButton(this);
	bishopButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Bishop, color }))));

	auto* rookButton = new QPushButton(this);
	rookButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Rook, color }))));

	auto* queenButton = new QPushButton(this);
	queenButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Queen, color }))));

	layout->addWidget(knightButton);
	layout->addWidget(bishopButton);
	layout->addWidget(rookButton);
	layout->addWidget(queenButton);
}