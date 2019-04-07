/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPieceGraphicsItem.cpp
https://inversepalindrome.com/
*/


#include "ChessPieceGraphicsItem.hpp"


ChessPieceGraphicsItem::ChessPieceGraphicsItem(const ChessPiece& chessPiece, const QPixmap& pixmap, QGraphicsItem* parent) :
    QGraphicsPixmapItem(pixmap, parent),
	chessPiece(chessPiece)
{
}

int ChessPieceGraphicsItem::type() const
{
    return Type;
}

ChessPiece ChessPieceGraphicsItem::getChessPiece()
{
	return chessPiece;
}

void ChessPieceGraphicsItem::setChessPiece(const ChessPiece& chessPiece)
{
	this->chessPiece = chessPiece;
}