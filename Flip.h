// Author: Jeremiah Kalmus
// File: Flip.h
// Date: May 15th, 2019
// Version: 1.0

/* 
 * OVERVIEW:
 *  Flip during construction takes 1 or zero parameter values and defines an encapsulated_string and a
 *  The client can then enter a non-negative integer and Flip will flip the encapsulated_strings up to the entered digits
 *  character.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * DESIGN DECISIONS AND ASSUMPTIONS:
 *  1 - flip_value of 0 will simply do nothing.
 *  
 *  2 - flip_value greater than the length of the encapsulated_string will simply slip the entire string.
 *      
 *  3 - flip_value cannot be negative
 *      
 * ---------------------------------------------------------------------------------------------------------------------------------
 * INTERFACE INVARIANTS:
 *  1 - Flip_Password:
 *
 * 		Enter a value into the Flip_Password method and the encapsulated_string characters will flip from the beginning of
 * 		the string to the value entered into the mathod. Values entered must be non-negative integers. 
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
#ifndef Flip_H
#define Flip_H

using namespace std;

class Flip
{
	public:
	  Flip();
	  Flip(string);
	  string Flip_Password(unsigned);
	  
	private:
	  string static const DEFAULT_STR; 
	  string encapsulated_string;
	  string flipped_string;
	
};
#endif