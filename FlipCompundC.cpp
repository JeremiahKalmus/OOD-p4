// Author: Jeremiah Kalmus
// File: FlipCompundC.cpp
// Date: May 15th, 2019
// Version: 1.0

/* 
 * IMPLEMENTATION INVARIANTS:
 * 	1 - Reference compundC and Flip for additional functionality.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * CLASS INVARIANTS:
 *  1 - CONSTRUCTORS:
 *  
 *      One constructor takes in 4 parameter which are the encapsulated_string that will be flipped in Flip_Password when called, the default password
 * 		length that is the p value in compundC Class (see compundC for details), the forbidden_char_input (see compundC for details), and the K number of 
 *		state changes the object can have before permenantly preventing further state changes (see compundC for details).
 *		The other constructor is a default constructor that calls the default constructor in compundC and Flip classes. See compundC and Flip for further
 * 		default constructor information.
 *
 *  2 - Check_Flipped_Password:
 *
 *		Is an unsigned integer that can be any value and will take all characters in the encapsulated_string up to the flip_digit 
 * 		number character in the string and flip that part of the string. If 0 or 1 is entered, then the string will be identical
 * 		to the dafult encapsulated_string (nothing will flip for 0 and the first character will flip with itself which is the same
 * 		result). If the flip_digit is equal or larger than the length of the encapsulated_string, then the whole string will be flipped_string
 * 		regardless of how much larger flip_digit is than the length of the encapsulated_string (see Flip for further information). Afterwards, the 
 * 		method will then take the returned flipped string and check that against the compundC specifications (see compundC for further information).
 * ---------------------------------------------------------------------------------------------------------------------------------
 */

#include<string>
#include "FlipCompundC.h"

using namespace std;

FlipCompundC::FlipCompundC() : compundC(), Flip() {}
FlipCompundC::FlipCompundC(string input_encapsulated_string, unsigned default_password_length, char forbidden_char_input, unsigned max_state_changes)
							: compundC(default_password_length, forbidden_char_input, max_state_changes), 
							Flip(input_encapsulated_string)
							 {}
// PRE: Password needs to be entered by the client							 
// POST: Object state may be toggled and state_counter may be incremented	
bool FlipCompundC::Check_Flipped_Password(unsigned flip_digit)
{
	return Password_Check(Flip_Password(flip_digit));
}