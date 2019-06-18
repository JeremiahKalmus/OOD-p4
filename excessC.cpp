// Author: Jeremiah Kalmus
// File: excessC.cpp
// Date: May 15th, 2019
// Version: 2.0

/* 
 * IMPLEMENTATION INVARIANTS:
 *  1 - Password_Check:
 *      
 *      This method is overridden since there was need for additional password checks in addition to those that exist in pwdCheck.cs.
 *      
 *  2 - Toggle_State:
 *  
 *      This method is overridden since it needs to constantly keep its own state opposite that of pwdCheck. If pwdCheck state is on
 *      then excessC is in its off state and vice-versa.
 *      
 *  3 - isActive:
 *  
 *      This accessor is overridden since excessC uses pwdCheck state to keep track of its own state, however, the states are inversed.
 *      This means that is pwdCheck object shows on/active, then excessC is really off/inactive.
 *      
 *  4 - See pwdCheck.cs for more information.
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
#include <ctype.h>
#include "excessC.h"

using namespace std;

char const excessC::DOLLAR_SIGN = '$';

excessC::excessC() : pwdCheck()
{
  on = false;
}
excessC::excessC(unsigned default_password_length, char forbidden_char_input) 
  : pwdCheck(default_password_length, forbidden_char_input)
{
  on = false;
}
bool excessC::isActive()
{
  return on;
}
// PRE: Password needs to be entered by the client
// POST: Object state may be toggled and state_counter may be incremented
bool excessC::Password_Check(string input_password)
{
  if (!on)
    {
      return pwdCheck::Password_Check(input_password);
    }
  else
    {
      actual_password_length = (unsigned)input_password.length();
      
      if (state_counter == minimum_password_length)
        {
          Toggle_State();
        }
      
      if (Password_Length_Check(input_password))
        {
          if (Character_P_isDigit_Check(input_password) && Dollar_Sign_Check(input_password) && 
              Mixed_Case_Check(input_password))
            {
              state_counter++;
              return true;
            }
        }
      state_counter++;
      return false;
    }
}
// PRE: Should only be called when state_counter is equal to p.
// POST: Will change state of pwdCheck object and excessC object.
bool excessC::Toggle_State()
{
  on = active;
  return pwdCheck::Toggle_State();
}
bool excessC::Character_P_isDigit_Check(string input_password)
{
  if (isdigit(input_password[(int)minimum_password_length - 1]))
    {
      return true;
    }
  else
    {
      return false;
    }
}
// PRE: State of object must be active.
bool excessC::Dollar_Sign_Check(string input_password)
{
  for (unsigned i = 0; i < actual_password_length; i++)
    {
      if ((unsigned)input_password[i] == (unsigned)DOLLAR_SIGN)
        {
          return true;
        }
    }
  return false;
}
// PRE: State of object must be active.
bool excessC::Mixed_Case_Check(string input_password)
{
  unsigned isUpper_counter = 0;
  unsigned isLower_counter = 0;
  
  for (unsigned i = 0; i < actual_password_length; i++)
    {
      if (isupper(input_password[i]))
        {
          isUpper_counter++;
        }
      else if (islower(input_password[i]))
        {
          isLower_counter++;
        }
    }
  if (isUpper_counter != 0 && isLower_counter != 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}
