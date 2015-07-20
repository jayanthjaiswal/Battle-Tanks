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
   FILE:        WindowManager.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/26 19:02:40 dcl3a>

   Description
   ===========
   Source file for the implementation of the DispatchListEntry and 
   WindowManager classes.
*/
#include "WindowManager.h"
#include <sys/time.h>
 
//#define DEBUG_UNHANDLED_EVENTS
#ifdef DEBUG_UNHANDLED_EVENTS
#include "EventNames.h"
#endif

//----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                         \\

int               ScreenNbr;
float             PixelsPerCentimeter;
Display          *display;
WindowManager     WinManager;

unsigned long int ColorTable[MaxColors];
unsigned long int ButtonColorTable[NbrButtonColors];

const char *ColorName[] = {
   "black",
   "white",
   "red1",
   "green1",
   "blue1",
   "yellow1",
   "cyan1",
   "magenta1"
};

const char *SecondChoiceColors[] = {
   "black",
   "white",
   "red2",
   "green2",
   "blue2",
   "yellow2",
   "cyan2",
   "magenta2",
};

const char *ButtonColorName[] = {
   "gray85",
   "gray92",
   "gray41",
};

const char *SecondChoiceButtonColors[] = {
   "gray86",
   "gray93",
   "gray42",
};

//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

//-------------------------------------------------------------------------
//  S e n d E x p o s e E v e n t
// Function:       Inserts an expose event into the event queque
// Parameters:     WindowHandle, a Window specifying the window handle of
//                    the window to expose
// Preconditions:  None
// Output:         None
// Postconditions: An expose event for the window with the window handle, 
//                 WindowHandle has been added to the event queque
// Returns:        None

void SendExposeEvent(const Window &WindowHandle) {   
   XEvent Draw;

   Draw.type               = Expose;
   Draw.xany.window        = WindowHandle;
   Draw.xany.send_event    = True;
   Draw.xexpose.type       = Expose;
   Draw.xexpose.send_event = True;
   Draw.xexpose.count      = 0;
   Draw.xexpose.display    = display;
   Draw.xexpose.window     = WindowHandle;

   XSendEvent(display, 
              WindowHandle,
              False, 
              ExposureMask, 
              &Draw);
};


//-------------------------------------------------------------------------
//  F i l t e r E v e n t
// Function:       Handles window events that require very little 
//                 maintenance
// Parameters:     Report, an XEvent specifying a window event
//                 Win, a SimpleWindow specifying the window that the event
//                    occured on
// Preconditions:  Both Report and Win must point to their own memory
// Output:         None
// Postconditions: Select event are handled others are left for dispatching
// Returns:        True, the event still needs to handled 
//                 False, the event was handled

Bool FilterEvent(XEvent *Report, const SimpleWindow *Win) {

   if (XFilterEvent(Report, None))
      return False;

   switch(Report->type) {
      case Expose:
         if (Report->xexpose.count != 0)
            return False;
      
         break;
      case ConfigureNotify:
         if ((l_to_d(Win->GetWidth() ) == Report->xconfigure.width) &&
             (l_to_d(Win->GetHeight()) == Report->xconfigure.height))
            if ((l_to_d(Win->GetXPosition()) == Report->xconfigure.x)   &&
                (l_to_d(Win->GetYPosition()) == Report->xconfigure.y))
               return False;

         break;
      case MappingNotify:
         XRefreshKeyboardMapping((XMappingEvent*) Report);
         return False;
   }

   return True;
}


//-------------------------------------------------------------------------
//  T e r m i n a t e
// Function:       Calls the window manager terminate to close all of the
//                 windows 
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The event queuque contains events to close all of the 
//                 windows
// Returns:        None

void Terminate() {

   WinManager.Terminate();
}


//-------------------------------------------------------------------------
//  G e t M i l l i s e c o n d s 
// Function:       Returns the number of milliseconds that have passed 
//                 since 00:00 Universal Coordinated Time, January 1, 1970
// Parameters:     None
// Preconditions:  None
// Output:         If a clock error occurs, a message is sent to standard
//                 output.
// Postconditions: If a clock error occurs, the program is terminated.
// Returns:        Upon successful completion, the number of milliseconds
//                 passes since Universal Coordinated Time. Otherwise, the 
//                 last known good time is returned.

long GetMilliseconds() {
   static  unsigned long int LastGoodTime(0);
   timeval Current;

   if (gettimeofday(&Current, NULL) == ClockError) {
      cout << "A clock error occured\n";
      Terminate();
      return LastGoodTime;
   }

   LastGoodTime = Current.tv_sec  * MilliSec +
                  Current.tv_usec * MilliSec / MicroSec;
   return LastGoodTime;
}

  
//-----------------------------------------------------------------------\\
//  S i m p l e W i n d o w   C o d e                                    \\

//-------------------------------------------------------------------------
//  S i m p l e W i n d o w
// Function:       Initializes member variables
// Parameters:     WindowTitle, a string specifying the title of the 
//                    window
//                 Width, a float specifying the logical width of the 
//                    window
//                 Height, a float specifying the logical height of the 
//                    window
//                 WindowPosition, a Position specifying the logical
//                    location in centimeters of the upper left corner of 
//                    the window
// Preconditions:  None
// Output:         None
// Postconditions: Member variables has been initialized
// Returns:        None

SimpleWindow::SimpleWindow(const string      &WindowTitle,
                           float              Width, 
                           float              Height,
                           const Position    &WindowPosition)
                         : Title             (WindowTitle),
                           LogX              (WindowPosition.GetXDistance()),
                           LogY              (WindowPosition.GetYDistance()),
                           LogWidth          (Width),
                           LogHeight         (Height),
                           RefreshCallback   (NULL),
                           QuitCallback      (NULL),
                           MouseClickCallback(NULL),
                           TimerCallback     (NULL),
                           TimerActive       (False),
                           AlarmTime         (0),
                           OldTime           (0),
                           window            (None),
                           WinStatus         (WindowClosed) {

}


SimpleWindow::SimpleWindow(const char*        WindowTitle,
                           float              Width,
                           float              Height,
                           const Position    &WindowPosition)
                         : Title             (WindowTitle),
                           LogX              (WindowPosition.GetXDistance()),
                           LogY              (WindowPosition.GetYDistance()),
                           LogWidth          (Width),
                           LogHeight         (Height),
                           RefreshCallback   (NULL),
                           QuitCallback      (NULL),
                           MouseClickCallback(NULL),
                           TimerCallback     (NULL),
                           TimerActive       (False),
                           AlarmTime         (0),
                           OldTime           (0),
                           window            (None),
                           WinStatus         (WindowClosed) {

}


//-------------------------------------------------------------------------
//  S i m p l e W i n d o w
// Function:       Creates an alert box notifying the user that
//                 SimpleWindow objects may not be copied and the program 
//                 is terminated 
// Parameters:     None
// Preconditions:  None
// Output:         An alert box
// Postconditions: The program is terminated.
// Returns:        None

SimpleWindow::SimpleWindow(const SimpleWindow &) {

   AlertWindow("SimpleWindow Copy Constructor", 
               "SimpleWindow objects may not be copied!",
                Terminate);
}


