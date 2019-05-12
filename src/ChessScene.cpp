/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessScene.cpp
https://inversepalindrome.com/
*/


#include "ChessScene.hpp"
#include "ChessUtility.hpp"
#include "ChessResources.hpp"
#include "ChessMoveValidation.hpp"
#include "ChessMoveGeneration.hpp"
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

void ChessScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (auto * graphicsPiece = getGraphicsPiece(event->scenePos()); graphicsPiece != nullptr &&
        graphicsPiece->getChessPiece().color == currentPlayer && event->button() == Qt::LeftButton)
    {
        sourcePosition = event->scenePos();

        graphicsPiece->setFlag(QGraphicsItem::ItemIsMovable, true);
    }

    QGraphicsScene::mousePressEvent(event);
}

void ChessScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    if (auto * graphicsPiece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(mouseGrabberItem());
        graphicsPiece != nullptr)
    {
        const auto oldPos = Chess::getChessPositionAt(sourcePosition);
        const auto newPos = Chess::getChessPositionAt(event->scenePos());
        auto movingPiece = chessBoard[oldPos.rank][oldPos.file];

        if (!leavesKingInCheck(movingPiece, oldPos, newPos))
        {
            const auto isCastling = Chess::isCastling(chessBoard, movingPiece, oldPos, newPos);

            if (isCastling == Chess::CastlingMode::Short)
            {
                handleShortCastling(movingPiece, graphicsPiece, oldPos, newPos);
            }
            else if (isCastling == Chess::CastlingMode::Long)
            {
                handleLongCastling(movingPiece, graphicsPiece, oldPos, newPos);
            }
            else if (Chess::isEnPassant(chessBoard, moveHistory, movingPiece, oldPos, newPos))
            {
                handleEnPassant(movingPiece, graphicsPiece, oldPos, newPos);
            }
            else if (canMove(movingPiece, oldPos, newPos))
            {
                handleRegularMove(movingPiece, graphicsPiece, oldPos, newPos);
            }
            else
            {
                graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), oldPos));
            }
        }
        else
        {
            graphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), oldPos));
        }

        graphicsPiece->setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

