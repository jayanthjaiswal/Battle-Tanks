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
   FILE:        Alert.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/27 16:30:30 dcl3a>

   Description
   ===========
   Source file for the implementation of the ButtonWindow and 
   AlertWindow classes.
*/         
#include "Alert.h"


//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern int               ScreenNbr;
extern Display          *display;
extern unsigned long int ColorTable[MaxColors];
extern unsigned long int ButtonColorTable[];

extern void Terminate();


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l  F u n c t i o n s                               \\

//-------------------------------------------------------------------------
//  C r e a t e W i n d o w
// Function:       Creates and displays a window
// Parameters:     window, a Window specifying the window handle
//                 Title, a string specifying the title of the window
//                 WinX, an integer specifying the x coordinate of the
//                    upper left hand corner of the window
//                 WinY, an integer specifying the y coordinate of the
//                    upper left hand corner of the window
//                 WinWidth, an integer specifying the width of the window
//                 WinHeigth, an integer specifying the height of the 
//                    window
//                 CustomSize, a boolean specifying whether the window is 
//                    resizable with the mouse. If not specified, a default 
//                    value of False is given.
// Preconditions:  display must be the current Display. ScreenNbr must be 
//                 a valid screen number.
// Output:         If either the window fails to be created or the window
//                 manager doesn't successfully receive information about
//                 window, a message is sent to standard output. Upon
//                 successful completion, a window is displayed.
// Postconditions: Upon successful completion, window contains a valid
//                 window handle. A window is displayed on Display,
//                 display and the window manager knows about the window.
// Returns:        True, a window is successfully created
//                 False, a window failed to be created

Bool CreateWindow(Window       &window,
                  const string &Title,
                  int           WinX,
                  int           WinY,
                  int           WinWidth,
                  int           WinHeight,
                  Pixmap        ScrBuff,
                  const Bool   &CustomSize) {

   window = XCreateSimpleWindow(display,
                                RootWindow(display, ScreenNbr),
                                WinX,
                                WinY,
                                WinWidth,
                                WinHeight,
                                BorderSize,
                                BlackPixel(display, ScreenNbr),
                                ColorTable[White]);

   XSelectInput(display, window, NormalWindowEventMask);

   if (window == None) {
      cerr << "Error opening window in function CreateWindow.\n";
      return False;
   }

   if (SetWindowHints(window,
                      Title,
                      WinX,
                      WinY,
                      WinWidth,
                      WinHeight,
                      CustomSize)) {
      XMapRaised(display, window);

      XEvent Report;
      XWindowEvent(display, window, ExposureMask, &Report);

      return True;
   }

   cout << "Window hints were unacceptible\n";

   XDestroyWindow(display, window);
   return False;
}


//-------------------------------------------------------------------------
//  S e t W i n d o w H i n t s
// Function:       Indicates to the window manager desirable attributes for 
//                 a newly created window.
// Parameters:     window, a Window specifying the window handle
//                 Title, a string specifying the title of the window
//                 WinX, an integer specifying the x coordinate of the 
//                    upper left hand corner of the window
//                 WinY, an integer specifying the y coordinate of the 
//                    upper left hand corner of the window
//                 WinWidth, an integer specifying the width of the window
//                 WinHeigth, an integer specifying the height of the 
//                    window
//                 CustomSize, a boolean specifying whether the window is 
//                    resizable with the mouse   
// Preconditions:  The Window, window must be a value window handle. 
//                 display must be the current Display.
// Output:         If memory allocation for the strings fails, a message is
//                 sent to standard output. Upon successful completion, a 
//                 border is placed around the window. 
// Postconditions: Upon successful completion, the window manager knows the 
//                 maximum and minimum size the window can be and its 
//                 location. The window is given a border. The window is 
//                 given a title. 
// Returns:        True, the window manager has successfully received 
//                    information regarding the window
//                 False, memory allocation failed

