//**************************************************************************
//
// Copyright (c) 1997.
//      Richard D. Irwin, Inc.
//
// This software may not be distributed further without permission from
// Richard D. Irwin, Inc.
//
// This software is distributed WITHOUT ANY WARRANTY. No claims are made
// as to its functionality or purpose.
//
// Author: Devon Lockwood
// Date: 1/30/97
// $Revision: 1.1 $
// $Name: $
//
//**************************************************************************
/* EzWindows Library Source File
   FILE:        dstring.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/26 19:49:58 dcl3a>

   Description
   ===========
   Source file for the implementation of the string class.
*/  
#include "dstring.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern void Terminate();


//-----------------------------------------------------------------------\\
//  s t r i n g  C o d e                                                 \\

//-------------------------------------------------------------------------
//  s t r i n g
// Function:       Initializes member variables
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: Member variables are initialized
// Returns:        None

string::string() : Length(DefaultLength), String(NULL) {

   String = new char[DefaultLength + 1];
   if (!String) {
      cout << "Unable to allocate memory for an array of size "
           << DefaultLength + 1 << endl;
      exit(1);
      return;
   }

   String[0] = NullCharacter;
}


//-------------------------------------------------------------------------
//  s t r i n g
// Function:       Initializes member variables and gives the string a
//                 specified length
// Parameters:     iLength, a integer specifying the amount of memory to
//                    allocate for the string
// Preconditions:  iLength must be greater than zero
// Output:         If iLength is less than zero or memory can't be 
//                 allocated for a string of iLength + 1, a message is sent
//                 to standard output.
// Postconditions: Member variables are initialized and String is allocated
//                 for iLength characters
// Returns:        None

string::string(int iLength) : Length(DefaultLength), String(NULL) {
	
   if (iLength <= 0)
      cout << "Unable to allocate memory for an array of size "
	   << iLength << endl
           << "Using a default length of " << DefaultLength << endl;
   else
      Length = iLength;

   String = new char[Length + 1];
   if (!String) {
      cout << "Unable to allocate memory for an array of size "
           << Length + 1 << endl;
      exit(1);
      return;
   }

   String[0] = NullCharacter;
}


//-------------------------------------------------------------------------
//  s t r i n g
// Function:       Initializes the string with a character array
// Parameters:     iString, a character array specifying the contents of 
//                    the new string
// Preconditions:  iString must point to valid memory.
// Output:         If iString doesn't point to valid memory, a message
//                 is sent to standard output.
// Postconditions: Member variables are initialized based on the character
//                 array passed as a parameter.
// Returns:        None

string::string(const char *iString) : Length(DefaultLength), String(NULL) {

   if (iString) {
      Length = strlen(iString);
      String = new char[Length + 1];

      if (!String) {
         cout << "Unable to allocate memory for an array of size " 
              << Length + 1 << endl;
         exit(1);
         return;
      }

      strcpy (String, iString);
   }
   else {
      cout << "A character array pointing to NULL was passed to a "
           << "string constructor\nInitializing with defaults\n";
      String = new char[Length + 1];
      String[0] = NullCharacter;
      } 
}


//-------------------------------------------------------------------------
//  s t r i n g
// Function:       Copy constructor
// Parameters:     Copy, a string specifying the string to copy
// Preconditions:  None
// Output:         If memory can't be allocated for the copy, a message
//                 is sent to standard output.
// Postconditions: A copy of the string passed as a parameter is made.
// Returns:        None

string::string(const string &Copy) : Length(Copy.Length), String(NULL) {

   String = new char[Copy.Length + 1];
   if (!String) {
      cout << "Unable to allocate memory for an array of size "
           << Copy.Length + 1 << endl;
      exit(1);
      return;
   }

   strcpy(String, Copy.String);
}


//-------------------------------------------------------------------------
//  ~ s t r i n g
// Function:       Deallocates memory devoted to th3e character array
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: Memory has been deallocated that was once devoted to
//                 the internal representation of the string
// Returns:        None