//-------------------------------------------------------------------------
//  ~ S i m p l e W i n d o w
// Function:       Closes the window
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The window is closed.
// Returns:        None

SimpleWindow::~SimpleWindow() {

   if (WinStatus == WindowOpen)
      Close();
}


//-------------------------------------------------------------------------
//  o p e r a t o r = 
// Function:       Generates an alert box informing the user that he or 
//                 she has tried to perform an unfavorable operation.
// Parameters:     None
// Preconditions:  None
// Output:         A message is drawn in the alert box indicating that
//                 assignments are not allowed 
// Postconditions: The program is terminated.
// Returns:        This window

SimpleWindow SimpleWindow::operator=(const SimpleWindow &) {

   AlertWindow("Assignment of SimpleWindow objects not allowed!",
	       "SimpleWindow Assignment", 
                Terminate);
   return *this;
}


//-------------------------------------------------------------------------
//  O p e n
// Function:       Creates the graphical window, displays it, and lets the
//                 window manager know about it
// Parameters:     None
// Preconditions:  Display, display must point to valid memory
// Output:         If the window manager is unable to add the window to its
//                 collection a message is sent to standard output.
// Postconditions: Upon successful completion, the window is displayed and
//                 registered with thte window manager. Otherwise, the
//                 program is terminated.
// Returns:        The window status (open, closed, or error).

WindowStatus SimpleWindow::Open() {

   WinX      = l_to_d(LogX);
   WinY      = l_to_d(LogY);
   WinHeight = l_to_d(LogHeight);
   WinWidth  = l_to_d(LogWidth);

   if (WinStatus != WindowClosed)
      return WinStatus;
   if (CreateWindow(window, Title, WinX, WinY, WinWidth, WinHeight,
    ScreenBuffer)) {
      if (!WinManager.Register(this)) {
         cout << "Unable to register a window.\n";
         XDestroyWindow(display, window);
         WinStatus = WindowFailure;
         return WindowFailure;
      }

      ScreenBuffer = XCreatePixmap(display, RootWindow(display, ScreenNbr),
       DisplayWidth(display, ScreenNbr), DisplayHeight(display, ScreenNbr),
        DefaultDepth(display, ScreenNbr));

      XGCValues GCValues;
      unsigned long AttributeMask = GCForeground | GCBackground;
      GCValues.foreground = ColorTable[White];
      GCValues.background = ColorTable[White];
      GC GraphicsContext = XCreateGC(display, ScreenBuffer, AttributeMask, &GCValues);

      XFillRectangle(display, ScreenBuffer, GraphicsContext,
       0, 0, DisplayWidth(display, ScreenNbr), DisplayHeight(display, ScreenNbr));
      XFreeGC(display, GraphicsContext);

     SetWMCloseWindow(window);
     WinStatus = WindowOpen;
     return WindowOpen;
   }

   WinStatus = WindowFailure;
   return WindowFailure;
}


//-------------------------------------------------------------------------
//  C l o s e
// Function:       Closes the window and unregisters it with the window
//                 manager
// Parameters:     None
// Preconditions:  Display, display must point to valid memory. Window,
//                 window must be a valid window.
// Output:         None
// Postconditions: The window is closed and it is removed from the window
//                 manager.
// Returns:        The window status (open, closed, or error).

WindowStatus SimpleWindow::Close() {

   if (TimerActive)
      StopTimer();

   //XFreePixmap(display, ScreenBuffer);

   if (WinManager.Unregister(window)) {
      XDestroyWindow(display, window);
      WinStatus = WindowClosed;

      return WinStatus;
   }

   WinStatus = WindowFailure;
   return WinStatus;
}


//-------------------------------------------------------------------------
//  G e t S t a t u s
// Function:       Returns the status of the window
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The window status (open, closed, or error).

WindowStatus SimpleWindow::GetStatus() const {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return WinStatus;
}


//-------------------------------------------------------------------------
//  R e n d e r T e x t 
// Function:       Draws a text message in the window
// Parameters:     UpperLeft, a Position specifying the logical location
//                    of the upper left corner of an invisible box which
//                    is used to center the text
//                 LowerRight, a Position specifying the logical location
//                    of the lower right corner of an invisible box which
//                    is used to center the text
//                 Message, a string specifying the message to draw
//                 BackgroundColor, a color specifying the color of the 
//                    background that the text will sit on
// Preconditions:  The window must be open
// Output:         None
// Postconditions: The text message is drawn in the window
// Returns:        None

void SimpleWindow::RenderText(const Position LabelCenter,
 const string &Message, const color &TextColor,
 const color &BackgroundColor) {

   XFontStruct *FontStruct;
   XGCValues GCValues;
   unsigned long AttributeMask;
   FontStruct = XLoadQueryFont(display, WindowFont.c_str());
   if (!FontStruct) {
      cout << "Unable to load the desired font: " << WindowFont.c_str() << endl;
      Terminate();
      return;
   }
   unsigned int TextWidth(XTextWidth(FontStruct, Message.c_str(),
    Message.length()));
   unsigned int TextHeight(FontStruct->ascent + FontStruct->descent);
   int XLocation = l_to_d(LabelCenter.GetXDistance()) - TextWidth / 2;
   int YLocation = l_to_d(LabelCenter.GetYDistance()) + TextHeight / 2;
   AttributeMask = GCForeground | GCBackground | GCFont;
   GCValues.font = FontStruct->fid;
   GCValues.foreground = ColorTable[TextColor];
   GCValues.background = ColorTable[BackgroundColor];


   // Draw text to screen
   GC GraphicsContext = XCreateGC(display, window,
    AttributeMask, &GCValues);
   XDrawImageString(display, window, GraphicsContext,
    XLocation, YLocation, Message.c_str(), Message.length());
   XFreeGC(display, GraphicsContext);


   // Draw text to screen buffer
   GC BufferGraphicsContext = XCreateGC(display, ScreenBuffer,
    AttributeMask, &GCValues);
   XDrawImageString(display, ScreenBuffer, BufferGraphicsContext,
    XLocation, YLocation, Message.c_str(), Message.length());
   XFreeGC(display, BufferGraphicsContext);


   XFreeFont(display, FontStruct);
   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}

void SimpleWindow::RenderText(const Position LabelCenter,
 const char* Message, const color &TextColor,
 const color &BackgroundColor) {

   XFontStruct *FontStruct;
   XGCValues GCValues;
   unsigned long AttributeMask;
   FontStruct = XLoadQueryFont(display, WindowFont.c_str());
   if (!FontStruct) {
      cout << "Unable to load the desired font: " << WindowFont.c_str() << endl;
      Terminate();
      return;
   }
   string TempString = Message;
   unsigned int TextWidth(XTextWidth(FontStruct, Message,
    TempString.length()));
   unsigned int TextHeight(FontStruct->ascent + FontStruct->descent);
   int XLocation = l_to_d(LabelCenter.GetXDistance()) - TextWidth / 2;
   int YLocation = l_to_d(LabelCenter.GetYDistance()) + TextHeight / 2;
   AttributeMask = GCForeground | GCBackground | GCFont;
   GCValues.font = FontStruct->fid;
   GCValues.foreground = ColorTable[TextColor];
   GCValues.background = ColorTable[BackgroundColor];


   // Draw text to screen
   GC GraphicsContext = XCreateGC(display, window,
    AttributeMask, &GCValues);
   XDrawImageString(display, window, GraphicsContext,
    XLocation, YLocation, Message, TempString.length());
   XFreeGC(display, GraphicsContext);


   // Draw text to screen buffer
   GC BufferGraphicsContext = XCreateGC(display, ScreenBuffer,
    AttributeMask, &GCValues);
   XDrawImageString(display, ScreenBuffer, BufferGraphicsContext,
    XLocation, YLocation, Message, TempString.length());
   XFreeGC(display, BufferGraphicsContext);


   XFreeFont(display, FontStruct);
   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}

