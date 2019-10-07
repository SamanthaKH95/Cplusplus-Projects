/*
 *  LL.h
 *
 *  COSC 052 Summer 2019
 *  Project #3
 *
 *  Due on: JUL 30, 2019
 *  Author: <skh50>
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */





#ifndef COSC052_SUMMER_2019P03_LL_H_
#define COSC052_SUMMER_2019P03_LL_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "DateTime.h"

#define DEBUG_LL_POP_BACK
//#define DEBUG_LL_INSERT

#include "Exceptions.h"

using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::bad_alloc;
using std::out_of_range;


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Node declaration (Template)                      **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node<T> *previous;
    
    Node(T = T(), Node<T> *next = NULL, Node<T> *previous = NULL);
    
}; //END definition templatized class Node




/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                             Milestone 1                                **
 **                 class Node declaration (non-template)                  **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
/*

class Node
{
public:
    char info;
    Node *next;
    Node *previous;
    
    Node(char = char(), Node *next = NULL, Node *previous = NULL);
    
}; //END declaration class Node

*/

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                             Milestone 1                                **
 **                 class LL declaration (non-template)                    **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

template <typename T>
class LL
{
    template <typename F> 
    friend std::ostream& operator<<(std::ostream& os, const LL<F> &rhsObj);
    
private:
    unsigned long count;
    Node<T> *header;
    Node<T> *trailer;
    
    void copyList(const LL<T>&);
    void initialize();
    
public:
    LL();
    LL(const LL<T>&);
    ~LL();
    
    LL<T>& operator=(const LL&);
    
    void push_back(T);
    void pop_back();
    T& back() const;
    
    void push_front(T);
    void pop_front();
    T& front() const;
    
    void clear();
    bool empty() const;
    unsigned long size() const {return count;}
    
    T& at(unsigned long ndx) const;
    
    void insert(unsigned long ndx, T);
    void remove(unsigned long ndx);
    
}; //END declaration class LL




/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                      Implementation Code                               **
 **                                                                        **
 **                      PUT YOUR CODE HERE                                **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                      class Node implementation                         **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/


/****************************************************************************
 *                         default constructor                              *
 ****************************************************************************/



// Instantiate a Node object
template <typename T>
Node<T>::Node(T i, Node<T> *next1, Node<T> *previous1)
{
    //cout << "we are in the constructor in the node class" << endl;
    //cout << "we are setting info member in the node class" << endl;
    info = i;
    //cout << "we are setting next pointer in the node class" << endl;
    next = next1;
    //cout << "we are setting previous pointer in the node class" << endl;
    previous = previous1;
    
    //cout << "we are finished in the constructor in the node class" << endl;
}



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                       class LL implementation                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/


/****************************************************************************
 *                         default constructor                              *
 ****************************************************************************/

template <typename T>
LL<T>::LL()
{
    //cout << "we are in the constructor in the LL" << endl;
    // Dynamically allocating memory for header and trailer sentinel
    // Call initialize
    
    //cout << "we are allocating for the header sentinel" << endl;
    header = new Node<T>();
    //cout << "we are allocating for the trailer sentinel" << endl;
    trailer = new Node<T>();
    //cout << "we are about to call initialize" << endl;
    initialize();
    
    //cout << "finished calling initialize and finished constructing LL" << endl;
    
}




/****************************************************************************
 *                      private method initialize                           *
 ****************************************************************************/

template <typename T>
void LL<T>::initialize()
{
    // Initialize empty list (could call from constructor or from existing list)
    // Set count to zero
    // Set sentinel pointers as appropriate for an empty list
    
    header->next = trailer;
    header->previous = header;
    trailer->previous = header;
    trailer->next = trailer;
    count = 0;
    
}



/****************************************************************************
 *                        member function empty                             *
 ****************************************************************************/

