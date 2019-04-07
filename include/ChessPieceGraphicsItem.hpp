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
    ChessPieceGraphicsItem(const ChessPiece& chessPiece, const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    virtual int type() const override;

    enum { Type = UserType + 1 };

	ChessPiece getChessPiece();
	void setChessPiece(const ChessPiece& chessPiece);

private:
	ChessPiece chessPiece;
};
