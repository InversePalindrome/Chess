/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessPosition.hpp"
#include "ChessConstants.hpp"
#include "ChessTransition.hpp"
#include "ChessPieceGraphicsItem.hpp"

#include <QGraphicsScene>

#include <vector>


class ChessScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ChessScene(QObject* parent = nullptr);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    bool canMove(const ChessPiece& movingPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const;
    bool isKingInCheck(Chess::Color kingColor) const;
    bool leavesKingInCheck(const ChessPiece& movingPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const;

    void manageHistory(const ChessPiece& droppedPiece, const ChessPiece& promotedPiece,
        const Chess::Position& oldPos, const Chess::Position& newPos);
    void manageDrop(const ChessPiece& movingPiece, const Chess::Position& newPos);
    void managePromotion(ChessPiece& movingPiece, ChessPieceGraphicsItem* graphicsPiece,
        const Chess::Position& newPos);

    void updateKingPosition(const ChessPiece& movingPiece, const Chess::Position newPos);
    void updateEndGame() const;

    void switchPlayer();

    ChessPieceGraphicsItem* getGraphicsPiece(const QPointF& position);

    Chess::Board<ChessPiece> chessBoard;
    Chess::Position lightKingPosition;
    Chess::Position darkKingPosition;
    std::vector<Chess::Transition> chessHistory;
    Chess::Color currentPlayer;

    QPointF sourcePosition;
    Chess::Board<ChessPieceGraphicsItem*> graphicsBoard;

signals:
    void gameEnded(Chess::EndResult result) const;
    void openPromotionDialog(ChessPiece& movingPiece);
};
