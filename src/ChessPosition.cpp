/*
Copyright (c) 2019 Inverse Palindrome
Chess - ChessPosition.cpp
https://inversepalindrome.com/
*/


#include "ChessPosition.hpp"


bool Chess::Position::operator==(const Position& position) const
{
    return this->rank == position.rank && this->file == position.file;
}

bool Chess::Position::operator!=(const Position& position) const
{
    return !(*this == position);
}
