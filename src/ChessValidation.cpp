/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessValidation.cpp
https://inversepalindrome.com/
*/


#include "Difference.hpp"
#include "ChessValidation.hpp"


bool Chess::isPawnMoveValid(const ChessBoard& chessBoard, Chess::Color pawnColor, bool hasMoved,
                            const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if((pawnColor == Chess::Color::Light && newPos.rank > oldPos.rank) ||
       (pawnColor == Chess::Color::Dark && newPos.rank < oldPos.rank))
    {
        return false;
    }

    if((newPos.file == oldPos.file && (Utility::diff(newPos.rank, oldPos.rank) == 1 || 
		(!hasMoved && Utility::diff(newPos.rank, oldPos.rank) == 2)) && 
		chessBoard[newPos.rank][newPos.file].piece == Chess::Piece::None) ||
       (Utility::diff(newPos.file, oldPos.file) == 1 && Utility::diff(newPos.rank, oldPos.rank) == 1 && 
       chessBoard[newPos.rank][newPos.file].piece != Chess::Piece::None))
    {
        return true;
    }

    return false;
}

bool Chess::isKnightMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos)
{
    if(Utility::diff(newPos.rank, oldPos.rank) == 2)
    {
        if(Utility::diff(newPos.file, oldPos.file) == 1)
        {
            return true;
        }
    }
    else if(Utility::diff(newPos.file, oldPos.file) == 2)
    {
        if(Utility::diff(newPos.rank, oldPos.rank) == 1)
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
	auto rankDiff = Utility::diff(oldPos.rank, newPos.rank);
	auto fileDiff = Utility::diff(oldPos.file, newPos.file);

    return (rankDiff == 1 && fileDiff == 1) || (rankDiff == 0 && fileDiff == 1)
		|| (rankDiff == 1 && fileDiff == 0);
}
