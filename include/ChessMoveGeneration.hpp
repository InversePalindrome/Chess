/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveGeneration.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessPosition.hpp"

#include <vector>


namespace Chess
{
	std::vector<Chess::Position> getPawnMoves(const ChessBoard& chessBoard,
		const Chess::Position& pos, Chess::Color pawnColor, bool hasMoved);
	std::vector<Chess::Position> getKnightMoves(const ChessBoard& chessBoard, const Chess::Position& pos);
	std::vector<Chess::Position> getBishopMoves(const ChessBoard& chessBoard, const Chess::Position& pos);
	std::vector<Chess::Position> getRookMoves(const ChessBoard& chessBoard, const Chess::Position& pos);
	std::vector<Chess::Position> getQueenMoves(const ChessBoard& chessBoard, const Chess::Position& pos);
	std::vector<Chess::Position> getKingMoves(const ChessBoard& chessBoard, Chess::Color kingColor, const Chess::Position& pos);
}