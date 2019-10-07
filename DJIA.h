//
//  DJIA.hpp
//  P1
//
//  Created by Samantha Ho on 7/15/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * DJIA.h
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
#ifndef COSC52Summer2019P1_DJIA_hpp
#define COSC52Summer2019P1_DJIA_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <sstream>

#include "DateTime.h"


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class DJIA declaration                                 **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class DJIA
{
    friend std::istream& operator>>(std::istream&, DJIA&);
    friend std::ostream& operator<<(std::ostream&, const DJIA&);
    
private:
    Date marketDate;
    double open;
    double high;
    double low;
    double close;
    long volume;
    double adjustedClose;
    std::string remarks;
    
public:
    DJIA(Date = Date(YEAR_MIN, MONTH_MIN, DAY_MIN), double = 0.0, double = 0.0,
         double = 0.0, double = 0.0,
         long = 0, double = 0.0, std::string = "");
    
    DJIA( const DJIA& );
    
    void setMarketDate(int, int, int);
    
    //implemented in-line, no need to redefine within cpp file for DJIA class 
    void setOpen(double o) { open = o; }
    void setHigh(double h) { high = h; }
    void setLow(double l) { low = l; }
    void setClose(double c) { close = c; }
    void setVolume(long v) { volume = v; }
    void setAdjustedClose(double ac) { adjustedClose = ac; }
    void setRemarks(std::string r) { remarks = r; }
    Date getMarketDate() const { return marketDate; }
    double getOpen() const { return open; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getClose() const { return close; }
    long getVolume() const { return volume; }
    double getAdjustedClose() const { return adjustedClose; }
    std::string getRemarks() const { return remarks; }
    
}; //END class DJIA declaration







#endif /* DJIA_hpp */