// returns true if list is empty
template <typename T>
bool LL<T>::empty() const
{
    
    return (header->next == trailer);
    
    /*bool isempty = false;
    if (header->next = trailer;
        header->previous = header;
        trailer->previous = header;
        trailer->next = trailer;)
    {
        isempty = true;
    }
    
    return isempty;*/
}


/****************************************************************************
 *                       member function copyList                           *
 ****************************************************************************/

// Consolidate code that would otherwise be duplicated in
// copy constructor and operator=

template <typename T>
void LL<T>::copyList(const LL<T> &otherLL)
{
    //copylist is a private function called by copy constructor and =operator
    //contains all duplicate code from the overloaded =operator and copy constructor
    try
    {
        Node<T> *current = otherLL.header->next;
        unsigned long newcount = otherLL.count;
        
        for (unsigned long i=0; i<newcount; i++)
        {
            //push_back calls insert function which dynamically allocates a new node
            push_back(current->info);
            current = current->next;
        }
        
    } //end try block
    catch(bad_alloc &e)
    {
        cout << "bad_alloc caught in LL class function copylist" << endl;
        cout << e.what();
    }
}


/****************************************************************************
 *                            copy constructor                              *
 ****************************************************************************/

// Instantiate a new object and make it a deep copy of an existing object
template <typename T>
LL<T>::LL(const LL<T> &otherLL)
{
    try
    {
        header = new Node<T>();
        trailer = new Node<T>();
        initialize(); //initialize empty list
        
        //traverse through the otherLL linked list to copy it over node by node
        
        copyList(otherLL);
    }//end try block
    catch(bad_alloc &e)
    {
        cout << "bad_alloc caught in LL class copy constructor" << endl;
        cout << e.what();
    }
    
    
}


/****************************************************************************
 *                               destructor                                 *
 ****************************************************************************/

template <typename T>
LL<T>::~LL()
{
    // Should call clear to deallocate Node objects on the list
    // Then, deallocate sentinel nodes here (clear should NOT deallocate sentinel nodes)
    
    clear();
    delete header;
    delete trailer;
    
}



/****************************************************************************
 *              non-member function overloaded operator=                    *
 ****************************************************************************/

// Make object on left side of assignment a deep copy of the right side object

template <typename T>
LL<T>& LL<T>:: operator=(const LL<T> &otherLL)
{
    try
    {
        LL newlinkedlist;
        
        newlinkedlist.initialize(); //initialize empty list
        newlinkedlist.copyList(otherLL);
        
        return newlinkedlist;
        
    }//end try block
    catch(bad_alloc &e)
    {
        cout << "bad_alloc caught in LL class overloaded =operator" << endl;
        cout << e.what();
    }

    
}


/****************************************************************************
 *                         member function insert                           *
 ****************************************************************************/

// Insert an object somewhere on the list
// Valid index values are [0, count]
// NOTE: count (or size()) is actually valid and results in the
//       object being inserted at the end of the list
//       The index passed to insert is the index that the object
//       being inserted will have once it has been inserted onto the list
template <typename T>
void LL<T>::insert(unsigned long ndx, T a)
{
    try
    {
        //this function has access to header and trailer
        if (ndx < 0 || ndx > count)
        {
            throw out_of_range("ndx is not within acceptable range\n");
        }
        if (ndx <= size())
        {
            Node<T> *V = header;
            Node<T> *W = header->next;
            
            //if ndx = 0, would not execute at all, V and W wont move
            //if ndx = count, will place at the end of list
            for (unsigned long i = 0; i<ndx; i++)
            {
                V = V->next;
                W = W->next;
            }
            
            Node<T> *Z = new Node<T> (a, W, V); //dynamically allocate a new node to insert
            W->previous = Z;
            V->next = Z;
            count++;
        }
        
    }//end try block
    catch(out_of_range &e)
    {
        cout << "out_of_range caught in LL class function insert" << endl;
        cout << e.what();
        throw;
    }
    
    
}


