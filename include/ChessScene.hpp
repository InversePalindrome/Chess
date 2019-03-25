/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"
#include "ChessBoard.hpp"

#include <QGraphicsScene>

#include <unordered_map>


class ChessScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ChessScene(ChessBoard& chessBoard, QObject* parent = nullptr);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    void populateScene();

    ChessBoard& chessBoard;

    std::unordered_map<ChessPiece, QString, ChessPieceHash> piecesGraphicsMap;
};