Bool SetWindowHints(const Window &window,
                    const string &Title,
                    int           WinX,
                    int           WinY, 
                    int           WinWidth, 
                    int           WinHeight,
                    const Bool   &CustomSize) {
   XTextProperty WindowName;
   XTextProperty IconName;
   XSizeHints    SizeHints;
   XWMHints      WMHints;
   int           status;

   char *WindowTitle((char *) Title.c_str());

   status = XStringListToTextProperty(&WindowTitle, 1, &WindowName);
   if (!status) {
      cerr << "Memory allocation for the WindowName string failed in "
           << "function SetWMHints.\n";
      return False;
   }

   status = XStringListToTextProperty(&WindowTitle,   1, &IconName);
   if (!status) {
      cerr << "Memory allocation for the IconName string failed in "
           << "function SetWMHints.\n";
      return False;
   }

   if (CustomSize) {
      SizeHints.min_width  = WinWidth;
      SizeHints.min_height = WinHeight;
      SizeHints.max_width  = WinWidth;
      SizeHints.max_height = WinHeight;
      SizeHints.flags      = PPosition | PSize | PMinSize | PMaxSize;
   }
   else {  
      SizeHints.min_width  = MinScreenWidth;
      SizeHints.min_height = MinScreenHeight;
      SizeHints.flags      = PPosition | PSize | PMinSize;
   }

   WMHints.input         = True;
   WMHints.initial_state = NormalState;
   WMHints.flags         = StateHint | InputHint;
  
   XSetWMProperties(display, 
                    window,
                   &WindowName,
                   &IconName,
          (char **) NULL, 
                    0, 
                   &SizeHints,
                   &WMHints,
    (XClassHint *) NULL);

  XFree(WindowName.value);
  XFree(IconName.value);
  return True;
};



//-------------------------------------------------------------------------
//  I s W M C l o s e W i n d ow
// Function:       Indicates whether the event received means that a user
//                 tried to close a window through the window manager.
// Parameters:     Report, a XClientMessageEvent specifying information 
//                    about a window event.
// Preconditions:  Report must point to valid memory.
// Output:         None
// Postconditions: None
// Returns:        True, a user requested to close a window through the
//                    window manager
//                 False, some other event occured

Bool IsWMCloseWindow(const XClientMessageEvent *Report) {
   Atom ProtocolsAtom(XInternAtom(display, "WM_PROTOCOLS",     False));
   Atom DeleteAtom   (XInternAtom(display, "WM_DELETE_WINDOW", False));

   if ((Report->message_type == ProtocolsAtom) && 
       (Report->data.l[0]    == DeleteAtom)    &&
       (Report->format       == DeleteWindowFormat))
      return True;

   return False;
}


//-------------------------------------------------------------------------
//  S e t W M C l o s e  W i n d o w
// Function:       Indicates to the window manager that closing the window 
//                 specified by window handle, window should be handled 
//                 internally with this software and not just closed 
//                 automatically.
// Parameters:     window, a Window specifying the window handle 
// Preconditions:  Window, window must be a valid window handle
// Output:         None
// Postconditions: The window manager knows not to close this window but
//                 rather to put a message in the event queue.
// Returns:        None

void SetWMCloseWindow(const Window &window) {
   Atom ProtocolsAtom(XInternAtom(display, "WM_PROTOCOLS",     False));
   Atom DeleteAtom   (XInternAtom(display, "WM_DELETE_WINDOW", False));

   if ((DeleteAtom != None) && (ProtocolsAtom != None))
      XSetWMProtocols(display, window, &DeleteAtom, 1);  
}


//-----------------------------------------------------------------------\\
//  B u t t o n W i n d o w  C o d e                                     \\

//-------------------------------------------------------------------------
//  B u t t o n W i n d o w
// Function:       Sets the state variable, Depressed to indicate that the
//                 button is in the up position.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: Depressed is set to False.
// Returns:        None

ButtonWindow::ButtonWindow() : Depressed(False), WindowState(WindowClosed) {

}


//-------------------------------------------------------------------------
//  ~ B u t t o n W i n d o w
// Function:       Does nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

ButtonWindow::~ButtonWindow() {

   if (WindowState == WindowOpen)
      Close();
}


//-------------------------------------------------------------------------
//  G e t W i n d o w
// Function:       Returns the window handle.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The window handle.

Window ButtonWindow::GetWindow() const {
         
   return window;
}


//-------------------------------------------------------------------------
//  O p e n
// Function:       Makes a button visible and active. 
// Parameters:     ParentWindow, a window specifying the window handle of 
//                    the window where the button will reside
//                 ParentWindowWidth, an integer specifying the width of 
//                    the parent window
//                 ParentWindowHeight, an integer specifying the height of
//                    paent window
// Preconditions:  Window, ParentWindow must be a valid window handle.
// Output:         If the window fails to open, a message is sent to 
//                 standard output. Upon successful completion, a window 
//                 that looks like a button is displayed
// Postconditions: A window is displayed that looks like a button with a
//                 label.
// Returns:        True, successful completion
//                 False, the window failed to open

