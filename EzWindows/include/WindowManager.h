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
   FILE:        WindowManager.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/25 15:16:20 dcl3a>

   Description
   ===========
   This file contains the class declarations of DispatchListEntry and  
   WindowManager and some function headers.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    DispatchListEntry
//
// Purpose:
//    Provides the capability to make a list of windows
//
// Member functions:
//    Private members:
//       SimpleWindow(const string   &WindowTitle    = NoTitle,
//                    float           Width          = DefaultWidth, 
//                    float           Height         = DefaultHeight,
//                    const Position &WindowPosition = LogicalOrigin)
//          Initializes the member variables
//          -- The first parameter specifies the title of the window.
//          -- The second parameter specifies the width of the window in 
//             centimeters.
//          -- The third parameter specifies the height of the window in
//             centimeters.
//          -- The forth parameter specifies the location of the upper 
//             left corner of the window in centimeters.
//       DispatchListEntry(SimpleWindow      *iPtrSimpleWindow, 
//                         DispatchListEntry *HeadOfList = NULL)
//          Initializes member variables
//          -- The first parameter specifies the window for this node.
//          -- The second parameter specifies what to connect on to the tail
//             this node.
//      ~DispatchListEntry()
//          Does nothing
//
// Instance Variables:
//    PtrSimpleWindow
//       A pointer to a SimpleWindow specifying the window of this node
//    Next
//       A pointer to a DispatchListEntry specifying the next node in the 
//       list
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Class name:
//    WindowManager
//
// Purpose:
//    Provides the capability to manupulate a collection of window
//
// Member functions:
//    Public members:
//       WindowManager()
//          Initializes member variables, opens the display, and obtains 
//          colors
//      ~WindowManager()
//          Closes any stray windows and closes the display
//       Bool Empty() const
//          Returns True if there are no windows open. Otherwise, False is
//          returned
//       Bool ColorsObtained() const
//          Returnes True if the colors needed for this application were
//          obtained successfully. Otherwise, False is returned
//       Bool IsApiMainCompleted() const
//          Returns True is ApiMain has been completed. Returns False if 
//          ApiMain is still in progress.
//       void CheckTimers()
//          Checks to see if there are any active timer. If a timer is 
//          active, it is checked to see if it has expired.
//       SimpleWindow* GetWindow(const Window &WindowHandle) const
//          Returns the window with the window handle, WindowHandle
//          -- The parameter specifies the window handle of the window to
//             return.
//       SimpleWindow* GetWindow(const XEvent &Report) const
//          Returns the window that the event Report occured on
//          -- The parameter specifies a window event
//       Window GetWindow(const SimpleWindow *WindowObject) const
//          Returns the window handle of the window passed as a parameter
//          -- The parameter specifies the window object to obtain the
//             window handle from.
//       Bool Register(SimpleWindow *PtrSimpleWindow)
//          Adds a window to the list of windows
//          -- The parameter specifies the window to add to the list.
//       Bool Unregister(const Window &window)
//          Removes a window from the list
//          -- The parameter specifies the window handle of the window to 
//             remove. 
//       DispatchStatus CloseAWindow(SimpleWindow *Win)
//          Closes the window specified by the parameter passed.
//          -- The parameter specifies the window to close.
//       void DescribeContents() const
//          Lists the window handles of the windows in the list
//       void CheckEvents()
//          Checks to see if events have occured. If window events have 
//          occured they are handled.
//       DispatchStatus DispatchMessage(XEvent &Report, SimpleWindow *Win)
//          Handles window events
//          -- The first parameter specifies the window event that occured.
//          -- The second parameter specifies the window that the event
//             occured on.
//       void ApiMainIsCompleted()
//          Lets the window manager know that ApiMain has been completed
//       void Terminate()
//          Puts a request to close each of the open windows into the event
//          queque.
//
//    Private members:
//       Bool InitializeColors(const char       **FirstChoice, 
//                             const char       **SecondChoice,
//                             unsigned long int *Table,
//                             int                NbrColors)
//          Obtains colors from the server. Returns True if successful and
//          False otherwise.
//          -- The first parameter specifies an array of first choice 
//             colors.
//          -- The second parameter specifies an array of second choice 
//             colors.
//       ManagerStatus CheckTermination()
//          Checks to see if there are any open windows. If not, ApiEnd is 
//          called. Otherwise, nothing happens.
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Additional functions:
//    void Terminate()
//       Calls the terminate function for the window manager which closes
//       all of the windows and end the program
//-----------------------------------------------------------------------//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "MessageGraphic.h"
#include "Alert.h"
#include "SimpleWindow.h"
#include <stdlib.h>

#ifndef USING_CC
#include <cmath>
#include <time.h>
#else
#include <math.h>
#include <sys/time.h>
#endif


const int  ClockError      = -1;
const int  OneSecond       = 1000;
const int  DisplayLengthCM = 29;
const int  MilliSec        = 1000;
const long MicroSec        = 1000000L;
           
enum ManagerStatus  {Quit, Running};
enum DispatchStatus {EndProgram, Handled, UnHandled};


//-----------------------------------------------------------------------\\
//  D i s p a t c h L i s t E n t r y  C l a s s                         \\

class DispatchListEntry {   
   private:
      DispatchListEntry(SimpleWindow      *iPtrSimpleWindow, 
                        DispatchListEntry *HeadOfList = NULL);
     ~DispatchListEntry();

      SimpleWindow      *PtrSimpleWindow;      
      DispatchListEntry *Next;

   friend class WindowManager;
};


//-----------------------------------------------------------------------\\
//  W i n d o w M a n a g e r  C l a s s                                 \\
  
class WindowManager {
   public:
      WindowManager();
     ~WindowManager();

      Bool Empty             () const;
      Bool ColorsObtained    () const;
      Bool IsApiMainCompleted() const;      

      void CheckTimers();      

      SimpleWindow* GetWindow(const Window       &window)       const;
      SimpleWindow* GetWindow(const XEvent       &Report)       const;
      Window        GetWindow(const SimpleWindow *WindowObject) const;

      Bool           Register    (SimpleWindow *PtrSimpleWindow);
      Bool           Unregister  (const Window &window);
      DispatchStatus CloseAWindow(SimpleWindow *Win); 

      void           DescribeContents() const;
      void           CheckEvents     ();       
      DispatchStatus DispatchMessage (XEvent &Report, SimpleWindow *Win);

      void ApiMainIsCompleted();
      void Terminate         ();

  private:
      Bool ColorsMatched;
      Bool ApiMainCompleted;

      unsigned int       ListSize;
      DispatchListEntry *DispatchList;

      Bool InitializeColors(const char       **FirstChoice, 
                            const char       **SecondChoice,
                            unsigned long int *Table,
                            int                NbrColors);
      ManagerStatus CheckTermination();
};


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

void Terminate();

                        
#endif