void SimpleWindow::RenderText(const Position &UpperLeft,
 const Position &LowerRight,
 const string &Message, const color &TextColor,
 const color &BackgroundColor) {

   XFontStruct *FontStruct;
   XGCValues GCValues;
   unsigned long AttributeMask;
   FontStruct = XLoadQueryFont(display, WindowFont.c_str());
   if (!FontStruct) {
      cout << "Unable to load the desired font: " << WindowFont.c_str() << endl;
      Terminate();
      return;
   }
   Position LabelCenter((UpperLeft.GetXDistance() + LowerRight.GetXDistance()) / 2.0,
    (UpperLeft.GetYDistance() + LowerRight.GetYDistance()) / 2.0);
   unsigned int TextWidth(XTextWidth(FontStruct, Message.c_str(),
    Message.length()));
   unsigned int TextHeight(FontStruct->ascent + FontStruct->descent);
   int XLocation = l_to_d(LabelCenter.GetXDistance()) - TextWidth / 2;
   int YLocation = l_to_d(LabelCenter.GetYDistance()) + TextHeight / 2;
   AttributeMask = GCForeground | GCBackground | GCFont;
   GCValues.font = FontStruct->fid;
   GCValues.foreground = ColorTable[TextColor];
   GCValues.background = ColorTable[BackgroundColor];


   // Draw text to screen
   GC GraphicsContext = XCreateGC(display, window,
    AttributeMask, &GCValues);
   XDrawImageString(display, window, GraphicsContext,
    XLocation, YLocation, Message.c_str(), Message.length());
   XFreeGC(display, GraphicsContext);


   // Draw text to screen buffer
   GC BufferGraphicsContext = XCreateGC(display, ScreenBuffer,
    AttributeMask, &GCValues);
   XDrawImageString(display, ScreenBuffer, BufferGraphicsContext,
    XLocation, YLocation, Message.c_str(), Message.length());
   XFreeGC(display, BufferGraphicsContext);


   XFreeFont(display, FontStruct);
   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}

void SimpleWindow::RenderText(const Position &UpperLeft,
 const Position &LowerRight,
 const char* Message, const color &TextColor,
 const color &BackgroundColor) {

   XFontStruct *FontStruct;
   XGCValues GCValues;
   unsigned long AttributeMask;
   FontStruct = XLoadQueryFont(display, WindowFont.c_str());
   if (!FontStruct) {
      cout << "Unable to load the desired font: " << WindowFont.c_str() << endl;
      Terminate();
      return;
   }
   Position LabelCenter((UpperLeft.GetXDistance() + LowerRight.GetXDistance()) / 2.0,
    (UpperLeft.GetYDistance() + LowerRight.GetYDistance()) / 2.0);
   string TempString = Message;
   unsigned int TextWidth(XTextWidth(FontStruct, Message,
    TempString.length()));
   unsigned int TextHeight(FontStruct->ascent + FontStruct->descent);
   int XLocation = l_to_d(LabelCenter.GetXDistance()) - TextWidth / 2;
   int YLocation = l_to_d(LabelCenter.GetYDistance()) + TextHeight / 2;
   AttributeMask = GCForeground | GCBackground | GCFont;
   GCValues.font = FontStruct->fid;
   GCValues.foreground = ColorTable[TextColor];
   GCValues.background = ColorTable[BackgroundColor];


   // Draw text to screen
   GC GraphicsContext = XCreateGC(display, window,
    AttributeMask, &GCValues);
   XDrawImageString(display, window, GraphicsContext,
    XLocation, YLocation, Message, TempString.length());
   XFreeGC(display, GraphicsContext);


   // Draw text to screen buffer
   GC BufferGraphicsContext = XCreateGC(display, ScreenBuffer,
    AttributeMask, &GCValues);
   XDrawImageString(display, ScreenBuffer, BufferGraphicsContext,
    XLocation, YLocation, Message, TempString.length());
   XFreeGC(display, BufferGraphicsContext);


   XFreeFont(display, FontStruct);
   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}

//-------------------------------------------------------------------------
//  D r a w B i t M a p
// Function:       Draws a bitmap in the window
// Parameters:     PixelMap, a Pixmap specifying the content of the bitmap
//                 UpperLeft, a Position specifying the logical location
//                    of the upper left corner of the bitmap
//                 LowerRight, a Position specifying the logical location
//                    of the lower right corner of the bitmap
// Preconditions:  The window must be open
// Output:         None
// Postconditions: The bitmap is drawn in the window
// Returns:        None

void SimpleWindow::DrawBitMap(const Pixmap   &PixelMap, 
			      const Position &UpperLeft,
			      const Position &Size) {

   // Draw bitmap to screen
   GC GraphicsContext(GetGraphicsContext(window,
    BlackPixel(display, ScreenNbr), ColorTable[White]));

   XCopyArea(display, PixelMap, window, GraphicsContext, 0, 0,
    l_to_d(Size.GetXDistance()), l_to_d(Size.GetYDistance()),
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()));

   XFreeGC(display, GraphicsContext);


   // Draw bitmap to screen buffer
   GC BufferGraphicsContext(GetGraphicsContext(ScreenBuffer,
    BlackPixel(display, ScreenNbr), ColorTable[White]));

   XCopyArea(display, PixelMap, ScreenBuffer, BufferGraphicsContext,
    0, 0, l_to_d(Size.GetXDistance()), l_to_d(Size.GetYDistance()),
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()));

   XFreeGC(display, BufferGraphicsContext);


   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}


//-------------------------------------------------------------------------
//  E r a s e 
// Function:       Draws a bitmap in the window
// Parameters:     PixelMap, a Pixmap specifying the content of the bitmap
//                 UpperLeft, a Position specifying the logical location
//                    of the upper left corner of the bitmap
//                 LowerRight, a Position specifying the logical location
//                    of the lower right corner of the bitmap
// Preconditions:  The window must be open
// Output:         None
// Postconditions: The bitmap is drawn in the window
// Returns:        None

void SimpleWindow::Erase(const Position &UpperLeft,
 float Width, float Height) {

   RenderRectangle(UpperLeft, UpperLeft + Position(Width, Height),
    White, false);

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}


//-------------------------------------------------------------------------
//  R e n d e r R e c t a n g l e
// Function:       Draws a rectangle in the window
// Parameters:     UpperLeft, a Position specifying the logical location
//                    of the upper left corner of the rectangle
//                 LowerRight, a Position specifying the logical location
//                    of the lower right corner of the rectangle
// Preconditions:  The window must be open
// Output:         None
// Postconditions: The rectangle is drawn in the window
// Returns:        None

