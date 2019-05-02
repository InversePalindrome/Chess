/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveValidation.cpp
https://inversepalindrome.com/
*/


#include "Difference.hpp"
#include "ChessMoveValidation.hpp"
#include "ChessMoveGeneration.hpp"


bool Chess::isEnPassantValid(const Chess::Board<ChessPiece>& chessBoard, const std::vector<Chess::Transition>& history,
    Chess::Color pawnColor, const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (pawnColor == Chess::Color::Light)
    {
        if (newPos.rank == oldPos.rank - 1)
        {
            //return true;
        }
    }
    else
    {
        if (newPos.rank == oldPos.rank + 1)
        {
            //return true;
        }
    }

    return false;
}

bool Chess::isCastlingMoveValid(const Chess::Board<ChessPiece>& chessBoard,
    const Chess::Position& oldPos, const Chess::Position& newPos)
{
    return false;
}

bool Chess::isPieceMoveValid(const Chess::Board<ChessPiece>& chessBoard,
    Chess::Color pieceColor, const Chess::Position& newPos)
{
    const auto targetPiece = chessBoard[newPos.rank][newPos.file];

    return targetPiece.piece == Chess::Piece::None || targetPiece.color != pieceColor;
}

bool Chess::isPawnMoveValid(const Chess::Board<ChessPiece>& chessBoard, Chess::Color pawnColor, bool hasMoved,
    const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (pawnColor == Chess::Color::Light)
    {
        if (const auto targetPiece = chessBoard[newPos.rank][newPos.file];
            (newPos.file == oldPos.file && ((newPos.rank == oldPos.rank - 1 && targetPiece.piece == Chess::Piece::None)
                || (!hasMoved && newPos.rank == oldPos.rank - 2 && chessBoard[newPos.rank + 1][newPos.file].piece == Chess::Piece::None
                    && targetPiece.piece == Chess::Piece::None))) || (newPos.rank == oldPos.rank - 1
                        && (newPos.file == oldPos.file + 1 || newPos.file == oldPos.file - 1)
                        && targetPiece.piece != Chess::Piece::None && targetPiece.color != pawnColor))
        {
            return true;
        }
    }
    else
    {
        if (const auto targetPiece = chessBoard[newPos.rank][newPos.file];
            (newPos.file == oldPos.file && ((newPos.rank == oldPos.rank + 1 && targetPiece.piece == Chess::Piece::None)
                || (!hasMoved && newPos.rank == oldPos.rank + 2 && chessBoard[newPos.rank - 1][newPos.file].piece == Chess::Piece::None
                    && targetPiece.piece == Chess::Piece::None))) || (newPos.rank == oldPos.rank + 1
                        && (newPos.file == oldPos.file + 1 || newPos.file == oldPos.file - 1)
                        && targetPiece.piece != Chess::Piece::None && targetPiece.color != pawnColor))
        {
            return true;
        }
    }

    return false;
}

bool Chess::isKnightMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (Utility::diff(newPos.rank, oldPos.rank) == 2)
    {
        if (Utility::diff(newPos.file, oldPos.file) == 1)
        {
            return true;
        }
    }
    else if (Utility::diff(newPos.file, oldPos.file) == 2)
    {
        if (Utility::diff(newPos.rank, oldPos.rank) == 1)
        {
            return true;
        }
    }

    return false;
}

