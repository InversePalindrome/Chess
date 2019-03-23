/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessView.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>


class ChessView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ChessView(QGraphicsScene* scene, QWidget* parent = nullptr);
};
