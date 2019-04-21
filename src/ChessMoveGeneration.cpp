/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveGeneration.cpp
https://inversepalindrome.com/
*/


#include "ChessMoveGeneration.hpp"


std::vector<Chess::Position> Chess::getPawnMoves(const Chess::Board<ChessPiece>& chessBoard,
	Chess::Color pawnColor, const Chess::Position& pos, bool hasMoved)
{
	std::vector<Chess::Position> moves;

	if (pawnColor == Chess::Color::Light)
	{
		if (!hasMoved && chessBoard[pos.rank - 1][pos.file].piece == Chess::Piece::None
			&& chessBoard[pos.rank - 2][pos.file].piece == Chess::Piece::None)
		{
			moves.push_back({ pos.rank - 2, pos.file });
		}
		if (chessBoard[pos.rank - 1][pos.file].piece == Chess::Piece::None)
		{
			moves.push_back({ pos.rank - 1, pos.file });
		}
		if (pos.file > 0)
		{
			if (const auto targetPiece = chessBoard[pos.rank - 1][pos.file - 1];
				targetPiece.piece != Chess::Piece::None && targetPiece.color != pawnColor)
			{
				moves.push_back({ pos.rank - 1, pos.file - 1 });
			}
		}
		if (pos.file < Chess::FILES - 1)
		{
			if (const auto targetPiece = chessBoard[pos.rank - 1][pos.file + 1];
				targetPiece.piece != Chess::Piece::None && targetPiece.color != pawnColor)
			{
				moves.push_back({ pos.rank - 1, pos.file + 1 });
			}
		}
	}
	else
	{
		if (!hasMoved && chessBoard[pos.rank + 1][pos.file].piece == Chess::Piece::None 
			&& chessBoard[pos.rank + 2][pos.file].piece == Chess::Piece::None)
		{
			moves.push_back({ pos.rank + 2, pos.file });
		}
		if (chessBoard[pos.rank + 1][pos.file].piece == Chess::Piece::None)
		{
			moves.push_back({ pos.rank + 1, pos.file });
		}
		if (pos.file > 0)
		{
			if (const auto targetPiece = chessBoard[pos.rank + 1][pos.file - 1];
				targetPiece.piece != Chess::Piece::None && targetPiece.color != pawnColor)
			{
				moves.push_back({ pos.rank + 1, pos.file - 1 });
			}
		}
		if (pos.file < Chess::FILES - 1)
		{
			if (const auto targetPiece = chessBoard[pos.rank + 1][pos.file + 1];
				targetPiece.piece != Chess::Piece::None && targetPiece.color != pawnColor)
			{
				moves.push_back({ pos.rank + 1, pos.file + 1 });
			}
		}
	}

	return moves;
}

std::vector<Chess::Position> Chess::getKnightMoves(const Chess::Board<ChessPiece>& chessBoard,
	Chess::Color color, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	Chess::Position knightMoves[] = { { pos.rank + 1, pos.file - 2 }, { pos.rank + 1, pos.file + 2 }
	, { pos.rank + 2, pos.file - 1}, { pos.rank + 2, pos.file + 1 }, { pos.rank - 1, pos.file - 2 }
	, { pos.rank - 1, pos.file + 2 }, { pos.rank - 2, pos.file - 1 }, { pos.rank - 2, pos.file + 1} };

	for (const auto& currPos : knightMoves)
	{
		if (currPos.rank >= 0 && currPos.rank < Chess::RANKS && currPos.file >= 0 && currPos.file < Chess::FILES)
		{
			if (const auto currPiece = chessBoard[currPos.rank][currPos.file]; 
				currPiece.piece == Chess::Piece::None || currPiece.color != color)
			{
				moves.push_back(currPos);
			}
		}
	}

	return moves;
}

std::vector<Chess::Position> Chess::getBishopMoves(const Chess::Board<ChessPiece>& chessBoard,
	Chess::Color color, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	for (auto currPos = Chess::Position{ pos.rank + 1, pos.file + 1 };
		currPos.rank < Chess::RANKS && currPos.file < Chess::FILES; ++currPos.rank, ++currPos.file)
	{
		const auto currPiece = chessBoard[currPos.rank][currPos.file];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back(currPos);
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back(currPos);
			break;
		}
	}

	for (auto currPos = Chess::Position{ pos.rank + 1, pos.file - 1 };
		currPos.rank < Chess::RANKS && currPos.file + 1 > 0; ++currPos.rank, --currPos.file)
	{
		const auto currPiece = chessBoard[currPos.rank][currPos.file];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back(currPos);
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back(currPos);
			break;
		}
	}

	for (auto currPos = Chess::Position{ pos.rank - 1, pos.file - 1 };
		currPos.rank + 1 > 0 && currPos.file + 1 > 0; --currPos.rank, --currPos.file)
	{
		const auto currPiece = chessBoard[currPos.rank][currPos.file];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back(currPos);
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back(currPos);
			break;
		}
	}

	for (auto currPos = Chess::Position{ pos.rank - 1, pos.file + 1 };
		currPos.rank + 1 > 0 && currPos.file < Chess::FILES; --currPos.rank, ++currPos.file)
	{
		const auto currPiece = chessBoard[currPos.rank][currPos.file];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back(currPos);
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back(currPos);
			break;
		}
	}

	return moves;
}

std::vector<Chess::Position> Chess::getRookMoves(const Chess::Board<ChessPiece>& chessBoard,
	Chess::Color color, const Chess::Position& pos)
{
	std::vector<Chess::Position> moves;

	for (std::size_t currFile = pos.file + 1; currFile < Chess::FILES; ++currFile)
	{
		const auto currPiece = chessBoard[pos.rank][currFile];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back({ pos.rank, currFile });
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back({ pos.rank, currFile });
			break;
		}
	}

	for (std::size_t currFile = pos.file - 1; currFile >= 0; --currFile)
	{
		const auto currPiece = chessBoard[pos.rank][currFile];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back({ pos.rank, currFile });
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back({ pos.rank, currFile });
			break;
		}
	}

	for (std::size_t currRank = pos.rank + 1; currRank < Chess::RANKS; ++currRank)
	{
		const auto currPiece = chessBoard[currRank][pos.file];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back({ currRank, pos.file });
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back({ currRank, pos.file });
			break;
		}
	}

	for (std::size_t currRank = pos.rank - 1; currRank >= 0; --currRank)
	{
		const auto currPiece = chessBoard[currRank][pos.file];

		if (currPiece.piece == Chess::Piece::None)
		{
			moves.push_back({ currRank, pos.file });
		}
		else if (currPiece.color == color)
		{
			break;
		}
		else
		{
			moves.push_back({ currRank, pos.file });
			break;
		}
	}

	return moves;
}

std::vector<Chess::Position> Chess::getQueenMoves(const Chess::Board<ChessPiece>& chessBoard,
	Chess::Color color, const Chess::Position& pos)
{
	auto moves = getBishopMoves(chessBoard, color, pos);
	auto rookMoves = getRookMoves(chessBoard, color, pos);

	moves.insert(end(moves), begin(rookMoves), end(rookMoves));

	return moves;
}

std::vector<Chess::Position> Chess::getKingMoves(const Chess::Board<ChessPiece>& chessBoard,
	Chess::Color color, const Chess::Position& pos)
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