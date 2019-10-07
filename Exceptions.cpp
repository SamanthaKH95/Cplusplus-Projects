//
//  Exceptions.cpp
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
#include "Exceptions.h"

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                 class Exceptions implementation code                   **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

//member initialization list, constructor of the derived class can call constructor of base class
//parent is invalid argument, can call constructor from parent
//pass the same string s, will show up in .what() function

file_open_error::file_open_error(std::string s) : invalid_argument(s)
{
}//end file_open_error_class, nothing else needed in body

bad_date_component::bad_date_component(std::string s) : invalid_argument(s)
{
     
}//end bad date component class

missing_arguments::missing_arguments(std::string s) : std::logic_error(s)
{
    
}//end missing_arguments component class

bad_mine_ID::bad_mine_ID(std::string s) : invalid_argument(s)
{
    
}//end bad_mine_ID component class

bad_mine_status::bad_mine_status(std::string s) : invalid_argument(s)
{
    
}//end bad_mine_status component class

bad_mine_flagMC::bad_mine_flagMC(std::string s) : invalid_argument(s)
{
    
}//end bad_mine_flagMC component class

