/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPosition.hpp
https://inversepalindrome.com/
*/


#pragma once

#include <cstddef>


namespace Chess
{
    struct Position
    {
        int rank = -1;
        int file = -1;

        bool operator==(const Position& position) const;
        bool operator!=(const Position& position) const;
    };
}
