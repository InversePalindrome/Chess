/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessUtility.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPosition.hpp"

#include <QRectF>
#include <QPointF>


namespace Chess
{
    Chess::Position getChessPositionAt(const QPointF& position);
    QPointF getGraphicsPosition(const QRectF& sceneRect, const Chess::Position& chessPosition);
}
