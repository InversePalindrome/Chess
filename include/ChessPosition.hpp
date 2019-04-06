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
        std::size_t rank = 0;
        std::size_t file = 0;

        bool operator==(const Position& position) const;
        bool operator!=(const Position& position) const;
    };
}
