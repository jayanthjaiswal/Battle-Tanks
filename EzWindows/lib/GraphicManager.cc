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
   FILE:        GraphicManager.cc
   AUTHOR:      Devon Lockwood
   Time-stamp:  <97/01/16 18:22:33 dcl3a>

   Description
   ===========
   Source file for the implementation of the GraphicManager class
*/      
#include "GraphicManager.h"
  

//-----------------------------------------------------------------------\\
//  G l o b a l   O b j e c t s                                          \\

extern void Terminate();


//-----------------------------------------------------------------------\\
//  G r a p h i c M a n a g e r   C o d e                                \\

//-------------------------------------------------------------------------
//  G r a p h i c M a n a g e r
// Function:       Initializes the member variables.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The member objects are initialized with default values. 
// Returns:        None

GraphicManager::GraphicManager() : ListSize(0), 
                                   Head    (NULL), 
                                   Tail    (NULL), 
                                   Current (NULL) {

}


//-------------------------------------------------------------------------
//  ~ G r a p h i c M a n a g e r
// Function:       Empties the list
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The list is empty.
// Returns:        None

GraphicManager::~GraphicManager() {
         
   EmptyList();
}


//-------------------------------------------------------------------------
//  G e t L i s t S i z e
// Function:       Returns the size of the list which is the number of 
//                 nodes
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The list size

unsigned int GraphicManager::GetListSize() const {
         
   return ListSize;
}


//-------------------------------------------------------------------------
//  I s E m p t y
// Function:       Indicates whether there are items in the list.
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        True, the list contains items. Otherwise, False. 

Bool GraphicManager::IsEmpty() const {
         
   return (ListSize == 0);
} 


//-------------------------------------------------------------------------
//  A p p e n d G r a p h i c
// Function:       Appends a GaphicNode to the end of the list
// Parameters:     NewGraphicNode, a pointer to a GraphicNode specifying
//                    the node to append
// Preconditions:  NewGraphicNode must own its own memory.
// Output:         If a NULL node is passed as a parameter it's assumed 
//                 that memory could not be allocated for the node. A 
//                 message is sent to standard output.
// Postconditions: Upon successful completion, a new node is appended to 
//                 the list. If for some reason the new node is NULL,
//                 the program is terminated.
// Returns:        None
  
void GraphicManager::AppendGraphic(GraphicNode *NewGraphicNode) {

   if (!NewGraphicNode) {
      cout << "Unable to allocate memory in function: GraphicManager\n";
      Terminate();
      return;  
   }
  
   if (Tail) {
      Tail->SetNext(NewGraphicNode);
      Tail = NewGraphicNode;
   }
   else
      Head = Tail = NewGraphicNode;

   ListSize++;
}
  

//-------------------------------------------------------------------------
//  I n s e r t G r a p h i c
// Function:       Inserts a GaphicNode to the front of the list
// Parameters:     NewGraphicNode, a pointer to a GraphicNode specifying
//                    the node to insert
// Preconditions:  NewGraphicNode must own its own memory.
// Output:         If a NULL node is passed as a parameter it's assumed 
//                 that memory could not be allocated for the node. A 
//                 message is sent to standard output.
// Postconditions: Upon successful completion, a new node is inserted into 
//                 the list. If for some reason the new node is NULL,
//                 the program is terminated.
// Returns:        None

void GraphicManager::InsertGraphic(GraphicNode *NewGraphicNode) {

   if (!NewGraphicNode) {
      cout << "Unable to allocate memory in function: InsertGraphic\n";
      Terminate();
      return;  
   }

   if (Head) {
      NewGraphicNode->SetNext(Head);
      Head = NewGraphicNode;
   }
   else
      Head = Tail = NewGraphicNode;

   ListSize++;   
}


//-------------------------------------------------------------------------
//  G e t L o w e r R i g h t O f F i r s t M e s s a g e 
// Function:       Searches for the first MessageGraphic in the list and
//                 returns the device coordinate position for its lower
//                 right corner
// Parameters:     None
// Preconditions:  The list must contain a MessageGraphic.
// Output:         If no MessageGraphics exist in the list, a message is
//                 sent to standard output.
// Postconditions: Upon successful completion, None. Otherwise, the 
//                 program is terminated.
// Returns:        The lower right device coordinate position of the first
//                 MessageGraphic in the list

GraphicPosition GraphicManager::GetLowerRightOfFirstMessage() const {
   const GraphicNode *FirstMessage(GetFirstMessage());
   
   if (FirstMessage)
      return FirstMessage->GetLowerRight();

   cout << "A request has been made to retrieve information from the "
        << "first item in a GraphicManager when there are no items "
        << "in the list.\n";
   cout << "The program is being terminated.\n";
   Terminate();

   return DeviceOrigin;
}


//-------------------------------------------------------------------------
//  F i r s t  
// Function:       Returns the first node in the list
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The internal list traverser points to the head of the 
//                 list.
// Returns:        The first node in the list

GraphicNode* GraphicManager::First() {

   Current = Head;
   return Head;
}


//-------------------------------------------------------------------------
//  N e x t  
// Function:       Returns the next node in the list
// Parameters:     None
// Preconditions:  First should have been called prior to calling this 
//                 function
// Output:         None
// Postconditions: The internal list traverser points to the next node in 
//                 the list.
// Returns:        The next node in the list

GraphicNode* GraphicManager::Next() {
   
   if (Current) {
      Current = Current->GetNext();
      return Current;
   }

   return NULL;
} 


//-------------------------------------------------------------------------
//  E m p t y L i s t  
// Function:       Removes all of the nodes in the list
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: The list is empty and is ready for reuse.
// Returns:        None
 
void GraphicManager::EmptyList() {
   GraphicNode *Temp(Head);

   while (Head) {
      Temp = Head;
      Head = Head->GetNext();
      delete Temp;
   }

   ListSize = 0;
   Head = Tail = NULL;
}


//-------------------------------------------------------------------------
//  G e t F i r s t M e s s a g e 
// Function:       Searches through the list for the first MessageGraphic
//                 and returns it
// Parameters:     None
// Preconditions:  None
// Output:         None
// Postconditions: None
// Returns:        The first MessageGraphic in the list or NULL

const GraphicNode* GraphicManager::GetFirstMessage() const {
   GraphicNode *Traverser(Head);

   while (Traverser) {
      if (Traverser->GetType() == Text)
         return Traverser;

      Traverser = Traverser->GetNext();
   }

   return NULL;
}





