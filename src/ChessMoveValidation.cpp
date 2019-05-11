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

    if (pieceColor == Chess::Color::Dark)
    {
        if (piecePos.rank < Chess::RANKS - 1 && piecePos.file > 0)
        {
            if (const auto currPiece = chessBoard[piecePos.rank + 1][piecePos.file - 1];
                currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Pawn)
            {
                return true;
            }
        }
        else if (piecePos.rank < Chess::RANKS - 1 && piecePos.file < Chess::FILES - 1)
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

bool Chess::isPawnPromoted(const Chess::Position& newPos)
{
    return newPos.rank == 0 || newPos.rank == Chess::RANKS - 1;
}