WindowStatus ButtonWindow::Open(const Window &ParentWindow,
                                int           ParentWindowWidth, 
                                int           ParentWindowHeight) {

   WinX      = ParentWindowWidth      / 2 -  ButtonWidth / 2;
   WinY      = ParentWindowHeight * 3 / 4 - ButtonHeight / 2;
   WinWidth  = ButtonWidth;
   WinHeight = ButtonHeight;

   window = XCreateSimpleWindow(display,
                                ParentWindow,
                                WinX,
                                WinY,
                                WinWidth,
                                WinHeight,
                                ButtonBorderSize,
                                BlackPixel(display, ScreenNbr),
                                ButtonColorTable[Top]);

   if (window == None) {
      cout << "Error opening window in function ButtonAsWindow::Open.\n";
      return WindowFailure;
   }

   XMapWindow  (display, window);
   XSelectInput(display, window, AlertButtonEventMask);
  
   ButtonGraphic(ButtonMessage, 
                 OkayUpPosition,
                 Position(WinWidth, WinHeight),
                 ButtonColorTable[TopShadow],
                 ButtonColorTable[BottomShadow],
                 window);
   Depressed = False;

   return WindowOpen;
}


//-------------------------------------------------------------------------
//  C l o s e
// Function:       Destroys the window
// Parameters:     None
// Preconditions:  Window, window must be a valid window handle
// Output:         The window is removed.
// Postconditions: The window is removed.
// Returns:        None

void ButtonWindow::Close() {

   if (WindowState == WindowOpen)
      XDestroyWindow(display, window);
}


//-------------------------------------------------------------------------
//  M o u s e C l i c k  E v e n t
// Function:       Redraws the button window to indicate the position of 
//                 the button.
// Parameters:     State, a ButtonState indicating whether the button is
//                    up or down
// Preconditions:  Window, window must be a valid window handle. The 
//                 ButtonColorTable must have valid data.
// Output:         The window is redrawn to indicate the state.
// Postconditions: The window is redrawn to indicate the state.
// Returns:        None

void ButtonWindow::MouseClickEvent(const ButtonState& State) {
   unsigned long int TopColor    (ButtonColorTable[BottomShadow]);
   unsigned long int BottomColor (ButtonColorTable[TopShadow]); 
   Position          TextPosition(OkayDownPosition);

   Depressed = True;
   if (State == ButtonUp) {
      TopColor     = ButtonColorTable[TopShadow];
      BottomColor  = ButtonColorTable[BottomShadow];
      TextPosition = OkayUpPosition;
      Depressed    = False;
   }

   ButtonGraphic(ButtonMessage,
                 TextPosition, 
                 Position(WinWidth, WinHeight),
                 TopColor,
                 BottomColor,
                 window);
}


//-------------------------------------------------------------------------
//  R e f r e s h E v e n t
// Function:       Redraws the button window
// Parameters:     None
// Preconditions:  Window, window must be a valid window handle. The 
//                 ButtonColorTable must have valid data.
// Output:         The window is redrawn.
// Postconditions: The window is redrawn.
// Returns:        None

void ButtonWindow::RefreshEvent() {
   unsigned long int TopColor    (ButtonColorTable[BottomShadow]);
   unsigned long int BottomColor (ButtonColorTable[TopShadow]); 
   Position          TextPosition(OkayDownPosition);

   if (!Depressed) {
      TopColor     = ButtonColorTable[TopShadow];
      BottomColor  = ButtonColorTable[BottomShadow];
      TextPosition = OkayUpPosition;
   }

   ButtonGraphic(ButtonMessage,
                 TextPosition, 
                 Position(WinWidth, WinHeight),
                 TopColor,
                 BottomColor,
                 window);
}


//-----------------------------------------------------------------------\\
//  A l e r t W i n d o w  C o d e                                       \\

//-------------------------------------------------------------------------
//  A l e r t W i n d o w
// Function:       Displays a dialog box with a message, traps the pointer 
//                 within the dialog box, and closes when a mouse click 
//                 event occurs in the button window.
// Parameters:     iWindowTitle, a string specifying the title of the 
//                    window
//                 iMessage, a string specifying the message to be placed
//                    within the window
// Preconditions:  Display, display must be valid.
// Output:         An alert box is displayed during the execution of this
//                 function and then closed.
// Postconditions: The alert window is closed
// Returns:        None

