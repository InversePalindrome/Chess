/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.cpp
https://inversepalindrome.com/
*/


#include "ChessScene.hpp"
#include "ChessBoardGraphicsItem.hpp"


ChessScene::ChessScene(ChessBoard& chessBoard, QObject* parent) :
    QGraphicsScene(parent),
    chessBoard(chessBoard),
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

void ChessScene::populateScene()
{
    addItem(new ChessBoardGraphicsItem());

    setSceneRect(itemsBoundingRect());

    for(std::size_t rank = 0; rank < Chess::RANKS; ++rank)
    {
        for(std::size_t file = 0; file < Chess::FILES; ++file)
        {
            if(piecesGraphicsMap.count(chessBoard[rank][file]))
            {
                auto* graphicPiece = new QGraphicsPixmapItem(QPixmap(":/Resources/ChessPieces/"
                                     + piecesGraphicsMap[chessBoard[rank][file]]).scaledToWidth(32));

                graphicPiece->setPos(sceneRect().left() + Chess::SQUARE_SIZE / 2 + Chess::SQUARE_SIZE * file,
                                     sceneRect().top() + Chess::SQUARE_SIZE / 2 + Chess::SQUARE_SIZE * rank);

                addItem(graphicPiece);
            }
        }
    }
}
