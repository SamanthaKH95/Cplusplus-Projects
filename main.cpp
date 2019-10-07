//
//  main.cpp
//  skh50P3
//
//  Created by Samantha Ho on 3/20/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * main.cpp
 *
 * COSC 051 Spring 2019
 * Project #3
 *
 * Due on: March 21, 2019
 * Author: skh50
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
using namespace std;

// local file path on my computer /Users/sam/Downloads/P3West.dat
// local file path on my computer /Users/sam/Downloads/P3South.dat
// local file path on my computer /Users/sam/Downloads/P3North.dat
// local file path on my computer /Users/sam/Downloads/P3East.dat
// local file path on my computer /Users/sam/Downloads/P3Other.dat
// local file path on my computer /Users/sam/Downloads/P3All.dat
/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function prototypes                           **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
char displayMenu();


void loadFile(string fName, bool &loadSuccess, vector<char> &vTyp,
              vector<int> &vDst, vector<int> &vWgt, vector<int> &vPno,
              vector<char> &vSO, vector<char> &vSD,
              vector<string> &vNum, vector<string> &vReg);


void allDetails(const vector<char> &vTyp,
                const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                const vector<char> &vSO, const vector<char> &vSD,
                const vector<string> &vNum, const vector<string> &vReg);


void estimateDetails(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg);


void summaryByType(const vector<char> &vTyp,
                   const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                   const vector<char> &vSO, const vector<char> &vSD,
                   const vector<string> &vNum, const vector<string> &vReg);


void summaryByRegion(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg);

void clearData (vector<char> &vTyp,
                vector<int> &vDst, vector<int> &vWgt, vector<int> &vPno,
                vector<char> &vSO, vector<char> &vSD,
                vector<string> &vNum, vector<string> &vReg);

void loadCosts(const vector<char> &vTyp,
                const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                const vector<char> &vSO, const vector<char> &vSD,
                const vector<string> &vNum, const vector<string> &vReg,
                vector<double> &vTotCost);

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          GLOBAL CONSTANTS                              **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

const double B_PACK_LOAD = 0.065;
const double B_PER_LB_MILE = 0.0011;
const double W_PACK_LOAD = 0.256;
const double W_PER_LB_MILE = 0.0011;
const double C_PACK_LOAD = 0.459;
const double C_PER_LB_MILE = 0.0012;
const int MIN_DRIVING_DISTANCE = 1;
const int MAX_DRIVING_DISTANCE = 3200;
const int WEIGHT_LOWER_BOUND = 1200;
const int WEIGHT_UPPER_BOUND = 18000;
const int MAX_PIANOS = 3;
const double STAIRS_SURCHARGE_RATE = 132;
const int NO_STAIRS_PIANO_SURCHARGE = 275;
const int ONE_STAIRS_PIANO_SURCHARGE = 575;
const int TWO_STAIRS_PIANO_SURCHARGE = 1075;

const string PROMPT_FILE = "Please enter the file path and name: ";
const string ERROR_FILE_OPEN = "ERROR: File open error, please check path and name of: ";
const string SUCCESS_FILE_OPEN = "File opened successfully for input: ";


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function main                                 **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

