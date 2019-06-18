// Author: Jeremiah Kalmus
// File: p4.cpp
// Date: May 15th, 2019
// Version: 1.0

/*
	DISCLAIMER:
		On the assignment it said "You should have arrays of distinct objects" and I thought
		this meant seperate arrays for each type/sub-type. There was no confirmation that we
		needed to use heterogeneous arrays until the class day when p4 was due. I admit, it 
		is my fault for not inquiring about this part of the assignment. My assignment does not use
		heterogeneous collections since that was my initial driver design. I attempted on the last
		day to use heterogeneous collections and my attempt is commented below my driver code if
		that counts for anything. I was not able to get that part to work in the end. My apologies.
*/

/*	OVERVIEW:
 * This driver will test seperate homogenous collections of objects in an array of size 10 each. The objects 'Flip', 'FlipPwdCheck',
 * 'FlipExcessC', and 'FlipCompundC' will be tested in ways that are described below.
 * ----------------------------------------------------------------------------------------------------------------------------------
 * TESTS:
 * 
 * Main:
 * 
 * Creates arrays containing the passwords read in from a file and of the 4 object types that will be tested. Also calls tests.
 * 
 * Read_File:
 * 
 * Opens a test file containing passwords. Inputs passwords into an array. Then closes the file.
 * 
 * Initialize_Obj_Arrays:
 * 
 * Creates random input values that are then entered into each array of objects. All of the objects at the same index of their
 * respective array will hold the same input parameters so each object can be compared to one another during testing. Important
 * information printed to the screen.
 * 
 * Test_Flip:
 * 
 * Test Flip object functionality with just one random integer entered into the Flip_Password() method
 * to see that it does indeed flip as described.
 *
 * Test_FlipPwdCheck:
 * 
 * I will test each object once to show that they work in the default state. Then I will force a state change of a single object where we expect
 * the object to always reject the password. After the state is changed I will test the object three more times
 * to show that it will only return false.
 * 
 * Test_FlipExcessC:
 * 
 *	I will test each object once in its default state before I force the change of state of all objects and then test them all once
 * more to show the results of a different state.
 * 
 * Test_FlipCompundC:
 *
 *	I will test each object once in its default state before I force the change of state for each object. I will then test each object
 * once more to show its different state which should reject all passwords and return false. Then I will change state P*K times to lock
 * the change of state operation of each object. I will then show that each object will keep the same state and operate like the state 
 * it is locked in.
 *
 * ----------------------------------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     
#include <time.h>
#include <sstream>

#include "pwdCheck.h"
#include "excessC.h"
#include "compundC.h"
#include "Flip.h"
#include "FlipPwdCheck.h"
#include "FlipExcessC.h"
#include "FlipCompundC.h"
 
using namespace std; 
  
const string READFILE = "test.txt";  
const string ASTERISK = "***********************************************************";
unsigned const TEST_OBJ_AMOUNT = 10; 
unsigned const PWD_ARRAY_SIZE = 10;
unsigned const PWD_FLIP_CHAR_MAX_LENGTH = 9;
unsigned const LENGTH_LIMIT = 10;
unsigned const MAX_K = 9;
string const POSSIBLE_ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"%&'()*+,-./:;<=>?@[]\\^_`|{}~ $#";

void Read_File(string*); 
void Initialize_Obj_Arrays(Flip*, FlipPwdCheck*, FlipExcessC*, FlipCompundC*, string*);
void Test_Flip(Flip*, string*);
void Test_FlipPwdCheck(FlipPwdCheck*, string*);
void Test_FlipExcessC(FlipExcessC*, string*);
void Test_FlipCompundC(FlipCompundC*, string*);
 
int main()
{
	string Password_Array[PWD_ARRAY_SIZE];
	Read_File(Password_Array);
	
	Flip Flip_Obj_Array[TEST_OBJ_AMOUNT];
	FlipPwdCheck FlipPwdCheck_Obj_Array[TEST_OBJ_AMOUNT];
	FlipExcessC FlipExcessC_Obj_Array[TEST_OBJ_AMOUNT];
	FlipCompundC FlipCompundC_Obj_Array[TEST_OBJ_AMOUNT];
	Initialize_Obj_Arrays(Flip_Obj_Array, FlipPwdCheck_Obj_Array, FlipExcessC_Obj_Array, 
							FlipCompundC_Obj_Array, Password_Array);
							
	Test_Flip(Flip_Obj_Array, Password_Array);
	Test_FlipPwdCheck(FlipPwdCheck_Obj_Array, Password_Array);
	Test_FlipExcessC(FlipExcessC_Obj_Array, Password_Array);
	Test_FlipCompundC(FlipCompundC_Obj_Array, Password_Array);
	
	return 0;
}
void Read_File(string* Password_Array)
{ 
	cout << ASTERISK << endl;
	cout << "Reading passwords from file and storing them in an array " << endl;
	cout << ASTERISK << endl << endl;
	
	unsigned count = 0;
	ifstream input;
    string line;
	
	input.open(READFILE);
  
  //check that it is open/readable
  if(input.fail()){
    cout << endl << "Sorry, file not available...exiting program...press enter"
         << endl;
    cin.get();      //Grabs the enter;
    return;
  }
  while(getline(input, line))
  {
	istringstream ss(line);
	
	ss >> Password_Array[count];
	count++;
  }
	input.close();
}
void Initialize_Obj_Arrays(Flip* Flip_Obj_Array, FlipPwdCheck* FlipPwdCheck_Obj_Array, 
	FlipExcessC* FlipExcessC_Obj_Array, FlipCompundC* FlipCompundC_Obj_Array, string* Password_Array)
{
	cout << ASTERISK << endl;
	cout << "Creating an array of objects for each object type tested " << endl;
	cout << "Objects tested will be 'Flip', 'FlipPwdCheck', 'FlipExcessC', " << endl 
		 << "and 'FlipCompundC'" << endl;
	cout << ASTERISK << endl << endl;
		 
	srand (time(0));
	char ascii_char;
	unsigned k_state_changes = 0;
	unsigned length = 0;
	unsigned index = 0;
	for (unsigned i = 0; i < TEST_OBJ_AMOUNT; i++)
	{
		index = rand() % POSSIBLE_ASCII.length();
		ascii_char = POSSIBLE_ASCII[index];
		length = rand() % LENGTH_LIMIT;
		k_state_changes = rand() % MAX_K + 1;
		
		Flip_Obj_Array[i] = Flip(Password_Array[i]);
		FlipPwdCheck_Obj_Array[i] = FlipPwdCheck(Password_Array[i], length, ascii_char);
		FlipExcessC_Obj_Array[i] = FlipExcessC(Password_Array[i], length, ascii_char);
		FlipCompundC_Obj_Array[i] = FlipCompundC(Password_Array[i], length, ascii_char, k_state_changes);

        cout << "Storing password: " << Password_Array[i] << endl;
		cout << "Length requirement for passwords is: " 
			 << FlipPwdCheck_Obj_Array[i].Minimum_Password_Length() << endl;
		cout << "Forbidden Ascii is: " << ascii_char << endl;
		cout << "in Flip_obj: " << i << endl;
		cout << "in FlipPwdCheck_obj: " << i << endl;
		cout << "in FlipExcessC_obj: " << i << endl;
		cout << "in FlipCompundC_obj: " << i << endl << endl;
	}
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
}
void Test_Flip(Flip* Flip_Obj_Array, string* Password_Array)
{
	cout << ASTERISK << endl;
	cout << "Testing 'Flip' objects " << endl;
	cout << ASTERISK << endl << endl;
	
	srand (time(0));
	unsigned const FLIP_OBJ_TEST_AMOUNT = 10;
	unsigned flipped_char_num = 0;
	for (unsigned i = 0; i < FLIP_OBJ_TEST_AMOUNT; i++)
	{
		flipped_char_num = rand() % PWD_FLIP_CHAR_MAX_LENGTH;
		cout << "Object " << i << " password flipped before character #: " << flipped_char_num << endl; 
		cout << "Original password: " << Password_Array[i] << endl;
		cout << "Flipped password: " << Flip_Obj_Array[i].Flip_Password(flipped_char_num) << endl << endl;
	}
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
}
void Test_FlipPwdCheck(FlipPwdCheck* FlipPwdCheck_Obj_Array, string* Password_Array)
{
	cout << ASTERISK << endl;
	cout << "Testing 'FlipPwdCheck' objects" << endl;
	cout << ASTERISK << endl << endl;
	
	srand (time(0));
	unsigned const FLIP_PWD_CHECK_TEST_AMOUNT = 10;
	unsigned const OBJ_ZERO = 0;
	unsigned const OFF_STATE_CHECKS = 3;
	unsigned flipped_char_num = 0;
	string flipped_pwd;
	
	for (unsigned i = 0; i < FLIP_PWD_CHECK_TEST_AMOUNT; i++)
	{
		flipped_char_num = rand() % PWD_FLIP_CHAR_MAX_LENGTH;
		flipped_pwd = FlipPwdCheck_Obj_Array[i].Flip_Password(flipped_char_num);
		cout << "Object " << i << " password flipped before character #: " << flipped_char_num << endl; 
		cout << "Original password: " << Password_Array[i] << endl;
		cout << "Flipped password: " << flipped_pwd << endl;
		cout << "Is the flipped password acceptable?: ";
		if (!FlipPwdCheck_Obj_Array[i].Password_Check(Password_Array[i]))
		{
			cout << "False" << endl;
		}
		else
		{
			cout << "True" << endl;
		}
		cout << "Does the flipped password pass the password check?: ";
		if (!FlipPwdCheck_Obj_Array[i].Check_Flipped_Password(flipped_char_num))
		{
			cout << "False" << endl << endl;
		}
		else
		{
			cout << "True" << endl << endl;
		}
	}
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
	cout << ASTERISK << endl;
	cout << "Now testing object " << OBJ_ZERO << " and changing its state " << endl;
	cout << ASTERISK << endl << endl;
	
	for (unsigned i = 0; i < (FlipPwdCheck_Obj_Array[OBJ_ZERO].Minimum_Password_Length() - 1); i++)
	{
		cout << "State of object " << OBJ_ZERO << ": "; 
		if (!FlipPwdCheck_Obj_Array[OBJ_ZERO].isActive())
		{
			cout << "OFF" << endl;
		}
		else
		{
			cout << "ON" << endl;
		}
		FlipPwdCheck_Obj_Array[OBJ_ZERO].Check_Flipped_Password(flipped_char_num);
	}
		cout << endl;
		cout << ASTERISK << endl;
		cout << "State of object " << OBJ_ZERO << " should now be off " << endl;
		cout << "Giving the object any password should make it return false" << endl;
		cout << ASTERISK << endl << endl;
		
		for (unsigned i = 0; i < OFF_STATE_CHECKS; i++)
		{
			flipped_pwd = FlipPwdCheck_Obj_Array[i].Flip_Password(flipped_char_num);
			cout << "Password flipped before character #: " << flipped_char_num << endl; 
			cout << "Original password: " << Password_Array[i] << endl;
			cout << "Flipped password: " << flipped_pwd << endl;
			cout << "State of object " << OBJ_ZERO << ": "; 
			if (!FlipPwdCheck_Obj_Array[OBJ_ZERO].isActive())
			{
				cout << "OFF" << endl;
			}
			else
			{
				cout << "ON" << endl;
			}
			cout << "Is the flipped password acceptable?: ";
			if (!FlipPwdCheck_Obj_Array[OBJ_ZERO].Check_Flipped_Password(flipped_char_num))
			{
				cout << "False" << endl << endl;
			}
			else
			{
				cout << "True" << endl << endl;
			}
		}
	
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
}
void Test_FlipExcessC(FlipExcessC* FlipExcessC_Obj_Array, string* Password_Array)
{
	cout << ASTERISK << endl;
	cout << "Testing 'FlipExcessC' objects " << endl;
	cout << "Starts in OFF State, therefore acts like FlipPwdCheck" << endl;
	cout << ASTERISK << endl << endl;
	
	srand (time(0));
	unsigned const FLIP_EXCESSC_TEST_AMOUNT = 10;
	unsigned flipped_char_num = 0;
	string flipped_pwd;
	
	for (unsigned i = 0; i < FLIP_EXCESSC_TEST_AMOUNT; i++)
	{
		flipped_char_num = rand() % PWD_FLIP_CHAR_MAX_LENGTH;
		flipped_pwd = FlipExcessC_Obj_Array[i].Flip_Password(flipped_char_num);
		cout << "Object " << i << " password flipped before character #: " << flipped_char_num << endl; 
		cout << "Original password: " << Password_Array[i] << endl;
		cout << "Flipped password: " << flipped_pwd << endl;
		cout << "Is the flipped password acceptable?: ";
		if (!FlipExcessC_Obj_Array[i].Password_Check(Password_Array[i]))
		{
			cout << "False" << endl;
		}
		else
		{
			cout << "True" << endl;
		}
		cout << "Does the flipped password pass the password check?: ";
		if (!FlipExcessC_Obj_Array[i].Check_Flipped_Password(flipped_char_num))
		{
			cout << "False" << endl << endl;
		}
		else
		{
			cout << "True" << endl << endl;
		}
	}
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
	cout << ASTERISK << endl;
	cout << "Now changing the state of all FlipExcessC objects" << endl;
	cout << ASTERISK << endl << endl;
	
	for ( unsigned i = 0; i < FLIP_EXCESSC_TEST_AMOUNT; i++)
	{
		for (unsigned j = 0; j < (FlipExcessC_Obj_Array[i].Minimum_Password_Length() - 1); j++)
		{
			cout << "State of object " << i << ": "; 
			if (!FlipExcessC_Obj_Array[i].isActive())
			{
				cout << "OFF" << endl;
			}
			else
			{
				cout << "ON" << endl;
			}
			FlipExcessC_Obj_Array[i].Check_Flipped_Password(flipped_char_num);
		}
		cout << endl;
	}
	cout << endl;
	cout << ASTERISK << endl;
	cout << "State of all objects should now be 'ON' " << endl;
	cout << "Pth character must be a #, case needs to be mixed, and a dollar" << endl;
	cout << "sign needs to be in the password for the flipped Pwd to pass the check" << endl;
	cout << ASTERISK << endl << endl;
	
	for (unsigned i = 0; i < FLIP_EXCESSC_TEST_AMOUNT; i++)
	{
		flipped_char_num = rand() % PWD_FLIP_CHAR_MAX_LENGTH;
		flipped_pwd = FlipExcessC_Obj_Array[i].Flip_Password(flipped_char_num);
		cout << "Object " << i << " password flipped before character #: " << flipped_char_num << endl; 
		cout << "Original password: " << Password_Array[i] << endl;
		cout << "Flipped password: " << flipped_pwd << endl;
		cout << "State of object " << i << ": "; 
		if (!FlipExcessC_Obj_Array[i].isActive())
		{
			cout << "OFF" << endl;
		}
		else
		{
			cout << "ON" << endl;
		}
		cout << "Is the flipped password acceptable?: ";
		if (!FlipExcessC_Obj_Array[i].Password_Check(Password_Array[i]))
		{
			cout << "False" << endl;
		}
		else
		{
			cout << "True" << endl;
		}
		cout << "Does the flipped password pass the password check?: ";
		if (!FlipExcessC_Obj_Array[i].Check_Flipped_Password(flipped_char_num))
		{
			cout << "False" << endl << endl;
		}
		else
		{
			cout << "True" << endl << endl;
		}
	}
	
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
}
void Test_FlipCompundC(FlipCompundC* FlipCompundC_Obj_Array, string* Password_Array)
{
	cout << ASTERISK << endl;
	cout << "Testing 'FlipCompundC' objects " << endl;
	cout << "Like PwdCheck but also requires a repeated character" << endl;
	cout << "After K state toggles, the object can no longer toggle state" << endl;
	cout << ASTERISK << endl << endl;
	
	srand (time(0));
	unsigned const FLIP_COMPUNDC_TEST_AMOUNT = 10;
	unsigned max_state_changes = 0;
	unsigned flipped_char_num = 0;
	string flipped_pwd;
	
	for (unsigned i = 0; i < FLIP_COMPUNDC_TEST_AMOUNT; i++)
	{
		flipped_char_num = rand() % PWD_FLIP_CHAR_MAX_LENGTH;
		flipped_pwd = FlipCompundC_Obj_Array[i].Flip_Password(flipped_char_num);
		cout << "Object " << i << " password flipped before character #: " << flipped_char_num << endl; 
		cout << "K number of toggles for object " << i << ": " 
			 << FlipCompundC_Obj_Array[i].State_Change_Limit() << endl;
		cout << "Original password: " << Password_Array[i] << endl;
		cout << "Flipped password: " << flipped_pwd << endl;
		cout << "Is the flipped password acceptable?: ";
		if (!FlipCompundC_Obj_Array[i].Password_Check(Password_Array[i]))
		{
			cout << "False" << endl;
		}
		else
		{
			cout << "True" << endl;
		}
		cout << "Does the flipped password pass the password check?: ";
		if (!FlipCompundC_Obj_Array[i].Check_Flipped_Password(flipped_char_num))
		{
			cout << "False" << endl << endl;
		}
		else
		{
			cout << "True" << endl << endl;
		}
	}
	
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
	cout << ASTERISK << endl;
	cout << "Now changing the state of all FlipCompundC objects" << endl;
	cout << ASTERISK << endl << endl;
	
	for ( unsigned i = 0; i < FLIP_COMPUNDC_TEST_AMOUNT; i++)
	{
		for (unsigned j = 0; j < (FlipCompundC_Obj_Array[i].Minimum_Password_Length()); j++)
		{
			cout << "State of object " << i << ": "; 
			if (!FlipCompundC_Obj_Array[i].isActive())
			{
				cout << "OFF" << endl;
			}
			else
			{
				cout << "ON" << endl;
			}
			FlipCompundC_Obj_Array[i].Check_Flipped_Password(flipped_char_num);
		}
		cout << endl;
	}
	cout << endl;
	cout << ASTERISK << endl;
	cout << "State of all objects should now be 'OFF' " << endl;
	cout << "All passwords should be rejected and return false" << endl;
	cout << ASTERISK << endl << endl;
	
	for (unsigned i = 0; i < FLIP_COMPUNDC_TEST_AMOUNT; i++)
	{
		flipped_char_num = rand() % PWD_FLIP_CHAR_MAX_LENGTH;
		flipped_pwd = FlipCompundC_Obj_Array[i].Flip_Password(flipped_char_num);
		cout << "Object " << i << " password flipped before character #: " << flipped_char_num << endl; 
		cout << "Original password: " << Password_Array[i] << endl;
		cout << "Flipped password: " << flipped_pwd << endl;
		cout << "State of object " << i << ": "; 
		if (!FlipCompundC_Obj_Array[i].isActive())
		{
			cout << "OFF" << endl;
		}
		else
		{
			cout << "ON" << endl;
		}
		cout << "Is the flipped password acceptable?: ";
		if (!FlipCompundC_Obj_Array[i].Password_Check(Password_Array[i]))
		{
			cout << "False" << endl;
		}
		else
		{
			cout << "True" << endl;
		}
		cout << "Does the flipped password pass the password check?: ";
		if (!FlipCompundC_Obj_Array[i].Check_Flipped_Password(flipped_char_num))
		{
			cout << "False" << endl << endl;
		}
		else
		{
			cout << "True" << endl << endl;
		}
	}
	
	cout << "PRESS ENTER TO CONTINUE...";
	cin.get();
	cout << endl;
	cout << ASTERISK << endl;
	cout << "Will now toggle the state of all FlipCompundC objects K times" << endl;
	cout << "States of all objects should be locked and should continue to have locked" << endl;
	cout << "functionality of state the object is locked at" << endl;
	cout << ASTERISK << endl << endl;


	for ( unsigned i = 0; i < FLIP_COMPUNDC_TEST_AMOUNT; i++)
	{
		max_state_changes = (FlipCompundC_Obj_Array[i].Minimum_Password_Length() * FlipCompundC_Obj_Array[i].State_Change_Limit());
		
		for (unsigned j = 0; j < (max_state_changes - 1); j++)
		{
			cout << "State of object " << i << ": "; 
			if (!FlipCompundC_Obj_Array[i].isActive())
			{
				cout << "OFF" << endl;
			}
			else
			{
				cout << "ON" << endl;
			}
			FlipCompundC_Obj_Array[i].Check_Flipped_Password(flipped_char_num);
		}
		cout << endl;
	}

	for (unsigned i = 0; i < FLIP_COMPUNDC_TEST_AMOUNT; i++)
	{
		flipped_char_num = rand() % PWD_FLIP_CHAR_MAX_LENGTH;
		flipped_pwd = FlipCompundC_Obj_Array[i].Flip_Password(flipped_char_num);
		cout << "Object " << i << " password flipped before character #: " << flipped_char_num << endl; 
		cout << "Original password: " << Password_Array[i] << endl;
		cout << "Flipped password: " << flipped_pwd << endl;
		cout << "Is the flipped password acceptable?: ";
		if (!FlipCompundC_Obj_Array[i].Password_Check(Password_Array[i]))
		{
			cout << "False" << endl;
		}
		else
		{
			cout << "True" << endl;
		}
		cout << "Does the flipped password pass the password check?: ";
		if (!FlipCompundC_Obj_Array[i].Check_Flipped_Password(flipped_char_num))
		{
			cout << "False" << endl << endl;
		}
		else
		{
			cout << "True" << endl << endl;
		}
	}

	cout << "PRESS ENTER TO END PROGRAM...";
	cin.get();
	cout << endl;
	cout << "EXITING...THANK YOU!" << endl;
}
/*
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     
#include <time.h>
#include <sstream>

#include "pwdCheck.h"
#include "excessC.h"
#include "compundC.h"
#include "Flip.h"
#include "FlipPwdCheck.h"
#include "FlipExcessC.h"
#include "FlipCompundC.h"
 
using namespace std; 
 
const string READFILE = "test.txt";  
const string ASTERISK = "***********************************************************";
unsigned const TEST_FLIP_OBJ_AMOUNT = 8; 
unsigned const TEST_PWDCHECK_OBJ_AMOUNT = 9;
unsigned const PWD_ARRAY_SIZE = 10;
unsigned const PWD_FLIP_CHAR_MAX_LENGTH = 9;
unsigned const LENGTH_LIMIT = 10;
unsigned const MAX_K = 9;
string const POSSIBLE_ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"%&'()*+,-./:;<=>?@[]\\^_`|{}~ $#";

void Read_File(string*); 
void Initialize_Obj_Arrays(Flip**, pwdCheck**, string*);
void Deallocation(Flip**, pwdCheck**);
void Object_Identification(Flip**, pwdCheck**, string*);
void Test_Flip(Flip*, string);

int main()
{
	string Password_Array[PWD_ARRAY_SIZE];
	Read_File(Password_Array);
	Flip* Flip_Obj_Array[TEST_FLIP_OBJ_AMOUNT * PWD_ARRAY_SIZE];
	pwdCheck* pwdCheck_Obj_Array[TEST_PWDCHECK_OBJ_AMOUNT * PWD_ARRAY_SIZE];
	Initialize_Obj_Arrays(Flip_Obj_Array, pwdCheck_Obj_Array, Password_Array);
	Object_Identification(Flip_Obj_Array, pwdCheck_Obj_Array, Password_Array);
	//Deallocation(Flip_Obj_Array, pwdCheck_Obj_Array);
	return 0;
}
void Read_File(string* Password_Array)
{ 
	cout << ASTERISK << endl;
	cout << "Reading passwords from file and storing them in an array " << endl;
	cout << ASTERISK << endl << endl;
	
	unsigned count = 0;
	ifstream input;
    string line;
	
	input.open(READFILE);
  
  //check that it is open/readable
  if(input.fail()){
    cout << endl << "Sorry, file not available...exiting program...press enter"
         << endl;
    cin.get();      //Grabs the enter;
    return;
  }
  while(getline(input, line))
  {
	istringstream ss(line);
	
	ss >> Password_Array[count];
	count++;
  }
	input.close();
}
void Initialize_Obj_Arrays(Flip** Flip_Obj_Array, pwdCheck** pwdCheck_Obj_Array, string* Password_Array)
{
	cout << ASTERISK << endl;
	cout << "Creating two heterogeneous arrays of objects comprised of objects " << endl;
	cout << "Objects tested will be 'Flip', 'FlipPwdCheck', 'FlipExcessC', " << endl 
		 << "and 'FlipCompundC'" << endl;
	cout << ASTERISK << endl << endl;
	
	srand (time(NULL));
	unsigned FLIP_OBJ_RANGE = 2;
	unsigned FLIP_PWDCHECK_OBJ_RANGE = 4;
	unsigned FLIP_EXCESSC_OBJ_RANGE = 6;
	char ascii_char;
	unsigned k_state_changes = 0;
	unsigned length = 0;
	unsigned count = 0;
	unsigned index = 0;
	for (unsigned i = 0; i < TEST_FLIP_OBJ_AMOUNT; i++)
	{
		index = rand() % POSSIBLE_ASCII.length();
		ascii_char = POSSIBLE_ASCII[index];
		length = rand() % LENGTH_LIMIT;
		k_state_changes = rand() % MAX_K + 1;
		
		if (i < FLIP_OBJ_RANGE)
		{
			for (unsigned j = 0 ; j < PWD_ARRAY_SIZE ; j++)
			{
				Flip_Obj_Array[count] = new FlipPwdCheck(Password_Array[j], length, ascii_char);
				pwdCheck_Obj_Array[count] = new FlipPwdCheck(Password_Array[j], length, ascii_char);
				count++;
			}
		}
		else if (FLIP_OBJ_RANGE <= i && i < FLIP_PWDCHECK_OBJ_RANGE)
		{
			for (unsigned j = 0 ; j < PWD_ARRAY_SIZE ; j++)
			{
				Flip_Obj_Array[count] = new FlipExcessC(Password_Array[j], length, ascii_char);
				pwdCheck_Obj_Array[count] = new FlipExcessC(Password_Array[j], length, ascii_char);
				count++;
			}
		}
		else if (FLIP_PWDCHECK_OBJ_RANGE <= i && i < FLIP_EXCESSC_OBJ_RANGE)
		{
			for (unsigned j = 0 ; j < PWD_ARRAY_SIZE ; j++)
			{
				Flip_Obj_Array[count] = new FlipCompundC(Password_Array[j], length, ascii_char, k_state_changes);
				pwdCheck_Obj_Array[count] = new FlipCompundC(Password_Array[j], length, ascii_char, k_state_changes);
				count++;
			}
		}
		else
		{
			for (unsigned j = 0 ; j < PWD_ARRAY_SIZE ; j++)
			{
				Flip_Obj_Array[count] = new Flip(Password_Array[j]);
				count++;
			}
		}
	}
}

void Deallocation(Flip** Flip_Obj_Array, pwdCheck** pwdCheck_Obj_Array){
    for(unsigned i = 0; i < TEST_FLIP_OBJ_AMOUNT * PWD_ARRAY_SIZE; i++){
        delete Flip_Obj_Array[i];
    }

    for(unsigned j = 0; j < TEST_PWDCHECK_OBJ_AMOUNT * PWD_ARRAY_SIZE; j++){
        delete pwdCheck_Obj_Array[j];
    }
}

void Object_Identification(Flip** Flip_Obj_Array, pwdCheck** pwdCheck_Obj_Array, string* Password_Array)
{
	cout << "1" << endl;
	for (unsigned i = 0; i < TEST_FLIP_OBJ_AMOUNT * PWD_ARRAY_SIZE; i++)
	{
		cout << i << endl;
		if ((dynamic_cast<FlipCompundC*> (Flip_Obj_Array[i])) ||
			(dynamic_cast<FlipPwdCheck*> (Flip_Obj_Array[i])) ||
			(dynamic_cast<FlipExcessC*> (Flip_Obj_Array[i])))
		{
					cout << "dog" << endl;
		}
		else 
		{
			cout << "YES" << endl;
			Test_Flip(Flip_Obj_Array[i], Password_Array[i]);
		}
	}

	for (unsigned i = 0; i < TEST_FLIP_OBJ_AMOUNT * PWD_ARRAY_SIZE; i++)
	{
		if ((dynamic_cast<FlipCompundC*> (pwdCheck_Obj_Array[i])) ||
			(dynamic_cast<FlipPwdCheck*> (pwdCheck_Obj_Array[i])) ||
			(dynamic_cast<FlipExcessC*> (pwdCheck_Obj_Array[i])))
		{
				
		}
		else 
		{
			
		}
	}
}
void Test_Flip(Flip* Flip_Obj, string Password)
{
cout << Password << endl;
cout << Flip_Obj->Flip_Password(3) << endl;

}
*/