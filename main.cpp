/*
 *  main.cpp
 *
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


#include "main.h"

int main(int argc, const char * argv[])
{
    LL<Date> dateLL;
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
            
            else
            {
                int recordsAccordingToFile;
                string commentsToIgnore;
                Date nextDateRecord;
                int year;
                int month;
                int day;
                char slash;
            
                //reading in total date records and ignoring comments in first line
                inFile >> recordsAccordingToFile;
                getline(inFile, commentsToIgnore);
                
                cout << "after reading in recordsAccordingToFile: " << recordsAccordingToFile << endl;
                cout << "comments to ignore: "<< commentsToIgnore << endl;
                
                inFile >> year >> slash >> month >> slash >> day;
                
                
                while (inFile)
                {
                    cout << endl << "in while loop" << endl;
                    cout << year << slash << month << slash << day;
                    nextDateRecord.setDate(year, month, day);
                    dateLL.push_back(nextDateRecord);
                    inFile >> year >> slash >> month >> slash >> day;
                }

                inFile.close();
                
                
                for (unsigned long i=0; i < dateLL.size(); i++)
                {
                    char slash = '/';
                    cout << endl << dateLL.at(i).getYear()
                                    << slash
                                 << dateLL.at(i).getMonth()
                                    << slash
                                 << dateLL.at(i).getDay() << endl;
                }
                
                cout << "this is the size of the linked list " << dateLL.size() << endl;
                
                ProcessTimer sw1;
                
                Date testDate(1916,11,23);
                
                sw1.setTimeStart(clock());
                //cout << "linear search found at index: " << dateLL.linearSearch(testDate) << endl;
                dateLL.bubbleSort(); //the right number of output
                //dateLL.selectionSort(); //1019 - 4 more than prof output, profs wont swap same #
                //dateLL.bubbleSortI(); //260167 - 261171,
                //cout << "binary search found at index: " << dateLL.binarySearch(testDate) << endl;
                sw1.setTimeEnd(clock());
                cout << "time started at: " << sw1.getTimeStart() << endl;
                cout << "time ended at: " <<sw1.getTimeEnd() << endl;
                cout << "time elapsed: " << fixed << sw1.getTimeElapsed() << endl;
                
                
 
                
                for (unsigned long i=0; i < dateLL.size(); i++)
                {
                    char slash = '/';
                    cout << endl << dateLL.at(i).getYear()
                    << slash
                    << dateLL.at(i).getMonth()
                    << slash
                    << dateLL.at(i).getDay() << endl;
                }
                 
                
            }//end else
        }//end second else
        
        
    }//end try
    catch ( file_open_error &e )
    {
        cout << "WARNING: ";
        cout << "file_open_error exception caught in function main." << endl;
        cout << e.what() << endl;
    }
    catch ( bad_date_component &e )
    {
        cout << "WARNING: ";
        cout << "bad_date_component exception caught in function loadMineData." << endl;
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
    catch(no_such_object &e)
    {
        cout << "No_Such_object error caught in main\n";
        throw;
    }
    catch(out_of_range &e)
    {
        cout << "caught out_of_range error in main" << endl;
    }
    catch(logic_error &e)
    {
        cout << "Logic Error caught in main\n";
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "caught unknown exception in function main" << endl;
        
    }
    
    
    return 0;
    
} // END function main


