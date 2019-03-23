/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessBoard.cpp
https://inversepalindrome.com/
*/


#include "ChessBoard.hpp"


ChessBoard::ChessBoard(QGraphicsItem* parent) :
    QGraphicsItem(parent),
    lightColor(255, 255, 255),
    darkColor(0, 0, 0)
{
    rect.setSize({FILES * SQUARE_SIZE, RANKS * SQUARE_SIZE});
    rect.moveCenter({0, 0});
}

QRectF ChessBoard::boundingRect() const
{  
    return rect.marginsAdded(QMarginsF(SQUARE_SIZE / 2.0, SQUARE_SIZE / 2.0, SQUARE_SIZE / 2.0,
                                       SQUARE_SIZE / 2.0));
}

void ChessBoard::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF drawingRect(rect.topLeft(), QSizeF(SQUARE_SIZE, SQUARE_SIZE));
    const auto leftRect = drawingRect.left();

    for(int i = 0; i < RANKS; ++i)
    {
        drawingRect.moveLeft(leftRect);

        for(int j = 0; j < FILES; ++j)
        {
            if((i % 2) == (j % 2))
            {
                painter->fillRect(drawingRect, lightColor);
            }
            else
            {
                painter->fillRect(drawingRect, darkColor);
            }

            drawingRect.moveLeft(drawingRect.left() + SQUARE_SIZE);
        }

        drawingRect.moveTop(drawingRect.top() + SQUARE_SIZE);
    }

    auto font = painter->font();
    font.setPointSizeF(font.pointSizeF() * 0.7);
    painter->setFont(font);

    const QString fileText = "abcdefgh";

    for(int j = 0; j < FILES; ++j)
    {
        const qreal horizontalItems[] = { rect.top() - SQUARE_SIZE / 2.0, rect.bottom() };

        for(const auto& item : horizontalItems)
        {
            drawingRect = { rect.left() + (SQUARE_SIZE * j), item, SQUARE_SIZE, SQUARE_SIZE / 2.0 };

            painter->drawText(drawingRect, Qt::AlignCenter, fileText[j]);
        }
    }

    for(int i = 0; i < RANKS; ++i)
    {
        const qreal verticalItems[] = { rect.left() - SQUARE_SIZE / 2.0, rect.right() };

        for(const auto& item : verticalItems)
        {
            drawingRect = { item, rect.top() + (SQUARE_SIZE * i), SQUARE_SIZE / 2.0, SQUARE_SIZE };

            painter->drawText(drawingRect, Qt::AlignCenter, QString::number(i + 1));
        }
    }
}
