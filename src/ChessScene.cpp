/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.cpp
https://inversepalindrome.com/
*/


#include "ChessScene.hpp"
#include "ChessUtility.hpp"
#include "ChessResources.hpp"
#include "ChessMoveValidation.hpp"
#include "ChessBoardGraphicsItem.hpp"

#include <QGraphicsSceneMouseEvent>


ChessScene::ChessScene(QObject* parent) :
    QGraphicsScene(parent),
    chessBoard(Chess::getInitialBoard()),
    lightKingPosition{ Chess::RANKS - 1, 4 },
    darkKingPosition{ 0, 4 },
    currentPlayer(Chess::Color::Light)
{
    auto* graphicChessBoard = new ChessBoardGraphicsItem();
    addItem(graphicChessBoard);
    
    setSceneRect(itemsBoundingRect());

    for (auto rank = 0; rank < Chess::RANKS; ++rank)
    {
        for (auto file = 0; file < Chess::FILES; ++file)
        {
            if (Chess::resources.count(chessBoard[rank][file]))
            {
                auto* graphicsPiece = new ChessPieceGraphicsItem(chessBoard[rank][file], QPixmap(":/Resources/ChessPieces/"
                    + QString::fromStdString(Chess::resources.at(chessBoard[rank][file]))).scaledToWidth(
                        Chess::PIECE_SIZE), graphicChessBoard);

                graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), Chess::Position{ rank, file }));

                graphicsBoard[rank][file] = graphicsPiece;
            }
        }
    }
}

void ChessScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (auto* graphicsPiece = getGraphicsPiece(event->scenePos()); graphicsPiece != nullptr &&
	    graphicsPiece->getChessPiece().color == currentPlayer && event->button() == Qt::LeftButton)
    {
	    sourcePosition = event->scenePos();

	    graphicsPiece->setFlag(QGraphicsItem::ItemIsMovable, true);
    }

    QGraphicsScene::mousePressEvent(event);
}

void ChessScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(auto* graphicsPiece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(mouseGrabberItem());
	  graphicsPiece != nullptr)
    {
        const auto oldPos = Chess::getChessPositionAt(sourcePosition);
        const auto newPos = Chess::getChessPositionAt(event->scenePos());
	    auto movingPiece = chessBoard[oldPos.rank][oldPos.file];
		
        if(canMove(movingPiece, oldPos, newPos) && !isKingInCheck(movingPiece, oldPos, newPos))
        {
		    movingPiece.hasMoved = true;

		    manageDrop(movingPiece, newPos);
		    managePromotion(movingPiece, graphicsPiece, newPos);
		    manageHistory(chessBoard[newPos.rank][newPos.file], movingPiece, oldPos, newPos);
			
		    chessBoard[oldPos.rank][oldPos.file] = ChessPiece{};
		    chessBoard[newPos.rank][newPos.file] = movingPiece;

		    graphicsBoard[oldPos.rank][oldPos.file] = nullptr;
		    graphicsBoard[newPos.rank][newPos.file] = graphicsPiece;

		    graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), newPos));

		    updateKingPosition(movingPiece, newPos);
            updateEndGame();

            switchPlayer();
        }
        else
        {
		    graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), oldPos));
        }

	    graphicsPiece->setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

