/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessPosition.hpp"
#include "ChessTransition.hpp"
#include "ChessPieceGraphicsItem.hpp"

#include <QGraphicsScene>

#include <array>
#include <vector>


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
    bool canMove(const ChessPiece& chessPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const;
	void manageDrop(const ChessPiece& movingChessPiece, const Chess::Position& newPosition);
	void switchPlayer();

    ChessPieceGraphicsItem* getGraphicsPiece(const QPointF& position);

    ChessBoard chessBoard;
	std::vector<Chess::Transition> chessHistory;
	Chess::Color currentPlayer;

    QPointF sourcePosition;
	std::array<std::array<ChessPieceGraphicsItem*, Chess::RANKS>, Chess::FILES> graphicsBoard;
};
