/*
 *  LL.h
 *
 *  COSC 052 Summer 2019
 *  Project #4
 *
 *  Due on: AUG 7, 2019
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
 *                                                                          *
 *                   class LL_iterator declaration                          *
 *                                                                          *
 ****************************************************************************/

/**
 * <P>The <code>LL_iterator</code> class (New for P4).</P>
 *
 * <P>This is a template class that provides a bi-directional iterator for LL objects.</P>
 *
 * <P>This class declaration is provided to students in COSC 052 Summer 2019
 * to use in part or in total for class projects.
 * Students may use this code as their own, without any attribution.</P>
 *
 * <P>Add this class declaration to file LL.h</P>
 *
 * @author W. A. Woods (waw23 at georgetown dot edu)
 * @version 1.1, 2019/7/30
 *
 */

template <typename T>
class LL_iterator
{
    
private:
    Node<T> *current;
    //pointer to point to the current
    //node in the linked list
    
public:
    
    LL_iterator();
    //default constructor
    //Postcondition: current = NULL;
    
    LL_iterator(Node<T> *ptr);
    //constructor with parameter
    //Postcondition: current = ptr;
    
    T& operator*();
    //overloaded dereferencing operator
    //Postcondition: Returns the info contained in the node
    
    LL_iterator<T> operator++();
    //overloaded pre-increment operator
    //Postcondition: The iterator is advanced to the next node in the linked list
    
    
    bool operator==(const LL_iterator<T> &rhsObj) const;
    //overloaded equality operator
    //Postcondition: Returns true if this iterator is equal to the
    //               iterator specified on the right hand side
    //               otherwise returns false
    
    bool operator!=(const LL_iterator<T> &rhsObj) const;
    //overloaded equality operator
    //Postcondition: Returns true if this iterator is NOT equal to the
    //               iterator specified on the right hand side
    //               otherwise returns false
    
    
}; //END class LL_iterator





/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                             Milestone 1                                **
 **                 class LL declaration (    template)                    **
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
    
    
    //P4 new methods
    void bubbleSort();
    void bubbleSortI();
    void selectionSort();
    unsigned long linearSearch(T lookfor);
    unsigned long binarySearch (T lookfor);
    
    LL_iterator<T> begin() {return LL_iterator<T>(header->next);}
    LL_iterator<T> end() {return LL_iterator<T>(trailer);}
    
    
    
    
}; //END declaration class LL


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
 *                        P4 New Member Functions                           *
 ****************************************************************************/
/****************************************************************************
 *                         class LL bubble sort I method                    *
 ****************************************************************************/
template <typename T>
void LL<T>::bubbleSortI()
{
   /* T temp;
    int swap = 0;
    
    //need two iterators
    
    for (LL_iterator<T> iter = begin(); iter != end(); ++iter)
        for (LL_iterator<T> iter2 = begin(); iter2!= end(); ++iter2)
        {
            if (*iter < *iter2)
            {
                //make swap
                cout << "swapping   " << *iter << " and " << *iter2 << endl; 
                temp = *iter;
                *iter = *iter2;
                *iter2 = temp;
                swap++;
            }
        }

 
    
    cout << "the total swaps:" << swap << endl; */
  
    try
    {
    
        T temp;
        unsigned long iteration;
        unsigned long index;
        int swap= 0;
        LL_iterator<T> iter = begin();
        LL_iterator<T> iter2 = begin();
        
        for (iteration = 1; iteration <count && iter != end(); iteration++)
        {
            iter = begin();
            iter2 = begin();
            ++iter2;
            
            for (index=0; index < count - iteration && iter != end() && iter2 != end(); index++,
                 ++iter, ++iter2)
            {
                if(*iter > *iter2)
                {
                    //make swap
                    temp = *iter;
                    *iter = *iter2;
                    *iter2 = temp;
                    swap++;
                }
                
            }//end inner loop
        }//end outer oop
        cout << "the total swaps:" << swap << endl;
    
    }//end try
    catch(out_of_range &e)
    {
        cout << "caught out_of_range error in bubblesortI" << endl;
        throw;
    }
    catch(...)
    {
        cout << "unknown exception caught in bubblesortI method" << endl;
        throw;
    }
    
}



/****************************************************************************
 *                         class LL bubble sort  method                     *
 ****************************************************************************/
template <typename T>
void LL<T>::bubbleSort()
{
    
    try
    {
        T temp;
        unsigned long iteration;
        unsigned long index;
        int swap= 0;
        
        
        for (iteration = 1; iteration <count; iteration++)
        {
            for (index=0; index < count - iteration; index++)
            {
                if(this->at(index) > this-> at(index+1))
                {
                    //make swap
                    temp = this->at(index);
                    this->at(index) = this->at(index+1);
                    this->at(index+1) = temp;
                    swap++;
                }
                
            }//end inner loop
        }//end outer oop
        cout << "the total swaps:" << swap << endl;
    }//end try
    catch(out_of_range &e)
    {
        cout << "caught out_of_range error in bubblesort" << endl;
        throw;
    }
    catch(...)
    {
        cout << "unknown exception caught in bubblesort method" << endl;
        throw;
    }
}//end bubblesort