int main()
{
    //initializing variables
    string FilePathAndName; //string to store file path and name
    char menuInput; //to store user menu input choice
    //initializing variables to send to functions
    bool loadSuccess;
    vector<char> vTyp; //move types
    vector<int> vDst; //move distances
    vector<int> vWgt; //move weights
    vector<int> vPno; //number of pianos
    vector<char> vSO; //stairs at origin
    vector<char> vSD; //stairs at destination
    vector<string> vNum; //estimate number
    vector<string> vReg; //region
    vector<double> vTotCost; //parallel vector to store total costs
    
    //welcome message
    cout << "Welcome to the BHMSI move cost calculator!" << endl << endl << endl;
    
    //calling function to display menu in a do while-loop, so that it executes at least once
    do {
        menuInput = displayMenu(); //calling displayMenu function
        menuInput = toupper(menuInput);
        
        //while loop to validate the input, display error and prompt for re-entry if needed
        while (menuInput != 'L' && menuInput != 'A' && menuInput != 'E' && menuInput != 'T'
               && menuInput != 'R' && menuInput != 'C' && menuInput != 'Q')
        {
            cout << "The input choice was incorrect, please re-enter an option from the menu:"
                 << endl;
            menuInput = displayMenu();
            menuInput = toupper(menuInput);
            
        } //END WHILE LOOP
        
        //if loop to call appropriate function, as long as user does not choose to quit
        if (menuInput != 'Q')
        {
            switch (menuInput)
            {
                case 'L': cout << "The User Asked To Do:" << menuInput << endl;
                    cout << PROMPT_FILE;
                    cin >> FilePathAndName;
                    //call loadFile function
                    loadFile(FilePathAndName, loadSuccess, vTyp,
                             vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                    //testing to see if vector size increased properly, works!!
                    //cout << "The size of the new vector is" << vTyp.size();
                    break;
                case 'A': cout << "The User Asked To Do:" << menuInput << endl;
                    if (loadSuccess == false) //testing for previous successful load file
                    {
                        cout << "ERROR: need at least one successfully loaded file" << endl;
                        cout << "Please try again" << endl;
                        break;
                    }
                    else
                    {
                        allDetails(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                        break;
                    }
                case 'E': cout << "The User Asked To Do:" << menuInput << endl;
                    if (loadSuccess == false) //testing for previous successful load file
                    {
                        cout << "ERROR: need at least one successfully loaded file" << endl;
                        cout << "Please try again" << endl;
                        break;
                    }
                    else
                    {
                        estimateDetails(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                        break;
                    }
                case 'T': cout << "The User Asked To Do:" << menuInput << endl;
                    if (loadSuccess == false) //testing for previous successful load file
                    {
                        cout << "ERROR: need at least one successfully loaded file" << endl;
                        cout << "Please try again" << endl;
                        break;
                    }
                    else
                    {
                        summaryByType(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                        break;
                    }
                case 'R': cout << "The User Asked To Do:" << menuInput << endl;
                    if (loadSuccess == false) //testing for previous successful load file
                    {
                        cout << "ERROR: need at least one successfully loaded file" << endl;
                        cout << "Please try again" << endl;
                        break;
                    }
                    else
                    {
                        summaryByRegion(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                        break;
                    }
                case 'C': cout << "The User Asked To Do:" << menuInput << endl;
                    clearData (vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                    cout << "Data has been cleared from vectors" << endl;
                    
            } //END Switch menu
        }//END if loop for function calls when user does not quit
        
    } while(menuInput != 'Q'); //END DO-WHILE LOOP, this repeats menu until user quits
    
    if (menuInput == 'Q')
    {
        cout << "Thank you for using the BHMSI move cost calculator (Menu Driven Version)." <<
                "The program will now terminate. Goodbye." << endl;
        exit(0);
    }
    
    
    
    return 0;
} // END MAIN FUNCTION

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          display_menu                                  **
 **               this function clears the screen and then                 **
 **                 displays the menu choices, gets menu choice            **
 **                                from user                               **
 ****************************************************************************
 ****************************************************************************/
char displayMenu()
{
    char menuInput;
    cout << endl;
    cout << right << setw(43) << "Load A Regional Move Data File" << setw (10) << "L" << endl;
    cout << right << setw(43) << "Display Details (All Loaded Data)" << setw (10) << "A" << endl;
    cout << right << setw(43) << "List Details For Specific Estimate Number" << setw (10) << "E"
         << endl;
    cout << right << setw(43) << "Display Summary By Move Type" << setw (10) << "T" << endl;
    cout << right << setw(43) << "Display Summary By Region" << setw (10) << "R" << endl;
    cout << right << setw(43) << "Clear All Data" << setw (10) << "C" << endl;
    cout << right << setw(43) << "Quit" << setw (10) << "Q" << endl << endl << endl;
    
    cout << left << "Please enter your choice: ";
    cin >> menuInput;
    cin.ignore(500, '\n');
    
    return menuInput;
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function loadFile                             **
 **               this function loads the data and performs                **
 **                 error checking on each entry as per project2           **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

void loadFile(string fName, bool &loadSuccess, vector<char> &vTyp,
              vector<int> &vDst, vector<int> &vWgt, vector<int> &vPno,
              vector<char> &vSO, vector<char> &vSD,
              vector<string> &vNum, vector<string> &vReg)
{   //initializing variables
    vector<double> vTotCost;
    string State;
    string Region;
    string UniqueID;    //string with no spaces
    string NameAndEmail; //with space
    string fileName = "";
    ifstream inFile;
    string headings = "";
    string oneRow = "";
    int DoubleDistance;
    int MinWeight;
    int DrivingDistance;
    int TotalWeightLBS;
    int NumPianos;
    int SetofStairs = 0;
    double StairsSurcharge = 0;
    double PianoSurcharge = 0;
    char MoveType;
    char MoreThan15StairsOrigin;
    char MoreThan15StairsDest;
    int ESTyear = 0, ESTmonth= 0, ESTday= 0; //to store estimate date components
    int Moveyear = 0, Movemonth= 0, Moveday= 0; //to store estimate date components
    char slash = '?'; //to store slash in between date components
    int TotalRecords =0;
    int TotalRecordsWithError = 0;
    int TotalRecordsWithoutError = 0;
    double TotalCost = 0.0; //total cost per move
    double totalAmount = 0.0; //total sales
    int error = 0; //to test/keep track of whether there is error in the entry
    
    //keeping count of move types on record
    int B_pack_count = 0;
    int B_pack_distance = 0;
    int B_pack_weight = 0;
    double B_pack_totalcost = 0.00;
    
    int W_pack_count = 0;
    int W_pack_distance = 0;
    int W_pack_weight = 0;
    double W_pack_totalcost = 0.00;
    
    int C_pack_count = 0;
    int C_pack_distance = 0;
    int C_pack_weight = 0;
    double C_pack_totalcost = 0.00;
    
    //opening file
    inFile.open(fName.c_str() );
    
    //error message
    if (!inFile)
    {
        cout << ERROR_FILE_OPEN << fName << endl; //file failed to open, error message
        cout << "File data did not successfully load." << endl;
        loadSuccess = false;
        return; //returns to main function
    } //end if statement for infile error
    
    else //processes data as per P2
    {
        loadSuccess = true;
        cout << SUCCESS_FILE_OPEN << fName << endl << endl; //file open success message
        getline(inFile, headings); //reading the headings line to get it out of the way
        
        //code to process data starts
        
        //outputting the headings
        cout << right << setw(12) << "Order" << setw(15) << "Move" << setw(13) <<
        "Move"<<setw(10) << "Dist." << setw(10) << "Weight" <<
        setw(10) <<"Number" << setw(10) <<
        "Stairs" << setw(10)<<"Move"<<setw(10) << "Total" << endl;
        
        cout << right << setw(11) << "Date" << setw(16) << "Date" << setw(13) <<
        "Code"<<setw(10) << "(Miles)" << setw(10) << "(LBS)" <<
        setw(10) <<"Pianos"<< setw(5) << "O" << setw(5) <<
        "D" << setw(12)<<"Number"<<setw(11) << "Cost ($)" << endl;
        
        cout << "----------------------------------------------------------";
        cout << "----------------------------------------------------------";
        cout << "----------------------------" << endl;
        
        
        
        //reading the data into variables for data validation
        while (inFile >> UniqueID >> ESTyear >> slash >> ESTmonth >> slash >> ESTday >>
               Moveyear >> slash >> Movemonth >> slash >> Moveday >> MoveType >>
               DrivingDistance >> TotalWeightLBS >> NumPianos >> MoreThan15StairsOrigin >>
               MoreThan15StairsDest >> State >> Region && getline(inFile, NameAndEmail))
        {
            
            TotalRecords++; //count total records in file
            SetofStairs = 0;
            
            //adjusting minimum entries before output
            if (NumPianos < 0) //need to adjust negative pianos into 0s before output
            {
                NumPianos = 0;
            }
            
            if(DrivingDistance < MIN_DRIVING_DISTANCE) //need to adjust milage less than 1
                //to 1 before output
            {
                DrivingDistance = MIN_DRIVING_DISTANCE;
            }
            
            //computing min weight value
            DoubleDistance = 2 * DrivingDistance;
            if (DoubleDistance < WEIGHT_LOWER_BOUND)
            {
                MinWeight = WEIGHT_LOWER_BOUND;
            }
            else
            {
                MinWeight = DoubleDistance;
            }
            
            cout << setfill(' ');
            cout << setw(4) << " " << ESTyear << slash << setfill('0') << setw(2) << ESTmonth
                            << slash << setw(2) << ESTday;
            cout << setfill(' ') << setw(10) << Moveyear << slash << setfill('0') << setw(2)
                                << Movemonth << slash << setw(2) << Moveday;
            cout << setfill(' ') << setw(9) << MoveType;
            cout << setw(11) << DrivingDistance;
            cout << setw(10) << TotalWeightLBS;
            cout << setw(7) << NumPianos;
            cout << setw(8) << MoreThan15StairsOrigin;
            cout << setw(5) << MoreThan15StairsDest;
            
            if (Movemonth < ESTmonth)
                Movemonth += 12;
            
            if (Movemonth-ESTmonth < 2)
            {
                cout << "\nERROR: The move date is too soon after the estimate date.";
                error++; //to indicate error item
            }
            if (Movemonth-ESTmonth > 6)
            {
                cout << "\nERROR: The move date is too long after the estimate date.";
                error++;
            }
            
            if (MoveType != 'B' && MoveType != 'b' && MoveType != 'W' && MoveType != 'w' &&
                MoveType != 'C' && MoveType != 'c')
            {
                cout << "\nERROR: Move type invalid";
                error++;
            }
            
            if (DrivingDistance > MAX_DRIVING_DISTANCE)
            {
                cout << "\nERROR: Distance exceeded max distance of 3200";
                error++;
            }
            
            if(TotalWeightLBS < MinWeight)
            {
                cout << "\nERROR: Weight entered less than minimum allowed";
                error++;
            }
            if (TotalWeightLBS > WEIGHT_UPPER_BOUND)
            {
                cout << "\nERROR: Weight entered exceeds max of 18000";
                error++;
            }
            
            
            
            if (NumPianos > MAX_PIANOS)
            {
                cout << "\nERROR: Maximum number of pianos exceeded.";
                error++;
            }
            
            if (MoreThan15StairsOrigin != 'y' && MoreThan15StairsOrigin != 'Y' &&
                MoreThan15StairsOrigin != 'n' && MoreThan15StairsOrigin != 'N')
            {
                cout << "\nERROR: answer of stairs at origin invalid";
                error++;
            }
            
            if (MoreThan15StairsDest != 'y' && MoreThan15StairsDest != 'Y' &&
                MoreThan15StairsDest != 'n' && MoreThan15StairsDest != 'N')
            {
                cout << "\nERROR: answer of stairs at destination invalid";
                error++;
            }
            
            
            if (error > 0) //entry is error if more than 0
            {
                //cout << endl;
                cout << "\nContact customer to resolve issues: " << NameAndEmail << endl << endl;
                TotalRecordsWithError++;
                error = 0; //restart error test for next iteration of loop
            } //error>0 if statement END
            
            
            else //entry is not error, calculate and output Unique ID and Total Cost
            {
                
                // calculating total cost
                //calculating total number of stairs exceeding 15 steps
                if (MoreThan15StairsOrigin == 'Y' || MoreThan15StairsOrigin == 'y')
                {
                    SetofStairs++;
                }
                if (MoreThan15StairsDest == 'Y' || MoreThan15StairsDest == 'y')
                {
                    SetofStairs++;
                }
                
                
                StairsSurcharge = STAIRS_SURCHARGE_RATE * SetofStairs;
                
                //figuring out piano surcharge based on sets of stairs
                if (SetofStairs == 0)
                {
                    PianoSurcharge = NumPianos * NO_STAIRS_PIANO_SURCHARGE;
                }
                if (SetofStairs == 1)
                {
                    PianoSurcharge = NumPianos * ONE_STAIRS_PIANO_SURCHARGE;
                }
                if (SetofStairs == 2)
                {
                    PianoSurcharge = NumPianos * TWO_STAIRS_PIANO_SURCHARGE;
                }
                
                //final calculations of cost depending on move type
                if (MoveType == 'B' || MoveType == 'b')
                {
                    TotalCost = (B_PACK_LOAD*TotalWeightLBS) +
                    (B_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge +
                    PianoSurcharge;
                    B_pack_count++;
                    B_pack_distance = B_pack_distance + DrivingDistance;
                    B_pack_weight = B_pack_weight + TotalWeightLBS;
                    B_pack_totalcost = B_pack_totalcost + TotalCost;
                }
                
                if (MoveType == 'C' ||MoveType == 'c')
                {
                    TotalCost = (C_PACK_LOAD*TotalWeightLBS) +
                    (C_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge +
                    PianoSurcharge;
                    C_pack_count++;
                    C_pack_distance = C_pack_distance + DrivingDistance;
                    C_pack_weight = C_pack_weight + TotalWeightLBS;
                    C_pack_totalcost = C_pack_totalcost + TotalCost;
                }
                
                if (MoveType == 'W'||MoveType == 'w')
                {
                    TotalCost = (W_PACK_LOAD*TotalWeightLBS) +
                    (W_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge +
                    PianoSurcharge;
                    W_pack_count++;
                    W_pack_distance = W_pack_distance + DrivingDistance;
                    W_pack_weight = W_pack_weight + TotalWeightLBS;
                    W_pack_totalcost = W_pack_totalcost + TotalCost;
                }
                
                
                cout << setw(13) << UniqueID;
                cout << setw(10) << TotalCost;
                cout << endl;
                
                TotalRecordsWithoutError++;
                totalAmount = totalAmount + TotalCost;
                
                //appending to the 9 vectors
                vTyp.push_back(MoveType);
                vDst.push_back(DrivingDistance);
                vWgt.push_back(TotalWeightLBS);
                vPno.push_back(NumPianos);
                vSO.push_back(MoreThan15StairsOrigin);
                vSD.push_back(MoreThan15StairsDest);
                vNum.push_back(UniqueID);
                vReg.push_back(Region);
                //vTotCost.push_back(TotalCost);
                
                
            }
            
        }//END while loop for reading lines and outputting data
        
        loadCosts(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg, vTotCost);
        
        
        cout << endl;
        cout << "Total Records: " << TotalRecords << "  ";
        cout << "Total Records With Errors: " << TotalRecordsWithError << "  ";
        cout << "Total Records Without Errors: "<< TotalRecordsWithoutError << "  ";
        cout << "Total Sales: $" << setprecision(2) << fixed << showpoint << totalAmount <<
                endl << endl;
        
        //outputting summary statistics
        cout << setw(50) << "TOTALS: Records Without Errors" << endl << endl;
        cout << setw(10) << left << "Type" << setw(10) << "Count" << setw(10) <<
        "Distance" << setw(10) << "Weight" << setw(10) << "Cost" << endl;
        cout << "-----------------------------------------------------------------------"<< endl;
        cout << setw(10) << left << "Basic" << setw(10) << B_pack_count << setw(10) <<
        B_pack_distance << setw(10) << B_pack_weight << setw(2) << "$" << fixed << setprecision(2)
        <<showpoint << setw(10) <<B_pack_totalcost << endl;
        
        cout << setw(10) << left << "Wall Pack" << setw(10) << W_pack_count << setw(10) <<
        W_pack_distance << setw(10) << W_pack_weight << setw(2) << "$" << fixed << setprecision(2)
        <<showpoint << setw(10) <<W_pack_totalcost << endl;
        
        cout << setw(10) << left << "Complete" << setw(10) << C_pack_count << setw(10) <<
        C_pack_distance << setw(10) << C_pack_weight << setw(2) << "$" << fixed << setprecision(2)
        <<showpoint << setw(10) <<C_pack_totalcost << endl << endl;
        
        cout << "Thank you for using the BHMSI move cost calculator (Menu Driven Version)."
            << endl;
        
        
    } // end ELSE and data processing
    
    return; //END return to main for menu to display again
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 function loadCosts - allows                            **
 **     for fector totcosts to be calculated and send to                   **
 **                 subsequent functions for use                           **
 ****************************************************************************
 ****************************************************************************/

void loadCosts(const vector<char> &vTyp,
               const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
               const vector<char> &vSO, const vector<char> &vSD,
               const vector<string> &vNum, const vector<string> &vReg,
               vector<double> &vTotCost)
{
    char MoreThan15StairsOrigin;
    char MoreThan15StairsDest;
    int SetofStairs;
    double StairsSurcharge;
    double PianoSurcharge;
    int NumPianos;
    char MoveType;
    double TotalCost;
    int TotalWeightLBS;
    int DrivingDistance;
    
    int B_pack_count =0;
    int B_pack_distance=0;
    int B_pack_weight=0;
    double B_pack_totalcost=0;
    
    int C_pack_count =0;
    int C_pack_distance =0;
    int C_pack_weight=0;
    double C_pack_totalcost=0;
    
    int W_pack_count =0;
    int W_pack_distance=0;
    int W_pack_weight=0;
    double W_pack_totalcost=0;
    
    
    
    for (unsigned long i = 0; i < vTyp.size(); i++)
    {
        MoveType = vTyp.at(i);
        DrivingDistance = vDst.at(i);
        TotalWeightLBS = vWgt.at(i);
        NumPianos = vPno.at(i);
        MoreThan15StairsDest = vSD.at(i);
        MoreThan15StairsOrigin = vSO.at(i);
        
        PianoSurcharge = 0;
        StairsSurcharge = 0;
        
        if (MoveType == 'B' || MoveType == 'b')
        {
            B_pack_count++;
        }
        if (MoveType == 'C' || MoveType == 'c')
        {
            C_pack_count++;
        }
        if (MoveType == 'W' || MoveType == 'w')
        {
            W_pack_count++;
        }
        
        SetofStairs = 0;
        // calculating total cost
        //calculating total number of stairs exceeding 15 steps
        if (MoreThan15StairsOrigin == 'Y' || MoreThan15StairsOrigin == 'y')
        {
            SetofStairs++;
        }
        if (MoreThan15StairsDest == 'Y' || MoreThan15StairsDest == 'y')
        {
            SetofStairs++;
        }
        
        
        StairsSurcharge = STAIRS_SURCHARGE_RATE * SetofStairs;
        
        //figuring out piano surcharge based on sets of stairs
        if (SetofStairs == 0)
        {
            PianoSurcharge = NumPianos * NO_STAIRS_PIANO_SURCHARGE;
        }
        if (SetofStairs == 1)
        {
            PianoSurcharge = NumPianos * ONE_STAIRS_PIANO_SURCHARGE;
        }
        if (SetofStairs == 2)
        {
            PianoSurcharge = NumPianos * TWO_STAIRS_PIANO_SURCHARGE;
        }
        
        //final calculations of cost depending on move type
        if (MoveType == 'B' || MoveType == 'b')
        {
            TotalCost = (B_PACK_LOAD*TotalWeightLBS) +
            (B_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge +
            PianoSurcharge;
            B_pack_count++;
            B_pack_distance = B_pack_distance + DrivingDistance;
            B_pack_weight = B_pack_weight + TotalWeightLBS;
            B_pack_totalcost = B_pack_totalcost + TotalCost;
        }
        
        if (MoveType == 'C' ||MoveType == 'c')
        {
            TotalCost = (C_PACK_LOAD*TotalWeightLBS) +
            (C_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge +
            PianoSurcharge;
            C_pack_count++;
            C_pack_distance = C_pack_distance + DrivingDistance;
            C_pack_weight = C_pack_weight + TotalWeightLBS;
            C_pack_totalcost = C_pack_totalcost + TotalCost;
        }
        
        if (MoveType == 'W'||MoveType == 'w')
        {
            TotalCost = (W_PACK_LOAD*TotalWeightLBS) +
            (W_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge +
            PianoSurcharge;
            W_pack_count++;
            W_pack_distance = W_pack_distance + DrivingDistance;
            W_pack_weight = W_pack_weight + TotalWeightLBS;
            W_pack_totalcost = W_pack_totalcost + TotalCost;
        }
        vTotCost.push_back(TotalCost);
    }//end for loop
}//END FUNCTION

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function allDetails                           **
 **               this function displays a listing of file data            **
 **                 and calculated data.                                   **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/


void allDetails(const vector<char> &vTyp,
                const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                const vector<char> &vSO, const vector<char> &vSD,
                const vector<string> &vNum, const vector<string> &vReg)
{
    vector<double> vTotCost;
    loadCosts(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg, vTotCost);
    //outputting the headings
    cout << setw(12) << "Move" << setw(15) << "Dist." << setw(13) <<
    "Weight"<<setw(10) << "Number" << setw(10) <<
    "Stairs" << setw(15)<<"Move"<<setw(15) << "Total" << endl;
    
    cout << setw(12) << "Type" << setw(15) << "(Miles)" << setw(13) <<
    "(Pounds)"<<setw(10) << "Pianos" << setw(5) << "O" << setw(5) <<
    "D" << setw(15)<<"Number"<< setw(15) << "Cost ($)" << endl;
    
    cout << "----------------------------------------------------------";
    cout << "----------------------------------------------------------";
    cout << "----------------------------" << endl;
    
    //initializing a count variable
    int count = 0;
    int totalRecords = 0;
    double total_cost = 0;
    //for loop to print out everything stored in all the vectors
    for (count = 0; count < vTyp.size(); count++)
    {
        cout << left;
        cout << setw(12) << vTyp[count];
        cout << setw(15) << vDst[count];
        cout << setw(13) << vWgt[count];
        cout << setw(10) << vPno[count];
        cout << setw(5) << vSO[count];
        cout << setw(5) << vSD[count];
        cout << setw(15) << vNum[count];
        cout << right << setw(10) << vTotCost[count];
        cout << endl;
        
        totalRecords++;
        total_cost += vTotCost[count];
        
    }
    
    cout << endl;
    cout << totalRecords << " total records." << endl;
    cout << total_cost << " total of all move charges" << endl;
    double averageMoveCharges = total_cost/ totalRecords; 
    cout << averageMoveCharges << " average of all move charges" << endl;
}//END function
/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function estimateDetails                      **
 **               this function displays a listing of file data            **
 **                 and calculated data, same as allDetails                **
 **                  but prompts user for estimate number                  **
 ****************************************************************************
 ****************************************************************************/
void estimateDetails(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg)
{
    vector<double> vTotCost;
    loadCosts(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg, vTotCost);
    string estimateNumber;
    int count = 0;
    int position = 0;
    bool truth = false;
    cout << "Enter the estimate number to display: " << endl;
    cin >> estimateNumber;
    

    //for loop to find the subscript of the corresponding estimate number
    for (count = 0; count < vNum.size(); count++)
    {
        if (vNum.at(count) == estimateNumber)
        {
            position = count;
            truth = true;
        }
        
    }
    
    if (truth == false)
    {
        cout << "No match has been found for the estimate number." << endl;
        cout << "Please try again with another estimate number." << endl;
        return;
    }
    
    //outputting the headings
    cout << setw(12) << "Move" << setw(15) << "Dist." << setw(13) <<
    "Weight"<<setw(10) << "Number" << setw(10) <<
    "Stairs" << setw(15)<<"Move"<<setw(15) << "Total" << endl;
    
    cout << setw(12) << "Type" << setw(15) << "(Miles)" << setw(13) <<
    "(Pounds)"<<setw(10) << "Pianos" << setw(5) << "O" << setw(5) <<
    "D" << setw(15)<<"Number"<<setw(15) << "Cost ($)" << endl;
    cout << "----------------------------------------------------------";
    cout << "----------------------------------------------------------";
    cout << "----------------------------" << endl;
    
    cout << setw(12) << vTyp[position];
    cout << setw(15) << vDst[position];
    cout << setw(13) << vWgt[position];
    cout << setw(10) << vPno[position];
    cout << setw(5) << vSO[position];
    cout << setw(5) << vSD[position];
    cout << setw(15) << vNum[position];
    cout << right << setw(10) << vTotCost[position];
    cout << endl << endl;
        
}
/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function summaryByType                        **
 **               this function displays a summary table of                **
 **                 totals depending on move type                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

void summaryByType(const vector<char> &vTyp,
                   const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                   const vector<char> &vSO, const vector<char> &vSD,
                   const vector<string> &vNum, const vector<string> &vReg)
{
    vector<double> vTotCost;
    loadCosts(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg, vTotCost);
    int count;
    int total_records = 0;
    int total_distance = 0;
    int total_weight = 0;
    double total_cost = 0;
    
    int total_B_count = 0;
    int total_B_distance = 0;
    int total_B_weight = 0;
    double total_B_cost = 0;
    
    int total_W_count = 0;
    int total_W_distance = 0;
    int total_W_weight = 0;
    double total_W_cost = 0;
    
    int total_C_count = 0;
    int total_C_distance = 0;
    int total_C_weight = 0;
    double total_C_cost = 0;
    
    for (count = 0; count < vTyp.size(); count++)
    {
        if (vTyp[count] == 'B' || vTyp[count] == 'b')
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_B_count++;
            total_B_distance += vDst[count];
            total_B_weight += vWgt[count];
            total_B_cost += vTotCost[count];
        }
        
        if (vTyp[count] == 'W' || vTyp[count] == 'w')
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_W_count++;
            total_W_distance += vDst[count];
            total_W_weight += vWgt[count];
            total_W_cost += vTotCost[count];
        }
        
        if (vTyp[count] == 'C' || vTyp[count] == 'c')
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_C_count++;
            total_C_distance += vDst[count];
            total_C_weight += vWgt[count];
            total_C_cost += vTotCost[count];
        } //END of if statements
    }//END of for loop
    
    cout << setw(25) << right << "TOTALS ( " << total_records << " records )" << endl;
    cout << setw(10) << left << "Type" << setw(10) << "Count" << setw(10) <<
    "Distance" << setw(10) << "Weight" << setw(10) << "Cost" << endl;
    cout << "-----------------------------------------------------------------------"<< endl;
    cout << setw(10) << left << "Basic" << setw(10) << total_B_count << setw(10) <<
    total_B_distance << setw(10) << total_B_weight << setw(2) << "$" << setw(10) << total_B_cost
    << endl;
    
    cout << setw(10) << left << "Wall Pack" << setw(10) << total_W_count << setw(10) <<
    total_W_distance << setw(10) << total_W_weight << setw(2) << "$" << setw(10) << total_W_cost
    << endl;
    
    cout << setw(10) << left << "Complete" << setw(10) << total_C_count << setw(10) <<
    total_C_distance << setw(10) << total_C_weight << setw(2) << "$" << setw(10) << total_C_cost
    << endl;
    
    cout << "-----------------------------------------------------------------------"<< endl;
    cout << setw(10) << left << "Total" << setw(10) << total_records << setw(10) <<
    total_distance << setw(10) << total_weight << setw(2) << "$" << setw(10) << total_cost
    << endl;
    
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function summaryByRegion                      **
 **               this function displays a summary table of                **
 **                 totals depending on region                             **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
void summaryByRegion(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg)
{
    vector<double> vTotCost;
    loadCosts(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg, vTotCost);
    int count;
    int total_records = 0;
    int total_distance = 0;
    int total_weight = 0;
    double total_cost = 0;
    
    int total_South_count = 0;
    int total_South_distance = 0;
    int total_South_weight = 0;
    double total_South_cost = 0;
    
    int total_West_count = 0;
    int total_West_distance = 0;
    int total_West_weight = 0;
    double total_West_cost = 0;
    
    int total_North_count = 0;
    int total_North_distance = 0;
    int total_North_weight = 0;
    double total_North_cost = 0;
    
    int total_East_count = 0;
    int total_East_distance = 0;
    int total_East_weight = 0;
    double total_East_cost = 0;
    
    int total_Other_count = 0;
    int total_Other_distance = 0;
    int total_Other_weight = 0;
    double total_Other_cost = 0;
    
    for (count = 0; count < vReg.size(); count++)
    {
        if (vReg[count] == "South")
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_South_count++;
            total_South_distance += vDst[count];
            total_South_weight += vWgt[count];
            total_South_cost += vTotCost[count];
        }
        
        if (vReg[count] == "West")
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_West_count++;
            total_West_distance += vDst[count];
            total_West_weight += vWgt[count];
            total_West_cost += vTotCost[count];
        }
        
        if (vReg[count] == "North")
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_North_count++;
            total_North_distance += vDst[count];
            total_North_weight += vWgt[count];
            total_North_cost += vTotCost[count];
        }
        
        if (vReg[count] == "East")
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_East_count++;
            total_East_distance += vDst[count];
            total_East_weight += vWgt[count];
            total_East_cost += vTotCost[count];
        }
        
        if (vReg[count] == "Other")
        {
            total_records++;
            total_distance = total_distance + vDst[count];
            total_weight = total_weight + vWgt[count];
            total_cost = total_cost + vTotCost[count];
            
            total_Other_count++;
            total_Other_distance += vDst[count];
            total_Other_weight += vWgt[count];
            total_Other_cost += vTotCost[count];
        }
        
        
        
        } //END of if statements
    
    cout << setw(25) << right << "TOTALS ( " << total_records << " records )" << endl;
    cout << setw(10) << left << "Region" << setw(10) << "Count" << setw(10) <<
    "Distance" << setw(10) << "Weight" << setw(10) << "Cost" << endl;
    cout << "-----------------------------------------------------------------------"<< endl;
    cout << setw(10) << left << "South" << setw(10) << total_South_count << setw(10) <<
    total_South_distance << setw(10) << total_South_weight << setw(2) << "$" << setw(10)
    << total_South_cost << endl;
    
    cout << setw(10) << left << "West" << setw(10) << total_West_count << setw(10) <<
    total_West_distance << setw(10) << total_West_weight << setw(2) << "$" << setw(10)
    << total_West_cost << endl;
    
    cout << setw(10) << left << "North" << setw(10) << total_North_count << setw(10) <<
    total_North_distance << setw(10) << total_North_weight << setw(2) << "$" << setw(10)
    << total_North_cost << endl;
    
    cout << setw(10) << left << "East" << setw(10) << total_East_count << setw(10) <<
    total_East_distance << setw(10) << total_East_weight << setw(2) << "$" << setw(10)
    << total_East_cost << endl;
    
    cout << setw(10) << left << "Other" << setw(10) << total_Other_count << setw(10) <<
    total_Other_distance << setw(10) << total_Other_weight << setw(2) << "$" << setw(10)
    << total_Other_cost << endl;
    
    cout << "-----------------------------------------------------------------------"<< endl;
    cout << setw(10) << left << "Total" << setw(10) << total_records << setw(10) <<
    total_distance << setw(10) << total_weight << setw(2) << "$" << setw(10) << total_cost
    << endl;
    }//END of for loop

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          CLEARING ALL DATA                             **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
void clearData (vector<char> &vTyp,
                vector<int> &vDst, vector<int> &vWgt, vector<int> &vPno,
                vector<char> &vSO, vector<char> &vSD,
                vector<string> &vNum, vector<string> &vReg)
{
    vector<double> vTotCost;
    loadCosts(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg, vTotCost);
    vTyp.clear();
    vDst.clear();
    vWgt.clear();
    vPno.clear();
    vSO.clear();
    vSD.clear();
    vNum.clear();
    vReg.clear();
    vTotCost.clear();
}