string::~string() {

   if (String)
      delete [] String;
}


//-------------------------------------------------------------------------
//  s e t
// Function:       Sets the contents of the string
// Parameters:     iString, a character array specifying the new contents
//                    of the string
// Preconditions:  iString must point to valid memory.
// Output:         If either iString was NULL or memory could not be
//                 allocated, a message is ent to standard output.
// Postconditions: The new contents of this string is iString.
// Returns:        None

void string::set(const char *iString) {
   int NewStringLength(strlen(iString));

   if (iString) {
      if (NewStringLength > Length) {
         if (String)
            delete [] String;

         String = new char[NewStringLength + 1];
         if (!String) {
            cout << "Unable to allocate memory for an array of size "
                 << NewStringLength + 1 << endl;
            exit(1);
            return;
         }

         Length = NewStringLength;
      }

      strcpy(String, iString);
   }
   else {
      cout << "A character array pointing to NULL was passed to a "
           << "string set\nSetting with defaults";
      if (!String) {
         Length = DefaultLength;
         String = new char[DefaultLength + 1];
         if (!String) {
            cout << "Unable to allocate memory for an array of size "
                 << NewStringLength + 1 << endl;
            exit(1);
            return;
         }
         
         String[0] = NullCharacter;
      }
   }
}


//-------------------------------------------------------------------------
//  l e n g t h
// Function:       Returns the length of the string in characters
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The length of the string

int string::length() const {

   return strlen(String);
}

int string::size() const {

   return strlen(String);
}

int string::find(char c) const {

   int length = strlen(String);
   for(int i = 0; i < length; i++) {
      if (String[i] == c) {
         return i;
      }
   }
   return length;
}

string string::substr(int begin, int length) const {

   string* NewString;
   NewString = new string();
   char StringBuffer[256];
   for (int i = 0; i < length; i++) {
      StringBuffer[i] = String[begin + i];
   }
   StringBuffer[length] = 0;
   NewString->set(StringBuffer);
   return *NewString;
}

//-------------------------------------------------------------------------
//  c _ s t r
// Function:       Returns the character array that is the internal
//                 representation
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The character array of this string

const char* string::c_str() const {

   return String;
}


//-------------------------------------------------------------------------
//  o p e r a t o r [ ] 
// Function:       Returns the character at the specified position
// Parameters:     Position, an integer specifying the index into the 
//                    internal character array
// Preconditions:  Position must be greater than zero and less than or
//                 equal to the string length
// Output:         If Position is out of bounds, a message is sent to 
//                 standard output 
// Postconditions: None
// Returns:        The character at Position 

char& string::operator[] (int Position) const {
	
   if ((Position < 0) || (Position >= Length)) {
      cout << "Attempted to index a string out of bounds.\n";
      exit(1);
      return String[0];
   }

   return String[Position];
}


//-------------------------------------------------------------------------
//  o p e r a t o r = = 
// Function:       Test for equality
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        1, the two strings are equal. Otherwise, 0.

int string::operator== (const string &Other) const {
	
   return (strcmp(Other.String, String) == 0);
}


//-------------------------------------------------------------------------
//  o p e r a t o r ! = 
// Function:       Test for inequality
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        1, the two strings aren't equal. Otherwise, 0.

int string::operator!= (const string &Other) const {
	
   return (!(operator==(Other)));
}


//-------------------------------------------------------------------------
//  o p e r a t o r < 
// Function:       Test to see if this string is case sensitive less than
//                 another string
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        1, this string is less than the other. Otherwise, 0.

int string::operator< (const string &Other) const {
	
   return (strcmp(String, Other.String) < 0);
}


//-------------------------------------------------------------------------
//  o p e r a t o r < = 
// Function:       Test to see if this string is case sensitive less than
//                 or equal to another string
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        1, this string is less than or equal to the other. 
//                 Otherwise, 0.

