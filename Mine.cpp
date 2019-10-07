//
//  Mine.cpp
//  052_P2
//
//  Created by Samantha Ho on 7/16/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 *  Mine.cpp
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


#include "Mine.h"
#include "MineLog.h"
#include "Exceptions.h"

//#define DEBUG_ABANDONED = 1
//#define DEBUG_WORKING = 1
//#define DEBUG_MINE = 1

using namespace std;



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 struct MineRecord implementation                       **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

MineRecord::MineRecord(string oneLine)
{
    try
    {
        int onLineColumn = 0;
        
        // one complete iteration of the outer loop parses one
        // element of the dataField array from the string oneLine
        // which is one line of data from the input file
        
        for ( int f = 0; f < FIELD_COUNT; f++ )
        {
            
            
            //clear contents of next data field
            dataField[f] = "";
            
            // each iteration of the inner loop adds one additional
            // character to the current dataField element
            
            for ( int c = 0; c < FIELD_SIZE[f]; c++ )
            {
                
                if ( f==0 && c==0 )
                {
                    dataField[0] = oneLine[0];
                }
                else
                {
                    //advance to next character in input line
                    onLineColumn++;
                    
                    dataField[f] += oneLine[onLineColumn];
                }
            }
            
            //advance over the spaces between columns
            onLineColumn += 4;
        }
        
        //correct the date format and store value to use in adjustedDate data member
        //date format from file is mm/dd/yyyy
        //date format for calls to our Date class functions is yyyy,mm,dd
        //see Gaddis p. 808 for atoi function and Gaddis page 818-820 for
        //substr and other string functions
        adjustedDate.setDate(atoi( (dataField[MINE_STATUS_DATE].substr(6,4)).c_str() ),
                             atoi( (dataField[MINE_STATUS_DATE].substr(0,2)).c_str() ),
                             atoi( (dataField[MINE_STATUS_DATE].substr(3,2)).c_str() ));
        
        //cout << "inside MineRecord constructor, searching for pointer to object matching code: ";
        //cout << dataField[FIPS_CODE] << endl;
                
        
    }
    catch ( bad_date_component &e )
    {
        cout << "ERROR: in constructor MineRecord::MineRecord()";
        cout << "\nrethrowning exception...\n";
        //cout << e.what() << endl;
        throw;
    }
    catch ( std::invalid_argument &e )
    {
        cout << "ERROR: in constructor MineRecord::MineRecord()";
        //cout << e.what() << endl;
        cout << "\nrethrowning exception...\n";
        throw;
    }
    catch (...)
    {
        cout << "Catch-all exception in constructor MineRecord::MineRecord()";
        cout << "\nrethrowning exception...\n";
        throw;
    }
    
} //END constructor MineRecord::MineRecord(string oneLine)


/****************************************************************************
 **                                                                        **
 **                    class Mine implementation                           **
 **                                                                        **
 ****************************************************************************/

//destructor
Mine::~Mine()
{}//nothing needed in destructor body?


//constructor with parameters, if none in parenthesis then uses default values
Mine::Mine(string mineID, string mineName, string nearestTown, string mineStatus,
           Date mineStatusDate)
{

    //the only two who needs validation - will do validation within its setter
    setMineID(mineID);
    setMineStatus(mineStatus);
    
    this->mineName = mineName;
    this->nearestTown = nearestTown;
    this->mineStatusDate = mineStatusDate; //invoking the copy constructor for the date class?
    //if so, will throw on its own there during validation?
    
    
}

//setter functions, where validation methods are!

void Mine::setMineStatus(string mStat)
{
    try
    {
        //cout << "mstat outputting...."<< mStat << endl;
        //minestatus is 20 characters wide
        
        if (mStat != "Active              " &&
            mStat != "Active2             " && //added active2 into validation 
            mStat != "Abandoned           " &&
            mStat != "Intermittent        " &&
            mStat != "Abandoned and Sealed" &&
            mStat != "NonProducing        " &&
            mStat != "Temporarily Idled   " &&
            mStat != "New Mine            ")
            
        {
            //skips over setting minestatus?
            throw bad_mine_status("bad_mine_status exception caught in setminestatus:\nmStat\n");
        }
    }
    catch (bad_mine_status &e)
    {
        cout << "bad_mine_status invalid argument caught in setMineStatus try block" << endl;
        cout << e.what();
        throw;
    }
    catch (invalid_argument &e)
    {
        cout << "bad_mine_ID caught in setMineStatus try block" << endl;
        cout << e.what();
        throw;
    }
    catch(...)
    {
        cout << "unknown exception caught in setMineStatus try block" << endl;
    }
    
    
    this->mineStatus = mStat;
    
}//end setminestatus function

