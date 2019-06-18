// Author: Jeremiah Kalmus
// File: compundC.cpp
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
 *      This method is overridden since it needed to be modified to keep track of how many state changes there have been and to lock out
 *      the objects toggling capabilities after k toggles.
 *      
 *  3 - See pwdCheck.cs for more information.
 *  
 * ---------------------------------------------------------------------------------------------------------------------------------
 * CLASS INVARIANTS:
 *  1 - CONSTRUCTOR:
 *  
 *      Takes in 3 parameters, one of which being the amount of times a compundC object can toggle states (value k). Initializes data
 *      members pertaining specifically to the compundC class. Parent constructor also fired. See pwdCheck.cs.
 *      
 *  2 - On/Active State:
 *  
 *      Same as the pwdCheck.cs with the addition of checking incoming passwords for at least one repeating character. Also, checking
 *      the number of state toggles the object has done and preventing more than k state toggles.
 *      
 *  3 - Off/Inactive State:
 *  
 *      Refer to pwdCheck.cs Off/Inactive state.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * UPDATES:
 * 		5/15/2019 - Password_Check method now increments state_counter in the check for Repeat_Character_Check.
 */
 
#include<string>
#include <ctype.h>
#include "compundC.h"

using namespace std;

  unsigned const compundC::DEFAULT_STATE_CHANGES = 4;
  unsigned const compundC::MAX_STATE_CHANGES = 10;

compundC::compundC() : pwdCheck()
{
  state_change_limit = DEFAULT_STATE_CHANGES;
  state_change_counter = 0;
  can_toggle = true;
}
compundC::compundC(unsigned default_password_length, char forbidden_char_input, unsigned max_state_changes = DEFAULT_STATE_CHANGES) 
					: pwdCheck(default_password_length, forbidden_char_input)
{
  if (max_state_changes > MAX_STATE_CHANGES || max_state_changes == 0)
    {
      state_change_limit = DEFAULT_STATE_CHANGES;
    }
  else
    {
      state_change_limit = max_state_changes;
    }
  state_change_counter = 0;
  can_toggle = true;
}
bool compundC::canToggle()
{
  return can_toggle;
}
unsigned compundC::State_Change_Limit()
{
  return state_change_limit;
}
// PRE: Client must enter a password.
// POST: State may be toggled, state_counter may be incremented, and the ability to toggle may be switched
        //       from true to false.
bool compundC::Password_Check(string input_password)
{
  actual_password_length = (unsigned)input_password.length();
  
  if (Max_Toggle_Check())
    {
		if (state_counter == minimum_password_length)
		{
			Toggle_State();
		}
    }
	if (!Repeat_Character_Check(input_password))
		{
			state_counter++;
			return false;
		}
	return pwdCheck::Password_Check(input_password);
}
// PRE: Should only be called when state_counter is equal to p.
// POST: May change state of object and increment state_change_counter. 
bool compundC::Toggle_State()
{
  if (can_toggle)
    {
      state_change_counter++;
      return pwdCheck::Toggle_State();
    }
  return false;
}
// PRE: State of object must be active.
bool compundC::Repeat_Character_Check(string input_password)
{
  for (unsigned i = 1; i < actual_password_length; i++)
    {
      unsigned j = 0;
      while (j < i)
        {
          if (input_password[i] == input_password[j])
            {
              return true;
            }
          j++;
        }
    }
  return false;
}
// POST: May change the objects ability to toggle state.
bool compundC::Max_Toggle_Check()
{
  if (state_change_counter == state_change_limit)
    {
      can_toggle = false;
    }
  return can_toggle;
}
