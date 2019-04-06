/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessUtility.cpp
https://inversepalindrome.com/
*/


#include "ChessUtility.hpp"
#include "ChessConstants.hpp"

#include <QRectF>


Chess::Position Chess::getChessPositionAt(const QPointF& position)
{
    QRectF chessRect;
    chessRect.setSize({ Chess::FILES * Chess::SQUARE_SIZE, Chess::RANKS * Chess::SQUARE_SIZE });
    chessRect.moveCenter({0, 0});

    if(!chessRect.contains(position))
    {
        return Chess::Position{};
    }

    auto file = static_cast<std::size_t>((position.x() + chessRect.width() / 2) / Chess::SQUARE_SIZE);
    auto rank = static_cast<std::size_t>((position.y() + chessRect.height() / 2) / Chess::SQUARE_SIZE);

    return Chess::Position{ file, rank };
}

QPointF Chess::getGraphicsPositionAt(const Chess::Position& position)
{
    QRectF chessRect;
    chessRect.setSize({ Chess::FILES * Chess::SQUARE_SIZE, Chess::RANKS * Chess::SQUARE_SIZE });
    chessRect.moveCenter({0, 0});

    qreal x = chessRect.left() + Chess::SQUARE_SIZE / 2 + Chess::SQUARE_SIZE * position.file;
    qreal y = chessRect.top() + Chess::SQUARE_SIZE / 2 + Chess::SQUARE_SIZE
            * (Chess::RANKS - position.rank - 1);

    return QPointF(x, y);
}
