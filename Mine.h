//
//  Mine.hpp
//  052_P2
//
//  Created by Samantha Ho on 7/16/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 *  Mine.h
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




#ifndef _COSC052_SUMMER_2019P02V01_MINE_H_
#define _COSC052_SUMMER_2019P02V01_MINE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include "DateTime.h"
#include "Exceptions.h"



#define DEBUG_FILE_OPENING = 1

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::istream;
using std::cin;
using std::vector;

const int FIELD_COUNT = 18;
const int FIELD_SIZE[FIELD_COUNT] = {7,41,30,30,50,63,12,23,2,2,25,9,7,11,20,10,31,1};

enum {MINE_ID, MINE_NAME, CONTACT_TITLE, NEAREST_TOWN, BUSINESS_NAME, STREET,
    PO_BOX, CITY, STATE_ABBR, FIPS_CODE, STATE_NAME, ZIP_CODE, POSTAL_CODE,
    MINE_TYPE_CODE, MINE_STATUS, MINE_STATUS_DATE, MINE_SIC_CODE, MINE_COAL_METAL_IND};

const int MINE_STATUS_COUNT = 7;
const string MINE_STATUS_VALUES[] = {"Active", "Abandoned", "Intermittent", "Abandoned and Sealed",
    "NonProducing", "Temporarily Idled", "New Mine"};
const int MINE_ID_LENGTH = 7;


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 struct MineRecord declaration                          **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

struct MineRecord
{
    string dataField[FIELD_COUNT];
    
    //date adjusted to our Date class format
    Date adjustedDate;
    
    //default constructor
    MineRecord(string = "");
    
};



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Mine declaration                                 **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class Mine
{
protected:
    string mineID;
    string mineName;
    string nearestTown;
    string mineStatus;
    Date mineStatusDate;
    
public:
    ~Mine();
    Mine(string = "1234567", string = "unknown", string = "unknown",
         string = "Abandoned           ", Date = Date(YEAR_DEFAULT,MONTH_DEFAULT,DAY_DEFAULT));
    
    string getMineID() const { return mineID; }
    string getMineName() const { return mineName; }
    string getNearestTown() const { return nearestTown; }
    string getMineStatus() const  { return mineStatus; }
    Date getStatusDate() const { return mineStatusDate; }
    void setMineID(string mID);
    void setMineStatus(string mStat);
    
    virtual void execReport1(ostream & = std::cout) const;
    
}; //END class Mine declaration



/****************************************************************************
 *                                                                          *
 *                    class Abandoned declaration                           *
 *                                                                          *
 ****************************************************************************/
class Abandoned : public Mine
{
    
private:

public:
    Abandoned();
    
    //using member initialization list
    Abandoned(const MineRecord &MRobj);
    ~Abandoned();

};
/****************************************************************************
 *                                                                          *
 *                    class Working declaration                             *
 *                                                                          *
 ****************************************************************************/
class Working : public Mine
{

private:
    string contactTitle;
    string businessName;
    string addressStreet;
    string addressCity;
    string addressState;
    string addressZipCode;
    string primarySicCode;
    char flagMetalCoal;

public:
    Working();
    Working (const MineRecord&);
    ~Working();
    
    //implement in-line is ok
    string getContactTitle() const {return contactTitle;}
    string getbusinessName() const {return businessName;}
    string getaddressStreet() const {return addressStreet;}
    string getaddressCity() const {return addressCity;}
    string getaddressState() const {return addressState;}
    string getaddressZipCode() const {return addressZipCode;}
    string getprimarySicCode() const {return primarySicCode;}
    char getflagMetalCoal() const {return flagMetalCoal;}
    
    void setFlagMetalCoal(char);
    bool isCoalProducing () const; 
    bool isMetalProducing () const;
    void execReport1(ostream & = std::cout) const ;



}; //end class declaration


#endif