void SimpleWindow::RenderRectangle(const Position &UpperLeft,
 const Position &LowerRight, const color &FillColor,
 const bool Border) {

   // Draw rectangle to screen
   GC GraphicsContext(GetGraphicsContext(window,
    ColorTable[FillColor], ColorTable[White]));

   XFillRectangle(display, window, GraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()));

   if (Border)
      XSetForeground(display, GraphicsContext, ColorTable[Black]);

   XDrawRectangle(display, window, GraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()));

   XFreeGC(display, GraphicsContext);


   // Draw rectangle to screen buffer
   GC BufferGraphicsContext(GetGraphicsContext(ScreenBuffer,
    ColorTable[FillColor], ColorTable[White]));

   XFillRectangle(display, ScreenBuffer, BufferGraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()));

   if (Border)
      XSetForeground(display, BufferGraphicsContext, ColorTable[Black]);

   XDrawRectangle(display, ScreenBuffer, BufferGraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()));

   XFreeGC(display, BufferGraphicsContext);


   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}

void SimpleWindow::RenderLine(const Position &Base,
 const Position &Endpoint, const color &Color,
 const float LineWidth) {

   // Draw line to screen
   GC GraphicsContext(GetGraphicsContext(window,
    ColorTable[Color], ColorTable[Color]));

   XSetLineAttributes(display, GraphicsContext, l_to_d(LineWidth),
    LineDoubleDash, CapRound, JoinRound);

   XDrawLine(display, window, GraphicsContext,
    l_to_d(Base.GetXDistance()), l_to_d(Base.GetYDistance()),
    l_to_d(Endpoint.GetXDistance()), l_to_d(Endpoint.GetYDistance()));

   XFreeGC(display, GraphicsContext);


   // Draw line to screen buffer
   GC BufferGraphicsContext(GetGraphicsContext(ScreenBuffer,
    ColorTable[Color], ColorTable[Color]));

   XSetLineAttributes(display, BufferGraphicsContext, l_to_d(LineWidth),
    LineDoubleDash, CapRound, JoinRound);

   XDrawLine(display, ScreenBuffer, BufferGraphicsContext,
    l_to_d(Base.GetXDistance()), l_to_d(Base.GetYDistance()),
    l_to_d(Endpoint.GetXDistance()), l_to_d(Endpoint.GetYDistance()));

   XFreeGC(display, BufferGraphicsContext);


   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}

//-------------------------------------------------------------------------
//  R e n d e r E l l i p s e
// Function:       Draws an ellipse in the window
// Parameters:     UpperLeft, a Position specifying the logical location
//                    of the upper left corner of the ellipse
//                 LowerRight, a Position specifying the logical location
//                    of the lower right corner of the ellipse
// Preconditions:  The window must be open
// Output:         None
// Postconditions: The ellipse is drawn in the window
// Returns:        None

void SimpleWindow::RenderEllipse(const Position &UpperLeft,
 const Position &LowerRight, const color &FillColor,
 const bool Border) {

   // Draw ellipse to screen
   GC GraphicsContext(GetGraphicsContext(window,
    ColorTable[FillColor], ColorTable[White]));

   XFillArc(display, window, GraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()),
    0, DeviceTwoPi);

   if (Border) XSetForeground(display, GraphicsContext, ColorTable[Black]);

   XDrawArc(display, window, GraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()),
    0, DeviceTwoPi);

   XFreeGC(display, GraphicsContext);


   // Draw ellipse to screen buffer
   GC BufferGraphicsContext(GetGraphicsContext(ScreenBuffer,
    ColorTable[FillColor], ColorTable[White]));

   XFillArc(display, ScreenBuffer, BufferGraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()),
    0, DeviceTwoPi);

   if (Border) XSetForeground(display, BufferGraphicsContext, ColorTable[Black]);

   XDrawArc(display, ScreenBuffer, BufferGraphicsContext,
    l_to_d(UpperLeft.GetXDistance()), l_to_d(UpperLeft.GetYDistance()),
    l_to_d(LowerRight.GetXDistance()) - l_to_d(UpperLeft.GetXDistance()),
    l_to_d(LowerRight.GetYDistance()) - l_to_d(UpperLeft.GetYDistance()),
    0, DeviceTwoPi);

   XFreeGC(display, BufferGraphicsContext);


   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}


//-------------------------------------------------------------------------
//  R e n d e r P o l y g o n
// Function:       Draws an polygon in the window
// Parameters:     PolyPoints, an array of Positions specifying the
//                    logical locations of the vertices of the polygon
//                 NbrPoints, an integer specifying the number of
//                    vertices in the polygon
//                 FillColor, a color specifying the fill color of the
//                    polygon
// Preconditions:  The window must be open
// Output:         None
// Postconditions: The polygon is drawn in the window
// Returns:        None

void SimpleWindow::RenderPolygon(const Position PolyPoints[],
 int NbrPoints, const color &FillColor, const bool Border) {

   XPoint *ConvertedPolyPoints;
   ConvertedPolyPoints = new XPoint[NbrPoints + 1];

   for (int i = 0; i < NbrPoints; i++) {
      ConvertedPolyPoints[i].x = l_to_d(PolyPoints[i].GetXDistance());
      ConvertedPolyPoints[i].y = l_to_d(PolyPoints[i].GetYDistance());
   }
   ConvertedPolyPoints[NbrPoints] = ConvertedPolyPoints[0];


   // Draw polygon to screen
   GC GraphicsContext(GetGraphicsContext(window,
    ColorTable[FillColor], ColorTable[White]));

   XFillPolygon(display, window, GraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, Complex, CoordModeOrigin);

   if (Border) XSetForeground(display, GraphicsContext, ColorTable[Black]);

   XDrawLines(display, window, GraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, CoordModeOrigin);

   XFreeGC(display, GraphicsContext);


   // Draw polygon to screen buffer
   GC BufferGraphicsContext(GetGraphicsContext(ScreenBuffer,
    ColorTable[FillColor], ColorTable[White]));

   XFillPolygon(display, ScreenBuffer, BufferGraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, Complex, CoordModeOrigin);

   if (Border) XSetForeground(display, BufferGraphicsContext, ColorTable[Black]);

   XDrawLines(display, ScreenBuffer, BufferGraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, CoordModeOrigin);

   XFreeGC(display, BufferGraphicsContext);


   delete [] ConvertedPolyPoints;

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}


//-------------------------------------------------------------------------
//  R e n d e r P o l y g o n
// Function:       Draws an polygon in the window
// Parameters:     PolyPoints, an array of Positions specifying the
//                    logical locations of the vertices of the polygon
//                 NbrPoints, an integer specifying the number of
//                    vertices in the polygon
//                 FillColor, a color specifying the fill color of the
//                    polygon
// Preconditions:  The window must be open
// Output:         None
// Postconditions: The polygon is drawn in the window
// Returns:        None

