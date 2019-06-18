// Author: Jeremiah Kalmus
// File: pwdCheck.cpp
// Date: May 15th, 2019
// Version: 2.0

/* 
 * OVERVIEW:
 *  pwdCheck during construction takes 2 parameter values and defines a minimum length requirement for passwords and a
 *  defult forbidden character. The client can then enter a password and pwdCheck will either accept the password or reject it
 *  depending if it meets the criteria of being a certain length p, if it contains no traces of a forbidden character, and if it
 *  is composed completely of characters between ASCII 32 and 127.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * DESIGN DECISIONS AND ASSUMPTIONS:
 *  1 - ASCII characters less than 32 are rejected since they are considered control characters.
 *  
 *  2 - ASCII character greater than 127 are rejected since they are non-frequently used special characters or accented characters
 *      that do not pertain to the english language.
 *      
 *  3 - Passwords cannot be negative length or length less than 4 or length greater than 30 since a password of negative length doesn't
 *      exist, a password length of less than 4 is an insecure password, and a password length of over 30 is unneccessary. Also, the 
 *      length of p follows the same rules except the maximum it can be is 20.
 *      
 *  4 - If the the a pwdCheck object is off/inactive, then all passwords will be rejected.
 *      
 * ---------------------------------------------------------------------------------------------------------------------------------
 * INTERFACE INVARIANTS:
 *  1 - State Changes:
 *  
 *      A pwdCheck object changes state if p number of passwords have been checked, where p is the minimum length a password is required
 *      to be in order to be accepted. 
 *      
 *  2 - Password_Check():
 *  
 *      When a pwdCheck object is on/active, it checks entered passwords into Password_Check() to see if they are at least length p,
 *      that each character is an ASCII character between 32 and 127, and that a forbidden character does not exist in the password.
 *      The method will return true if all these conditions are met and false otherwise. A pwdCheck object will reject all passwords
 *      if it is in an off/inactive state.
 *  
 *  3 - Accessors (Password_Length, Minimum_Password_Length, isActive):
 *  
 *      The client can request access to see the length of the last entered password with Password_Length, the minimum length 
 *      requirement for the password to be accepted (p length) with Minimum_Password_Length, and the status of the object with 
 *      isActive.
 *  
 * ---------------------------------------------------------------------------------------------------------------------------------
 * CLASS INVARIANTS:
 *  1 - CONSTRUCTOR:
 *  
 *      Client can input up to 2 parameters. The parameters are minimum required password length (p), and a forbidden character. If the
 *      client enters fewer paremeters, then the parameters that are not filled will be set to a default value. Default length p is
 *      '6' and the default forbidden character is a 'space'. The constructor will also check to see if the forbidden character is an
 *      ASCII character between 32 and 127. If the forbidden character is not within these bounds, then it will be set to its default 
 *      value. Also, if the length of p entered is less than 4 or greater than 20, the p value will be set to its default. In the end,
 *      the constructor initializes all data members.
 *      
 *  2 - On/Active State:
 *  
 *      Checks passwords entered by the client to see if they are at least length p, whether all characters of the password are ASCII
 *      characters between ASCII 32 and ASCII 127, and if the forbidden character doesn't exist in the password. The state of a pwdCheck
 *      object will toggle between on and off if p passwords are checked.
 *  
 *  3 - Off/Inactive State: 
 *      
 *      Rejects all passwords.
 *      
 * ---------------------------------------------------------------------------------------------------------------------------------
 */
#include <string>
#ifndef pwdCheck_H
#define pwdCheck_H

using namespace std;

class pwdCheck
{
 public:
  pwdCheck();
  pwdCheck(unsigned default_password_length, char forbidden_char_input);
  unsigned Password_Length();
  unsigned Minimum_Password_Length();
  virtual bool isActive();
  virtual bool Password_Check(string);
	 
 protected:
  unsigned static const DEFAULT_PASSWORD_LENGTH;
  unsigned static const MAX_PWD_LENGTH_REQUIRMENT;
  unsigned static const MIN_PASSWORD_LENGTH;
  unsigned static const ASCII_MIN;
  unsigned static const ASCII_MAX;
  unsigned static const MAX_PWD_LENGTH;
  char static const DEFAULT_FORBIDDEN_CHAR;
  unsigned minimum_password_length;
  bool active;
  unsigned state_counter;
  unsigned actual_password_length;
  char forbidden_character;
  bool Password_Length_Check(string);
  virtual bool Toggle_State();
  
 private:
  bool Forbidden_Char_And_ASCII_Check(string);
};
#endif
