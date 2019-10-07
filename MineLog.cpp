//
//  MineLog.cpp
//
//  Created by Samantha Ho on 7/16/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/* *
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

#include <stdio.h>
#include "MineLog.h"
#include "DateTime.h"
#include "Mine.h"
#include "Exceptions.h"

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                 class MineLog implementation code                      **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

//constructor, loop through all MineRecord structrs on vector
//on each iteration test minestatus, testing if first 9 characters is 'abandoned'
//using substring

MineLog::MineLog(const vector<MineRecord> &vMRec)

{
    int abandonedacc = 0;
    int workingacc = 0;
    //cout << "this is before the for loop and this is the size of the vector " << endl;
    //cout << vMRec.size() << endl;
    
    for (unsigned long count = 0; count < vMRec.size(); count++)
    {
        //cout << "iterating for loop....." << endl;
        if (vMRec.at(count).dataField[MINE_STATUS].substr(0,9) == "Abandoned")
        {
            try
            {
                //cout << "instantiating abandoned and pushing to linked list..." << endl;
                Abandoned Aobj(vMRec.at(count));
                //calling convert constructor for this specific row of data
                //nested try, does not stop while
                //this is for unwining the stack from the setting functions
                //purpose is to skip over this next part to not append to vector or dynamically
                //allocate memory if its invalid
                
                //dynamic allocation through getting pushed onto LL
                abandonedMines.push_back(Aobj); //calls convert constructor,
                abandonedacc++;
                
            }
            catch (bad_alloc &e)
            {
                cout << "bad_alloc caught in constructor MineLog" << endl;
                cout << e.what();
            }
            catch (invalid_argument &e)
            {
                cout << e.what(); //meaning it failed validation, will skip object but do next
                //iteration
            }
            catch (...)
            {
                cout << "ERROR: unknown exception caught in constructor MineLog" << endl;
            }
            
            
        }
        
        else
        {
            try
            
            {
                //cout << "instantiating working and pushing to linked list..." << endl;
                Working Wobj(vMRec.at(count));
                //calling convert constructor
                //will skip this next appending part if exception is thrown from mines 
                workingMines.push_back(Wobj);
                workingacc++;
            }
            
            
            catch (bad_alloc &e)
            {
                cout << "bad_alloc caught in constructor MineLog" << endl;
                cout << e.what();
            }
            catch(bad_mine_ID &e)
            {
                cout << "bad_mine_ID caught in minelog constructor" << endl;
                cout << e.what();
            }
            catch (invalid_argument &e)
            {
                cout << "invalid argument caught in nested try in minelog constructor" << endl; 
                cout << e.what(); //meaning it failed validation, will skip object but do next
                //iteration
            }
            catch (...)
            {
                cout << "ERROR: unknown exception caught in constructor MineLog" << endl;
            }
            
        }
        
        //cout << endl;
    }
    cout << "Total accumulated Instantiated Abandoned Objects: " << abandonedacc <<endl;
    cout << "Total accumulated Instantiated Working Objects: " << workingacc << endl;
}//end constructor

MineLog::~MineLog()
{
}//end destructor stub, traverse list to destruct the dynamically allocated memory!


//purpose: count of working mines that are coal producing
//another example of virtual polymorphic behavior
//when looping through vector, the compiler sees its a pointer to the base class
//getflagmetalcoal is a member of the minelog

int MineLog::getCountCoalProducing() const
{
    int returnValue =0;
    //Node<Working> *current = workingMines.at(0); //start pointing to first node in list
    for (unsigned long count = 0; count < workingMines.size(); count++)
    {
        Working workObj = workingMines.at(count);
        if (workObj.getflagMetalCoal() == 'C' ||
            workObj.getflagMetalCoal() == 'c')
        {
            returnValue++;
        }
        
      
    }
    return returnValue;
}

//purpose: count of working mines that are metal producing
int MineLog::getCountMetalProducing() const
{
    int returnValue =0;
    //Node<Working> *current = workingMines.at(0); //start pointing to first node in list
    for (unsigned long count = 0; count < workingMines.size(); count++)
    {
        Working workObj = workingMines.at(count);
        if (workObj.getflagMetalCoal() == 'm' ||
            workObj.getflagMetalCoal() == 'M')
        {
            returnValue++;
        }
        
        
    }
    return returnValue;
}



//a virtual function, should exhibit different output when called by abandoned vs working
void MineLog::displayExecReport1(std::ostream &out) const
{

    
    cout << "The following are Abandoned records from the Abandoned LL : " << endl;
    for (unsigned long i = 0; i < abandonedMines.size(); i++)
    {
        abandonedMines.at(i).execReport1(out);
        out << endl;
    }
    
    cout << "The following are Working records from the Working LL : " << endl;
    for (unsigned long i = 0; i < workingMines.size(); i++)
    {
        workingMines.at(i).execReport1(out);
        out << endl;
    }
}
