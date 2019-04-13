/*
Copyright (c) 2019 Inverse Palindrome
Chess - Difference.hpp
https://inversepalindrome.com/
*/


#pragma once


namespace Utility
{
	template<typename T>
	T diff(const T& a, const T& b) {
		return (a > b) ? (a - b) : (b - a);
	}
}
