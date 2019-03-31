/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessConstants.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <cstddef>


namespace Chess
{
    static constexpr int FILES = 8;
    static constexpr int RANKS = 8;
    static constexpr int SQUARE_SIZE = 148;
    static constexpr int PIECE_SIZE = 120;

    enum class Piece { None, Pawn, Knight, Bishop, Rook, King, Queen };
    enum class Color { Light, Dark };

    struct Position
    {
        std::size_t file = 0;
        std::size_t rank = 0;
    };

    struct Transition
    {
        Position oldPosition;
        Position newPosition;
    };
}
