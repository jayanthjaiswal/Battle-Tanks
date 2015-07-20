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
// Authors: James P. Cohoon and Jack W. Davidson
// Date: 7/15/96
// $Revision: 1.3 $
// $Name: $
//
//**************************************************************************
// Class Label interface


#ifndef LABEL_H
#define LABEL_H

// MSVC++ 4.0 does not support the string class
#include <string.h>
#include "shape.h"

#ifdef NAMESPACE
using namespace std;
#endif

class Label : public WindowObject {
	public:

		Label(SimpleWindow &Window, const Position &p,
		 const string &Text, const color &TextColor = Black,
       const color &c = White);
		Label(SimpleWindow &Window, float XCoord, float YCoord,
		 const string &Text, const color &TextColor = Black,
       const color &c = White);
		Label(SimpleWindow &Window, const Position &p,
		 const char *Text, const color &TextColor = Black,
       const color &c = White);
		Label(SimpleWindow &Window, float XCoord, float YCoord,
		 const char *Text, const color &TextColor = Black,
       const color &c = White);
      ~Label();
		color GetColor() const;
		void SetColor(const color &c);
		void Draw();
      void Erase();
	private:
		color BackgroundColor;
      color TextColor;
		string Text;
};
#endif