AlertWindow::AlertWindow(const string &iWindowTitle, 
                         const string &iMessage,
                         void (*Operation)()) 
                       : WindowTitle (iWindowTitle),
                         Message     (iMessage) {

   Drawables.InsertGraphic(new EllipseGraphic  (ExclamationColor, 
		   			        UpperLeftExCircle, 
			   		        LowerRightExCircle));
   Drawables.AppendGraphic(new X11BitMapGraphic(exclam_bits,
		   			        ExclamationColor,
			   		        ExclamationPosition,
                                                ExclamationSize));

   AddMessageToList();
   if (!SetLocationAndSize()) {
      Terminate();
      return;
   }

   if ((Open()) && (Operation))
      Operation();
}


//-------------------------------------------------------------------------
//  ~ A l e r t W i n d o w
// Function:       Nothing
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        None

AlertWindow::~AlertWindow() {

}


//-------------------------------------------------------------------------
//  A d d M e s s a g e T o L i s t
// Function:       Adds the message to the list of drawables for the dialog 
//                 box.
// Parameters:     None
// Preconditions:  Display, display must be valid.
// Output:         None
// Postconditions: GraphicManager, Drawables contains the message to be 
//                 displayed in the dialog box.
// Returns:        None

void AlertWindow::AddMessageToList() {
   XFontStruct *Font;
  
   if (LoadFont(&Font, WindowFont)) {
      unsigned int TextWidth(XTextWidth(Font,
                                        Message.c_str(), 
                                        Message.length()));
      unsigned int TextHeight(Font->ascent + Font->descent);
      Position     TextSize  (d_to_l(TextWidth), d_to_l(TextHeight));

      Drawables.AppendGraphic(new MessageGraphic(Message,
					         White, 
					         AlertTextPosition, 
					         AlertTextPosition + 
                                                    TextSize));
      XFreeFont(display, Font);
   }
   else {
      cout << "\n\nAlertWindow::AddMessageToList\n"
           << "Unable to obtain to allocate memory to a font structure\n";
      Terminate();
      return;
   }
}


//-------------------------------------------------------------------------
//  S e t L o c a t i o n A n d S i z e
// Function:       Set the size and location of the window.
// Parameters:     None
// Preconditions:  Display, display must be valid. The message must be in
//                 the list of drawables, Drawables.
// Output:         If the font for the message fails to load, a message is
//                 sent to standard output.
// Postconditions: Upon successful completion, the size and location of the 
//                 window are set.
// Returns:        True, successful completion
//                 False, the font failed to load

Bool AlertWindow::SetLocationAndSize() {
   unsigned int  MaxWindowWidth(DisplayWidth(display, ScreenNbr));  
   unsigned int  TextWidth;
   XFontStruct  *Font;

   if (LoadFont(&Font, WindowFont)) {
      TextWidth = XTextWidth(Font,
                             WindowTitle.c_str(), 
                             WindowTitle.length());
      XFreeFont(display, Font);
   }
   else {
      cout << "\n\nAlertWindow::SetLocationAndSize\n"
           << "Unable to allocate memory to a font structure\n";
      return False;
   }

   WinWidth = AlertWindowDefaultWidth;
   if (TextWidth > DefaultTitleWidth) {
      if (TextWidth < MaxWindowWidth)
         WinWidth = DefaultTitleSpacing + TextWidth;
      else
         WinWidth = MaxWindowWidth - SpaceBuffer;
   }

   int LowerRightOfText(
      Drawables.GetLowerRightOfFirstMessage().GetXCoordinate() +
      AlertTextSpaceBuffer);
   if ((LowerRightOfText > WinWidth) && (LowerRightOfText < MaxWindowWidth))
      WinWidth  = LowerRightOfText;
   else if (LowerRightOfText > MaxWindowWidth)
      WinWidth = MaxWindowWidth - SpaceBuffer;

   GraphicPosition CenterOfDisplay(DisplayWidth (display, ScreenNbr) / 2, 
                                   DisplayHeight(display, ScreenNbr) / 2);
   WinX      = CenterOfDisplay.GetXCoordinate()  - (WinWidth / 2);
   WinY      = CenterOfDisplay.GetYCoordinate() - 
              (AlertWindowDefaultHeight  / 2);
   WinHeight = AlertWindowDefaultHeight;

   return True;
}


