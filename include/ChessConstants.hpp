/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessConstants.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <cstddef>


namespace Chess
{
    static constexpr std::size_t FILES = 8;
    static constexpr std::size_t RANKS = 8;
    static constexpr std::size_t SQUARE_SIZE = 148;
    static constexpr std::size_t PIECE_SIZE = 120;

    enum class Piece { None, Pawn, Knight, Bishop, Rook, King, Queen };
    enum class Color { Light, Dark };
}
