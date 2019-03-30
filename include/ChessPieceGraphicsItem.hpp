/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPieceGraphicsItem.hpp
https://inversepalindrome.com/
*/


#include "ChessPiece.hpp"

#include <QGraphicsPixmapItem>


class ChessPieceGraphicsItem : public QGraphicsPixmapItem
{
public:
    ChessPieceGraphicsItem(const QPixmap& pixmap, const ChessPiece& chessPiece, QGraphicsItem* parent = nullptr);

    virtual int type() const override;

    ChessPiece getPiece() const;

    enum { Type = UserType + 1 };

private:
    ChessPiece chessPiece;
};
