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
/* EzWindows Library Header Filer
   FILE:        SimpleWindow.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/24 12:51:03 dcl3a>

   Description
   ===========
   This file contains the class declaration of SimpleWindow and some 
   function headers.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    SimpleWindow
//
// Purpose:
//    Encapsulates methods for creating and manipulating windows
//
// Member functions:
//    Public members:
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
//       SimpleWindow(const SimpleWindow &CopyWindow)
//          Displays an alert box and terminates the program. 
//          SimpleWindow objects should not be copied.
//          -- The parameter specifies the SimpleWindow to copy. 
//      ~SimpleWindow()
//          Closes the window.
//       SimpleWindow operator=(const SimpleWindow &NewWindow)
//          Displays an alert box and terminates the program. Assignment 
//          of SimpleWindow objects not allowed.
//          -- The parameter specifies the new window.
//       WindowStatus Open()
//          Creates the graphical window and displays it
//       WindowStatus Close()
//          Stops the timer if it is active, destroys the window, and
//          removes it from the display
//       WindowStatus GetStatus() const
//          Returns the status of the window. A window is either open or
//          closed or an error has occured.
//       void DrawBitMap(const Pixmap   &PixelMap,
//                       const Position &UpperLeft,
//                       const Position &Size)
//          Draws a bitmap in the window
//          -- The first parameter specifies the data that constitutes
//             the bitmap.
//          -- The second parameter specifies the location of the upper
//             left corner of the bitmap in centimeters.
//          -- The third parameter specifies the dimensions of the bitmap
//             in centimeters.
//       void Erase(const Position &UpperLeft,
//                  float           Width,
//                  float           Height,
//                  const color    &Color = DefaultColor)
//          Draws a rectangle to cover up something in the window
//          -- The first parameter specifies the location in centimeters
//             of the upper left corner of the rectangle to draw.
//          -- The second parameter specifies the width in centimeters of
//             the rectangle to draw.
//          -- The third parameter specifies the height in centimeters of
//             the rectangle to draw.
//          -- The forth parameter specifies the color of the rectangle
//             to draw.
//       void RenderRectangle(const Position &UpperLeft,
//                            const Position &LowerRight,
//                            const color    &FillColor = DefaultColor,
//                            const bool     Border = false)
//          Draws a rectangle with a black border
//          -- The first parameter specifies the location in centimeters
//             of the upper left corner of the rectangle.
//          -- The second parameter specifies the location in centimeters
//             of the lower right corner of the rectangle.
//          -- The third parameter specifies the fill color of the
//             rectangle.
//          -- The fourth parameter specifies whether or not the rectangle
//             will be drawn with a black outline.
//       void RenderLine(const Position &Base,
//                       const Position &Endpoint,
//                       const color    &Color,
//                       const float    LineWidth)
//          Draws a line
//          -- The first parameter specifies the location in centimeters
//             of one endpoint of the line.
//          -- The second parameter specifies the location in centimeters
//             of the other endpoint of the line.
//          -- The third parameter specifies the color of the line.
//          -- The fourth paramter specifies the line width in centimeters.
//       void RenderEllipse(const Position &UpperLeft,
//                          const Position &LowerRight,
//                          const color    &FillColor = DefaultColor,
//                          const bool     Border = false)
//          Draws an ellipse with a black border
//          -- The first parameter specifies the location in centimeters
//             of the upper left corner of a bounding box.
//          -- The second parameter specifies the location in centimeters
//             of the lower right corner of a bounding box.
//          -- The third parameter specifies the fill color of the
//             ellipse.
//          -- The fourth parameter specifies whether or not the ellipse
//             will be drawn with a black outline.
//       void RenderPolygon(const Position PolyPoints[],
//                          int            NbrPoints,
//                          const color    &FillColor = DefaultColor,
//                          const bool     Border = false)
//          Draws a polygon with a black border
//          -- The first parameter specifies an array of logical locations
//             that make up the vertices of the polygon.
//          -- The second parameter specifies the number of vertices that
//             the polygon has.
//          -- The third parameter specifies the fill color of the polygon.
//          -- The fourth parameter specifies whether or not the polygon
//             will be drawn with a black outline.
//       void RenderPolygon(const vector<Position> PolyPoints[],
//                          int                    NbrPoints,
//                          const color            &FillColor = DefaultColor,
//                          const bool             Border = false)
//          Draws a polygon with a black border
//          -- The first parameter specifies a vector of logical locations
//             that make up the vertices of the polygon.
//          -- The second parameter specifies the number of vertices that
//             the polygon has.
//          -- The third parameter specifies the fill color of the polygon.
//          -- The fourth parameter specifies whether or not the polygon
//             will be drawn with a black outline.
//       void RenderText(const Position &UpperLeft,
//                       const Position &LowerRight,
//                       const string   &Message         = DefaultMessage,
//                       const color    &BackgroundColor = DefaultColor)
//          Draws text
//          -- The first parameter specifies the logical location for the
//             upper left corner of an invisible box used to center the 
//             text.
//          -- The second parameter specifies the logical location for the
//             lower right corner of an invisible box used to center the 
//             text.
//          -- The third parameter specifies the message that is the text.
//          -- The forth parameter specifies the background color of the 
//             text.
//       void Message(const string &Message = DefaultMessage)
//          Generates an alert box with the message passed as a parameter.
//          -- The parameter specifies the message to put in the alert box.
//       float GetWidth() const
//          Returns the logical width of the window
//       float GetHeight() const
//          Returns the logical height of the window
//       float GetXPosition() const
//          Returns the logical x coordinate of the upper left corner of the
//          window
//       float GetYPosition() const
//          Returns the logical y coordinate of the upper left corner of the
//          window
//       Position GetCenter() const
//          Returns the logical position of the center of the window
//       Position GetPosition() const
//          Returns the logical position of the upper left corner of the 
//          window
//       int StartTimer(int Interval)
//          Starts the interval timer associated with this window. Each time
//          the timer expires, the function set by SetTimerCallback get 
//          called.
//       void StopTimer()
//          Stops the interval timer associated with this window.
//       void SetQuitCallback(const QuitCallbackFunction &Callback)
//          Sets the function that will be called when the window is closed
//       void SetTimerCallback(const TimerTickCallbackFunction &Callback)
//          Sets the function that will be called when the timer expires
//       void SetRefreshCallback(const RefreshCallbackFunction &Callback)
//          Sets the function that will be called when the window is 
//          damaged 
//       void SetMouseClickCallback(const MouseClickCallbackFunction &Callback)
//          Sets the function that will be called when a mouse click occurs
//
//    Protected members:
//       virtual int QuitEvent()
//          Calls the function associated with the window closing
//       virtual int RefreshEvent()
//          Calls the function assoicated with the window being exposed
//       virtual int MouseClickEvent(const Position &MousePosn)
//          Calls the function associated with mouse clicks
//       virtual Bool TimerEvent()
//          Calls the function associated with the timer expiring
//
//    Private members:
//       void CheckTimer()
//          Checks to see if the timer has expired. If the timer has expired,
//          the timer callback function is called.
//       void ConfigureEvent(const XEvent &Report)
//
// Instance Variables:
//    window
//       A Window specifying the window handle
//    Title
//       A string specifying the title of the window
//    WinStatus
//       A WindowStatus specifying whether the window is open, closed, or
//       an error has occured
//    RefreshCallback
//       A RefreshCallbackFunction specifying the function to call when
//       the window is exposed. (Default function refreshes screen from
//       screen buffer.)
//    QuitCallback
//       A QuitCallbackFunction specifying the function to call when the
//       window is closed
//    TimerCallback
//       A TimerTickCallbackFunction specifying the function to call when
//       the timer expires
//    MouseClickCallback
//       A MouseClickCallbackFunction specifying the function to call when 
//       a mouse click occurs
//    TimerActive
//       A Bool specifying whether the timer is active 
//    AlarmTime
//       An unsigned long int specifying how many milliseconds pass before
//       the timer expires
//    OldTime
//       A long specifying the amount of time that has elapsed since the 
//       last time the timer was checked
//    WinX
//       An integer specifying the device x coordinate for the location of
//       the upper left corner of the window
//    WinY
//       An integer specifying the device y coordinate for the location of
//       the upper left corner of the window
//    WinWidth
//       An integer specifying the device width of the window
//    WinHeight
//       An integer specifying the device height of the window
//    LogX
//       A float specifying the logical x coordinate for the location of
//       the upper left corner of the window
//    LogY
//       A float specifying the logical y coordinate for the location of
//       the upper left corner of the window
//    LogWidth
//       A float specifying the logical width of the window
//    LogHeight
//       A float specifying the logical height of the window
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Additional functions:
//    int ApiMain()
//       The user defined main function used to interface this library
//    int ApiEnd()
//       The user defined end function used to handle any clean up duties
//       before the program ends
//    long GetMilliseconds()
//       Returns the number of milliseconds that have passed since 00:00
//       Universal Coordinated Time, January 1, 1970.
//-----------------------------------------------------------------------//

#ifndef SIMPLEWINDOW_H
#define SIMPLEWINDOW_H

#include "Constants.h"
#include <vector>


const int    DefaultWidth    = 8;
const int    DefaultHeight   = 8;

#ifndef USING_CC
const color  DefaultColor     (White);
const string DefaultMessage   ("Message");
#else
const color  DefaultColor    = White;
const string DefaultMessage  = "Message";
#endif

typedef int (*TimerTickCallbackFunction) ();
typedef int (*MouseClickCallbackFunction)(const Position &);
typedef int (*RefreshCallbackFunction)   ();
typedef int (*QuitCallbackFunction)      ();


//-----------------------------------------------------------------------\\
//  S i m p l e W i n d o w   C l a s s                                  \\

class SimpleWindow {
   public:
      SimpleWindow(const string &WindowTitle,
       float Width = DefaultWidth, float Height = DefaultHeight,
       const Position &WindowPosition = LogicalOrigin);
      SimpleWindow(const char* WindowTitle = "Untitled",
       float Width = DefaultWidth, float Height = DefaultHeight,
       const Position &WindowPosition = LogicalOrigin);
      SimpleWindow(const SimpleWindow &CopyWindow);
     ~SimpleWindow();

      SimpleWindow operator=(const SimpleWindow &NewWindow);

      WindowStatus Open ();
      WindowStatus Close();

      WindowStatus GetStatus() const;

      void DrawBitMap(const Pixmap &PixelMap, const Position &UpperLeft,
       const Position &Size);
      void Erase(const Position &UpperLeft, float Width, float Height);
      void RenderRectangle(const Position &UpperLeft,
       const Position &LowerRight, const color &FillColor,
       const bool Border = false);
      void RenderLine(const Position &Base, const Position &Endpoint,
       const color &Color, const float LineWidth);
      void RenderEllipse(const Position &UpperLeft,
       const Position &LowerRight, const color &FillColor,
       const bool Border = false);
      void RenderPolygon(const Position PolyPoints[], int NbrPoints,
       const color &FillColor, const bool Border = false);
      void RenderPolygon(const vector<Position> &PolyPoints, int NPoints,
		 const color &Color, const bool Border = false);
      void RenderText(const Position LabelCenter,
       const string &Message = DefaultMessage,
       const color &TextColor = Black,
       const color &BackgroundColor = DefaultColor);
      void RenderText(const Position LabelCenter,
       const char* Message = DefaultMessage.c_str(),
       const color &TextColor = Black,
       const color &BackgroundColor = DefaultColor);
      void RenderText(const Position &UpperLeft,
       const Position &LowerRight,
       const string &Message = DefaultMessage,
       const color &TextColor = Black,
       const color &BackgroundColor = DefaultColor);
      void RenderText(const Position &UpperLeft,
       const Position &LowerRight,
       const char* Message = DefaultMessage.c_str(),
       const color &TextColor = Black,
       const color &BackgroundColor = DefaultColor);

      void Message(const string &Message = DefaultMessage);

      float GetWidth    () const;
      float GetHeight   () const;
      float GetXPosition() const;
      float GetYPosition() const;

      Position GetCenter  () const;
      Position GetPosition() const;

      bool  StartTimer(int Interval);
      void StopTimer();

      void SetQuitCallback      (const QuitCallbackFunction       &Callback);
      void SetTimerCallback     (const TimerTickCallbackFunction  &Callback);
      void SetRefreshCallback   (const RefreshCallbackFunction    &Callback);
      void SetMouseClickCallback(const MouseClickCallbackFunction &Callback);

   protected:
      virtual Bool  QuitEvent      ();
      virtual Bool  RefreshEvent   ();
      virtual Bool TimerEvent     ();
      virtual Bool  MouseClickEvent(const Position &MousePosn);

   private:
      Window                     window;
      Pixmap                     ScreenBuffer;
      string                     Title;
      WindowStatus               WinStatus;

      RefreshCallbackFunction    RefreshCallback;
      QuitCallbackFunction       QuitCallback;
      TimerTickCallbackFunction  TimerCallback;
      MouseClickCallbackFunction MouseClickCallback;      

      Bool                       TimerActive;
      unsigned long int          AlarmTime;
#ifndef USING_CC
      long                       OldTime;
#else
      unsigned long int          OldTime;
#endif

      int                        WinX; 
      int                        WinY; 
      int                        WinWidth;  
      int                        WinHeight;
      float                      LogX; 
      float                      LogY; 
      float                      LogWidth; 
      float                      LogHeight; 

      void CheckTimer    ();
      void ConfigureEvent(const XEvent &Report);

   friend class WindowManager;
};


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

int ApiMain();
int ApiEnd ();

long GetMilliseconds();


#endif









