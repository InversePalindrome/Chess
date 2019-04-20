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
            currPos.rank < Chess::RANKS && currPos.file < Chess::FILES; ++currPos.rank, ++currPos.file)
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
            currPos.rank < Chess::RANKS && currPos.file + 1 > 0; ++currPos.rank, --currPos.file)
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
            currPos.rank + 1 > 0 && currPos.file + 1 > 0; --currPos.rank, --currPos.file)
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
            currPos.rank + 1 > 0 && currPos.file < Chess::FILES; --currPos.rank, ++currPos.file)
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

bool Chess::canBeCaptured(const ChessBoard& chessBoard, Chess::Color pieceColor, const Chess::Position& piecePos)
{
	for(auto currRank = piecePos.rank + 1; currRank < Chess::RANKS; ++currRank)
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

	for(auto currRank = piecePos.rank - 1; currRank + 1 > 0; --currRank)
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

	for(auto currFile = piecePos.file + 1; currFile < Chess::FILES; ++currFile)
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
	
	for(auto currFile = piecePos.file - 1; currFile + 1 > 0; --currFile)
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
		 currPos.rank < Chess::RANKS && currPos.file + 1 > 0; ++currPos.rank, --currPos.file)
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
		 currPos.rank + 1 > 0 && currPos.file + 1 > 0; --currPos.rank, --currPos.file)
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
		 currPos.rank + 1 > 0 && currPos.file < Chess::FILES; --currPos.rank, ++currPos.file)
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
	, { piecePos.rank + 2, piecePos.file -  1}, { piecePos.rank + 2, piecePos.file + 1 }, { piecePos.rank - 1, piecePos.file - 2}
	, { piecePos.rank - 1, piecePos.file + 2 }, { piecePos.rank - 2, piecePos.file - 1 }, { piecePos.rank - 2, piecePos.file + 1} };

	for (const auto& currPos : knightMoves)
	{
		if (currPos.rank >= 0 && currPos.rank < Chess::RANKS && currPos.file >= 0 && currPos.file < Chess::FILES)
		{
			const auto currPiece = chessBoard[currPos.rank][currPos.file];

			if (currPiece.color != pieceColor && currPiece.piece == Chess::Piece::Knight)
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
			const auto currPiece = chessBoard[currPos.rank][currPos.file];

			if (currPiece.color != pieceColor && currPiece.piece == Chess::Piece::King)
			{
				return true;
			}
		}
	}
	
	if (pieceColor == Chess::Color::Dark)
	{
		if (piecePos.rank < Chess::RANKS - 1 && piecePos.file > 0)
		{
			const auto currPiece = chessBoard[piecePos.rank + 1][piecePos.file - 1];

			if (currPiece.piece == Chess::Piece::Pawn && currPiece.color != pieceColor)
			{
				return true;
			}
		}
		else if (piecePos.rank < Chess::RANKS - 1 && piecePos.file < Chess::FILES - 1)
		{
			const auto currPiece = chessBoard[piecePos.rank + 1][piecePos.file + 1];

			if (currPiece.piece == Chess::Piece::Pawn && currPiece.color != pieceColor)
			{
				return true;
			}
		}
	}
	else
	{
		if (piecePos.rank > 0 && piecePos.file > 0)
		{
			const auto currPiece = chessBoard[piecePos.rank - 1][piecePos.file - 1];

			if (currPiece.piece == Chess::Piece::Pawn && currPiece.color != pieceColor)
			{
				return true;
			}
		}
		else if (piecePos.rank > 0 && piecePos.file < Chess::FILES - 1)
		{
			const auto currPiece = chessBoard[piecePos.rank - 1][piecePos.file + 1];

			if (currPiece.piece == Chess::Piece::Pawn && currPiece.color != pieceColor)
			{
				return true;
			}
		}
	}

	return false;
}

bool Chess::isCheckmate(const ChessBoard& chessBoard, Chess::Color kingColor, const Chess::Position& kingPos, const Chess::Position& attackerPos)
{
	auto testChessBoard = chessBoard;

	Chess::Position kingMoves[] = { { kingPos.rank + 1, kingPos.file - 1 }, { kingPos.rank + 1, kingPos.file + 1 },
	{ kingPos.rank + 1, kingPos.file }, { kingPos.rank , kingPos.file + 1}, { kingPos.rank, kingPos.file - 1},
	{ kingPos.rank - 1, kingPos.file + 1 }, { kingPos.rank - 1, kingPos.file - 1}, { kingPos.rank - 1, kingPos.file } };

	for (const auto& currPos : kingMoves)
	{
		const auto currPiece = chessBoard[currPos.rank][currPos.file];

		if (currPiece.color == kingColor && currPiece.piece != Chess::Piece::None)
		{
			continue;
		}
		else
		{
			testChessBoard[kingPos.rank][kingPos.file] = ChessPiece{};
			testChessBoard[currPos.rank][currPos.file] = ChessPiece{ Chess::Piece::King, kingColor };

			if (!canBeCaptured(testChessBoard, kingColor, currPos))
			{
				return false;
			}

			testChessBoard[currPos.rank][currPos.file] = currPiece;
			testChessBoard[kingPos.rank][kingPos.file] = ChessPiece{ Chess::Piece::King, kingColor };
		}
	}

	if (kingColor == Chess::Color::Light)
	{
		if (canBeCaptured(chessBoard, Chess::Color::Dark, attackerPos))
		{
			return false;
		}
	}
	else
	{
		if (canBeCaptured(chessBoard, Chess::Color::Light, attackerPos))
		{
			return false;
		}
	}

	return true;
}

bool Chess::isPawnPromoted(const Chess::Position& newPos)
{
	return newPos.rank == 0 || newPos.rank == Chess::RANKS - 1;
}