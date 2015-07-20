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
   FILE:        Alert.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/24 03:07:45 dcl3a>

   Description
   ===========
   Class definitions for ButtonWindow and AlertWindow
*/

//-----------------------------------------------------------------------\\
// Class name:
//    ButtonWindow
//
// Purpose:
//    An instantiated ButtonWindow gives the visual illusion that 
//    a button exists. A ButtonWindow changes its visual appearance 
//    when a mouse click event occurs within it.
//
// Member functions:
//    Public members:
//       ButtonWindow()
//          Sets the state variable Depressed to False indicating that 
//          the button is in the up position.
//      ~ButtonWindow()
//          No clean up is necessary.
//       Bool Open(const Window &ParentWindow,
//                 int           ParentWindowWidth, 
//                 int           ParentWindowHeight)
//          Creates the actual window that is the button and displays it.
//          Returns True if the function is successfully completed. 
//          Otherwise, False is returned.
//          -- The first parameter specifies the window where the button 
//             will be placed.
//          -- The second parameter specifies the width of the window 
//             where button will be placed.
//          -- The third parameter specifies the height of the window
//             where the button will be placed.       
//       void Close()
//          Destroys the window that is the button.
//       void MouseClickEvent(const ButtonState &State = Down)
//          Redraws the button window to indicate the position of the button.
//          -- The parameter specifies whether the button is up or down. The
//             default value is Down.
//       void RefreshEvent()
//          Redraws the button.
//       Window GetWindow() const
//          Returns the window handle.
//
// Instance variables:
//    WinX
//       An integer specifying the x coordinate for the upper left 
//       corner of the window 
//    WinY
//       An integer specifying the y coordinate for the upper left 
//       corner of the window
//    WinWidth
//       An integer specifying the width of the window  
//    WinHeight
//       An integer specifying the height of the window
//    Depressed
//       A boolean indicating whether the button is up or down
//    window
//       A Window specifying the window handle.
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------\\
// Class name:
//    AlertWindow
//
// Purpose:
//    Provides a graphical dialog box for displaying messages.
//
// Member functions:
//    Public members:
//       AlertWindow(const string &iWindowTitle, 
//                   const string &iMessage, 
//                   void (*Operation)() = NULL)
//          Displays a dialog box with a message, traps the pointer 
//          within the dialog box, and closes when a mouse click 
//          event occurs in the button window.
//          -- The first parameter specifies the title to be placed on
//             the dialog box.
//          -- The second parameter specifies the message to be placed
//             within the dialog box.
//          -- The third parameter specifies an optional operation to be
//             executed when the dialog box is closed.
//      ~AlertWindow()
//          No code necessary. All the work to create and destory the 
//          dailog box is performed in the constructor.
//
//    Private members:
//       void AddMessageToList()
//          Adds the message to the list of drawables for the dialog box.
//       Bool SetLocationAndSize()
//          Determines the location and size of the dialog box. Returns 
//          True if the function is successfully completed. Otherwise,
//          False is returned.
//       void EventHandler()
//          Sets up an event loop to wait for a mouse click.
//       void Open()
//          Creates the window and displays it.
//       void RefreshEvent()
//          Redraws the window.
//       Bool ButtonPressed(int MouseButton)
//          Informs the button that a mouse click has occured with in it
//          indicating that it should redraw itself in the currect state.
//          True is returned if the window is still open. Otherwise, False,
//          is returned.
//          -- The first parameter specifies the mouse button that was
//             pushed.
//
// Instance variables:
//    WinX
//       An integer specifying the x coordinate for the upper left 
//       corner of the window 
//    WinY
//       An integer specifying the y coordinate for the upper left 
//       corner of the window
//    WinWidth
//       An integer specifying the width of the window  
//    WinHeight
//       An integer specifying the height of the window
//    Depressed
//       A boolean indicating whether the button is up or down
//    window
//       A Window specifying the window handle.
//    WindowTitle
//       A string specifying the title of the dialog box.
//    Message
//       A string specifying the message placed inside the dialog box.
//    ButtonWin
//       A ButtonWindow specifying the button mechanism for the dialog
//       box.
//    Drawables
//       A GraphicManager used to keep track of the drawables for the
//       alert box.
//-----------------------------------------------------------------------//

 
//-----------------------------------------------------------------------\\
// Additional functions:
//    Bool SetWindowHints(const Window &window,
//                        const string &Title,
//                        int           WinX,
//                        int           WinY,
//                        int           WinWidth, 
//                        int           WinHeight,
//                        const Bool   &CustomSize)
//       Indicates to the window manager desirable attributes for a
//       newly created window. The window manager may or may not use
//       this information. Returns True if the function is successfully 
//       completed. Otherwise, False is returned. 
//       -- The first parameter specifies the window handle for the
//          window being setup.
//       -- The second parameter specifies the title of the window.
//       -- The third parameter specifies the x coordinate of the upper
//          left hand corner of the window.
//       -- The forth parameter specifies the y coordinate of the upper
//          left hand corner of the window.
//       -- The fifth parameter specifies the width of the window.
//       -- The sixth parameter specifies the height of the window.
//       -- The last parameter specifies whether the window is resizable
//          with the mouse.
//    Bool CreateWindow(Window       &window,
//                      const string &Title,
//                      int           WinX,
//                      int           WinY, 
//                      int           WinWidth, 
//                      int           WinHeight,
//                      const Bool   &CustomSize = False)
//       Creates and displays a window. Returns True if the function is 
//       successfully completed. Otherwise, False is returned.
//       -- The first parameter specifies the window handle for the
//          window being setup.
//       -- The second parameter specifies the title of the window.
//       -- The third parameter specifies the x coordinate of the upper
//          left hand corner of the window.
//       -- The forth parameter specifies the y coordinate of the upper
//          left hand corner of the window.
//       -- The fifth parameter specifies the width of the window.
//       -- The sixth parameter specifies the height of the window.
//       -- The last parameter optionally specifies whether the window 
//          is resizable with the mouse. The default value is False.
//    Bool IsWMCloseWindow(const XClientMessageEvent *Report)
//       Returns True if the window manager received a request to close
//       a window by the user. Otherwise, False is returned.
//       -- The parameter specifies the event that occured.
//    void SetWMCloseWindow(const Window &window)
//       Indicates to the window manager that closing the window should
//       be handled internally with this software and not just closed 
//       automatically.
//       -- The parameter specifies the window handle for the window 
//          given this status.
//-----------------------------------------------------------------------//