void Mine::setMineID(string mID)
{
    try
    {
        if (mID.length() != MINE_ID_LENGTH)
        {
            //skips over?
            throw bad_mine_ID("bad mine ID exception caught in setMineID\nmID\n");
        }
        if(mID.length() == MINE_ID_LENGTH)
        {
            bool is_it_a_digit = true;
            
            for (int count = 0; count < mID.length(); count++)
            {
                is_it_a_digit = isdigit(mID.at(count));
                if (is_it_a_digit == false)
                {
                    throw bad_mine_ID("bad mine ID exception caught in setMineID\nmID\n");
                }
            }
        }
    }//end try block
    
    catch (bad_mine_ID &e)
    {
        cout << "bad_mine_ID invalid argument caught in setMineID" << endl;
        cout << e.what();
        throw;
    }
    catch (invalid_argument &e)
    {
        cout << "invalid argument caught in setMineID" << endl;
        cout << e.what();
        throw;
    }
    catch (...)
    {
        cout << "unknown error caught in setMineID" << endl;
    }

    //if passed validation
    this->mineID = mID;
}

//getter functions all implemented in-line within class declaration

//virtual function to be used by abandoned and working derived objects
void Mine::execReport1(ostream & out) const
{
    out << mineID << "  " << mineName << "  " << getStatusDate()<< "  " << getNearestTown()
    << "   " << mineStatus << endl;
    
}


/****************************************************************************
 **                                                                        **
 **                   class Abandoned implementation                       **
 **                                                                        **
 ****************************************************************************/

//polymorphic behavior during runtime exhibits during the displayexec function, the two classes
//will have different formats when displayed

//constructor
Abandoned::Abandoned()
{}

Abandoned::Abandoned(const MineRecord &MRobj) : Mine(MRobj.dataField[MINE_ID],
                                                     MRobj.dataField[MINE_NAME],
                                                     MRobj.dataField[NEAREST_TOWN],
                                                     MRobj.dataField[MINE_STATUS],
                                                     MRobj.adjustedDate)
//everything is done in member initialization list so no need for body
{}

Abandoned::~Abandoned()
{} //no need for stuff in body?



/****************************************************************************
 **                                                                        **
 **                   class Working implementation                         **
 **                                                                        **
 ****************************************************************************/

//default constructor with default values if not sent with paramters
Working::Working()
{
    contactTitle = "";
    businessName = "";
    addressStreet = "";
    addressCity = "";
    addressState = "";
    addressZipCode = "";
    primarySicCode = "";
    
    //initializing with a dummycause you dont want exeception passed
    setFlagMetalCoal('M');

}

//using a member initialization list in the constructor
Working::Working (const MineRecord &MRobj) : Mine(MRobj.dataField[MINE_ID],
                                                  MRobj.dataField[MINE_NAME],
                                                  MRobj.dataField[NEAREST_TOWN],
                                                  MRobj.dataField[MINE_STATUS],
                                                  MRobj.adjustedDate)

{
    //assign directly
    contactTitle = MRobj.dataField[CONTACT_TITLE];
    businessName = MRobj.dataField[BUSINESS_NAME];
    addressStreet = MRobj.dataField[STREET];
    addressCity = MRobj.dataField[CITY];
    addressState = MRobj.dataField[STATE_NAME];
    addressZipCode = MRobj.dataField[ZIP_CODE];
    //because requires validation 
    setFlagMetalCoal((MRobj.dataField[MINE_COAL_METAL_IND]).at(0));
    
}


//destructor
Working::~Working()
{}

//getter functions all implemented in-line

void Working::setFlagMetalCoal(char ch)
{
    //VALIDATION HAPPENS HERE
    try
    {
        if (ch != 'C' && ch != 'c' && ch != 'M' && ch != 'm')
        {
            throw bad_mine_flagMC("bad_mine_flagMC exception caught in setter function\nch\n");
        }
    }
    catch (bad_mine_flagMC &e)
    {
        cout << "bad_mine_flagMC invalid argument caught in setMineID: " << endl;
        cout << e.what();
        throw;
    }
    catch(invalid_argument &e)
    {
        cout << "Invalid Argument caught in setFlagMetalCoal..." << endl;
        cout << e.what();
        //not rethrown
    }
    //else it is set to value
    flagMetalCoal = ch;
}

bool Working::isCoalProducing ()const
{
    //returning truth value
    return (flagMetalCoal == 'c' || flagMetalCoal == 'C');

}
bool Working::isMetalProducing() const
{
    return (flagMetalCoal == 'm' || flagMetalCoal == 'M');

}
void Working::execReport1(std::ostream &out) const 
{
    
    //outputting specific working member variables into stream
    
    //in order to output the base class - overriden function - run report from base class first
    //and then
    
    Mine::execReport1(out);
    
    //polymorphic output for Working items, the mine class has its own display stream object
    //so would both execute or just this one? or do i call both within the display function?
    out << contactTitle << endl << businessName << endl << addressStreet << "    " << endl;
    out << addressCity << "   " << addressState << "    " << addressZipCode << "   " << endl;
    out << primarySicCode << "   " << flagMetalCoal << endl;
    out << endl;
}

 