/****************************************************************************
 *                         class LL selection sort method                   *
 ****************************************************************************/

template <typename T>
void LL<T>::selectionSort()
{
    
    try
    {
        unsigned long index;
        unsigned long indexOfSmallest;
        unsigned long location;
        T temp;
        int swap = 0;
        
        for (index =0; index < count - 1; index++)
        {
            //Step A (find index of smallest value in unsorted list
            indexOfSmallest = index;
            
            for (location = index +1; location < count; location++)
            {
                if (this->at(location) < this->at(indexOfSmallest))
                {
                    indexOfSmallest = location;
                    
                }
                
                
            }//end inner loop
            
            //step B: (swap value at indexofsmallest with the top of unsorted list)
            temp = this->at(indexOfSmallest);
            this->at(indexOfSmallest) = this->at(index);
            this->at(index) = temp;
            swap++;
        }//end outerloop
        
        cout << "the total swaps:" << swap << endl;
    }//end try
    catch (out_of_range &e)
    {
        cout << "caught out_of_range exception in linear sort" << endl;
        throw;
    }
    catch(...)
    {
        cout << "unknown exception caught in selection sort method" << endl;
        throw;
    }
}

/****************************************************************************
 *                         class LL linearSearch method                     *
 ****************************************************************************/
template <typename T>
unsigned long LL<T>::linearSearch(T lookfor)
{
    double foundAt = 0;
    bool found = false;
    string errMessageUnknown = " ";
    string errMessageNotFound = "caught logic error in linear search method";
    
    try
    {
        while (foundAt < count && !found)
        {
            if (this->at(foundAt) == lookfor)
            {
                found = true;
                
            }
            else
            {
                foundAt++;
            }
        }//end while loop
        if (!found)
        {
            throw no_such_object(errMessageNotFound);
        }
    }//end try block
    catch(no_such_object &e)
    {
        cout << e.what();
        throw;
    }
    catch(logic_error &e)
    {
        throw;//point is, you don't want the return at the bottom to happen
    }
    catch(...)
    {
        errMessageUnknown = "unknown exception caught in linear search method";
        cout << errMessageUnknown << endl;
        throw;
    }
    
    
    return foundAt;
}

/****************************************************************************
 *                         class LL binarySearch method                     *
 ****************************************************************************/

template <typename T>
unsigned long LL<T>::binarySearch (T lookfor)
{
    unsigned long first = 0;
    unsigned long last = count - 1;
    unsigned long mid;
    bool found = false;
    string errMessageUnknown = " ";
    string errMessageNotFound = "caught logic error in binary search method";
    
    try
    {
        while (first <= last && !found)
        {
            mid = (first+last)/2;
            if (this->at(mid) == lookfor)
            {
                found = true;
            }
            else if (this->at(mid) > lookfor)
            {
                last = mid - 1;
            }
            else
            {
                first = mid + 1;
            }
        }// end while
        if (!found)
        {
            throw no_such_object(errMessageNotFound);
        }//end if
    }// end try
    catch(no_such_object &e)
    {
        cout << e.what();
        throw;
    }
    catch(logic_error &e)
    {
        throw;//point is, you don't want the return at the bottom to happen
    }
    catch(...)
    {
        errMessageUnknown = "unknown exception caught in binary  search method";
        cout << errMessageUnknown << endl;
        throw;
    }
    
    return mid;
}

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




 
/***************************************************************************
 *                                                                          *
 *                   class LL_iterator implementation                       *
 *                                                                          *
 ***************************************************************************/

//default constructor

template <typename T>
LL_iterator<T> :: LL_iterator()
{
    current = NULL;
}

//constructor with parameters
template <typename T>
LL_iterator<T>:: LL_iterator(Node<T> *ptr)
{
    current = ptr;
}

//overloaded dereferencing operator to return info in current node
template <typename T>
T& LL_iterator<T>::operator*()
{
    //overloaded dereferencing operator, Returns the info contained in the node
    return current->info;
    
}

//overloaded ++ operator

template <typename T>
LL_iterator<T> LL_iterator<T>::operator++()
{
    //overloaded pre-increment operator
    //Postcondition: The iterator is advanced to the next node in the linked list
    
    LL_iterator temp;
    
    current = current->next;
    temp.current = this->current;
    
    return temp;
    
}

//overloaded == operator

template <typename T>
bool LL_iterator<T>::operator==(const LL_iterator<T> &rhsObj) const
{
    //Postcondition: Returns true if this iterator is equal to the
    //               iterator specified on the right hand side
    //               otherwise returns false
    
    bool result = false;
    
    result = this->current == rhsObj.current;
    
    return result;
}


//overloaded != operator
template <typename T>
bool LL_iterator<T>:: operator!=(const LL_iterator<T> &rhsObj) const
{
    //Postcondition: Returns true if this iterator is NOT equal to the
    //               iterator specified on the right hand side
    //               otherwise returns false
    
    bool result = false;
    
    result = this->current != rhsObj.current;
    
    return result;
}

#endif  /*    COSC052_SUMMER_2019P03_LL_H_    */

