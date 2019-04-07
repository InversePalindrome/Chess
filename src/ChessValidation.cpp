/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessValidation.cpp
https://inversepalindrome.com/
*/


#include "ChessValidation.hpp"


bool Chess::isPawnMoveValid(const ChessBoard& chessBoard, Chess::Color pawnColor, bool hasMoved,
                            const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if((pawnColor == Chess::Color::Light && newPos.rank != oldPos.rank - 1) ||
       (pawnColor == Chess::Color::Dark && newPos.rank != oldPos.rank + 1))
    {
        return false;
    }

    if((newPos.file == oldPos.file && chessBoard[newPos.rank][newPos.file].piece == Chess::Piece::None) ||
       ((newPos.file == oldPos.file + 1 || newPos.file == oldPos.file - 1) &&
       chessBoard[newPos.rank][newPos.file].piece != Chess::Piece::None))
    {
        return true;
    }

    return false;
}

bool Chess::isKnightMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if(newPos.rank == oldPos.rank + 2 || newPos.rank == oldPos.rank - 2)
    {
        if(newPos.file == oldPos.file + 1 || newPos.file == oldPos.file - 1)
        {
            return true;
        }
    }
    else if(newPos.file == oldPos.file + 2 || newPos.file == oldPos.file - 2)
    {
        if(newPos.rank == oldPos.rank + 1 || newPos.rank == oldPos.rank - 1)
        {
            return true;
        }
    }

    return false;
}

bool Chess::isBishopMoveValid(const ChessBoard& chessBoard, const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if(oldPos.rank < newPos.rank && oldPos.file < newPos.file)
    {
        for(auto currPos = Chess::Position{ oldPos.rank + 1, oldPos.file + 1};
            currPos.rank < Chess::RANKS || currPos.file < Chess::FILES; ++currPos.rank, ++currPos.file)
        {
            if(newPos == currPos)
            {
                return true;
            }
            else if(chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    if(oldPos.rank < newPos.rank && oldPos.file > newPos.file)
    {
        for(auto currPos = Chess::Position{ oldPos.rank + 1, oldPos.file - 1};
            currPos.rank < Chess::RANKS || currPos.file + 1 > 0; ++currPos.rank, --currPos.file)
        {
            if(newPos == currPos)
            {
                return true;
            }
            else if(chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    if(oldPos.rank > newPos.rank && oldPos.file > newPos.file)
    {
        for(auto currPos = Chess::Position{ oldPos.rank - 1, oldPos.file - 1};
            currPos.rank + 1 > 0 || currPos.file + 1 > 0; --currPos.rank, --currPos.file)
        {
            if(newPos == currPos)
            {
                return true;
            }
            else if(chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    if(oldPos.rank > newPos.rank && oldPos.file < newPos.file)
    {
        for(auto currPos = Chess::Position{ oldPos.rank - 1, oldPos.file + 1};
            currPos.rank + 1 > 0 || currPos.file < Chess::FILES; --currPos.rank, ++currPos.file)
        {
            if(newPos == currPos)
            {
                return true;
            }
            else if(chessBoard[currPos.rank][currPos.file].piece != Chess::Piece::None)
            {
                return false;
            }
        }
    }

    return false;
}

bool Chess::isRookMoveValid(const ChessBoard& chessBoard, const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if(oldPos.rank == newPos.rank)
    {
        if(oldPos.file < newPos.file)
        {
            for(std::size_t currFile = oldPos.file + 1; currFile < newPos.file; ++currFile)
            {
                if(chessBoard[oldPos.rank][currFile].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
        else if(oldPos.file > newPos.file)
        {
            for(std::size_t currFile = oldPos.file - 1; currFile > newPos.file; --currFile)
            {
                if(chessBoard[oldPos.rank][currFile].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
    }
    else if(oldPos.file == newPos.file)
    {
        if(oldPos.rank < newPos.rank)
        {
            for(std::size_t currRank = oldPos.rank + 1; currRank < newPos.rank; ++currRank)
            {
                if(chessBoard[currRank][oldPos.file].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
        else if(oldPos.rank > newPos.rank)
        {
            for(std::size_t currRank = oldPos.rank - 1; currRank > newPos.rank; --currRank)
            {
                if(chessBoard[currRank][oldPos.file].piece != Chess::Piece::None)
                {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

bool Chess::isQueenMoveValid(const ChessBoard& chessBoard, const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if(oldPos.rank == newPos.rank || oldPos.file == newPos.file)
    {
        return isRookMoveValid(chessBoard, oldPos, newPos);
    }

    return isBishopMoveValid(chessBoard, oldPos, newPos);
}

bool Chess::isKingMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos)
{
    return oldPos.rank == newPos.rank + 1 || oldPos.rank == newPos.rank - 1 || oldPos.file == newPos.file + 1
       || oldPos.file == newPos.file - 1;
}
