// Author: Jeremiah Kalmus
// File: Flip.cpp
// Date: May 15th, 2019
// Version: 1.0

/* 
 * IMPLEMENTATION INVARIANTS:
 *  1 - encapsulated_string:
 *
 * 		This data member is never changed after it is set and flipped_string is manipulated to achieve the desired effect.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * CLASS INVARIANTS:
 *  1 - CONSTRUCTORS:
 *  
 *      One constructor takes in 1 parameter which is the encapsulated_string that will be flipped in Flip_Password when called.
 *		The other constructor is a default constructor that sets the encapsulated_string to a default value.
 *      
 *  2 - Flip_Password:
 *
 *		Is an unsigned integer that can be any value and will take all characters in the encapsulated_string up to the flip_digit 
 * 		number character in the string and flip that part of the string. If 0 or 1 is entered, then the string will be identical
 * 		to the dafult encapsulated_string (nothing will flip for 0 and the first character will flip with itself which is the same
 * 		result). If the flip_digit is equal or larger than the length of the encapsulated_string, then the whole string will be flipped_string
 * 		regardless of how much larger flip_digit is than the length of the encapsulated_string.  
 * ---------------------------------------------------------------------------------------------------------------------------------
 */

#include <string>
#include "Flip.h"

using namespace std;

string const Flip::DEFAULT_STR = "Default";

Flip::Flip()
{
	encapsulated_string = DEFAULT_STR;
	flipped_string = encapsulated_string;
}
Flip::Flip(string input_encapsulated_string)
{
	encapsulated_string = input_encapsulated_string;
	flipped_string = encapsulated_string;
}
// POST: Flipped string will change from being equal to the string entered during construction
//		 to the appropriate flipped string.
string Flip::Flip_Password(unsigned flip_digit)
{
	flipped_string = encapsulated_string;
	if (flip_digit >= encapsulated_string.length())
	{
		for (unsigned i = 0; i < encapsulated_string.length(); i++)
		{
			flipped_string[i] = encapsulated_string[(encapsulated_string.length()-1) - i];
		}
	}
	else
	{
		for (unsigned i = 0; i < flip_digit; i++)
		{
			 flipped_string[i] = encapsulated_string[(flip_digit-1)-i];
		}
	}
	return flipped_string;
}