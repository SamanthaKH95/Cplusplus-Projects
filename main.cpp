//
//  main.cpp
//  skh50P2
//
//  Created by Samantha Ho on 2/14/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * main.cpp
 *
 * COSC 051 Spring 2019
 * Project #2
 *
 * Due on: February 26, 2019
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
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <stdio.h>
using namespace std;

//defining constants used in cost calculation, no magic numbers!
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



int main()
{
    string PROMPT_FILE = "Please enter the file path and name: ";
    string ERROR_FILE_OPEN = "ERROR: File open error, check path and name.";
    string SUCCESS_FILE_OPEN = "File opened successfully for input: ";
    //initiate varible and appropriate variable types

    char MoveType;
    int DrivingDistance;
    int TotalWeightLBS;
    int NumPianos;
    char MoreThan15StairsOrigin;
    char MoreThan15StairsDest;
    int DoubleDistance;
    int MinWeight;
    int SetofStairs = 0;
    double StairsSurcharge;
    double PianoSurcharge = 0;
    string UniqueID;    //string with no spaces
    string NameAndEmail; //with space
    string fileName = "";
    ifstream inFile;
    string headings = "";
    string oneRow = "";
    int TotalRecords =0;
    int TotalRecordsWithError = 0;
    int TotalRecordsWithoutError = 0;
    int ESTyear = 0, ESTmonth= 0, ESTday= 0; //to store estimate date components
    int Moveyear = 0, Movemonth= 0, Moveday= 0; //to store estimate date components
    char slash = '?'; //to store slash in between date components
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
    
    //local location of test file 1 on my computer :
    // /Users/sam/Desktop/COSC-051/skh50P2/P2S1.dat
    
    //welcome message
    cout << "Welcome To Bubba Hotep Moving & Storage Inc.!" << endl;
    cout << "This program will help you calculate move costs for bulk data input." << endl;
    

    
    
    //prompting data file input
    cout << PROMPT_FILE;
    cin >> fileName;
    cout << fixed << setprecision (2) << showpoint;  //to format output of totals
    
    inFile.open(fileName.c_str() );
    if (!inFile)
    {
        cout << ERROR_FILE_OPEN << fileName << endl; //file failed to open, error message
        
    } //end if statement for infile error
    else
    {
        cout << SUCCESS_FILE_OPEN << fileName << endl << endl; //file open success message
        
        //code to process data starts
        
        getline(inFile, headings); //reading the headings line to get it out of the way
        
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
               MoreThan15StairsDest && getline(inFile, NameAndEmail))
        {
            
            TotalRecords++; //count total records in file
            SetofStairs = 0;
            
            //adjusting minimum entries before output
            if (NumPianos < 0) //need to adjust negative pianos into 0s before output
            {
                NumPianos = 0;
            }
            
            if(DrivingDistance < MIN_DRIVING_DISTANCE) //need to adjust milage less than 1 to 1 before output
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
            cout << setw(4) << " " << ESTyear << slash << setfill('0') << setw(2) << ESTmonth << slash << setw(2) << ESTday;
            cout << setfill(' ') << setw(10) << Moveyear << slash << setfill('0') << setw(2) << Movemonth << slash << setw(2) << Moveday;
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
                
                //cout << "Set of stairs: " << SetofStairs << endl;
                
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
                    TotalCost = (B_PACK_LOAD*TotalWeightLBS) + (B_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge + PianoSurcharge;
                    B_pack_count++;
                    B_pack_distance = B_pack_distance + DrivingDistance;
                    B_pack_weight = B_pack_weight + TotalWeightLBS;
                    B_pack_totalcost = B_pack_totalcost + TotalCost;
                }
                
                if (MoveType == 'C' ||MoveType == 'c')
                {
                    TotalCost = (C_PACK_LOAD*TotalWeightLBS) + (C_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge + PianoSurcharge;
                    C_pack_count++;
                    C_pack_distance = C_pack_distance + DrivingDistance;
                    C_pack_weight = C_pack_weight + TotalWeightLBS;
                    C_pack_totalcost = C_pack_totalcost + TotalCost;
                }
                
                if (MoveType == 'W'||MoveType == 'w')
                {
                    TotalCost = (W_PACK_LOAD*TotalWeightLBS) + (W_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge + PianoSurcharge;
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
            }
            
        }//END while loop for reading lines and outputting data
               
        cout << endl;
        cout << "Total Records: " << TotalRecords << "  ";
        cout << "Total Records With Errors: " << TotalRecordsWithError << "  ";
        cout << "Total Records Without Errors: "<< TotalRecordsWithoutError << "  ";
        cout << "Total Sales: $" << totalAmount << endl << endl;
        
        //outputting summary statistics
        cout << setw(50) << "TOTALS: Records Without Errors" << endl << endl;
        cout << setw(10) << left << "Type" << setw(10) << "Count" << setw(10) <<
        "Distance" << setw(10) << "Weight" << setw(10) << "Cost" << endl;
        cout << "-----------------------------------------------------------------------"<< endl;
        cout << setw(10) << left << "Basic" << setw(10) << B_pack_count << setw(10) <<
        B_pack_distance << setw(10) << B_pack_weight << setw(2) << "$" << setw(10) << B_pack_totalcost << endl;
        cout << setw(10) << left << "Wall Pack" << setw(10) << W_pack_count << setw(10) <<
        W_pack_distance << setw(10) << W_pack_weight << setw(2) << "$" << setw(10) << W_pack_totalcost << endl;
        cout << setw(10) << left << "Complete" << setw(10) << C_pack_count << setw(10) <<
        C_pack_distance << setw(10) << C_pack_weight << setw(2) << "$" << setw(10) << C_pack_totalcost << endl << endl;
        
        cout << "Thank you for using the BHMSI move cost calculator (Menu Driven Version)." << endl;
        
        
        
       
        
        
        
        
        
        
        
        
        inFile.close();
    } //END else block paired with if !inFile
    
    
    return 0;

    } //END main function
