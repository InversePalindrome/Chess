/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessBoard.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <QPainter>
#include <QGraphicsItem>


class ChessBoard : public QGraphicsItem
{
public:
    explicit ChessBoard(QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    static constexpr int FILES = 8;
    static constexpr int RANKS = 8;
    static constexpr qreal SQUARE_SIZE = 64;

private:
    QRectF rect;
    QColor lightColor;
    QColor darkColor;
};
