//
//  DJIA.cpp
//  P1
//
//  Created by Samantha Ho on 7/15/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * DJIA.cpp
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
#include "DJIA.h"
using namespace std;

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                 class DJIA implementation code                         **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

istream& operator>>(std::istream& in, DJIA& dj) //for inputting
{
    if(!in)
    {
        // the stream is in a failed state already, throw an exception and do
        // not attempt any processing
        // this exception is being thrown outside of the try block so it
        // will immediately transfer control back to the calling function
        
        throw invalid_argument(failedInitialStream);
    }
    try
    {
        // here we extract values from stream object
        // if a stream extraction operation fails, treat that as a function ending
        // exception condition, HOWEVER, do not re-throw the exception, this allows the
        // calling function to decide how to deal with the stream being in a failed state
        string warnMsg = "WARNING: ";
        warnMsg += "stream extraction operation failed in operator>> of DJIA class.\n";
        
        char dash = '-';
        char comma = ',';
        
        
        Date marketDate;
        int day;
        int month;
        int year;
        
        double open;
        double high;
        double low;
        double close;
        long volume;
        double adjustedClose;
        std::string remarks;
        
        // a row of data contains the row number (integer), time (hh:mm),
        // and remarks (string with spaces)
        // extract one or more values, then test to see if stream is in a failed state
        // if it is in a failed state throw runtime_error exception
        // catch that exception object, but do not rethrow
        // the exception ends the function, but not the program
        
        in >> day >> dash >> month >> dash >> year >> comma >> open >> comma >> high >> comma >>
        low >> comma >> close >> comma  >> volume >> comma >> adjustedClose;
        //cin.ignore('\n', 500); //read in rest of line but not use
        
        if (year > yeardifferentiator)
        {
            year = year+nineteenthcentury;
        }
        else if (year <= yeardifferentiator)
        {
            year = year + twentyfirstcentury;
        }
        
        //cout << day << " " << month << " " << year << endl;
        
        if (!in)
            throw runtime_error(warnMsg); //testing for reading past the end of file
        
        //setting DJIA member variables with the data that was just read in
        
        dj.setMarketDate(year, month, day);
        dj.setOpen(open);
        dj.setHigh(high);
        dj.setLow(low);
        dj.setClose(close);
        dj.setVolume(volume);
        dj.setAdjustedClose(adjustedClose);
        dj.setRemarks(remarks);
        
        
        
       
        
    }
    catch (invalid_argument &e)
    {
        cout << "Invalid Argument Error caught in DJIA >> operator\n";
        cout << e.what() << endl;
        throw;
    }
    catch(runtime_error &e)
    {
        cout << "Runtime Error caught in DJIA >> operator\n"; 
        cout << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown Exception caught in DJIA >> operator\n";
    }
    return in;
}
ostream& operator<<(std::ostream& out, const DJIA& dj) //for outputting each row back
{
    out << dj.marketDate << " " << dj.open << " " << dj.high << " " << dj.low << " " << dj.close
    << " " << dj.volume << " " << dj.adjustedClose << " " << dj.remarks << endl;
    return out;
}

//constructor, uses default values in class declaration if no paramaters passed
DJIA::DJIA (Date dt, double open, double high, double low, double close, long volume,
            double adjudstedClose, string remarks)
{
    setMarketDate(dt.getYear(), dt.getMonth(), dt.getDay());
    setOpen(open);
    setHigh(high);
    setLow(low);
    setClose(close);
    setVolume(volume);
    setAdjustedClose(adjudstedClose);
    setRemarks(remarks); 
}

//copy constructor, memberwise assignment, can directly access private members of object copied 
DJIA::DJIA(const DJIA& dj)
{
    //a DJIA object is passed by constant reference to this constructor
    this->marketDate = dj.getMarketDate();
    this->open = dj.getOpen();
    this->high = dj.getHigh();
    this->low =dj.getLow();
    this->close = dj.getClose();
    this->volume = dj.getVolume();
    this->adjustedClose = dj.getAdjustedClose();
    this->remarks = dj.getRemarks();
    
}

void DJIA::setMarketDate(int yyyy, int mm, int dd)
{
    //calling setterfunction for marketdate date object with these parameter values
    
    //changing the year to appropriate 4-digit before sending it to the setDate function
    try
    {
        /*if (yyyy > yeardifferentiator)
        {
            yyyy = yyyy +nineteenthcentury;
        }
        else if (yyyy <= yeardifferentiator)
        {
            yyyy = yyyy + twentyfirstcentury;
        }
        */
        marketDate.setDate(yyyy, mm, dd);
    }
    
    catch (invalid_argument &e)
    {
        remarks = remarks + e.what();   
    }
    
}

//setter functions were all defined in-line within the header file 