bool ChessScene::canMove(const ChessPiece& movingPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const
{
    if ((movingPiece.piece == Chess::Piece::King && Chess::isCastlingMoveValid(chessBoard, oldPos, newPos)) ||
	   (movingPiece.piece == Chess::Piece::Pawn && Chess::isEnPassantValid(chessBoard,
	   chessHistory, movingPiece.color, oldPos, newPos)))
    {
	    return true;
    }
    if (!Chess::isPieceMoveValid(chessBoard, movingPiece.color, newPos))
    {
	    return false;
    }

    switch(movingPiece.piece)
    {
        case Chess::Piece::Pawn:
            return Chess::isPawnMoveValid(chessBoard, movingPiece.color, movingPiece.hasMoved, oldPos, newPos);
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

bool ChessScene::isKingInCheck(Chess::Color kingColor) const
{
    if (kingColor == Chess::Color::Light)
    {
        return Chess::canBeCaptured(chessBoard, kingColor, lightKingPosition);
    }
    else
    {
        return Chess::canBeCaptured(chessBoard, kingColor, darkKingPosition);
    }
}

bool ChessScene::isKingInCheck(const ChessPiece& movingPiece, const Chess::Position& oldPos, const Chess::Position& newPos) const
{
    auto testChessBoard = chessBoard;
    testChessBoard[oldPos.rank][oldPos.file] = ChessPiece{};
    testChessBoard[newPos.rank][newPos.file] = movingPiece;

    Chess::Position kingPosition;

    if (movingPiece.piece == Chess::Piece::King)
    {
	    kingPosition = newPos;
    }
    else if (currentPlayer == Chess::Color::Light)
    {
	    kingPosition = lightKingPosition;
    }
    else
    {
	    kingPosition = darkKingPosition;
    }
	
    return Chess::canBeCaptured(testChessBoard, movingPiece.color, kingPosition);
}

void ChessScene::manageHistory(const ChessPiece& droppedPiece, const ChessPiece& promotedPiece,
	const Chess::Position& oldPos, const Chess::Position& newPos)
{
	std::vector<Chess::Move> moves;
	moves.push_back({ oldPos, newPos });

	chessHistory.push_back({ moves, droppedPiece, promotedPiece });
}

void ChessScene::manageDrop(const ChessPiece& movingPiece, const Chess::Position& newPosition)
{
    if (const auto& currentPiece = chessBoard[newPosition.rank][newPosition.file];
	    currentPiece.piece != Chess::Piece::None && currentPiece.color != movingPiece.color)
    {
	    if (auto* takenGraphicsPiece = graphicsBoard[newPosition.rank][newPosition.file];
		    takenGraphicsPiece)
	    {
		    removeItem(takenGraphicsPiece);
		    delete takenGraphicsPiece;
	    }
    }
}

void ChessScene::managePromotion(ChessPiece& movingPiece, ChessPieceGraphicsItem* graphicsPiece, 
	const Chess::Position& newPos)
{
	if (movingPiece.piece == Chess::Piece::Pawn && Chess::isPawnPromoted(newPos))
	{
		emit openPromotionDialog(movingPiece);

		graphicsPiece->setPixmap(QPixmap(":/Resources/ChessPieces/"+ QString::fromStdString
		(Chess::resources.at(movingPiece))).scaledToWidth(Chess::PIECE_SIZE));
	}
}

void ChessScene::updateKingPosition(const ChessPiece& movingPiece, const Chess::Position newPos)
{
	if (movingPiece.piece == Chess::Piece::King)
	{
		if (movingPiece.color == Chess::Color::Light)
		{
			lightKingPosition = newPos;
		}
		else
		{
			darkKingPosition = newPos;
		}
	}
}

void ChessScene::updateEndGame() const
{
    if (currentPlayer == Chess::Color::Light)
    {
        if (!Chess::hasValidMoves(chessBoard, Chess::Color::Dark, darkKingPosition))
        {
            if (isKingInCheck(Chess::Color::Dark))
            {
                emit gameEnded(Chess::EndResult::LightWon);
            }
            else
            {
                emit gameEnded(Chess::EndResult::Stalemate);
            }
        }
    }
    else
    {
       if (!Chess::hasValidMoves(chessBoard, Chess::Color::Light, lightKingPosition))
       {
           if (isKingInCheck(Chess::Color::Light))
           {
               emit gameEnded(Chess::EndResult::DarkWon);
           }
           else
           {
               emit gameEnded(Chess::EndResult::Stalemate);
           }
       }
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