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
    bool canMove(const ChessPiece& movingPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const;
	bool leavesKingInCheck(const ChessPiece& movingPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const;

	void manageDrop(const ChessPiece& movingPiece, const Chess::Position& newPos);
	void managePromotion(ChessPiece& movingPiece, ChessPieceGraphicsItem* graphicsPiece, const Chess::Position& newPos);

	void updateKingPosition(const ChessPiece& movingPiece, const Chess::Position newPos);

	void switchPlayer();


    ChessPieceGraphicsItem* getGraphicsPiece(const QPointF& position);

    ChessBoard chessBoard;
	Chess::Position lightKingPosition;
	Chess::Position darkKingPosition;
	std::vector<Chess::Transition> chessHistory;
	Chess::Color currentPlayer;

    QPointF sourcePosition;
	std::array<std::array<ChessPieceGraphicsItem*, Chess::RANKS>, Chess::FILES> graphicsBoard;

signals:
	void openPromotionDialog(ChessPiece& movingPiece);
};
