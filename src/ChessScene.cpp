/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.cpp
https://inversepalindrome.com/
*/


#include "ChessScene.hpp"
#include "ChessUtility.hpp"
#include "ChessValidation.hpp"
#include "ChessBoardGraphicsItem.hpp"

#include <QGraphicsSceneMouseEvent>


ChessScene::ChessScene(QObject* parent) :
    QGraphicsScene(parent),
    piecesGraphicsMap({ { ChessPiece{Chess::Piece::Pawn, Chess::Color::Light }, "LightPawn.png" },
                  { ChessPiece{ Chess::Piece::Knight, Chess::Color::Light }, "LightKnight.png" },
                  { ChessPiece{ Chess::Piece::Bishop, Chess::Color::Light }, "LightBishop.png" },
                  { ChessPiece{ Chess::Piece::Rook, Chess::Color::Light }, "LightRook.png" },
                  { ChessPiece{ Chess::Piece::King, Chess::Color::Light }, "LightKing.png" },
                  { ChessPiece{ Chess::Piece::Queen, Chess::Color::Light }, "LightQueen.png" },
                  { ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark }, "DarkPawn.png" },
                  { ChessPiece{ Chess::Piece::Knight, Chess::Color::Dark }, "DarkKnight.png" },
                  { ChessPiece{ Chess::Piece::Bishop, Chess::Color::Dark }, "DarkBishop.png" },
                  { ChessPiece{ Chess::Piece::Rook, Chess::Color::Dark }, "DarkRook.png" },
                  { ChessPiece{ Chess::Piece::King, Chess::Color::Dark }, "DarkKing.png" },
                  { ChessPiece{ Chess::Piece::Queen, Chess::Color::Dark }, "DarkQueen.png" }, })
{
    populateScene();
}

void ChessScene::populateScene()
{
    auto* graphicChessBoard = new ChessBoardGraphicsItem();

    addItem(graphicChessBoard);

    setSceneRect(itemsBoundingRect());

    for(std::size_t rank = 0; rank < Chess::RANKS; ++rank)
    {
        for(std::size_t file = 0; file < Chess::FILES; ++file)
        {
            if(piecesGraphicsMap.count(chessBoard[rank][file]))
            {
                auto* graphicsPiece = new ChessPieceGraphicsItem(QPixmap(":/Resources/ChessPieces/"
                                     + piecesGraphicsMap[chessBoard[rank][file]]).scaledToWidth(
                                     Chess::PIECE_SIZE), chessBoard[rank][file], graphicChessBoard);

                graphicsPiece->setPos(sceneRect().left() + Chess::SQUARE_SIZE / 2 + Chess::SQUARE_SIZE * file,
                                     sceneRect().top() + Chess::SQUARE_SIZE / 2 + Chess::SQUARE_SIZE * rank);
            }
        }
    }
}

void ChessScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //auto* piece = getGraphicsPiece(event->scenePos());

    QGraphicsScene::mouseMoveEvent(event);
}

void ChessScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    auto* piece = getGraphicsPiece(event->scenePos());

    if(piece == nullptr || event->button() != Qt::LeftButton)
    {
        return;
    }

    sourcePosition = event->scenePos();

    piece->setFlag(QGraphicsItem::ItemIsMovable, true);

    QGraphicsScene::mousePressEvent(event);
}

void ChessScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    auto* piece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(mouseGrabberItem());

    if(piece != nullptr)
    {
        const auto oldPosition = Chess::getChessPositionAt(sourcePosition);
        const auto newPosition = Chess::getChessPositionAt(event->scenePos());


    }

    QGraphicsScene::mouseReleaseEvent(event);
}

ChessPieceGraphicsItem* ChessScene::getGraphicsPiece(const QPointF& position)
{
    const auto items = this->items(position);

    for(auto item : items)
    {
        auto* piece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(item);

        if(piece != nullptr)
        {
            return piece;
        }
    }

    return nullptr;
}
