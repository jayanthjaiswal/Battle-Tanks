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
   FILE:        GraphicManager.h
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/16 18:25:23 dcl3a>

   Description
   ===========
   This file contains the class declaration of GraphicManager.
*/

//-----------------------------------------------------------------------\\
// Class name:
//    GraphicManager
//
// Purpose:
//    Encapsulates methods for manipulating a list of Graphic objects
//
// Member functions:
//    Public members:
//       GraphicManager()
//          Initializes member variables
//      ~GraphicManager()
//          Deallocates the memory dedicated to the items in the list
//       unsigned int GetListSize() const
//          Returns the size of the list which is the number of Graphic 
//          objects
//       Bool IsEmpty() const
//          Returns True if the list is empty. Returns False otherwise.
//       GraphicNode* First()
//          Returns the first item in the list
//       GraphicNode* Next()
//          Moves an internal pointer to the next item in the list and 
//          returns that item
//       void InsertGraphic(GraphicNode *NewGraphicNode)
//          Inserts a pointer to a GraphicNode into the front of the list
//          -- The parameter specifies the GraphicNode to insert into
//             the list.
//       void AppendGraphic(GraphicNode *NewGraphicNode)
//          Appends a pointer to a GraphicNode to the end of the list
//          -- The parameter specifies the GraphicNode to append to the 
//             list.
//      const GraphicNode* GetFirstMessage() const
//          Searches through the list for the first Graphic that is a
//          MessageGraphic and returns it
//      GraphicPosition GetLowerRightOfFirstMessage() const
//          Searches through the list for the first Graphic that is a
//          MessageGraphic and returns its device coordinate position
//          for it lower right corner 
//      void EmptyList()
//          Deallocates memory devoted to item in the list and resets the
//          state
//
// Instance variables:
//    ListSize
//       A unsigned int specifying the number of nodes in the list 
//    Head
//       A pointer to a GraphicNode specifying the first node in the list
//    Tail
//       A pointer to a GraphicNode specifying the last node in the list
//    Current
//       A pointer to a GraphicNode specifying the current node for 
//       purposes of traversing the list
//-----------------------------------------------------------------------//

#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "Graphic.h" 


//-----------------------------------------------------------------------\\
//  G r a p h i c M a n a g e r  C l a s s                               \\

class GraphicManager {
   public:
      GraphicManager();
     ~GraphicManager();

      unsigned int GetListSize() const;
      Bool         IsEmpty    () const;
      GraphicNode* First();
      GraphicNode* Next ();

      void InsertGraphic(GraphicNode *NewGraphicNode);
      void AppendGraphic(GraphicNode *NewGraphicNode);
     
      const GraphicNode* GetFirstMessage            () const;
      GraphicPosition    GetLowerRightOfFirstMessage() const;

      void EmptyList();

   private:
      unsigned int ListSize;
      GraphicNode *Head;
      GraphicNode *Tail;
      GraphicNode *Current;
};


#endif
