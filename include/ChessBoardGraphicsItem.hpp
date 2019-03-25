/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessBoardGraphicsItem.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <QPainter>
#include <QGraphicsItem>


class ChessBoardGraphicsItem : public QGraphicsItem
{
public:
    explicit ChessBoardGraphicsItem(QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
    QRectF rect;
    QColor lightColor;
    QColor darkColor;
};