void SimpleWindow::RenderPolygon(const vector<Position> &PolyPoints,
 int NbrPoints, const color &FillColor, const bool Border) {

   XPoint *ConvertedPolyPoints;
   ConvertedPolyPoints = new XPoint[NbrPoints + 1];

   for (int i = 0; i < NbrPoints; i++) {
      ConvertedPolyPoints[i].x = l_to_d(PolyPoints[i].GetXDistance());
      ConvertedPolyPoints[i].y = l_to_d(PolyPoints[i].GetYDistance());
   }
   ConvertedPolyPoints[NbrPoints] = ConvertedPolyPoints[0];


   // Draw polygon to screen
   GC GraphicsContext(GetGraphicsContext(window,
    ColorTable[FillColor], ColorTable[White]));

   XFillPolygon(display, window, GraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, Complex, CoordModeOrigin);

   if (Border) XSetForeground(display, GraphicsContext, ColorTable[Black]);

   XDrawLines(display, window, GraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, CoordModeOrigin);

   XFreeGC(display, GraphicsContext);


   // Draw polygon to screen buffer
   GC BufferGraphicsContext(GetGraphicsContext(ScreenBuffer,
    ColorTable[FillColor], ColorTable[White]));

   XFillPolygon(display, ScreenBuffer, BufferGraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, Complex, CoordModeOrigin);

   if (Border) XSetForeground(display, BufferGraphicsContext, ColorTable[Black]);

   XDrawLines(display, ScreenBuffer, BufferGraphicsContext,
    ConvertedPolyPoints, NbrPoints + 1, CoordModeOrigin);

   XFreeGC(display, BufferGraphicsContext);


   delete [] ConvertedPolyPoints;

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}


//-------------------------------------------------------------------------
//  M e s s a g e
// Function:       Creates an alert box with the message passed as a 
//                 parameter
// Parameters:     Message, a string specifying the message to draw in
//                    the alert box
// Preconditions:  The window must be open
// Output:         An alert box is created.
// Postconditions: None
// Returns:        None

void SimpleWindow::Message(const string &Message) {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   AlertWindow(Title, Message);
}


//-------------------------------------------------------------------------
//  G e t W i d t h
// Function:       Returns the logical width of the window 
// Parameters:     None
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: None
// Returns:        The logical width of the window

float SimpleWindow::GetWidth() const {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return d_to_l(WinWidth); 
}


//-------------------------------------------------------------------------
//  G e t H e i g h t
// Function:       Returns the logical height of the window
// Parameters:     None
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: None
// Returns:        The logical height of the window

float SimpleWindow::GetHeight() const {
  
   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return d_to_l(WinHeight);
}


//-------------------------------------------------------------------------
//  G e t X P o s i t i o n
// Function:       Returns the logical x coordinate of the upper left 
//                 corner of the window 
// Parameters:     None
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: None
// Returns:        The logical x coordinate of the upper left corner of 
//                 the window

float SimpleWindow::GetXPosition() const {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return d_to_l(WinX);
}


//-------------------------------------------------------------------------
//  G e t Y P o s i t i o n
// Function:       Returns the logical y coordinate of the upper left 
//                 corner of the window
// Parameters:     None
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: None
// Returns:        The logical y coordinate of the upper left corner of 
//                 the window

float SimpleWindow::GetYPosition() const {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return d_to_l(WinY);     
}


//-------------------------------------------------------------------------
//  G e t P o s i t i o n
// Function:       Returns the logical location of the upper left corner 
//                 of the window 
// Parameters:     None
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: None
// Returns:        The logical location of the upper left corner of
//                 the window

Position SimpleWindow::GetPosition() const {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return Position(GetXPosition(), GetYPosition()); 
}


//-------------------------------------------------------------------------
//  G e t C e n t e r
// Function:       Returns the logical location of the center of the 
//                 window 
// Parameters:     None
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: None
// Returns:        The logical location of the ceneter of the window

Position SimpleWindow::GetCenter() const {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return Position(d_to_l(WinWidth) * 0.5, d_to_l(WinHeight) * 0.5);
}


//-------------------------------------------------------------------------
//  S e t R e f r e s h C a l l b a c k
// Function:       Informs this window how to handle refresh events
// Parameters:     Callback, a RefreshCallbackFunction specifying the 
//                    function to call when a refresh event occurs
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: The refresh callback function is set.
// Returns:        None

void SimpleWindow::SetRefreshCallback(
   const RefreshCallbackFunction &Callback) {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   RefreshCallback = Callback;
}


//-------------------------------------------------------------------------
//  S e t Q u i t C a l l b a c k
// Function:       Informs this window what to do when it closes
// Parameters:     Callback, a QuitCallbackFunction specifying the 
//                    function to call when the window is closed
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: The quit callback function is set.
// Returns:        None

void SimpleWindow::SetQuitCallback(const QuitCallbackFunction &Callback) {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   QuitCallback = Callback;
}


//-------------------------------------------------------------------------
//  S e t T i m e r C a l l b a c k
// Function:       Informs this window how to handle timer events
// Parameters:     Callback, a TimerTickCallbackFunction specifying the 
//                    function to call when the time expires
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: The timer callback function is set.
// Returns:        None

void SimpleWindow::SetTimerCallback(
   const TimerTickCallbackFunction &Callback) {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   TimerCallback = Callback;
}


//-------------------------------------------------------------------------
//  S t a r t T i m e r
// Function:       Turns the interval timer on and if ApiMain is still in
//                 progress, events are checked
// Parameters:     Interval, an integer specifying the length of time in
//                    milliseconds before the timer expires 
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: If ApiMain is not finished, events are checked
// Returns:        1 for succesful completion. If the function is not 
//                 successfully completed, an shut down sequence is 
//                 started.

bool SimpleWindow::StartTimer(int Interval) {

   AlarmTime   = Interval;
   TimerActive = True;
   OldTime     = GetMilliseconds();

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   return true;
}


//-------------------------------------------------------------------------
//  S t o p T i m e r
// Function:       Turns the interval timer off and if ApiMain is still in
//                 progress, events are checked
// Parameters:     None
// Preconditions:  The display must be open.
// Output:         None
// Postconditions: If ApiMain is not finished, events are checked
// Returns:        None

void SimpleWindow::StopTimer() {

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();

   TimerActive = False;
}


//-------------------------------------------------------------------------
//  C o n f i g u r e E v e n t 
// Function:       Sets the window position and size attributes
// Parameters:     Report, an XEvent specifying the attributes that 
//                    changed based on a window event
// Preconditions:  None
// Output:         None
// Postconditions: The window size and position attributes haved been set
// Returns:        None
  
void SimpleWindow::ConfigureEvent(const XEvent &Report) {
                                
   WinX      = Report.xconfigure.x;
   WinY      = Report.xconfigure.y;
   LogX      = d_to_l(Report.xconfigure.x);
   LogY      = d_to_l(Report.xconfigure.y);

   WinWidth  = Report.xconfigure.width;
   WinHeight = Report.xconfigure.height;
   LogWidth  = d_to_l(Report.xconfigure.width);
   LogHeight = d_to_l(Report.xconfigure.height);
}


//-------------------------------------------------------------------------
//  C h e c k T i m e r 
// Function:       Checks to see if the timer has expired. If it has, the
//                 timer event callback is called
// Parameters:     None
// Preconditions:  The display and the window must be open.
// Output:         Depends on the timer event
// Postconditions: If the timer has expired, the timer callback function
//                 is called and the timer is reset.
// Returns:        None

