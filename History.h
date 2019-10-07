//
//  History.hpp
//  P1
//
//  Created by Samantha Ho on 7/15/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * History.h
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
#ifndef COSC52Summer2019P1_History_hpp
#define COSC52Summer2019P1_History_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <array>
#include <vector>

#include "DJIA.h"


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class History declaration                              **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class History
{
    
private:
    std::vector<DJIA> DJIA_List;
    
public:
    History();
    int input(std::istream &);
    void output(std::ostream & = std::cout);
    double getAverageAdjClose() const;
    double getAverageAdjClose(int) const;
    double getAverageAdjClose(int, int) const;
    
}; //END class History declaration



#endif /* History_hpp */
