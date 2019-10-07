//
//  Exceptions.h
//  052_P2
//
//  Created by Samantha Ho on 7/16/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 *  Exceptions.h

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
//we are defining our own exception classes derived from the system exception classes 





#ifndef _COSC052_SUMMER_2019P2_EXCEPTIONS_H_
#define _COSC052_SUMMER_2019P2_EXCEPTIONS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
//#include "DateTime.h"

using std::string;
using std::logic_error;


// below is an example of deriving our own exception classes
// they do not have to be very complicated
// implementation code for the constructor is just as simple
// all that has to happen is to call the base class
// constructor and pass the string argument
//
// put the other derived exception class declarations in this file


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **            exception class file_open_error declaration                 **
 **            exception class bad_date_component declaration              **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class file_open_error : public std::invalid_argument
{
public:
    file_open_error(std::string); //convert constructor, converts object of other type to itself
    
}; // END file_open_error



class bad_date_component : public std::invalid_argument
{
public:
    bad_date_component(std::string);
    
}; // END bad_date_component

class missing_arguments : public std::logic_error
{
public:
    missing_arguments(std::string);

};

class no_such_object : public std:: logic_error
{
public:
    no_such_object(std::string);
};

class bad_mine_ID : public std::invalid_argument
{
public:
    bad_mine_ID(std::string);
    
};

class bad_mine_status : public std::invalid_argument
{
public:
    bad_mine_status(std::string);
    
};

class bad_mine_flagMC : public std::invalid_argument
{
public:
    bad_mine_flagMC(std::string);
    
};




#endif /* Exceptions_h */


