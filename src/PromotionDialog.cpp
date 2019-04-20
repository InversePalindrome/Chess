/*
Copyright (c) 2019 Inverse Palindrome
Chess - PromotionDialog.cpp
https://inversepalindrome.com/
*/


#include "ChessResources.hpp"
#include "PromotionDialog.hpp"

#include <QBoxLayout>
#include <QPushButton>


PromotionDialog::PromotionDialog(ChessPiece& promotedPiece, QWidget* parent) :
	QDialog(parent, Qt::WindowTitleHint)
{
	setFixedSize(800, 300);
	setWindowTitle("Pawn Promotion");
	setAttribute(Qt::WA_DeleteOnClose);

	auto* layout = new QHBoxLayout(this);

	auto* knightButton = new QPushButton(this);
	knightButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Knight, promotedPiece.color }))));
	knightButton->setIconSize({ Chess::PIECE_SIZE, Chess::PIECE_SIZE });
	connect(knightButton, &QPushButton::clicked, [this, &promotedPiece]()
	{ 
		promotedPiece.piece = Chess::Piece::Knight; 
		close();
	});

	auto* bishopButton = new QPushButton(this);
	bishopButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Bishop, promotedPiece.color }))));
	bishopButton->setIconSize({ Chess::PIECE_SIZE, Chess::PIECE_SIZE });
	connect(bishopButton, &QPushButton::clicked, [this, &promotedPiece]()
	{ 
		promotedPiece.piece = Chess::Piece::Bishop; 
		close();
	});

	auto* rookButton = new QPushButton(this);
	rookButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Rook, promotedPiece.color }))));
	rookButton->setIconSize({ Chess::PIECE_SIZE, Chess::PIECE_SIZE });
	connect(rookButton, &QPushButton::clicked, [this, &promotedPiece]() 
	{
		promotedPiece.piece = Chess::Piece::Rook; 
		close();
	});

	auto* queenButton = new QPushButton(this);
	queenButton->setIcon(QIcon(":/Resources/ChessPieces/" + QString::fromStdString(Chess::resources.at
	(ChessPiece{ Chess::Piece::Queen, promotedPiece.color }))));
	queenButton->setIconSize({ Chess::PIECE_SIZE, Chess::PIECE_SIZE });
	connect(queenButton, &QPushButton::clicked, [this, &promotedPiece]() 
	{ 
		promotedPiece.piece = Chess::Piece::Queen;
		close();
	});
	
	layout->addWidget(knightButton);
	layout->addWidget(bishopButton);
	layout->addWidget(rookButton);
	layout->addWidget(queenButton);
}