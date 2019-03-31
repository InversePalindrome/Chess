/*
Copyright (c) 2019 Inverse Palindrome
Chess - MoveValidator.cpp
https://inversepalindrome.com/
*/


#include "MoveValidator.hpp"


MoveValidator::MoveValidator(const ChessBoard& chessBoard) :
    chessBoard(chessBoard)
{
}

bool MoveValidator::isPawnMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const
{
    return true;
}

bool MoveValidator::isKnightMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const
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

bool MoveValidator::isBishopMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const
{
    if(oldPos.rank < newPos.rank && oldPos.file < newPos.file)
    {

    }

    return false;
}

bool MoveValidator::isRookMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const
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

bool MoveValidator::isQueenMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const
{
    if(oldPos.rank == newPos.rank || oldPos.file == newPos.file)
    {
        return isRookMoveValid(oldPos, newPos);
    }

    return isBishopMoveValid(oldPos, newPos);
}

bool MoveValidator::isKingMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos) const
{
    return oldPos.rank == newPos.rank + 1 || oldPos.rank == newPos.rank - 1 || oldPos.file == newPos.file + 1
       || oldPos.file == newPos.file - 1;
}