bool ChessScene::canMove(const ChessPiece & movingPiece, const Chess::Position & oldPos, const Chess::Position & newPos) const
{
    const auto validMoves = Chess::getPieceMoves(chessBoard, movingPiece, oldPos);

    return std::find(std::begin(validMoves), std::end(validMoves), newPos) != std::end(validMoves);
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

bool ChessScene::leavesKingInCheck(const ChessPiece & movingPiece, const Chess::Position & oldPos, const Chess::Position & newPos) const
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

void ChessScene::addMove(const ChessPiece & movingPiece,
    const Chess::Position & oldPos, const Chess::Position & newPos)
{
    moveHistory.push_back({ movingPiece, oldPos, newPos });
}

void ChessScene::handleShortCastling(ChessPiece & movingPiece, ChessPieceGraphicsItem * movingGraphicsPiece,
    const Chess::Position & oldPos, const Chess::Position & newPos)
{
    auto movingRook = chessBoard[oldPos.rank][Chess::FILES - 1];

    movePiece(movingPiece, movingGraphicsPiece, oldPos, newPos);
    movePiece(movingRook, graphicsBoard[oldPos.rank][Chess::FILES - 1],
        { oldPos.rank, Chess::FILES - 1 }, { oldPos.rank, Chess::FILES - 3 });

    addMove(movingPiece, oldPos, newPos);
    addMove(movingRook, { oldPos.rank, Chess::FILES - 1 }, { oldPos.rank, Chess::FILES - 3 });

    updateEndGame();

    switchPlayer();
}

void ChessScene::handleLongCastling(ChessPiece & movingPiece, ChessPieceGraphicsItem * movingGraphicsPiece,
    const Chess::Position & oldPos, const Chess::Position & newPos)
{
    auto movingRook = chessBoard[oldPos.rank][0];

    movePiece(movingPiece, movingGraphicsPiece, oldPos, newPos);
    movePiece(movingRook, graphicsBoard[oldPos.rank][0],
        { oldPos.rank, 0 }, { oldPos.rank, 3 });

    addMove(movingPiece, oldPos, newPos);
    addMove(movingRook, { oldPos.rank, Chess::FILES - 1 }, { oldPos.rank, Chess::FILES - 3 });

    updateEndGame();

    switchPlayer();
}

void ChessScene::handleEnPassant(ChessPiece & movingPiece, ChessPieceGraphicsItem * movingGraphicsPiece,
    const Chess::Position & oldPos, const Chess::Position & newPos)
{
    movePiece(movingPiece, movingGraphicsPiece, oldPos, newPos);

    addMove(movingPiece, oldPos, newPos);

    removeGraphicsPiece({ moveHistory.back().newPos.rank, moveHistory.back().newPos.file });

    updateEndGame();

    switchPlayer();
}

void ChessScene::handleRegularMove(ChessPiece & movingPiece, ChessPieceGraphicsItem * movingGraphicsPiece,
    const Chess::Position & oldPos, const Chess::Position & newPos)
{
    manageDrop(movingPiece, newPos);
    managePromotion(movingPiece, movingGraphicsPiece, newPos);

    addMove(movingPiece, oldPos, newPos);

    movePiece(movingPiece, movingGraphicsPiece, oldPos, newPos);

    updateKingPosition(movingPiece, newPos);
    updateEndGame();

    switchPlayer();
}

void ChessScene::manageDrop(const ChessPiece & movingPiece, const Chess::Position & newPosition)
{
    if (const auto& currentPiece = chessBoard[newPosition.rank][newPosition.file];
        currentPiece.piece != Chess::Piece::None && currentPiece.color != movingPiece.color)
    {
        removeGraphicsPiece(newPosition);
    }
}

void ChessScene::managePromotion(ChessPiece & movingPiece, ChessPieceGraphicsItem * graphicsPiece,
    const Chess::Position & newPos)
{
    if (Chess::isPawnPromoted(movingPiece, newPos))
    {
        emit openPromotionDialog(movingPiece);

        graphicsPiece->setPixmap(QPixmap(":/Resources/ChessPieces/" + QString::fromStdString
        (Chess::resources.at(movingPiece))).scaledToWidth(Chess::PIECE_SIZE));
    }
}

void ChessScene::updateKingPosition(const ChessPiece & movingPiece, const Chess::Position newPos)
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

void ChessScene::movePiece(ChessPiece & movingPiece, ChessPieceGraphicsItem * movingGraphicsPiece,
    const Chess::Position & oldPos, const Chess::Position & newPos)
{
    movingPiece.hasMoved = true;

    chessBoard[oldPos.rank][oldPos.file] = ChessPiece{};
    chessBoard[newPos.rank][newPos.file] = movingPiece;

    graphicsBoard[oldPos.rank][oldPos.file] = nullptr;
    graphicsBoard[newPos.rank][newPos.file] = movingGraphicsPiece;

    movingGraphicsPiece->setPos(Chess::getGraphicsPosition(sceneRect(), newPos));
}

ChessPieceGraphicsItem* ChessScene::getGraphicsPiece(const QPointF & position)
{
    const auto items = this->items(position);

    for (auto item : items)
    {
        if (auto * piece = qgraphicsitem_cast<ChessPieceGraphicsItem*>(item); piece != nullptr)
        {
            return piece;
        }
    }

    return nullptr;
}

void ChessScene::removeGraphicsPiece(const Chess::Position & pos)
{
    if (auto* graphicsPieceToRemove = graphicsBoard[pos.rank][pos.file];
        graphicsPieceToRemove)
    {
        removeItem(graphicsPieceToRemove);
        delete graphicsPieceToRemove;
    }
}