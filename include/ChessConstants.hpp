/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessConstants.hpp
https://inversepalindrome.com/
*/


#pragma once


namespace Chess
{
    static constexpr int FILES = 8;
    static constexpr int RANKS = 8;
    static constexpr int SQUARE_SIZE = 148;
    static constexpr int PIECE_SIZE = 120;

    enum class Piece { None, Pawn, Knight, Bishop, Rook, King, Queen };
    enum class Color { Light, Dark };
    enum class EndResult { LightWon, DarkWon, Stalemate };
    enum class CastlingMode { None, Short, Long };
}
