/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessResources.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessPiece.hpp"

#include <string>
#include <unordered_map>


namespace Chess
{
	const std::unordered_map<ChessPiece, std::string, ChessPieceHash> resources =
	{	
		{ ChessPiece{Chess::Piece::Pawn, Chess::Color::Light }, "LightPawn.png" },
		{ ChessPiece{ Chess::Piece::Knight, Chess::Color::Light }, "LightKnight.png" },
		{ ChessPiece{ Chess::Piece::Bishop, Chess::Color::Light }, "LightBishop.png" },
		{ ChessPiece{ Chess::Piece::Rook, Chess::Color::Light }, "LightRook.png" },
		{ ChessPiece{ Chess::Piece::King, Chess::Color::Light }, "LightKing.png" },
		{ ChessPiece{ Chess::Piece::Queen, Chess::Color::Light }, "LightQueen.png" },
		{ ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark }, "DarkPawn.png" },
		{ ChessPiece{ Chess::Piece::Knight, Chess::Color::Dark }, "DarkKnight.png" },
		{ ChessPiece{ Chess::Piece::Bishop, Chess::Color::Dark }, "DarkBishop.png" },
		{ ChessPiece{ Chess::Piece::Rook, Chess::Color::Dark }, "DarkRook.png" },
		{ ChessPiece{ Chess::Piece::King, Chess::Color::Dark }, "DarkKing.png" },
		{ ChessPiece{ Chess::Piece::Queen, Chess::Color::Dark }, "DarkQueen.png" },
	};
}
