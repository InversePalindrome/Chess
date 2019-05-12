/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveValidation.cpp
https://inversepalindrome.com/
*/


#include "Difference.hpp"
#include "ChessMoveValidation.hpp"
#include "ChessMoveGeneration.hpp"


bool Chess::canBeCaptured(const Chess::Board<ChessPiece>& chessBoard,
    Chess::Color pieceColor, const Chess::Position& piecePos)
{
    for (auto currRank = piecePos.rank + 1; currRank < Chess::RANKS; ++currRank)
    {
        const auto currPiece = chessBoard[currRank][piecePos.file];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Rook &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    for (auto currRank = piecePos.rank - 1; currRank >= 0; --currRank)
    {
        const auto currPiece = chessBoard[currRank][piecePos.file];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Rook &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    for (auto currFile = piecePos.file + 1; currFile < Chess::FILES; ++currFile)
    {
        const auto currPiece = chessBoard[piecePos.rank][currFile];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Rook &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    for (auto currFile = piecePos.file - 1; currFile >= 0; --currFile)
    {
        const auto currPiece = chessBoard[piecePos.rank][currFile];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Rook &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    for (auto currPos = Chess::Position{ piecePos.rank + 1, piecePos.file + 1 };
        currPos.rank < Chess::RANKS && currPos.file < Chess::FILES; ++currPos.rank, ++currPos.file)
    {
        const auto currPiece = chessBoard[currPos.rank][currPos.file];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Bishop &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    for (auto currPos = Chess::Position{ piecePos.rank + 1, piecePos.file - 1 };
        currPos.rank < Chess::RANKS && currPos.file >= 0; ++currPos.rank, --currPos.file)
    {
        const auto currPiece = chessBoard[currPos.rank][currPos.file];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Bishop &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    for (auto currPos = Chess::Position{ piecePos.rank - 1, piecePos.file - 1 };
        currPos.rank >= 0 && currPos.file >= 0; --currPos.rank, --currPos.file)
    {
        const auto currPiece = chessBoard[currPos.rank][currPos.file];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Bishop &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    for (auto currPos = Chess::Position{ piecePos.rank - 1, piecePos.file + 1 };
        currPos.rank >= 0 && currPos.file < Chess::FILES; --currPos.rank, ++currPos.file)
    {
        const auto currPiece = chessBoard[currPos.rank][currPos.file];

        if (currPiece.piece == Chess::Piece::None)
        {
            continue;
        }
        else if (currPiece.color == pieceColor || (currPiece.piece != Chess::Piece::Bishop &&
            currPiece.piece != Chess::Piece::Queen))
        {
            break;
        }
        else
        {
            return true;
        }
    }

    Chess::Position knightMoves[] = { { piecePos.rank + 1, piecePos.file - 2 }, { piecePos.rank + 1, piecePos.file + 2 }
    , { piecePos.rank + 2, piecePos.file - 1}, { piecePos.rank + 2, piecePos.file + 1 }, { piecePos.rank - 1, piecePos.file - 2}
    , { piecePos.rank - 1, piecePos.file + 2 }, { piecePos.rank - 2, piecePos.file - 1 }, { piecePos.rank - 2, piecePos.file + 1} };

    for (const auto& currPos : knightMoves)
    {
        if (currPos.rank >= 0 && currPos.rank < Chess::RANKS && currPos.file >= 0 && currPos.file < Chess::FILES)
        {
            if (const auto currPiece = chessBoard[currPos.rank][currPos.file];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Knight)
            {
                return true;
            }
        }
    }

    Chess::Position kingMoves[] = { { piecePos.rank + 1, piecePos.file - 1 }, { piecePos.rank + 1, piecePos.file + 1 },
    { piecePos.rank + 1, piecePos.file }, { piecePos.rank , piecePos.file + 1}, { piecePos.rank, piecePos.file - 1},
    { piecePos.rank - 1, piecePos.file + 1 }, { piecePos.rank - 1, piecePos.file - 1}, { piecePos.rank - 1, piecePos.file } };

    for (const auto& currPos : kingMoves)
    {
        if (currPos.rank >= 0 && currPos.rank < Chess::RANKS && currPos.file >= 0 && currPos.file < Chess::FILES)
        {
            if (const auto currPiece = chessBoard[currPos.rank][currPos.file];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::King)
            {
                return true;
            }
        }
    }

    if (pieceColor == Chess::Color::Light)
    {
        if (piecePos.rank > 0 && piecePos.file > 0)
        {
            if (const auto currPiece = chessBoard[piecePos.rank - 1][piecePos.file - 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
        if (piecePos.rank > 0 && piecePos.file < Chess::FILES - 1)
        {
            if (const auto currPiece = chessBoard[piecePos.rank - 1][piecePos.file + 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
    }
    else
    {
        if (piecePos.rank < Chess::RANKS - 1 && piecePos.file > 0)
        {
            if (const auto currPiece = chessBoard[piecePos.rank + 1][piecePos.file - 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
        if (piecePos.rank < Chess::RANKS - 1 && piecePos.file < Chess::FILES - 1)
        {
            if (const auto currPiece = chessBoard[piecePos.rank + 1][piecePos.file + 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
    }

    return false;
}

bool Chess::hasValidMoves(const Chess::Board<ChessPiece>& chessBoard,
    Chess::Color kingColor, const Chess::Position& kingPos)
{
    for (auto rank = 0; rank < Chess::RANKS; ++rank)
    {
        for (auto file = 0; file < Chess::FILES; ++file)
        {
            if (const auto chessPiece = chessBoard[rank][file];
                chessPiece.piece != Chess::Piece::None && chessPiece.color == kingColor)
            {
                Chess::Position pos{ rank, file };
                const auto movingPiece = chessBoard[pos.rank][pos.file];
                std::vector<Chess::Position> validMoves = Chess::getPieceMoves(chessBoard, movingPiece, pos);

                for (const auto& newPos : validMoves)
                {
                    auto testChessBoard = chessBoard;

                    testChessBoard[pos.rank][pos.file] = ChessPiece{};
                    testChessBoard[newPos.rank][newPos.file] = movingPiece;

                    auto currKingPos = kingPos;
                    if (movingPiece.piece == Chess::Piece::King)
                    {
                        currKingPos = newPos;
                    }

                    if (!canBeCaptured(testChessBoard, kingColor, currKingPos))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

Chess::CastlingMode Chess::isCastling(const Chess::Board<ChessPiece>& chessBoard, const ChessPiece& movingPiece,
    const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (movingPiece.piece == Chess::Piece::King && !movingPiece.hasMoved)
    {
        if (movingPiece.color == Chess::Color::Light)
        {
            if (const auto possibleRook = chessBoard[Chess::RANKS - 1][Chess::FILES - 1];
                oldPos.file == newPos.file - 2 &&
                possibleRook.piece == Chess::Piece::Rook && possibleRook.color == movingPiece.color &&
                !possibleRook.hasMoved && chessBoard[Chess::RANKS - 1][Chess::FILES - 2].piece == Chess::Piece::None
                && chessBoard[Chess::RANKS - 1][Chess::FILES - 3].piece == Chess::Piece::None
                && !canBeCaptured(chessBoard, movingPiece.color, { Chess::RANKS - 1, Chess::FILES - 2 })
                && !canBeCaptured(chessBoard, movingPiece.color, { Chess::RANKS - 1, Chess::FILES - 3 }))
            {
                return Chess::CastlingMode::Short;
            }
            else if (const auto possibleRook = chessBoard[Chess::RANKS - 1][0];
                newPos.file == oldPos.file - 2 &&
                possibleRook.piece == Chess::Piece::Rook && possibleRook.color == movingPiece.color &&
                !possibleRook.hasMoved && chessBoard[Chess::RANKS - 1][1].piece == Chess::Piece::None
                && chessBoard[Chess::RANKS - 1][2].piece == Chess::Piece::None &&
                chessBoard[Chess::RANKS - 1][3].piece == Chess::Piece::None
                && !canBeCaptured(chessBoard, movingPiece.color, { Chess::RANKS - 1, 1 })
                && !canBeCaptured(chessBoard, movingPiece.color, { Chess::RANKS - 1, 2 })
                && !canBeCaptured(chessBoard, movingPiece.color, { Chess::RANKS - 1, 3 }))
            {
                return Chess::CastlingMode::Long;
            }
        }
        else
        {
            if (const auto possibleRook = chessBoard[0][Chess::FILES - 1];
                oldPos.file == newPos.file - 2 &&
                possibleRook.piece == Chess::Piece::Rook && possibleRook.color == movingPiece.color &&
                !possibleRook.hasMoved && chessBoard[0][Chess::FILES - 2].piece == Chess::Piece::None
                && chessBoard[0][Chess::FILES - 3].piece == Chess::Piece::None
                && !canBeCaptured(chessBoard, movingPiece.color, { 0, Chess::FILES - 2 })
                && !canBeCaptured(chessBoard, movingPiece.color, { 0, Chess::FILES - 3 }))
            {
                return Chess::CastlingMode::Short;
            }
            else if (const auto possibleRook = chessBoard[0][0];
                newPos.file == oldPos.file - 2 &&
                possibleRook.piece == Chess::Piece::Rook && possibleRook.color == movingPiece.color &&
                !possibleRook.hasMoved && chessBoard[0][1].piece == Chess::Piece::None
                && chessBoard[0][2].piece == Chess::Piece::None && chessBoard[0][3].piece == Chess::Piece::None
                && !canBeCaptured(chessBoard, movingPiece.color, { 0, 1 })
                && !canBeCaptured(chessBoard, movingPiece.color, { 0, 2 })
                && !canBeCaptured(chessBoard, movingPiece.color, { 0, 3 }))
            {
                return Chess::CastlingMode::Long;
            }
        }
    }

    return Chess::CastlingMode::None;
}

bool Chess::isEnPassant(const Chess::Board<ChessPiece>& chessBoard, const
    std::vector<Chess::Move>& moveHistory, const ChessPiece& movingPiece,
    const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (!std::empty(moveHistory) && movingPiece.piece == Chess::Piece::Pawn)
    {
        const auto& lastMove = moveHistory.back();

        if (lastMove.movingPiece.piece == Chess::Piece::Pawn)
        {
            if (movingPiece.color == Chess::Color::Light)
            {
                return lastMove.newPos.rank - lastMove.oldPos.rank == 2
                    && oldPos.rank - newPos.rank == 1 && newPos.file == lastMove.newPos.file;
            }
            else
            {
                return lastMove.oldPos.rank - lastMove.newPos.rank == 2
                    && newPos.rank - oldPos.rank == 1 && newPos.file == lastMove.newPos.file;
            }
        }
    }

    return false;
}

bool Chess::isPawnPromoted(const ChessPiece& movingPiece, const Chess::Position& newPos)
{
    if (movingPiece.piece == Chess::Piece::Pawn)
    {
        if (movingPiece.color == Chess::Color::Light)
        {
            return newPos.rank == 0;
        }
        else
        {
            return newPos.rank == Chess::RANKS - 1;
        }
    }

    return false;
}