/****************************************************************************
 *                        member function push_back                         *
 ****************************************************************************/

// append an object to the end of the list

template <typename T>
void LL<T>::push_back(T a)
{
    try
    {
        insert(count, a);
        
        /*
         trailer->previous = new Node(a, trailer, trailer->previous);
         trailer->previous->previous->next = trailer->previous; */
    }//end try block
    catch(bad_alloc &e)
    {
        cout << "bad_alloc caught in LL class function push_back" << endl;
        cout << e.what();
    }

}




/****************************************************************************
 *                       member function push_front                         *
 ****************************************************************************/

// insert an object at the front of the list
template <typename T>
void LL<T>::push_front(T a)
{
    try
    {
        insert(0, a);
        
        /*
         header->next = new Node (a, head->next, head);
         header->next->next->previous = head->next; */
    }//end try block
    catch(bad_alloc &e)
    {
        cout << "bad_alloc caught in LL class function push_front" << endl;
        cout << e.what();
    }
    
}




/****************************************************************************
 *                         member function clear                            *
 ****************************************************************************/

// while its not empty???
// Deallocate all non-sentinel nodes
// Make the list empty and ready to re-use
// Should call initialize after deleting non-sentinel nodes

template <typename T>
void LL<T>::clear()
{
    Node<T> *current = NULL;
    
    while (header->next!=trailer)
    {
        current = header->next;
        header->next = current->next;
        delete current;
        current = header;
    }
    
    initialize(); //calling initialize in order to re-link the pointers

}



/****************************************************************************
 *                          member function front                           *
 ****************************************************************************/

// return reference to first object on list

template <typename T>
T& LL<T>::front() const
{
    try
    {
        if (header->next == trailer)
        {
            //nothing to do
            cout << "There is nothing at the front of the list" << endl;
            throw no_such_object("There is nothing in front of the list to reference\n");
        }

        

        
        //return header->next->info;
    }//end try block
    catch(no_such_object &e)
    {
        cout << "ERROR: no_such_object exception caught in LL class function front" << endl;
        cout << e.what();
        throw;
    }

  return at(0);
}



/****************************************************************************
 *                          member function back                            *
 ****************************************************************************/
// back() // return reference to last object on list

template <typename T>
T& LL<T>::back() const
{
    try
    {
        if (header->next == trailer)
        {
            cout << "The list is empty, will return empty info" << endl;
            throw no_such_object("list in empty, cannot return reference to last");
        }
        else
        {
            return at(count-1);
        }
        // return trailer->previous->info;
    }//end try block
    catch(no_such_object &e)
    {
        cout << "ERROR: no_such_object exception caught in LL class function back" << endl;
        cout << e.what();
        throw;
    }
  
    return at(count-1);
}



/****************************************************************************
 *                          member function pop_back                        *
 ****************************************************************************/


template <typename T>
void LL<T>::pop_back()
{
    // removes the last list object and deallocates memory
    
    try
    {
        if (header->next == trailer)
        {
            //nothing to do
            std::cout << "list is already empty\n";
            throw no_such_object("list is empty, cannot pop_back");
        }
        else
        {
            remove(count-1);
        }
    }//end try block
    catch(no_such_object &e)
    {
        cout << "ERROR: no_such_object exception caught in LL class function pop_back" << endl;
        cout << e.what();
        throw;
    }
    
}



/****************************************************************************
 *                         member function at const                         *
 ****************************************************************************/

// return reference/its info data member to object at specified index
// Valid values are [0, count-1]

