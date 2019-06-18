// Author: Jeremiah Kalmus
// File: FlipPwdCheck.h
// Date: May 15th, 2019
// Version: 1.0

/* 
 * OVERVIEW:
 *  FlipPwdCheck will take the encpsulated password, flip the first 'flip_digit' amount of characters in the string, and then
 * 	compare that result with pwdCheck to see if it passes or not.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * DESIGN DECISIONS AND ASSUMPTIONS:
 *  1 - Check_Flipped_Password:
 * 		
 *      This method will flip first and then compare the flipped password and return a boolean to the client whether it passed the
 * 		check or not. 
 * ---------------------------------------------------------------------------------------------------------------------------------
 * INTERFACE INVARIANTS:
 *  1 - Check_Flipped_Password:
 *
 * 		Enter a value into the Flip_Password method and the encapsulated_string characters will flip from the beginning of
 * 		the string to the value entered into the mathod. Afterwards, the flipped string will be checked to see if it meets certain
 * 		specifications (reference pwdCheck for specifications). Values entered can be any non-negative integer.  
 * 
 * 	2 - Reference pwdChek and Flip for additional functionality.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * CLASS INVARIANTS:
 *  1 - CONSTRUCTORS:
 *  
 *      One constructor takes in 3 parameter which are the encapsulated_string that will be flipped in Flip_Password when called, the default password
 * 		length that is the p value in pwdCheck Class (see pwdCheck for details), and the forbidden_char_input (see pwdCheck for details).
 *		The other constructor is a default constructor that calls the default constructor in pwdCheck and Flip classes. See pwdCheck and Flip for further
 * 		default constructor information.
 *
 *  2 - Check_Flipped_Password:
 *
 *		Is an unsigned integer that can be any value and will take all characters in the encapsulated_string up to the flip_digit 
 * 		number character in the string and flip that part of the string. If 0 or 1 is entered, then the string will be identical
 * 		to the dafult encapsulated_string (nothing will flip for 0 and the first character will flip with itself which is the same
 * 		result). If the flip_digit is equal or larger than the length of the encapsulated_string, then the whole string will be flipped_string
 * 		regardless of how much larger flip_digit is than the length of the encapsulated_string (see Flip for further information). Afterwards, the 
 * 		method will then take the returned flipped string and check that against the pwdCheck specifications (see pwdCheck for further information).
 * ---------------------------------------------------------------------------------------------------------------------------------
 */

#include<string>
#ifndef FlipPwdCheck_H
#define FlipPwdCheck_H

#include "pwdCheck.h"
#include "Flip.h"

using namespace std;

class FlipPwdCheck : public pwdCheck, public Flip
{
	public:
	  FlipPwdCheck();
	  FlipPwdCheck(string input_encapsulated_string, unsigned default_password_length, char forbidden_char_input); 
	  virtual bool Check_Flipped_Password(unsigned);
	  
};
#endif