//-------------------------------------------------------------------------
//  O p e n 
// Function:       Creates the window and displays it.
// Parameters:     None
// Preconditions:  Display, display must be valid.
// Output:         If either the button failed to open or the window could
//                 not be created, a message is sent to standard output. 
//                 Upon successful completion, the alert box is displayed.
// Postconditions: The alert box is displayed.
// Returns:        True, successful completion
//                 False, either the button failed to open or the window 
//                    could not be created

Bool AlertWindow::Open() {
   
   if (CreateWindow(window, 
                    WindowTitle, 
                    WinX, 
                    WinY, 
                    WinWidth, 
                    WinHeight,
                    True)) {
      XSelectInput(display, window, AlertWindowEventMask);
      SetWMCloseWindow(window);
      
      if (!ButtonWin.Open(window, WinWidth, WinHeight)) {
         cout << "Error setting up the button in function "
              << "AlertWindow::Open.\n";
         XDestroyWindow(display, window);
         Terminate();
         return False;
      }

      RefreshEvent();
      XGrabPointer(display,
                   window,
                   True,
                   ButtonEventMask,
                   GrabModeAsync,
                   GrabModeAsync,
                   window,
                   None,
                   CurrentTime);

      EventHandler();

      XUngrabPointer(display, CurrentTime);
   }
   else {
      cout << "Unable to open the Alert box.\n";
      Terminate();
      return False;
   }

   return True;
}


//-------------------------------------------------------------------------
//  E v e n t H a n d l e r
// Function:       Sets up an event loop to wait for a mouse click.
// Parameters:     None
// Preconditions:  Display, display must be valid.
// Output:         None
// Postconditions: The user pushed the button and the window closed.
// Returns:        None

void AlertWindow::EventHandler() {
   XEvent Report;
   Bool   WindowOpen(True);

   while (WindowOpen) {
      XNextEvent(display, &Report);
      switch(Report.type) {
         case Expose:
            if (Report.xexpose.count == 0) {
               if (Report.xany.window == window)
                  RefreshEvent();
               else if (Report.xany.window == ButtonWin.GetWindow())
                  ButtonWin.RefreshEvent();
	    }

            break;
         case ClientMessage:
            if (IsWMCloseWindow((XClientMessageEvent*) &Report)) {
               if (Report.xany.window == window) {
                  ButtonWin.Close();
                  XDestroyWindow(display, window);
                  WindowOpen = False;
	       }
	    }

            break;
         case ButtonPress:
            if (Report.xany.window == ButtonWin.GetWindow())
               WindowOpen = ButtonPressed(Report.xbutton.button);

            break;
         case MappingNotify:
            XRefreshKeyboardMapping((XMappingEvent *) &Report);
            break;
      }
   }
}


//-------------------------------------------------------------------------
//  R e f r e s h E v e n t
// Function:       Redraws the alert box
// Parameters:     None
// Preconditions:  Window, window must be a valid window handle. Display, 
//                 display must be valid.
// Output:         The window is redrawn.
// Postconditions: The window is redrawn.
// Returns:        None

void AlertWindow::RefreshEvent() {
   int          ithDrawable(0);
   GraphicNode *Traverser(Drawables.First());

   for (;ithDrawable <= NbrStaticAlertDrawables; ithDrawable++) {
      Traverser->Draw(window);
      Traverser = Drawables.Next();
   }

}


//-------------------------------------------------------------------------
//  B u t t o n P r e s s e d
// Function:       Informs the button that a mouse click has occured with 
//                 in it indicating that it should redraw itself in the 
//                 currect state.
// Parameters:     MouseButton, an integer specifying which mouse button
//                    was pushed
// Preconditions:  The alert window must be open.
// Output:         As the mouse click events occur in the button window, 
//                 the button window redraws itself.
// Postconditions: The mouse button has been released and either the 
//                 window has been closed or the button has come back up. 
// Returns:        False, the window is closed. Otherwise, True is 
//                 returned.

Bool AlertWindow::ButtonPressed(int MouseButton) {
   XEvent       Report;
   unsigned int Button(MouseButton);
 
   ButtonWin.MouseClickEvent();

   while (True) {
      while (XCheckTypedEvent(display, ButtonPress, &Report));
      XMaskEvent(display, ButtonReleaseMask, &Report);

      if (Report.xbutton.button = Button)
         break;
   }

   if (Report.xbutton.window == ButtonWin.GetWindow()) {
      ButtonWin.Close();
      XDestroyWindow(display, window);          
      return False;        
   }
   else
      ButtonWin.MouseClickEvent(ButtonUp);

   return True;
}







