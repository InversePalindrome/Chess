/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessMove.hpp"
#include "ChessBoard.hpp"
#include "ChessPosition.hpp"
#include "ChessConstants.hpp"
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

    void addMove(const ChessPiece& movingPiece,
        const Chess::Position& oldPos, const Chess::Position& newPos);

    void handleShortCastling(ChessPiece& movingPiece, ChessPieceGraphicsItem* movingGraphicsPiece,
        const Chess::Position& oldPos, const Chess::Position& newPos);
    void handleLongCastling(ChessPiece& movingPiece, ChessPieceGraphicsItem* movingGraphicsPiece, const Chess::Position& oldPos,
        const Chess::Position& newPos);
    void handleEnPassant(ChessPiece& movingPiece, ChessPieceGraphicsItem* movingGraphicsPiece,
        const Chess::Position& oldPos, const Chess::Position& newPos);
    void handleRegularMove(ChessPiece& movingPiece, ChessPieceGraphicsItem* movingGraphicsPiece,
        const Chess::Position& oldPos, const Chess::Position& newPos);

    void manageDrop(const ChessPiece& movingPiece, const Chess::Position& newPos);
    void managePromotion(ChessPiece& movingPiece, ChessPieceGraphicsItem* graphicsPiece,
        const Chess::Position& newPos);

    void updateKingPosition(const ChessPiece& movingPiece, const Chess::Position newPos);
    void updateEndGame() const;

    void switchPlayer();

    void movePiece(ChessPiece& movingPiece, ChessPieceGraphicsItem* movingGraphicsPiece,
        const Chess::Position& oldPos, const Chess::Position& newPos);

    ChessPieceGraphicsItem* getGraphicsPiece(const QPointF& pos);
    void removeGraphicsPiece(const Chess::Position& pos);

    Chess::Board<ChessPiece> chessBoard;
    Chess::Position lightKingPosition;
    Chess::Position darkKingPosition;
    std::vector<Chess::Move> moveHistory;
    Chess::Color currentPlayer;

    QPointF sourcePosition;
    Chess::Board<ChessPieceGraphicsItem*> graphicsBoard;

signals:
    void gameEnded(Chess::EndResult result) const;
    void openPromotionDialog(ChessPiece& movingPiece);
};
