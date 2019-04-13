/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.cpp
https://inversepalindrome.com/
*/


#include "ChessScene.hpp"
#include "ChessUtility.hpp"
#include "ChessResources.hpp"
#include "ChessValidation.hpp"
#include "ChessBoardGraphicsItem.hpp"

#include <QGraphicsSceneMouseEvent>


ChessScene::ChessScene(QObject* parent) :
    QGraphicsScene(parent),
	currentPlayer(Chess::Color::Light)
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
            if(Chess::resources.count(chessBoard[rank][file]))
            {
                auto* graphicsPiece = new ChessPieceGraphicsItem(chessBoard[rank][file], QPixmap(":/Resources/ChessPieces/"
                                     + QString::fromStdString(Chess::resources.at(chessBoard[rank][file]))).scaledToWidth(
                                     Chess::PIECE_SIZE), graphicChessBoard);
				
				graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), Chess::Position{rank, file}));
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
	if (auto * graphicsPiece = getGraphicsPiece(event->scenePos()); graphicsPiece != nullptr &&
		graphicsPiece->getChessPiece().color == currentPlayer && event->button() == Qt::LeftButton)
	{
		sourcePosition = event->scenePos();

		graphicsPiece->setFlag(QGraphicsItem::ItemIsMovable, true);
	}

    QGraphicsScene::mousePressEvent(event);
}

void ChessScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(auto * graphicsPiece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(mouseGrabberItem());
	  graphicsPiece != nullptr)
    {
        const auto oldPosition = Chess::getChessPositionAt(sourcePosition);
        const auto newPosition = Chess::getChessPositionAt(event->scenePos());
		auto movingPiece = chessBoard[oldPosition.rank][oldPosition.file];

        if(canMove(movingPiece, oldPosition, newPosition))
        {
			movingPiece.hasMoved = true;

			manageDrop(movingPiece, newPosition);
			
			chessBoard[oldPosition.rank][oldPosition.file] = ChessPiece{};
			chessBoard[newPosition.rank][newPosition.file] = movingPiece;

			graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), newPosition));

			switchPlayer();
        }
        else
        {
			graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), oldPosition));
        }

		graphicsPiece->setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

bool ChessScene::canMove(const ChessPiece& chessPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const
{
    switch(chessPiece.piece)
    {
        case Chess::Piece::Pawn:
            return Chess::isPawnMoveValid(chessBoard, chessPiece.color, chessPiece.hasMoved, oldPos, newPos);
        case Chess::Piece::Knight:
            return Chess::isKnightMoveValid(oldPos, newPos);
        case Chess::Piece::Bishop:
            return Chess::isBishopMoveValid(chessBoard, oldPos, newPos);
        case Chess::Piece::Rook:
            return Chess::isRookMoveValid(chessBoard, oldPos, newPos);
        case Chess::Piece::Queen:
            return Chess::isQueenMoveValid(chessBoard, oldPos, newPos);
        case Chess::Piece::King:
            return Chess::isKingMoveValid(oldPos, newPos);
    }

    return false;
}

void ChessScene::manageDrop(const ChessPiece& movingPiece, const Chess::Position& newPosition)
{
	if (auto currentPiece = chessBoard[newPosition.rank][newPosition.file];
		currentPiece.piece != Chess::Piece::None && currentPiece.color != movingPiece.color)
	{
		auto* takenGraphicsPiece = getGraphicsPiece(Chess::getGraphicsPosition(sceneRect(), newPosition), currentPiece);

		removeItem(takenGraphicsPiece);
	}
}

void ChessScene::switchPlayer()
{
	if (currentPlayer == Chess::Color::Light)
	{
		currentPlayer = Chess::Color::Dark;
	}
	else
	{
		currentPlayer = Chess::Color::Light;
	}
}

ChessPieceGraphicsItem* ChessScene::getGraphicsPiece(const QPointF& position)
{
    const auto items = this->items(position);

    for(auto item : items)
    {
        if(auto * piece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(item); piece != nullptr)
        {
            return piece;
        }
    }

    return nullptr;
}

ChessPieceGraphicsItem* ChessScene::getGraphicsPiece(const QPointF& position, const ChessPiece& chessPiece)
{
	const auto items = this->items(position);

	for (auto item : items)
	{
		if (auto * piece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(item); 
			piece != nullptr && piece->getChessPiece() == chessPiece)
		{
			return piece;
		}
	}

	return nullptr;
}