#ifndef ALERT_H
#define ALERT_H

#include "exclam.xbm"
#include "EllipseGraphic.h"
#include "X11BitmapGraphic.h"
#include "ButtonGraphic.h"
#include "GraphicManager.h"


const int             SpaceBuffer              = 20;
const int             AlertWindowDefaultWidth  = 277;
const int             AlertWindowDefaultHeight = 126;
const int             DefaultTitleWidth        = 190;
const int             DefaultTitleSpacing      = 10;
const int             AlertTextSpaceBuffer     = 15;
const int             ButtonBorderSize         = 1;
const int             BorderSize               = 1;
const int             MinScreenWidth           = 120;
const int             MinScreenHeight          = 0;
const int             DeleteWindowFormat       = 32;
const int             NbrButtonColors          = 3;
const int             NbrStaticAlertDrawables  = 2;
const long            ButtonEventMask          = ButtonPressMask |     
                                                 ButtonReleaseMask;
const long            AlertButtonEventMask     = ExposureMask        |
                                                 OwnerGrabButtonMask |
                                                 ButtonEventMask;
const long            AlertWindowEventMask     = ExposureMask    | 
                                                 ButtonEventMask;     
const long            NormalWindowEventMask    = ExposureMask |      
                                                 StructureNotifyMask;

#ifndef USING_CC
const color           ExclamationColor           (Yellow);
const string          ButtonMessage              ("O K");
#else
const color           ExclamationColor          = Yellow;
const string          ButtonMessage             = "O K";
#endif

const Position        ExclamationPosition        (0.78, 0.52);
const Position        UpperLeftExCircle          (0.5,  0.5);
const Position        LowerRightExCircle         (1.3,  1.3);
const Position        AlertTextPosition          (1.75, 0.7);
const Position        OkayUpPosition             (1.9,  0.8);
const Position        OkayDownPosition           (2.0,  0.9);

const GraphicPosition ExclamationSize     (exclam_width, exclam_height);

enum ButtonState {ButtonUp, ButtonDown};


//-----------------------------------------------------------------------\\
//  B u t t o n W i n d o w  C l a s s                                   \\

class ButtonWindow {
   public:
      ButtonWindow();
     ~ButtonWindow();

      WindowStatus Open(const Window &ParentWindow,
                        int           ParentWindowWidth, 
                        int           ParentWindowHeight);
      void Close();

      void MouseClickEvent(const ButtonState &State = ButtonDown);
      void RefreshEvent   ();

      Window GetWindow() const;

   private:
      int WinX; 
      int WinY; 
      int WinWidth;  
      int WinHeight;

      Bool         Depressed;
      Window       window;
      WindowStatus WindowState;
};


//-----------------------------------------------------------------------\\
//  A l e r t W i n d o w  C l a s s                                     \\

class AlertWindow {
   public:
      AlertWindow(const string &iWindowTitle, 
                  const string &iMessage,
                  void (*Operation)() = NULL);
     ~AlertWindow();

   private:
      int WinX; 
      int WinY; 
      int WinWidth;  
      int WinHeight;

      string WindowTitle;
      string Message;

      Window         window;
      ButtonWindow   ButtonWin;
      GraphicManager Drawables;

      void AddMessageToList  ();
      Bool SetLocationAndSize();
      void EventHandler      ();
      Bool Open              ();
      void RefreshEvent      ();
      Bool ButtonPressed     (int MouseButton);
};


//-----------------------------------------------------------------------\\
//  A d d i t i o n a l   F u n c t i o n s                              \\

Bool CreateWindow  (Window       &window,
                    const string &Title,
                    int           WinX,
                    int           WinY,
                    int           WinWidth,
                    int           WinHeight,
                    Pixmap        ScrBuff,
                    const Bool   &CustomSize = False);
Bool SetWindowHints(const Window &window,
                    const string &Title,
                    int           WinX,
                    int           WinY,
                    int           WinWidth,
                    int           WinHeight,
                    const Bool   &CustomSize);

Bool IsWMCloseWindow (const XClientMessageEvent *Report);
void SetWMCloseWindow(const Window              &window);


#endif









