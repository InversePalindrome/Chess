/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessUtility.cpp
https://inversepalindrome.com/
*/


#include "ChessUtility.hpp"
#include "ChessConstants.hpp"


Chess::Position Chess::getChessPositionAt(const QPointF& position)
{
    QRectF chessRect;
    chessRect.setSize({ Chess::RANKS * Chess::SQUARE_SIZE, Chess::FILES * Chess::SQUARE_SIZE });
    chessRect.moveCenter({0, 0});

    if(!chessRect.contains(position))
    {
        return Chess::Position{};
    }

	auto rank = static_cast<std::size_t>((position.y() + chessRect.height() / 2) / Chess::SQUARE_SIZE);
    auto file = static_cast<std::size_t>((position.x() + chessRect.width() / 2) / Chess::SQUARE_SIZE);

    return Chess::Position{ rank, file };
}

QPointF Chess::getGraphicsPosition(const QRectF& sceneRect, const Chess::Position& chessPosition)
{
	return { sceneRect.left() + Chess::SQUARE_SIZE / 2.0 + Chess::SQUARE_SIZE * chessPosition.file,
			sceneRect.top() + Chess::SQUARE_SIZE / 2.0 + Chess::SQUARE_SIZE * chessPosition.rank };
}