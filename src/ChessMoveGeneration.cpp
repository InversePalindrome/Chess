/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveGeneration.cpp
https://inversepalindrome.com/
*/


#include "ChessMoveGeneration.hpp"


std::vector<Chess::Position> Chess::getPawnMoves(const ChessBoard& chessBoard,
	const Chess::Position& pos, Chess::Color pawnColor, bool hasMoved)
{
	std::vector<Chess::Position> moves;

	return moves;
}

std::vector<Chess::Position> Chess::getKnightMoves(const ChessBoard& chessBoard, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	return moves;
}

std::vector<Chess::Position> Chess::getBishopMoves(const ChessBoard& chessBoard, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	return moves;
}

std::vector<Chess::Position> Chess::getRookMoves(const ChessBoard& chessBoard, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	return moves;
}

std::vector<Chess::Position> Chess::getQueenMoves(const ChessBoard& chessBoard, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	return moves;
}

std::vector<Chess::Position> Chess::getKingMoves(const ChessBoard& chessBoard, Chess::Color color, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	Chess::Position kingMoves[] = { { pos.rank + 1, pos.file - 1 }, { pos.rank + 1, pos.file + 1 },
	{ pos.rank + 1, pos.file }, { pos.rank , pos.file + 1}, { pos.rank, pos.file - 1},
	{ pos.rank - 1, pos.file + 1 }, { pos.rank - 1, pos.file - 1}, { pos.rank - 1, pos.file } };

	for (const auto& currPos : kingMoves)
	{
		if (currPos.rank >= 0 && currPos.rank < Chess::RANKS && currPos.file >= 0 && currPos.file < Chess::FILES)
		{
			if (const auto chessPiece = chessBoard[currPos.rank][currPos.file]; 
				chessPiece.piece == Chess::Piece::None || chessPiece.color != color)
			{
				moves.push_back(currPos);
			}
		}
	}

	return moves;
}