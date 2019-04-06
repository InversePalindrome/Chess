/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "ChessPieceGraphicsItem.hpp"

#include <QHideEvent>
#include <QGraphicsScene>

#include <vector>
#include <unordered_map>


class ChessScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ChessScene(QObject* parent = nullptr);

    void populateScene();

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    ChessPieceGraphicsItem* getGraphicsPiece(const QPointF& position);

    ChessBoard chessBoard;

    std::unordered_map<ChessPiece, QString, ChessPieceHash> piecesGraphicsMap;

    QPointF sourcePosition;
};