void SimpleWindow::CheckTimer() {
   long DiffTime(GetMilliseconds() - OldTime);

   if (DiffTime >= AlarmTime) {
      TimerEvent();
      OldTime = GetMilliseconds();
   }
}


//-------------------------------------------------------------------------
//  T i m e r E v e n t 
// Function:       If a timer callback function is set, it is called.
// Parameters:     None
// Preconditions:  None
// Output:         Depends on the callback function
// Postconditions: If a callback function is set, it is called.
// Returns:        True, a timer event was handled successfully. 
//                 Otherwise, False is returned.
  
Bool SimpleWindow::TimerEvent() {
	
   if (TimerCallback)
      return (TimerCallback)();

   return False;
}


//-------------------------------------------------------------------------
//  S e t M o u s e C l i c k C a l l b a c k 
// Function:       Sets the call-back function for mouse click events
// Parameters:     Callback, a MouseClickCallbackFunction specifying the 
//                    function to call when a mouse click occurs
// Preconditions:  The window and the display must be open.
// Output:         None
// Postconditions: The call-back function for mouse events is set. If 
//                 ApiMain is still in progress, events are checked. 
// Returns:        None

void SimpleWindow::SetMouseClickCallback(
   const MouseClickCallbackFunction &Callback) {
         
   MouseClickCallback = Callback;
   XSelectInput(display, window, ButtonEventMask | NormalWindowEventMask);

   if (!WinManager.IsApiMainCompleted())
      WinManager.CheckEvents();
}
    

//-------------------------------------------------------------------------
//  R e f r e s h E v e n t
// Function:       If a refresh call-back is set, it is called.
// Parameters:     None
// Preconditions:  The window and the display must be open.
// Output:         The window is redrawn by the call-back function.
// Postconditions: The window is repaired.
// Returns:        True, the call-back function was called successfully. 
//                 Otherwise, False is returned.

Bool SimpleWindow::RefreshEvent() {

   if (RefreshCallback)
      return (RefreshCallback)();
   else {

      GC GraphicsContext(GetGraphicsContext(window,
       ColorTable[White], ColorTable[White]));

      XCopyArea(display, ScreenBuffer, window, GraphicsContext, 0, 0,
       WinWidth, WinHeight, 0, 0);

      XFreeGC(display, GraphicsContext);

   }

   return False;
}


//-------------------------------------------------------------------------
//  Q u i t E v e n t
// Function:       If a quit call-back is set, it is called.
// Parameters:     None
// Preconditions:  The window and the display must be open.
// Output:         Depends on the call-back function
// Postconditions: The quit call-back is called
// Returns:        True, the call-back function was called successfully. 
//                 Otherwise, False is returned.

Bool SimpleWindow::QuitEvent() {
	 
   if (QuitCallback)
      return (QuitCallback)();

   return False;
}


//-------------------------------------------------------------------------
//  M o u s e C l i c k E v e n t
// Function:       If a mouse click call-back is set, it is called.
// Parameters:     MousePosn, a Position specifying the logical location
//                    of the mouse pointer when the click occured
// Preconditions:  None
// Output:         Depends on the call-back function
// Postconditions: The mouse call-back is called
// Returns:        True, the call-back function was called successfully. 
//                 Otherwise, False is returned.

Bool SimpleWindow::MouseClickEvent(const Position &MousePosn) {
         
   if (MouseClickCallback)
      return (MouseClickCallback)(MousePosn);
	 
   return False;
}


//-----------------------------------------------------------------------\\
//  D i s p a t c h L i s t E n t r y  C o d e                           \\

//-------------------------------------------------------------------------
//  D i s p a t c h L i s t E n t r y
// Function:       Initializes member variables
// Parameters:     iPtrSimpleWindow, a SimpleWindow specifying the window
//                    for this node
//                 HeadOfList, a pointer to a DispatchListEntry specifying
//                    the node that is the current head of the list
// Preconditions:  HeadOfList must point to its own memory or NULL
// Output:         None
// Postconditions: Member variables are initialized.
// Returns:        None

DispatchListEntry::DispatchListEntry(SimpleWindow      *iPtrSimpleWindow, 
                                     DispatchListEntry *HeadOfList) 
                                   : PtrSimpleWindow   (iPtrSimpleWindow), 
                                     Next              (HeadOfList) {

}


//-------------------------------------------------------------------------
//  D i s p a t c h L i s t E n t r y
// Function:       Does nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

DispatchListEntry::~DispatchListEntry() {

}


//-----------------------------------------------------------------------\\
//  W i n d o w M a n a g e r   C o d e                                  \\

//-------------------------------------------------------------------------
//  W i n d o w M a n a g e r
// Function:       Initializes member variables and global variables
// Parameters:     None
// Preconditions:  Global variables display, ScreenNbr, ColorTable, and
//                 ButtonColorTable must be defined
// Output:         If an error occurs opening the display or obtaining 
//                 colors a message is sent to standard output 
// Postconditions: Member variables and global variables are initialized
// Returns:        None

WindowManager::WindowManager() : ListSize             (0), 
                                 DispatchList         (NULL),
                                 ColorsMatched        (True),
                                 ApiMainCompleted     (False) {

   display = XOpenDisplay(NULL);
   if (!display) {
      cerr << "ERROR opening display [" 
           << XDisplayName(NULL) << "]\n";
      exit(EXIT_SUCCESS);
   }
  
   ScreenNbr = DefaultScreen(display);

   PixelsPerCentimeter = floor((float) DisplayWidth(display, ScreenNbr)  / 
                               DisplayLengthCM);

   ColorsMatched = False;
   if (InitializeColors(ColorName, 
                        SecondChoiceColors, 
                        ColorTable,
                        MaxColors) &&
       InitializeColors(ButtonColorName, 
                        SecondChoiceButtonColors, 
                        ButtonColorTable,
                        NbrButtonColors))
      ColorsMatched = True;
}
          

//-------------------------------------------------------------------------
//  ~ W i n d o w M a n a g e r
// Function:       Empties the window manager list of windows and closes 
//                 the display
// Parameters:     None
// Preconditions:  None
// Output:         If the window manager is not empty, something unexpected
//                 has happended. The user is notified by standard output.
// Postconditions: The window manager is empty and the display is closed
// Returns:        None

WindowManager::~WindowManager() {

   if (!Empty()) {
      cout << "Attempted to terminated the program with a nonempty "
           << "window manager\n";   
      
      DispatchListEntry *Traverser(DispatchList);
      while (DispatchList) {
         if (DispatchList->PtrSimpleWindow)
            DispatchList->PtrSimpleWindow->Close();

         Traverser    = DispatchList;
         DispatchList = DispatchList->Next;
         delete Traverser;
         }
      }

   if (ColorsMatched) {
      XCloseDisplay(display);
      }
}


//-------------------------------------------------------------------------
//  I n i t i a l i z e C o  l o r s
// Function:       Obtains colors from the server
// Parameters:     FirstChoice, an array of character pointers specifying
//                    first choice colors
//                 SecondChoice, an array of character pointers specifying
//                    second choice colors
//                 Tables, an array of long integers specifying color
//                    palette values
//                 NbrColors, an integer specifying the number of colors 
//                    to obtain from the server
// Preconditions:  FirstChoice, SecondChoice, and Table  must point to 
//                 valid memory. The display must be open.
// Output:         If neither first or second choice colors can be 
//                 obtained, a message is sent to standard output
// Postconditions: Upon successful completion, this application has the
//                 desired colors available.
// Returns:        True, colors were successfully obtained. Otherwise, 
//                 False.

