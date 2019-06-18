// Author: Jeremiah Kalmus
// File: pwdCheck.cpp
// Date: May 15th, 2019
// Version: 2.0

/* 
 * IMPLEMENTATION INVARIANTS:
 *  1 - Protected is used for all data members since it is known that other classes will rely on pwdCheck as a parent class and will 
 *      need to access the data members of the parent for optimal use.
 *      
 *  2 - isActive, Password_Check, and Toggle_State are all defined as virtual since child classes may need to override and modify the
 *      functionality of these pwdCheck methods. 
 *      
 *  3 - State is toggled every p passwords that are entered.
 *  
 *  4 - Minimum password length by dafault is 6.
 *  
 *  5 - Default forbidden character is a space.
 *  
 *  6 - State is toggled in the Toggle_State() potected method. Data member keeping track of state it called 'active'.
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
#include "pwdCheck.h"
#include "excessC.h"
#include "compundC.h"

using namespace std;

  unsigned const pwdCheck::DEFAULT_PASSWORD_LENGTH = 6;
  unsigned const pwdCheck::MAX_PWD_LENGTH_REQUIRMENT = 20;
  unsigned const pwdCheck::MIN_PASSWORD_LENGTH = 4;
  unsigned const pwdCheck::ASCII_MIN = 32;
  unsigned const pwdCheck::ASCII_MAX = 127;
  unsigned const pwdCheck::MAX_PWD_LENGTH = 30;
  char const pwdCheck::DEFAULT_FORBIDDEN_CHAR = ' ';

pwdCheck::pwdCheck()
{
  minimum_password_length = DEFAULT_PASSWORD_LENGTH;
  forbidden_character = DEFAULT_FORBIDDEN_CHAR;
  active = true;
  state_counter = 0;
  actual_password_length = 0;
}
pwdCheck::pwdCheck(unsigned default_password_length, char forbidden_char_input)
{
  if (default_password_length < MIN_PASSWORD_LENGTH || default_password_length > MAX_PWD_LENGTH_REQUIRMENT)
    {
      minimum_password_length = DEFAULT_PASSWORD_LENGTH;
    }
  else
    {
      minimum_password_length = default_password_length;
    }
  if ((unsigned)forbidden_char_input < ASCII_MIN || (unsigned)forbidden_char_input > ASCII_MAX)
    {
      forbidden_character = DEFAULT_FORBIDDEN_CHAR;
    }
  else
	{
	  forbidden_character = forbidden_char_input;
	}
  active = true;
  state_counter = 0;
  actual_password_length = 0;

}
unsigned pwdCheck::Password_Length()
{
  return actual_password_length;
}
unsigned pwdCheck::Minimum_Password_Length()
{
  return minimum_password_length;
}
bool pwdCheck::isActive()
{
  return active;
}
// PRE: Password needs to be entered by the client
// POST: Object state may be toggled and state_counter may be incremented
bool pwdCheck::Password_Check(string input_password)
{
	
  if (state_counter == minimum_password_length)
    {
      Toggle_State();
    }
  
  actual_password_length = (unsigned)input_password.length();
  
  if (active)
    {
      if (Forbidden_Char_And_ASCII_Check(input_password) && Password_Length_Check(input_password))
        {
          state_counter++;
		  if (state_counter == minimum_password_length)
			{
				Toggle_State();
			}
          return true;
        }
    }
  state_counter++;
    if (state_counter == minimum_password_length)
      {
        Toggle_State();
      }
  return false;
}
// PRE: State of object must be active
bool pwdCheck::Password_Length_Check(string input_password)
{
  if (actual_password_length >= minimum_password_length && actual_password_length <= MAX_PWD_LENGTH) 
    {
      return true;
    }
	else
	{
		return false;
	}
}
// PRE: Should only be called when state_counter is equal to p.
// POST: State of object will be toggled and state_counter will be reset.
bool pwdCheck::Toggle_State()
{
  if (active)
    {
      active = false;
    }
  else
    {
      active = true;
    }
  state_counter = 0;
  return active;
}
// PRE: State of object must be active
bool pwdCheck::Forbidden_Char_And_ASCII_Check(string input_password)
{
  for (unsigned i = 0; i < actual_password_length; i++)
    {
      if (input_password[i] == forbidden_character || (((unsigned)input_password[i] < ASCII_MIN) ||
                                                       ((unsigned)input_password[i] > ASCII_MAX)))
        {
          return false;
        }
    }
  return true;
}
