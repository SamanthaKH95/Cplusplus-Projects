//
//  main.cpp
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




#include "main.h"
using namespace std; 

void loadMineData(ifstream &inFile, vector<MineRecord> &vMRec);


int main(int argc, const char * argv[])
{
    // define vector of MineRecord struct objects, each object is one line of data file 
    vector<MineRecord> mR;
    // define string to store data filename and path that is passes as first cmd. line argument
    string fileName;
    // define ifstream object
    ifstream inFile;
    // should "wrap" all other code except return 0 in a try block
    
    try
    {
        if (argc < 2)
        {
            //testing for lack of command line argument
            //throw invalid_argument("missing file name as cmd line arg.\n");
            throw missing_arguments("missing file name as cmd line arg");
        }
        
        else
        {
            fileName = string(argv[1]); //converting filename from cmd line arg
            inFile.open(fileName.c_str());
            
            if (!inFile)
            {
                //throw runtime_error("input file failed to open\nfileName\n");
                throw file_open_error("input file failed to open\nfileName\n");
            }
            
            //calling loadMineDate function, do not try to pass by reference when calling!
            loadMineData(inFile, mR);
            
            //now the mR minerecord vector is filled, use it below
            
            
        }
        
        inFile.close();
        
        //instantiate MineLog object, pass it the vector of minerecord objects
        //then this MineLog constructor will parce through the minerecords and mark them
        //as abandoned or working
        cout << "instantiating minelog object" << endl; 
        
        MineLog MLobj(mR);
        
        cout << "finished instatiating" << endl; 
        
        cout << "getting ready to displayexec" << endl;
        //it never finishes, something in display threw unknown exception that terminated main 
        
        MLobj.displayExecReport1(); //producing output to screen to test MineLog
        
        cout << "displayexecreport finished" << endl;
        
        
        cout << "Count of working mines that are coal producing: " <<
                MLobj.getCountCoalProducing() << endl;
        
        cout << "Count of working mines that are metal producing: " <<
                MLobj.getCountMetalProducing() << endl;
        
        

        
        //deallocate dynamically allocated memory within destructor 
        
        
    }//end try
    catch ( file_open_error &e )
    {
        cout << "WARNING: ";
        cout << "file_open_error exception caught in function main." << endl;
        cout << e.what() << endl;
    }
    catch (invalid_argument &e)
    {
        cout << "caught invalid argument exception in function main" << endl;
        cout << e.what();
    }
    catch ( missing_arguments &e )
    {
        cout << "WARNING: ";
        cout << "missing_arguments logic error exception caught in function main." << endl;
        cout << e.what() << endl;
    }
    catch(runtime_error &e)
    {
        cout << "Runtime Error caught in main\n";
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "caught unknown exception in function main" << endl;
        
    }
    
    
    return 0;
    
} // END function main



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 function loadMineData                                  **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

void loadMineData(ifstream &inFile, vector<MineRecord> &vMRec)
{
    int recordCount = 0;
    int recordAdded = 0;
    string oneLine = "";
    int recordsAccordingToFile = 0;
    string commentsToIgnore = "";
    string testMe = "";
    
    if (!inFile)
    {
        cout << "error with input file stream ";
        throw std::invalid_argument("file stream error, stream initially in failed state\n");
    }
    
    recordCount = 0;
    
    // read the first line that is NOT data, this will not be used anywhere
    inFile >> recordsAccordingToFile;
    getline(inFile, commentsToIgnore);
    
    // loop through all rows of the input data file
    while ( getline(inFile, oneLine) )
    {
        //cout << "oneLine: " << oneLine << endl;  // test output
        
        // this try block is designed so that any exception thrown will
        // prevent that current row of data from being added to the
        // vector of MineRecord objects
        
        try
        {
            recordCount++;
            
            // MineRecord constructor will throw several exceptions
            // mainly we expect an exception if any of the
            // date components are invalid
            
            MineRecord nextMineRecord(oneLine);
            
            // if an exception is thrown by MineRecord::MineRecord
            // then the following two statements will be skipped
            
            vMRec.push_back(nextMineRecord);
            recordAdded++;
        }
        catch ( bad_date_component &e )
        {
            cout << "WARNING: ";
            cout << "bad_date_component exception caught in function loadMineData." << endl;
            cout << e.what() << endl;
        }
        catch ( std::invalid_argument &e )
        {
            cout << "WARNING: ";
            cout << "invalid_argument exception caught in function loadMineData." << endl;
            cout << e.what() << endl;
        }
        catch (...)
        {
            cout << "WARNING: unknown exception caught in function loadMineData" << endl;
        }
        
    }
    
    cout << "finished reading file data..." << recordCount << " lines read." << endl;
    cout << recordAdded << " objects added to vector of MineRecord objects." << endl;
    
    
}  // END function loadMineData