Bool WindowManager::InitializeColors(const char        **FirstChoice,
                                     const char        **SecondChoice,
                                     unsigned long int  *Table,
                                     int                 NbrColors) {
   int CurrentColor(0);
   XColor Current, ScreenColor;
   Colormap DefaultColorMap(DefaultColormap(display, ScreenNbr));

   for (; CurrentColor < NbrColors; CurrentColor++) {
      if (XAllocNamedColor(display, 
                           DefaultColorMap, 
                           FirstChoice[CurrentColor],
                          &Current,
                          &ScreenColor))
         Table[CurrentColor] = Current.pixel;
      else if (XAllocNamedColor(display, 
                                DefaultColorMap,
                                SecondChoice[CurrentColor],
                               &Current,
                               &ScreenColor))
         Table[CurrentColor] = Current.pixel;
      else {
         cerr << "In function: WindowManager\n"
              << "\tFailed to find a color match for colors: "
              << FirstChoice[CurrentColor] << " and "
              << SecondChoice[CurrentColor] 
              << ".\n\tClose down any applications that might be using\n\t"
              << "these colors and try again.\n";
         return False;
      }
   }

   return True;
}


//-------------------------------------------------------------------------
//  E m p t y
// Function:       Returns True if the window manager isn't managing any
//                 windows.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        True, the window manager is empty. Otherwise, False.

Bool WindowManager::Empty() const { 
         
   return (ListSize == 0);
}


//-------------------------------------------------------------------------
//  R e g i s t e r
// Function:       Add a window to the collection of windows being managed
// Parameters:     PtrSimpleWindow, a pointer to a SimpleWindow specifying
//                    the window to add to the window manager
// Preconditions:  PtrSimpleWindow ust point to valid memory.
// Output:         If PtrSimpleWindow dosen't exist or memory can't be 
//                 allocated for a new node, a message is sent to standard
//                 output
// Postconditions: Upon successful completion, the window is added to the
//                 list of the managed windows. If unable to allocate 
//                 memory a shut down sequence is started. 
// Returns:        True, the window is registered. Otherwise, False.

Bool WindowManager::Register(SimpleWindow *PtrSimpleWindow) {
   DispatchListEntry *NewEntry;
   
   if (!PtrSimpleWindow) {
      cout << "Error: Trying to register a nonexistent window.\n";
      return False;
   } 

   NewEntry = new DispatchListEntry(PtrSimpleWindow, DispatchList);
   if (!NewEntry) {
      cout << "Error: Unable to allocate memory while trying to "
           << "register a window.\n";
      Terminate();
      return False;
   }

   DispatchList = NewEntry;
   ListSize++;
   return True;
}


//-------------------------------------------------------------------------
//  U n R e g i s t e r
// Function:       Remove a window from the collection of windows being 
//                 managed
// Parameters:     window, a Window specifying the window handle of the 
//                    window to remove 
// Preconditions:  window should be a valid window handle
// Output:         If window doesn't have a window handle number, a 
//                 message is sent to standard output
// Postconditions: Upon successful completion, the window is removed from 
//                 the list of the managed windows.
// Returns:        True, the window is removed. Otherwise, False.

Bool WindowManager::Unregister(const Window &window) {
   DispatchListEntry *Traverser(DispatchList);
   DispatchListEntry *PrevEntry(DispatchList);

   if (window == None) {
      cout << "Window requested to remove doesn't exist\n";
      return False;
   }

   for (; Traverser; PrevEntry = Traverser, Traverser = Traverser->Next) {
      if (Traverser->PtrSimpleWindow->window == window) {
         if (PrevEntry == Traverser)
            DispatchList = Traverser->Next;
         else                                
            PrevEntry->Next = Traverser->Next;

         delete Traverser;
         ListSize--;
         return True;
      }
   }

   return False; 
}
	
   
//-------------------------------------------------------------------------
//  C l o s e A W i n d o w
// Function:       Closes a window
// Parameters:     Win, a pointer to a SimpleWindow specifying the window
//                    to close
// Preconditions:  Win must point to valid memory.
// Output:         If window wasn't closed properly. a message is sent to 
//                 standard output
// Postconditions: Upon successful completion, the window is closed.
// Returns:        Handled, the window was closed successfully
//                 UnHandled, the window was closed properly
//                 EndProgram, no more windows exist in the window manager

DispatchStatus WindowManager::CloseAWindow(SimpleWindow *Win) {
   
   Win->QuitEvent();

   if (Win->GetStatus() == WindowOpen)
      if (Win->Close() == WindowFailure) {
         cout << "A window wasn't closed properly\n"; 
         return UnHandled;
      }

   if (CheckTermination() == Quit)
      return EndProgram;

   return Handled;
}


//-------------------------------------------------------------------------
//  G e t W i n d o w
// Function:       Obtain a window from the window manager
// Parameters:     WindowHandle, a Window specifying the window handle of
//                    the window to get
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        A pointer to the SimpleWindow object that is the window.
//                 Otherwise, NULL.

SimpleWindow *WindowManager::GetWindow(const Window &WindowHandle) const {
   DispatchListEntry *Traverser(DispatchList);

   for (; Traverser; Traverser = Traverser->Next)
      if (Traverser->PtrSimpleWindow->window == WindowHandle)
         return Traverser->PtrSimpleWindow;

   return NULL;
}


//-------------------------------------------------------------------------
//  D e s c r i b e C o n t e n t s
// Function:       Lists the window handles of the windows being managed
// Parameters:     None
// Preconditions:  None
// Output:         A list of the window handles of the windows being 
//                 managed
// Postconditions: None
// Returns:        None

void WindowManager::DescribeContents() const {
   DispatchListEntry *Traverser(DispatchList);

   cout << "The windows manager contains the following elements:\n";

   for (; Traverser; Traverser = Traverser->Next) {
      cout << "\t" << Traverser->PtrSimpleWindow->window << endl;
   }
}


//-------------------------------------------------------------------------
//  G e t W i n d o w
// Function:       Obtain a window from the window manager
// Parameters:     Report, a XEvent specifying a window event that occured
//                    on the window to get
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        A pointer to the SimpleWindow object that is the window.
//                 Otherwise, NULL.

SimpleWindow *WindowManager::GetWindow(const XEvent &Report) const {
   DispatchListEntry *Traverser(DispatchList);

   for (; Traverser; Traverser = Traverser->Next)
      if (Traverser->PtrSimpleWindow->window == Report.xany.window)
         return Traverser->PtrSimpleWindow;

   return NULL;
}


//-------------------------------------------------------------------------
//  D i s p a t c h M e s s a g e
// Function:       Handles the window events for the windows in the window 
//                 manager
// Parameters:     Report, an XEvent specifying the window event that 
//                    occured
//                 Win, a pointer to a SimpleWindow specifying the window
//                    that the event occured on. 
// Preconditions:  Win must point to valid memory.
// Output:         None
// Postconditions: Upon successful completion, the event specified report 
//                 is handled
// Returns:        Handled, the event was dispatched
//                 UnHandled, the event was not processed
//                 EndProgram, no windows are left in the window manager

