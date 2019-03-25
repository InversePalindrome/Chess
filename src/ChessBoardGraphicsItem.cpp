/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessBoardGraphicsItem.cpp
https://inversepalindrome.com/
*/


#include "ChessConstants.hpp"
#include "ChessBoardGraphicsItem.hpp"


ChessBoardGraphicsItem::ChessBoardGraphicsItem(QGraphicsItem* parent) :
    QGraphicsItem(parent),
    lightColor(255, 255, 255),
    darkColor(0, 0, 0)
{
    rect.setSize({ Chess::FILES * Chess::SQUARE_SIZE, Chess::RANKS * Chess::SQUARE_SIZE });
    rect.moveCenter({0, 0});
}

QRectF ChessBoardGraphicsItem::boundingRect() const
{  
    return rect.marginsAdded(QMarginsF(Chess::SQUARE_SIZE / 2.0, Chess::SQUARE_SIZE / 2.0, Chess::SQUARE_SIZE / 2.0,
                                       Chess::SQUARE_SIZE / 2.0));
}

void ChessBoardGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF drawingRect(rect.topLeft(), QSizeF(Chess::SQUARE_SIZE, Chess::SQUARE_SIZE));
    const auto leftRect = drawingRect.left();

    for(int i = 0; i < Chess::RANKS; ++i)
    {
        drawingRect.moveLeft(leftRect);

        for(int j = 0; j < Chess::FILES; ++j)
        {
            if((i % 2) == (j % 2))
            {
                painter->fillRect(drawingRect, lightColor);
            }
            else
            {
                painter->fillRect(drawingRect, darkColor);
            }

            drawingRect.moveLeft(drawingRect.left() + Chess::SQUARE_SIZE);
        }

        drawingRect.moveTop(drawingRect.top() + Chess::SQUARE_SIZE);
    }

    auto font = painter->font();
    font.setPointSizeF(font.pointSizeF() * 0.7);
    painter->setFont(font);

    const QString fileText = "abcdefgh";

    for(int j = 0; j < Chess::FILES; ++j)
    {
        const qreal horizontalItems[] = { rect.top() - Chess::SQUARE_SIZE / 2.0, rect.bottom() };

        for(const auto& item : horizontalItems)
        {
            drawingRect = { rect.left() + (Chess::SQUARE_SIZE * j), item, Chess::SQUARE_SIZE, Chess::SQUARE_SIZE / 2.0 };

            painter->drawText(drawingRect, Qt::AlignCenter, fileText[j]);
        }
    }

    for(int i = 0; i < Chess::RANKS; ++i)
    {
        const qreal verticalItems[] = { rect.left() - Chess::SQUARE_SIZE / 2.0, rect.right() };

        for(const auto& item : verticalItems)
        {
            drawingRect = { item, rect.top() + (Chess::SQUARE_SIZE * i), Chess::SQUARE_SIZE / 2.0, Chess::SQUARE_SIZE };

            painter->drawText(drawingRect, Qt::AlignCenter, QString::number(i + 1));
        }
    }
}