template <typename T>
T& LL<T>::at(unsigned long ndx) const
{
    //Node<T> *D = header;
    Node<T> *E = header->next;
    //Node<T> *F = E->next;
    
    try
    {
        if (ndx < 0 || ndx > count-1)
        {
            cout << "ndx value invalid" << endl; 
            throw out_of_range("ndx value is not within acceptable range\n");
        }
        else
        {
            //if index is 0, the helper pointers do not move at all
            for (unsigned long i = 0; i < ndx; i++)
            {
                //D = D->next;
                E = E->next;
                //F = F->next;
            }
        }
    
        
    }//end try block
    
    catch(out_of_range &e)
    {
       cout << "out_of_range caught in LL class function at" << endl;
       cout << e.what();
       throw;
    
    }
    
    return E->info;
    
}



/****************************************************************************
 *                       member function pop_front                          *
 ****************************************************************************/

// remove first object on list

template <typename T>
void LL<T>::pop_front()
{
    try
    {
        if (header->next == trailer)
        {
            cout << "The list is empty, nothing to remove" << endl;
            throw no_such_object("list empty, cannot remove first object on list\n"); 
        }
        else
        {
            remove(0);
        }
        
    }//end try block
    catch(no_such_object &e)
    {
        cout << "ERROR: no_such_object exception caught in LL class function pop_front" << endl;
        cout << e.what();
        throw;
    }
    
    
    
}



/****************************************************************************
 *                        member function remove                            *
 ****************************************************************************/

// Remove node at specified index
// Valid values are [0, count-1]

//0 deletes the first one in list???

template <typename T>
void LL<T>::remove(unsigned long ndx)
{
    try
    {
        Node<T> *A = header;
        Node<T> *B = header->next;
        Node<T> *C = B->next;
        
        //if index is 0, the helper pointers do not move at all
        for (unsigned long i = 0; i < ndx; i++)
        {
            A = A->next;
            B = B->next;
            C = C->next;
        }
        
        delete B;
        
        //re-link
        A->next = C;
        C->previous = A;
        
        count--;

    }//end try block
    catch(out_of_range &e)
    {
        cout << "out_of_range caught in LL class function remove" << endl;
        cout << e.what();
        throw;
    }
    
    
}



/****************************************************************************
 **                                                                        **
 **                             Milestone 1                                **
 **                        void LL::pop_back()                             **
 **                            non-template                                **
 **                                                                        **
 **               This code is provided to students                        **
 **               in COSC 052 Summer 2019 to use in part                   **
 **               or in total for class projects.                          **
 **               Students may use this code as their                      **
 **               own, without any attribution.                            **
 **                                                                        **
 **                                                                        **
 **               NOTE: requires your working LL::remove method            **
 **                     requires new no_such_object exception class        **
 **                                                                        **
 ****************************************************************************/


/****************************************************************************
 *                        member function pop_back                          *
 ****************************************************************************/

/*
void LL::pop_back()
{
    
    if (header->next == trailer)
    {
        //nothing to do
        std::cout << "list is already empty\n";
        throw no_such_object("list is empty, cannot pop_back");
    }
    else
    {
        remove(count-1);
    }
    
} //END LL::pop_back()
*/


/****************************************************************************
 **                                                                        **
 **                             Milestone 1                                **
 **      std::ostream& operator<<(std::ostream& os, const LL &rhsObj)      **
 **                            non-template                                **
 **                                                                        **
 **               This code is provided to students                        **
 **               in COSC 052 Summer 2019 to use in part                   **
 **               or in total for class projects.                          **
 **               Students may use this code as their                      **
 **               own, without any attribution.                            **
 **                                                                        **
 ****************************************************************************/



/****************************************************************************
 *              non-member function overloaded operator<<                   *
 ****************************************************************************/
template <typename F>
std::ostream& operator<<(std::ostream& os, const LL<F> &rhsObj)
{
    // begin on object immediately after the header sentinel node
    Node<F> *current = rhsObj.header->next;
    
    // end once reaching the trailer sentinel node
    while ( current->next != current )
    {
        os << current->info << "  ";
        
        current = current->next;
    }
    
    return os;
    
} //END overloaded stream insertion operator for LL class







#endif  /*    COSC052_SUMMER_2019P03_LL_H_    */

