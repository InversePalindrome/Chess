/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPieceGraphicsItem.cpp
https://inversepalindrome.com/
*/


#include "ChessPieceGraphicsItem.hpp"


ChessPieceGraphicsItem::ChessPieceGraphicsItem(const QPixmap& pixmap, const ChessPiece& chessPiece, QGraphicsItem* parent) :
    QGraphicsPixmapItem(pixmap, parent),
    chessPiece(chessPiece)
{
}

int ChessPieceGraphicsItem::type() const
{
    return Type;
}

ChessPiece ChessPieceGraphicsItem::getPiece() const
{
    return chessPiece;
}