int string::operator<= (const string &Other) const {
	
   return ((operator<(Other)) || (operator==(Other)));
}


//-------------------------------------------------------------------------
//  o p e r a t o r >
// Function:       Test to see if this string is case sensitive greater
//                 than another string
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        1, this string is greater than the other. Otherwise, 0.

int string::operator> (const string &Other) const {
	
   return (!(operator<=(Other)));
}


//-------------------------------------------------------------------------
//  o p e r a t o r > =
// Function:       Test to see if this string is case sensitive greater
//                 than or equal to another string
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        1, this string is greater than or equal the other. 
//                 Otherwise, 0.

int string::operator>= (const string &Other) const {
	
   return (!(operator<(Other)));
}


//-------------------------------------------------------------------------
//  o p e r a t o r +
// Function:       Makes a new string by adding another string to this one
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         If unable to allocate memory for the new string, a 
//                 message is sent to standard ouput 
// Postconditions: Upon successful completion, a new string is created.
//                 Otherwise, the program is terminated.
// Returns:        The new string

string string::operator+ (const string &Other) const {
   char *NewString(new char[length() + Other.length() + 1]);

   if (!NewString) {
      cout << "Unable to allocate memory for an array of size "
           << Other.length() + length() + 1 << endl;
      exit(1);
      return *this;
    }

    strcpy(NewString, String);
    strcat(NewString, Other.String);

    string Temp(NewString);
    delete [] NewString;
    return Temp;
}


//-------------------------------------------------------------------------
//  o p e r a t o r + = 
// Function:       Concatenates another string to this one
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         None
// Postconditions: Upon successful completion, this string has the other 
//                 string appended to it. Otherwise, the program is 
//                 terminated.
// Returns:        This string

string& string::operator+= (const string &Other) {
	
   set((operator+(Other)).String);
   return *this;
}


//-------------------------------------------------------------------------
//  o p e r a t o r =
// Function:       Assigns another string to this one
// Parameters:     Other, a string specifying the other string
// Preconditions:  None
// Output:         If unable to allocate memory, a message is sent to
//                 standard ouput 
// Postconditions: Upon successful completion, this string has been 
//                 modified making it equal to the other string. 
//                 Otherwise, the program is terminated.
// Returns:        This string

string& string::operator=(const string &Other) {

   if (Length < Other.length()) {
      if (String)
         delete [] String;

      Length = Other.length();
      String = new char[Length + 1];
      if (!String) {
         cout << "Unable to allocate memory for an array of size "
              << Other.length() + 1 << endl;
         exit(1);
         return *this;
      }
   }

   strcpy(String, Other.String);
   return *this;
}


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

//-------------------------------------------------------------------------
//  o p e r a t o r > >
// Function:       Handles in stream manipulation of a string
// Parameters:     InString, a string specifying the string to modify
// Preconditions:  None
// Output:         If unable to allocate memory, a message is sent to
//                 standard ouput
// Postconditions: Upon successful completion, the string contains
//                 information from the stream. Otherwise, the program is
//                 terminated.
// Returns:        The in stream used

istream& operator>> (istream &InStream, string &InString) {
   char Buffer[256];

   InStream >> Buffer;
   InString.set(Buffer);

   return InStream;
}


//-------------------------------------------------------------------------
//  o p e r a t o r < <
// Function:       Handles out stream manipulation of a string
// Parameters:     InString, a string specifying the string to put into
//                    the out stream
// Preconditions:  None
// Output:         None
// Postconditions: The out stream contains the string
// Returns:        The out stream used

ostream& operator<< (ostream &OutStream, const string &OutString) {

   OutStream << OutString.c_str();
   return OutStream;
}

void getline(istream &InStream, string &InString, char TerminalChar) {

   char TempCharacter;
   char BufferString[256];
   cin.getline(BufferString, 256, TerminalChar);
   InString.set(BufferString);
   return;
}

