//
//  main.cpp
//  P1
//
//  Created by Samantha Ho on 7/15/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
* main.cpp
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

#include "main.h"
using namespace std;

int main(int argc, const char * argv[])
{
    int total_records = 0;
    
    // test local file path /Users/sam/Desktop/COSC-051/COSC052/P1/GivenFilesP1/history.dat
    try
    {
        if (argc < 2)
        {
            //testing for lack of command line argument after ./a.out
            throw logic_error("ERROR: must enter command line argument for data file.");
        }
        else
        {
            string inputFilePathName(argv[1]);
            string header;
            
            //instantiating history object and loading all data from history.dat
            History h1;
            ifstream inFile;
            
            //opening file
            inFile.open(inputFilePathName.c_str());
            try
            {
                if (!inFile)
                {
                    throw invalid_argument("File Failed To Open");
                }
            }
            catch (invalid_argument &e)
            {
                cout << "Invalid Argument Caught in nested try block in main" <<endl;
                cout << e.what() << endl;
            } 
            //getline to ignore the first row of stuff
            getline (inFile, header);
            
            if (inFile)
            {
                //if inFile works then load history.dat by calling input function of history class
                total_records = h1.input(inFile);
                cout << "Average Adjusted Close for month: " << h1.getAverageAdjClose(1980, 05)
                    << endl;
                cout << "Average Adjusted Close for year: " << h1.getAverageAdjClose(1958) << endl;
                cout << "Total records in this file: " << total_records << endl;
                
            }
            
            inFile.close(); //closing infile
            
        }
    }
    catch(logic_error &e)
    {
        cout << "Exception caught in main - command line argument error" << endl; 
        cout << e.what() << endl;
    }
    
    

    //if statement to test for command line argument
    //else
    
    
    
    
    
    
    return 0;
}
