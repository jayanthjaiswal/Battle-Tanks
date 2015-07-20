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
/* EzWindows Library Header File
   FILE:        dstring.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/26 19:50:06 dcl3a>

   Description
   ===========
   This file contains the class declarations of string.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    string
//
// Purpose:
//    Provides the ability to manipulate character arrays easily
//
// Member functions:
//    Public members:
//       string()
//          Initializes member variables
//       string(int iLength)
//          Creates an empty string with memory allocated for iMaxLength
//          characters
//          -- The parameter specifies the maximum number of characters
//             this string will contain.
//       string(const char *iString)
//          Promotes a character array into a string
//          -- The parameter specifies the contents of the string.
//       string(const string &Copy)
//          Copy constructor
//          -- The parameter specifies the string to copy.
//      ~string()
//          Deallocates the memory devoted to the character array
//       void set(const char *NewString)
//          Changes the internal character array to the one passed by 
//          parameter
//          -- The parameter specifies the new contents of the string.      
//       int length() const
//          Returns the length in characters of the string
//       const char* c_str() const
//          Returns the contents of the string
//       char& operator[] (int Position) const
//          Returns the character at the indicated position
//          -- The parameter specifies the index of the character to return
//       int operator== (const string &Other) const
//          Tests for equality between this string and another string
//          -- The parameter specifies the other string
//       int operator!= (const string &Other) const
//          Tests for inequality between this string and another string
//          -- The parameter specifies the other string
//       int operator< (const string &Other) const
//          Tests case sensitive whether this string is alphabetically less 
//          than another string
//          -- The parameter specifies the other string
//       int operator<= (const string &Other) const
//          Tests case sensitive whether this string is alphabetically less 
//          than or equal to another string
//          -- The parameter specifies the other string
//       int operator> (const string &Other) const
//          Tests case sensitive whether this string is alphabetically 
//          greater than another string
//          -- The parameter specifies the other string
//       int operator>= (const string &Other) const
//          Tests case sensitive whether this string is alphabetically 
//          greater than or equal to another string
//          -- The parameter specifies the other string
//       string operator+ (const string &Other) const
//          Adds this string with another string and returns the new string
//          -- The parameter specifies the other string
//       string& operator= (const string &Other)
//          Assigns another string to this string
//          -- The parameter specifies the other string
//       string& operator+= (const string &Other)
//          Concatenates another string onto the end of this string
//          -- The parameter specifies the other string
//
// Instance Variables:
//    String
//       A character array specifying the contents of the string
//    Length
//       An integer specifying the length in number of characters of the 
//       string
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Additional functions:
//    istream& operator>> (istream &InStream,  string &InString)
//       Handles instream manipulation of strings
//       -- The first parameter specifies the in stream being used
//       -- The second parameter specifies the string being manipulated
//          by the stream.
//    ostream& operator<< (ostream &OutStream, const string &OutString)
//       Handles outstream manipulation of strings
//       -- The first parameter specifies the out stream being used
//       -- The second parameter specifies the string being inserted into
//          the out stream.
//-----------------------------------------------------------------------//

#ifndef DSTRING_H
#define DSTRING_H

#include <iostream.h>
#include <string.h>
#include <stdlib.h>


const int  DefaultLength = 20;
const char NullCharacter = (char) 0;


//-----------------------------------------------------------------------\\
//  s t r i n g   C l a s s                                              \\

class string {
   public:
      string();
      string(int iLength);
      string(const char *iString);
      string(const string &Copy);
     ~string();

      void set(const char *NewString);

      int         length() const;
      int size() const;
      int find(char c) const;
      string substr(int begin, int length) const;
      const char* c_str()  const;
      char&  operator[] (int Position)        const;
      int    operator== (const string &Other) const;
      int    operator!= (const string &Other) const;
      int    operator<  (const string &Other) const;
      int    operator<= (const string &Other) const;
      int    operator>  (const string &Other) const;
      int    operator>= (const string &Other) const;
      string operator+  (const string &Other) const;

      string& operator=  (const string &Other);
      string& operator+= (const string &Other);

   private:
      char *String;
      int   Length;
};


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

istream& operator>> (istream &InStream, string &InString);
ostream& operator<< (ostream &OutStream, const string &OutString);
void getline(istream &InStream, string &InString, char TerminalChar);

#endif
