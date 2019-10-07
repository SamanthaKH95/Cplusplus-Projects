//
//  MineLog.cpp
//  052_P2
//
//  Created by Samantha Ho on 7/16/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
*  COSC 052 Summer 2019
*  Project #2
*
*  Due on: JUL 22, 2019
*  Author: Samantha Ho, netid: skh50
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
*
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
    Mine *ptr = NULL;
    
    for (unsigned long count = 0; count < vMRec.size(); count++)
    {
        //cout << vMRec.at(count).dataField[MINE_ID] << "    ";
        if (vMRec.at(count).dataField[MINE_STATUS].substr(0,9) == "Abandoned")
        {
            //cout << vMRec.at(count).dataField[MINE_STATUS] << "   ";
            try
            {
                Abandoned Aobj(vMRec.at(count));
                //calling convert constructor for this specific row of data
                //nested try, does not stop while
                //this is for unwining the stack from the setting functions
                //purpose is to skip over this next part to not append to vector or dynamically
                //allocate memory
                
                //dynamic allocation
                ptr = new Abandoned (vMRec.at(count)); //calls convert constructor,
                //gets appeneded to vector
                mines.push_back(ptr);
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
                //cout << "Working" << "    ";
                Working Wobj(vMRec.at(count));
                //calling convert constructor
                //will skip this next appending part if exception is thrown from mines 
                ptr = new Working (vMRec.at(count));
                mines.push_back(ptr);
                workingacc++;
            }
            catch (bad_alloc &e)
            {
                cout << "bad_alloc caught in constructor MineLog" << endl;
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
    cout << "Total Instantiated Abandoned Objects: " << abandonedacc <<endl;
    cout << "Total Instantiated Working Objects: " << workingacc << endl;
}//end constructor

MineLog::~MineLog()
{
    for (unsigned long count =0; count < mines.size(); count ++)
    {
        delete mines.at(count);
        
    }
    
}//end destructor stub, traverse list to destruct the dynamically allocated memory!


//purpose: count of working mines that are coal producing
//another example of virtual polymorphic behavior
//when looping through vector, the compiler sees its a pointer to the base class
//getflagmetalcoal is a member of the minelog

int MineLog::getCountCoalProducing() const
{
    int returnValue =0;
    Working *ptr = NULL;
    for (unsigned long count = 0; count < mines.size(); count++)
    {
        ptr = dynamic_cast<Working*>(mines.at(count)); //casting base class pointer to derived
        //will fail if address of abanoned
        //first will test if pointer was dynamically cast
        
        if (ptr && (ptr->getflagMetalCoal() == 'C' ||
            ptr->getflagMetalCoal() == 'c'))
        {
            returnValue++;
        }
    }
    return returnValue;
}

//purpose: count of working mines that are metal producing
int MineLog::getCountMetalProducing() const
{
    int returnValue = 0;
    Working *ptr = NULL;
    for (unsigned long count = 0; count < mines.size(); count++)
    {
        ptr = dynamic_cast<Working*>(mines.at(count));
        
        if (ptr && (ptr->getflagMetalCoal() == 'm' ||
                    ptr->getflagMetalCoal() == 'M'))
        {
            returnValue++;
        }
    }
    return returnValue;
}

//a virtual function, should exhibit different output when called by abandoned vs working
void MineLog::displayExecReport1() const
{
    for (unsigned long count = 0; count < mines.size(); count++)
    {
        //displays it for each mine object within pointer vector 
        mines.at(count)->execReport1();

    }
}
