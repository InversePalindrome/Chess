/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.hpp
https://inversepalindrome.com/
*/


#include "ChessScene.hpp"
#include "ChessBoard.hpp"


ChessScene::ChessScene(QObject* parent) :
    QGraphicsScene(parent)
{
    addItem(new ChessBoard());

    setSceneRect(itemsBoundingRect());
}

void ChessScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void ChessScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
}

void ChessScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}
