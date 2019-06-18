// Author: Jeremiah Kalmus
// File: excessC.h
// Date: May 15th, 2019
// Version: 2.0

/* 
 * OVERVIEW:
 * excessC during construction will call the parent pwdCheck constructor for length p and the forbidden character (see pwdCheck.cs).
 * excessC in its off state acts like pwdCheck in its on state. In excessC's on state, it checks if $ is in the password, if there is 
 * at least one lower case and one upper case character in the password, and that the pth character in the password is a digit.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * DESIGN DECISIONS AND ASSUMPTIONS:
 *  1 - Starts in off state where excessC acts like pwdCheck when pwdCheck is in its on state.
 *  
 *  2 - excessC's on state only checks if $ is in the password, if there is at least one lower case and one upper case character in 
 *      the password, and that the pth character in the password is a digit. It does not have any functionality from pwdChck.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * INTERFACE INVARIANTS:
 *  1 - State Changes:
 *  
 *      State will change after p password checks where p is the minimum acceptable length for a password. 
 *  
 *  2 - Password_Check():
 *  
 *      Will check to see the state of the object and if it is on, then incoming passwords will be checked to see if there is at least
 *      one upper case and one lower case letter in the password, $ is in the password, and that the pth character in the password be a
 *      digit. If the object is in its off state, it will act just like pwdCheck (see pwdCheck.cs inteface invariants).
 *  
 *  3 - Accessors (isActive):
 *  
 *      The client can use isActive to keep track of whether the excessC object is on/active or off/inactive.
 *  
 * ---------------------------------------------------------------------------------------------------------------------------------
 * CLASS INVARIANTS:
 *  1 - CONSTRUCTOR:
 *  
 *      Initialized private data members and fires pwdCheck constructor. See CONSTRUCTOR in pwdCheck.cs for further information.
 *      
 *  2 - On/Active State:
 *  
 *      Checks incoming passwords to see if $ is in the password, if there is at least one lower case and one upper case character in 
 *      the password, and that the pth character in the password is a digit. It does not have any functionality from pwdChck.
 *  
 *  3 - Off/Inactive State:
 *  
 *      Acts exactly like pwdCheck when pwdCheck is in an on state.
 *      
 * ---------------------------------------------------------------------------------------------------------------------------------
 */
#include<string>
#ifndef excessC_H
#define excessC_H

#include "pwdCheck.h"

using namespace std;

class excessC : public pwdCheck
{
 public:
  excessC();
  excessC(unsigned default_password_length, char forbidden_char_input); 
  bool isActive();
  bool Password_Check(string);
  
 protected:
  bool Toggle_State();
  
 private:
  char static const DOLLAR_SIGN;
  bool on;
  bool Character_P_isDigit_Check(string);
  bool Dollar_Sign_Check(string);
  bool Mixed_Case_Check(string);
};
#endif
