// Author: Jeremiah Kalmus
// File: compundC.h
// Date: May 15th, 2019
// Version: 2.0

/* 
 * OVERVIEW:
 * compundC during initialization will call the parent constructor for length p and the forbidden character (see pwdCheck.cs) and
 * also accept a third parameter which is a length k which determines how many times a compundC objects state can be toggled before
 * it loses the ability to toggle states. compundC objects act like pwdCheck objects except when a compundC object is on/active, a 
 * password will only be accepted if it satisfies the pwdCheck criteria, at least one character is repeated, and it cannot toggle 
 * states more than k times.
 * 
 * ---------------------------------------------------------------------------------------------------------------------------------
 * DESIGN DECISIONS AND ASSUMPTIONS:
 *  1 - If a state change parameter is entered and it is 0 or greater than 10, the default k value will be used which is 4. If no 
 *      parameters are entered, then deafult values will be set for p, k, and the forbidden character. The k value by default is 4,
 *      the p value and forbidden character are specified in pwdCheck.cs.
 *  
 *  2 - A Password repeating at least one character does not need to be successive characters. An example of acceptable passwords given
 *      their lengths are appropriate and no forbidden characters exist (e.g. ABCDEFGA). A is repeated and therefore passes that 
 *      constraint.
 *      
 *  3 - Accessors were provided to help the client keep track of the objects progress toward k state changes.
 *  
 *  4 - Working off of assumptions made in pwdCheck.cs.
 * ---------------------------------------------------------------------------------------------------------------------------------
 * INTERFACE INVARIANTS:
 *  1 - State Changes:
 *  
 *      State will change after p password checks where p is the minimum acceptable length for a password. After k state changes where
 *      k is the amount of state changes an object can have, the object will become locked and state change will no longer be possible.
 *  
 *  2 - Password_Check():
 *  
 *      Will check to see the state of the object and if it is on, then incoming passwords will be checked to see if any character
 *      repeats, as well as other functionality specified in Password_Check() in pwdCheck.cs.
 *  
 *  3 - Accessors (canToggle, State_Change_Limit):
 *  
 *      The client can view if the object can be toggled (meaning the object has not toggled k times yet) with canToggle. The client
 *      can also see the amount of times the object can toggle state with State_Change_Limit. All accessors from pwdCheck can also we
 *      called in compundC (see pwdCheck.cs).
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
 */
 
#include<string>
#ifndef compundC_H
#define compundC_H

#include "pwdCheck.h"

using namespace std;

class compundC : public pwdCheck
{
 public:
  compundC();
  compundC(unsigned default_password_length, char forbidden_char_input, 
			unsigned max_state_changes);
  bool canToggle();
  unsigned State_Change_Limit();
  bool Password_Check(string);
  
    unsigned state_change_counter;
  
 protected:
  bool Toggle_State();
  
 private:
  unsigned static const DEFAULT_STATE_CHANGES;
  unsigned static const MAX_STATE_CHANGES;
  unsigned state_change_limit;

  bool can_toggle;
  bool Repeat_Character_Check(string);
  bool Max_Toggle_Check();
  
};
#endif
