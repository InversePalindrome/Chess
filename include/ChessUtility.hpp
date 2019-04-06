/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessUtility.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPosition.hpp"

#include <QPointF>


namespace Chess
{
    Chess::Position getChessPositionAt(const QPointF& position);
    QPointF getGraphicsPositionAt(const Chess::Position& position);
}