DispatchStatus WindowManager::DispatchMessage(XEvent       &Report, 
                                              SimpleWindow *Win) {      
   switch(Report.type) {
      case Expose:
         Win->RefreshEvent();

	 return Handled;
      case ClientMessage:
         if (IsWMCloseWindow((XClientMessageEvent*) &Report))
            return CloseAWindow(Win);

         return UnHandled;
      case DestroyNotify:
         return CloseAWindow(Win);

      case ButtonPress:
         return Handled;

      case ButtonRelease:
         Win->MouseClickEvent(Position(d_to_l(Report.xbutton.x),
                                       d_to_l(Report.xbutton.y)));

         return Handled;
      case ConfigureNotify:
         Win->ConfigureEvent(Report);

         return Handled; 
   }

   return UnHandled;
}


//-------------------------------------------------------------------------
//  C h e c k E v e n t s
// Function:       Checks to see if a window has been altered in size or
//                 location or if it has been closed. Checks active timers
//                 to see if any have expired. The x server and cout are 
//                 flushed.
// Parameters:     None
// Preconditions:  The display must be open
// Output:         If DEBUG_UNHANDLED_EVENTS is defined, messages are 
//                 generated for events that occur and window is not 
//                 identified.
// Postconditions: Selected window events are handled, the timers are
//                 checked, and the server is flushed
// Returns:        None

void WindowManager::CheckEvents() {
   static Bool   Entered(False);
   XEvent        Report;
   SimpleWindow *Win(NULL);

   XFlush(display);
   if (!Entered) {
      Entered = True;

      while (XCheckMaskEvent (display, 
                              StructureNotifyMask, 
                             &Report) ||
             XCheckTypedEvent(display, 
                              ClientMessage,
                             &Report)) {

         Win = GetWindow(Report);
         if (Win) {
            if (FilterEvent(&Report, Win))      
               DispatchMessage(Report, Win);
         }
#ifdef DEBUG_UNHANDLED_EVENTS
         else {
            cout << "An event occurred and no window was identified.\n"
                 << "Event type: " << EventNames[Report.type] << "\n"
                 << "Window:     " << Report.xany.window << "\n";
         }
#endif
      }

      CheckTimers();
#ifdef USING_CC
      cout << flush;
#endif
      Entered = False;
   }
   else
      Entered = False;
}


//-------------------------------------------------------------------------
//  C h e c k T i m e r s
// Function:       Checks to see if any timers have expired
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The timers are updated
// Returns:        None

void WindowManager::CheckTimers() {
   DispatchListEntry *Traverser(DispatchList);

   while (Traverser) {
      if (Traverser->PtrSimpleWindow->TimerActive)
         Traverser->PtrSimpleWindow->CheckTimer();

      Traverser = Traverser->Next;
   }
}


//-------------------------------------------------------------------------
//  T e r m i n a t e
// Function:       Puts a message on the event queue to close each of the
//                 windows being managed by the window manager
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The event queue contains a message to close each of the
//                 windows being handled by the window manager
// Returns:        None

void WindowManager::Terminate() {

   if (!DispatchList)
      return;

   DispatchListEntry *Traverser(DispatchList);
   XEvent             CloseDown;

   while (Traverser) {

      CloseDown.type               = DestroyNotify;
      CloseDown.xany.type          = DestroyNotify;
      CloseDown.xany.window        = Traverser->PtrSimpleWindow->window;
      CloseDown.xclient.type       = DestroyNotify;
      CloseDown.xclient.send_event = True;
      CloseDown.xclient.display    = display;
      CloseDown.xclient.window     = Traverser->PtrSimpleWindow->window;

      XSendEvent(display, 
                 Traverser->PtrSimpleWindow->window, 
                 False, 
                 StructureNotifyMask, 
                &CloseDown);

      Traverser = Traverser->Next;
   }
}


//-------------------------------------------------------------------------
//  C h e c k T e r m i n a t i o n
// Function:       Checks to see if the window manager is empty. If it is,
//                 ApiEnd is called.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: If the window manager is empty, ApiEnd is called
// Returns:        Quit, the window manager is empty and ApiEnd has been 
//                 called. Otherise, Running.

ManagerStatus WindowManager::CheckTermination() {

   if (Empty()) {
      ApiEnd();
      return Quit;
   }
 
   return Running;
}


//-------------------------------------------------------------------------
//  G e t W i n d o w
// Function:       Obtain a window from the window manager
// Parameters:     WindowObject, a pointer to a SimpleWindow specifying 
//                    the window to get
// Preconditions:  WindowObject must point to valid memory.
// Output:         None
// Postconditions: None
// Returns:        The window handle of the window requested
  
Window WindowManager::GetWindow(const SimpleWindow *WindowObject) const {
         
    return ((WindowObject) ? WindowObject->window : None);
}


//-------------------------------------------------------------------------
//  A p i M a i n I s C o m p l e t e d 
// Function:       Informs the window manager that ApiMain has been 
//                 completed
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: ApiMainCompleted is set to True.
// Returns:        None
  
void WindowManager::ApiMainIsCompleted() {
         
   ApiMainCompleted = True;
}


//-------------------------------------------------------------------------
//  I s A p i M a i n I s C o m p l e t e d 
// Function:       Returns True if ApiMain has been completed
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        True, ApiMain completed. False, ApiMain still in 
//                 progress

Bool WindowManager::IsApiMainCompleted() const {
         
   return ApiMainCompleted;
}


//-------------------------------------------------------------------------
//  C o l o r s M a t c h e d  
// Function:       Returns True if colors were obtained from the server
//                 successfully 
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        True, needed colors are available. Otherise, False.

Bool WindowManager::ColorsObtained() const {
         
   return ColorsMatched;
}


//-----------------------------------------------------------------------\\
//  M a i n  F u n c t i o n                                             \\

#ifndef USING_CC
int main() {
#else
int main() {
#endif
   XEvent         Report;
   DispatchStatus status(Handled);
   SimpleWindow  *Win;

   if (WinManager.ColorsObtained()) {
      ApiMain();
      WinManager.ApiMainIsCompleted();

      while ((status != EndProgram) && (!WinManager.Empty())) {
 
         if (XPending(display) > 0) {
            XNextEvent(display, &Report);
            Win = WinManager.GetWindow(Report);
            if (Win) {
               if (FilterEvent(&Report, Win)) {
                  status = WinManager.DispatchMessage(Report, Win);

#ifdef DEBUG_UNHANDLED_EVENTS                     
                  if (status == UnHandled)
                     cout << "Unhandled Event: " << EventNames[Report.type] 
                          << endl
                          << "Window:          " << Report.xany.window << "\n";
#endif
               }
            }  

#ifdef DEBUG_UNHANDLED_EVENTS
            else {
               cout << "An event occurred and no window was identified.\n"
                    << "Event type: " << EventNames[Report.type] << "\n"
                    << "Window:     " << Report.xany.window << "\n";
            }
#endif
         }

         WinManager.CheckTimers();
#ifdef USING_CC
         cout << flush;
#endif
      }
   }

#ifdef USING_CC
   return 1;
#endif
}


