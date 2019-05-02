/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessMoveValidation.hpp
https://inversepalindrome.com/
*/


#pragma once

#include "ChessBoard.hpp"
#include "ChessPosition.hpp"
#include "ChessTransition.hpp"


namespace Chess
{
   bool isEnPassantValid(const Chess::Board<ChessPiece>& chessBoard, const std::vector<Chess::Transition>& history,
	    Chess::Color pawnColor, const Chess::Position& oldPos, const Chess::Position& newPos);

    bool isCastlingMoveValid(const Chess::Board<ChessPiece>& chessBoard, const Chess::Position& oldPos, const Chess::Position& newPos);

    bool isPieceMoveValid(const Chess::Board<ChessPiece>& chessBoard, Chess::Color pieceColor, const Chess::Position& newPos);

    bool isPawnMoveValid(const Chess::Board<ChessPiece>& chessBoard, Chess::Color pawnColor, bool hasMoved,
		const Chess::Position& oldPos, const Chess::Position& newPos);

    bool isKnightMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos);

    bool isBishopMoveValid(const Chess::Board<ChessPiece>& chessBoard, const Chess::Position& oldPos, 
		const Chess::Position& newPos);

    bool isRookMoveValid(const Chess::Board<ChessPiece>& chessBoard, const Chess::Position& oldPos, 
		const Chess::Position& newPos);

    bool isQueenMoveValid(const Chess::Board<ChessPiece>& chessBoard, const Chess::Position& oldPos,
	    const Chess::Position& newPos);

    bool isKingMoveValid(const Chess::Position& oldPos, const Chess::Position& newPos);

    bool canBeCaptured(const Chess::Board<ChessPiece>& chessBoard, Chess::Color kingColor, 
        const Chess::Position& kingPos);

    bool hasValidMoves(const Chess::Board<ChessPiece>& chessBoard, Chess::Color kingColor,
	    const Chess::Position& kingPos);

    bool isPawnPromoted(const Chess::Position& newPos);
}
