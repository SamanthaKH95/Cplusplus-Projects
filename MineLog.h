//
//  MineLog.h
//  052_P2
//
//  Created by Samantha Ho on 7/16/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 *  MineLog.h
 *
 *
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


#ifndef _COSC052_SUMMER_2019P02V01_MINE_LOG_H
#define _COSC052_SUMMER_2019P02V01_MINE_LOG_H

#include "Mine.h"
using std::vector;
using namespace std;




/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class MineLog declaration                              **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class MineLog
{
private:
    
    vector<Mine*> mines; //defined to store pointers to the base class
    //but can also store addresses of derived objects! dynamically allocate memory and
    //store address
    
public:
    MineLog(const vector<MineRecord> &); //pushes into private member vector after
    //deciding if the thing is abandonded obj or working obj, but only got one vector for two
    //different types of objects -> polymorphism
    
    //this needs to iterate/traverse through the vector and delete all the elements !!
    ~MineLog();
    
    unsigned long size() const {return mines.size();} //implemented in-line
    
    int getCountCoalProducing() const;
    int getCountMetalProducing() const;
    
    virtual void displayExecReport1() const;
    
}; //END class MineLog declaration



#endif
