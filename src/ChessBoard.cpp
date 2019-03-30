/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessBoard.cpp
https://inversepalindrome.com/
*/


#include "ChessBoard.hpp"


ChessBoard::ChessBoard()
{
    resetBoard();
}

void ChessBoard::resetBoard()
{
    board =
    {{
        { ChessPiece{ Chess::Piece::Rook, Chess::Color::Dark }, ChessPiece{ Chess::Piece::Knight, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Bishop, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Queen, Chess::Color::Dark}, ChessPiece{ Chess::Piece::King, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Bishop, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Knight, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Rook, Chess::Color::Dark} },
        { ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark }, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Dark} },
        { ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{} },
        { ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{} },
        { ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{} },
        { ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{}, ChessPiece{} },
        { ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light }, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light}, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light }, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light }, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light }, ChessPiece{ Chess::Piece::Pawn, Chess::Color::Light } },
        { ChessPiece{ Chess::Piece::Rook, Chess::Color::Light}, ChessPiece{ Chess::Piece::Knight, Chess::Color::Light}, ChessPiece{ Chess::Piece::Bishop, Chess::Color::Light}, ChessPiece{ Chess::Piece::Queen, Chess::Color::Light}, ChessPiece{ Chess::Piece::King, Chess::Color::Light }, ChessPiece{ Chess::Piece::Bishop, Chess::Color::Light }, ChessPiece{ Chess::Piece::Knight, Chess::Color::Light }, ChessPiece{ Chess::Piece::Rook, Chess::Color::Light } }
     }};
}

std::array<ChessPiece, Chess::RANKS>& ChessBoard::operator[](const std::size_t index)
{
    return board[index];
}

const std::array<ChessPiece, Chess::RANKS>& ChessBoard::operator[](const std::size_t index) const
{
    return board[index];
}