bool Chess::isBishopMoveValid(const Chess::Board<ChessPiece>& chessBoard,
    const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (oldPos.rank < newPos.rank && oldPos.file < newPos.file)
    {
        for (auto currPos = Chess::Position{ oldPos.rank + 1, oldPos.file + 1 };
            currPos.rank < Chess::RANKS && currPos.file < Chess::FILES; ++currPos.rank, ++currPos.file)
        {
            if (newPos == currPos)
            {
                return true;
            }
            else if (chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    if (oldPos.rank < newPos.rank && oldPos.file > newPos.file)
    {
        for (auto currPos = Chess::Position{ oldPos.rank + 1, oldPos.file - 1 };
            currPos.rank < Chess::RANKS && currPos.file >= 0; ++currPos.rank, --currPos.file)
        {
            if (newPos == currPos)
            {
                return true;
            }
            else if (chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    if (oldPos.rank > newPos.rank && oldPos.file > newPos.file)
    {
        for (auto currPos = Chess::Position{ oldPos.rank - 1, oldPos.file - 1 };
            currPos.rank >= 0 && currPos.file >= 0; --currPos.rank, --currPos.file)
        {
            if (newPos == currPos)
            {
                return true;
            }
            else if (chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    if (oldPos.rank > newPos.rank && oldPos.file < newPos.file)
    {
        for (auto currPos = Chess::Position{ oldPos.rank - 1, oldPos.file + 1 };
            currPos.rank >= 0 && currPos.file < Chess::FILES; --currPos.rank, ++currPos.file)
        {
            if (newPos == currPos)
            {
                return true;
            }
            else if (chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    return false;
}

bool Chess::isRookMoveValid(const Chess::Board<ChessPiece>& chessBoard,
    const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (oldPos.rank == newPos.rank)
    {
        if (oldPos.file < newPos.file)
        {
            for (auto currFile = oldPos.file + 1; currFile < newPos.file; ++currFile)
            {
                if (chessBoard[oldPos.rank][currFile].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
        else if (oldPos.file > newPos.file)
        {
            for (auto currFile = oldPos.file - 1; currFile > newPos.file; --currFile)
            {
                if (chessBoard[oldPos.rank][currFile].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
    }
    else if (oldPos.file == newPos.file)
    {
        if (oldPos.rank < newPos.rank)
        {
            for (auto currRank = oldPos.rank + 1; currRank < newPos.rank; ++currRank)
            {
                if (chessBoard[currRank][oldPos.file].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
        else if (oldPos.rank > newPos.rank)
        {
            for (auto currRank = oldPos.rank - 1; currRank > newPos.rank; --currRank)
            {
                if (chessBoard[currRank][oldPos.file].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

bool Chess::isQueenMoveValid(const Chess::Board<ChessPiece>& chessBoard,
    const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if (oldPos.rank == newPos.rank || oldPos.file == newPos.file)
    {
        return isRookMoveValid(chessBoard, oldPos, newPos);
    }

    return isBishopMoveValid(chessBoard, oldPos, newPos);
}

bool Chess::isKingMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos)
{
    const auto rankDiff = Utility::diff(oldPos.rank, newPos.rank);
    const auto fileDiff = Utility::diff(oldPos.file, newPos.file);

    return (rankDiff == 1 && fileDiff == 1) || (rankDiff == 0 && fileDiff == 1)
        || (rankDiff == 1 && fileDiff == 0);
}

bool Chess::canBeCaptured(const Chess::Board<ChessPiece> & chessBoard,
    Chess::Color pieceColor, const Chess::Position & piecePos)
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

    if (pieceColor == Chess::Color::Dark)
    {
        if (piecePos.rank <= Chess::RANKS - 1 && piecePos.file > 0)
        {
            if (const auto currPiece = chessBoard[piecePos.rank + 1][piecePos.file - 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
        else if (piecePos.rank <= Chess::RANKS - 1 && piecePos.file < Chess::FILES - 1)
        {
            if (const auto currPiece = chessBoard[piecePos.rank + 1][piecePos.file + 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
    }
    else
    {
        if (piecePos.rank > 0 && piecePos.file > 0)
        {
            if (const auto currPiece = chessBoard[piecePos.rank - 1][piecePos.file - 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
        else if (piecePos.rank > 0 && piecePos.file < Chess::FILES - 1)
        {
            if (const auto currPiece = chessBoard[piecePos.rank - 1][piecePos.file + 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
    }

    return false;
}

bool Chess::hasValidMoves(const Chess::Board<ChessPiece> & chessBoard,
    Chess::Color kingColor, const Chess::Position & kingPos)
{
    for (auto rank = 0; rank < Chess::RANKS; ++rank)
    {
        for (auto file = 0; file < Chess::FILES; ++file)
        {
            if (const auto chessPiece = chessBoard[rank][file];
                chessPiece.piece != Chess::Piece::None && chessPiece.color == kingColor)
            {
                Chess::Position pos{ rank, file };
                std::vector<Chess::Position> validPositions;

                switch (chessPiece.piece)
                {
                case Piece::Pawn:
                    validPositions = Chess::getPawnMoves(chessBoard, kingColor, pos, chessPiece.hasMoved);
                    break;
                case Piece::Knight:
                    validPositions = Chess::getKnightMoves(chessBoard, kingColor, pos);
                    break;
                case Piece::Bishop:
                    validPositions = Chess::getBishopMoves(chessBoard, kingColor, pos);
                    break;
                case Piece::Queen:
                    validPositions = Chess::getQueenMoves(chessBoard, kingColor, pos);
                    break;
                case Piece::King:
                    validPositions = Chess::getKingMoves(chessBoard, kingColor, pos);
                    break;
                }

                for (const auto& pos : validPositions)
                {
                    if (!canBeCaptured(chessBoard, kingColor, pos))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Chess::isPawnPromoted(const Chess::Position & newPos)
{
    return newPos.rank == 0 || newPos.rank == Chess::RANKS - 1;
}