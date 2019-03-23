/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPiece.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <QGraphicsPixmapItem>


class ChessPiece : public QGraphicsPixmapItem
{
public:
    explicit ChessPiece(QGraphicsItem* parent = nullptr);
};
