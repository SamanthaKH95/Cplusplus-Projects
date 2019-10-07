//
//  DateTime.hpp
//  P1
//
//  Created by Samantha Ho on 7/15/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * DateTime.h
 *
 *  COSC 052 Summer 2019
 *  Project #1
 *
 *  Due on: JUL 15, 2019
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


#ifndef COSC52Summer2019P1_Date_h
#define COSC52Summer2019P1_Date_h

#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <sstream>
using std::ostream;
using std::istream;
using std::string;
using std::cout;
using std::endl;
using std::invalid_argument;
using std::runtime_error;

//global constants
const int YEAR_DEFAULT  = 1492;
const int MONTH_DEFAULT = 1;
const int DAY_DEFAULT   = 1;

const int nineteenthcentury = 1900;
const int twentyfirstcentury = 2000;
const int yeardifferentiator = 25; 

const int YEAR_MIN = 1492;
const int YEAR_MAX = 2192;
const int MONTH_MIN = 1;
const int MONTH_MAX = 12;
const int DAY_MIN = 1;
const int DAY_MAX = 31;

const int MIN_HOUR = 0;
const int MAX_HOUR = 24;    // assumes that 24:00 is valid for midnight, 00:00 would also be valid
const int MIN_MINUTE = 0;
const int MAX_MINUTE = 59;

const string ERR_DD_INVALID_P1 = "The day value is outside of acceptable range ";
const string ERR_DD_INVALID_P2 = "( 1 <= day <= 31 )\n";
const string ERR_MM_INVALID_P1 = "The month value is outside of acceptable range ";
const string ERR_MM_INVALID_P2 = "( 1 <= month <= 12 )\n";
const string ERR_YY_INVALID_P1 = "The year value is outside of acceptable range ";
const string ERR_YY_INVALID_P2 = "( 1492 <= year <= 2192 )\n";

const string IAerrmessage = "Invalid Argument Error Detected";
const string failedInitialStream = "Input Stream is initially in failed state, funct ending";
const string REinsertmessage = "Attempted to read past end of input stream, funct ending";

//#define DEBUG_DATE = 1

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Date declaration                                 **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class Date
{
    friend std::istream& operator>>(std::istream&, Date&);
    friend std::ostream& operator<<(std::ostream&, const Date&);
    
private:
    int yyyy;
    int mm;
    int dd;
    
public:
    Date(int=YEAR_MIN, int=MONTH_MIN, int=DAY_MIN); //yyyy, mm, dd default construct
    Date(const Date&);
    void setDate(int, int, int);  //yyyy, mm, dd
    void setDate(const Date&);
    const Date& operator=(const Date&);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool operator ==(const Date&) const;
    bool operator !=(const Date&) const;
    bool operator <=(const Date&) const;
    bool operator <(const Date&) const;
    bool operator >=(const Date&) const;
    bool operator >(const Date&) const;
    
}; //END class Date declaration


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Time declaration                                 **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class Time
{
    //Overloaded stream extraction operator
    //
    //Postcondition: Extracts values for each data member from
    //the input stream.  Format of the data in the stream
    //is assumed to be:  hh:mm
    //
    //The delimiting character is read and discarded.
    //
    friend std::istream& operator>>(std::istream &in, Time &t);
    
    
    //Overloaded stream insertion operator.
    //
    //Postcondition: The time is output to the steam.  Delimiting
    //characters are replaced and the decimal point is added
    //between the seconds and fraction sections.  The result
    //is a time value output in the same format as was read in.
    //
    friend std::ostream& operator<<(std::ostream &os, const Time &t);
    
    
private:
    //two digit integer for hour of day
    int hh;
    
    //two digit integer for minute of day
    int mm;
    
    
public:
    
    //constructor with parameters, with default values
    //This constructor calls the member function setTime()
    //and passes the same arguments as were passed in to
    //the constructor, function setTime() updates the data members
    //and completes data validation.
    //
    //Postcondition: Sets the values of hh and mm
    //according to the values of the arguments passed in.
    //If no values are passed, this acts as the default constructor
    //all integer data members are set to zero
    //
    Time(int = 0, int = 0);
    
    
    //Function to set the values of the object data members,
    //can be called directly or by a constructor.
    //
    //Postcondition: Data members are set to the values
    //of the respective arguments passed in.  Values passed
    //are also validated, if any validation tests fail
    //then the data members are set to default values.
    //Note that this validation strategy is a business rule for
    //our project and would probably not be appropriate for
    //most situations and could result in unintended consequences.
    //
    void setTime(int, int);
    
    
    //In-line function to return the hour value.
    //
    //Postcondtion: The value of data member hh is retured.
    //
    int getHour() const {return hh;}
    
    //In-line function to return the minute value.
    //
    //Postcondtion: The value of data member mm is retured.
    //
    int getMinute() const {return mm;}
    
    
    //Overloaded assignment operator.
    //
    //Postcondtion: The values of right hand side object's
    //data members are copied to the respective data
    //members of the left hand side object.
    //The overloaded assignment operator calls setTime
    //so that data being copied are validated.
    //
    Time operator=(const Time&);
    
    
}; //END class Time declaration



#endif





