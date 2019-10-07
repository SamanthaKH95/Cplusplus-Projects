    //
//  History.cpp
//  P1
//
//  Created by Samantha Ho on 7/15/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * History.cpp
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
#include "History.h"
#include "DJIA.h"
using namespace std;

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                 class History implementation code                      **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

//manual constructor isn't needed because vector is already initialized as empty
History::History()
{}

int History::input(istream& in)
{
    
    int record_count = 0; //accumulator for total record count
    //load DJIA records from an input stream, returns total record count
    //       should test to ensure input data stream is in
    //       a working state sometime before the while loop
    
    DJIA dj1;
    
    // as long as the stream is in a working state, extract another object
    // and append it to the vector
    try
    {
        if (!in)
        {
            throw invalid_argument(failedInitialStream);
        }
        
        while (in >> dj1)
        {
            DJIA_List.push_back(dj1);
            record_count++;
        }
    }
   
    catch(invalid_argument &e)
    {
        cout << "caught invalid_argument exception in History class operator >>\n";
        cout << e.what();
    }
    
    
    return record_count;
}

void History::output(std::ostream &out)
{
    //outputs contents of vector, default output is to the terminal screen
    for (unsigned long i=0; i < DJIA_List.size(); i++)
    {
        out << DJIA_List.at(i) << endl;
    }
}

double History::getAverageAdjClose() const
{
    double total_adjclose = 0.0; //accumulator
    //for all records
    for (unsigned long i=0; i <DJIA_List.size(); i++)
    {
        total_adjclose = total_adjclose + DJIA_List[i].getAdjustedClose();
    }
    
    //to stop from being stale
    return total_adjclose / DJIA_List.size();
}

double History::getAverageAdjClose(int year) const
{
    //for specific year
    int specificyear = year;
    double total_adjclose = 0.0;
    int specific_year_records = 0;
    
    for (unsigned long i=0; i < DJIA_List.size(); i++)
    {
        if (DJIA_List[i].getMarketDate().getYear() == specificyear)
        {
            total_adjclose = total_adjclose + DJIA_List[i].getAdjustedClose();
            specific_year_records++;
        }
    }
    
    return total_adjclose / specific_year_records;
}
double History::getAverageAdjClose(int year, int month) const
{
    //for specific year and month
    int specificyear = year;
    int specificmonth = month;
    double total_adjclose = 0.0;
    int specific_year_records = 0;
    
    for (unsigned long i=0; i < DJIA_List.size(); i++)
    {
        if (DJIA_List[i].getMarketDate().getYear() == specificyear &&
            DJIA_List[i].getMarketDate().getMonth() == specificmonth)
        {
            total_adjclose = total_adjclose + DJIA_List[i].getAdjustedClose();
            specific_year_records++;
        }
    }
    
    return total_adjclose / specific_year_records;
}
