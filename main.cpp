//
//  main.cpp
//  skh50P1
//  program will calculate the cost of a move for Bubba Hotep Moving and Storage, Inc.
//  Created by Samantha Ho on 2/11/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * main.cpp
 *
 * COSC 051 Spring 2019
 * Project #1 (Code)
 *
 * Due on: February 13, 2019
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
using namespace std;

//defining global constants used in cost calculations, cost values stored as floating point w/ double
double B_PACK_LOAD = 0.065;
double B_PER_LB_MILE = 0.0011;
double W_PACK_LOAD = 0.256;
double W_PER_LB_MILE = 0.0011;
double C_PACK_LOAD = 0.459;
double C_PER_LB_MILE = 0.0012;

int main()

{
    
    
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
    double FinalCost;
    
    //welcome message, program starts asking user input and validating input to be within range
    cout << "Hello! Welcome to Bubba Hotep Moving & Storage, Inc.'s Move Calculator. " << endl;
    cout << "This program will help you calculate the cost of a move." << endl;
    
    //inputting move type and validating input, changes input to uppercase for standardization
    //also ignores characters after first letter to clear buffer
    cout << "Please input the move type: 'B' for Basic, 'W' for Wall Pack, and 'C' for complete" << endl;
    cin >> MoveType;
    MoveType = toupper(MoveType);
    cin.ignore(500, '\n');
    if (MoveType != 'B' && MoveType != 'W' && MoveType !='C')
    {//outputting error message
        cout << "Move type invalid, please re-enter move type with 'B', 'C', or 'W'." << endl;
        return main(); //restarts from beginning of main
    }
    
    //inputting and validating driving distance between 1 and 3200, if less than 1 will use 1, if
    //more than 3200 will terminate
    cout << "Please input the number of miles for the move. (If less than 1 will use 1.)" << endl;
    cout << "(If non-integer is inputted, decimal portion of the number will be truncated! Better round up your decimal.) :" << endl;
    cin >> DrivingDistance;
    if (DrivingDistance < 1)
    {
        DrivingDistance = 1;
    }
    if (DrivingDistance > 3200)
    {
        cout << "You've exceeded the upperlimit of 3200 miles - please visit Bertha Bartholomew's Moving and Storage, Inc." << endl;
        cout << "They specialize in larger commercial moves. The program will restart now, please enter new values if needed. Goodbye" << endl;
        return main ();
    }

    //inputting and validating that weight is at least 1200 or double distance of move, whichever is greater
    //If entered value is lower than minimum, program will continue processing using corresponding minimum
    //If more than 18000, program will output error message and terminate
    cout << "Please input the total weight of the items in the move. Must be at least 1200 LBs or double distance of move, whichever is greater." <<endl;
    cout << "If entered value is lower than minimum, program will calculate with required minimum." << endl;
    cout << "If a non-integer, the decimal portion will be truncated: " << endl;
    cin >> TotalWeightLBS;
    DoubleDistance = 2 * DrivingDistance;
    if (DoubleDistance < 1200)
    {
        MinWeight = 1200;
    }
    else
    {
        MinWeight = DoubleDistance;
    }
    
    if (TotalWeightLBS < MinWeight)
    {
        TotalWeightLBS = MinWeight;
    }
    if (TotalWeightLBS > 18000)
    {
        cout << "You have exceeded the maximum weight of 18000 LBs, please visit Bertha Bartholomew's Moving and Storage, Inc." << endl;
        cout << "They specialize in large commercial moves. This program will restart now, goodbye." << endl;
        return main();
        
    }
    
    //inputting and validating number of pianos
    cout << "Please enter the number of pianos. If none, enter 0: " << endl;
    cin >> NumPianos;
    if (NumPianos > 3)
    {
        cout << "You've exceeded the upper limit of pianos, not even Bertha's will move more than 3 pianos for you." << endl;
        cout << "Please try again if you would like to move 3 pianos or less. The program will terminate now, goodbye." << endl;
        return main ();
    }
    if (NumPianos < 0)
    {
        NumPianos = 0; // pianos cannot be negative
    }
    
    
    //validating whether to charge stair surcharge at origin/destination and corresponding surcharge amount
    cout << "Is there at least one set of stairs at origin that exceeds 15 steps? Enter 'Y' for yes and 'N' for no" << endl;
    cin >> MoreThan15StairsOrigin;
    MoreThan15StairsOrigin = toupper (MoreThan15StairsOrigin); //making any input uppercase for ease of validation
    cin.ignore(500, '\n'); //ignoring everything after first char
    if (MoreThan15StairsOrigin == 'Y')
    {
        SetofStairs = SetofStairs + 1;
    }
    cout << "Is there at least one set of stairs at destination that exceeds 15 steps? Enter 'Y' for yes and 'N' for no" << endl;
    cin >> MoreThan15StairsDest;
    MoreThan15StairsDest = toupper (MoreThan15StairsDest); //makes input uppercase for ease of validation
    cin.ignore(500, '\n'); //ignores everything after first char
    if (MoreThan15StairsDest == 'Y')
    {
        SetofStairs = SetofStairs + 1;
    }
    
    StairsSurcharge = 132 * SetofStairs;
    
    //figuring out piano surcharge based on sets of stairs
    if (SetofStairs == 0)
    {
        PianoSurcharge = NumPianos * 275;
    }
    if (SetofStairs == 1)
    {
        PianoSurcharge = NumPianos * 575;
    }
    if (SetofStairs == 2)
    {
        PianoSurcharge = NumPianos * 1075;
    }
    
    //final calculations of cost depending on move type
    if (MoveType == 'B')
    {
        FinalCost = (B_PACK_LOAD*TotalWeightLBS) + (B_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge + PianoSurcharge;
        cout << endl;
        cout << "Your entries for this move are:" << endl;
        cout << setw(7) << "B" << setw(4) << " - " << "Basic Move Type" << endl;
        cout << setw(7) << DrivingDistance << setw(4) << " - " << "miles from origin to destination" << endl;
        cout << setw(7) << TotalWeightLBS << setw(4) << " - " << "total pounds of content to move" << endl;
        cout << setw(7) << NumPianos << setw(4) << " - " << "total number of pianos to move" << endl;
        cout << setw(7) << MoreThan15StairsOrigin << setw(4) << " - " << "are there more than 15 stairs at origin?" << endl;
        cout << setw(7) << MoreThan15StairsDest << setw(4) << " - " << "are there more than 15 stairs at destination?" << endl;
        cout << setw(7) << SetofStairs << setw(4) << " - "<< "location(s) with more than 15 stairs"<< endl;
        cout << endl;
        
        cout << "Your cost for a Basic Move with these values is:" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << (B_PACK_LOAD*TotalWeightLBS) << setw(4) << " - " << "packing cost" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << (B_PER_LB_MILE*TotalWeightLBS*DrivingDistance) << setw(4) << " - " << "moving cost" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << PianoSurcharge << setw(4) << " - " << "piano surcharge" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << StairsSurcharge << setw(4) << " - " << "stairs surcharge" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << FinalCost << setw(4) << " - " << "TOTAL" << endl;
        
    }
    
    if (MoveType == 'C')
    {
        FinalCost = (C_PACK_LOAD*TotalWeightLBS) + (C_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge + PianoSurcharge;
        cout << endl;
        cout << "Your entries for this move are:" << endl;
        cout << setw(7) << "C" << setw(4) << " - " << "Complete Move Type" << endl;
        cout << setw(7) << DrivingDistance << setw(4) << " - " << "miles from origin to destination" << endl;
        cout << setw(7) << TotalWeightLBS << setw(4) << " - " << "total pounds of content to move" << endl;
        cout << setw(7) << NumPianos << setw(4) << " - " << "total number of pianos to move" << endl;
        cout << setw(7) << MoreThan15StairsOrigin << setw(4) << " - " << "are there more than 15 stairs at origin?" << endl;
        cout << setw(7) << MoreThan15StairsDest << setw(4) << " - " << "are there more than 15 stairs at destination?" << endl;
        cout << setw(7) << SetofStairs << setw(4) << " - "<< "location(s) with more than 15 stairs"<< endl;
        cout << endl;
        
        cout << "Your cost for a Complete Move with these values is:" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << (C_PACK_LOAD*TotalWeightLBS) << setw(4) << " - " << "packing cost" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << (C_PER_LB_MILE*TotalWeightLBS*DrivingDistance) << setw(4) << " - " << "moving cost" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << PianoSurcharge << setw(4) << " - " << "piano surcharge" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << StairsSurcharge << setw(4) << " - " << "stairs surcharge" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << FinalCost << setw(4) << " - " << "TOTAL" << endl;
        
    }
    
    if (MoveType == 'W')
    {
        FinalCost = (W_PACK_LOAD*TotalWeightLBS) + (W_PER_LB_MILE*TotalWeightLBS*DrivingDistance) + StairsSurcharge + PianoSurcharge;
        cout << endl;
        
        cout << "Your entries for this move are:" << endl;
        cout << setw(7) << "W" << setw(4) << " - " << "Wall Pack Move Type" << endl;
        cout << setw(7) << DrivingDistance << setw(4) << " - " << "miles from origin to destination" << endl;
        cout << setw(7) << TotalWeightLBS << setw(4) << " - " << "total pounds of content to move" << endl;
        cout << setw(7) << NumPianos << setw(4) << " - " << "total number of pianos to move" << endl;
        cout << setw(7) << MoreThan15StairsOrigin << setw(4) << " - " << "are there more than 15 stairs at origin?" << endl;
        cout << setw(7) << MoreThan15StairsDest << setw(4) << " - " << "are there more than 15 stairs at destination?" << endl;
        cout << setw(7) << SetofStairs << setw(4) << " - "<< "location(s) with more than 15 stairs"<< endl;
        cout << endl;
        
        cout << "Your cost for a Wall Pack Move with these values is:" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << (W_PACK_LOAD*TotalWeightLBS) << setw(4) << " - " << "packing cost" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << (W_PER_LB_MILE*TotalWeightLBS*DrivingDistance) << setw(4) << " - " << "moving cost" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << PianoSurcharge << setw(4) << " - " << "piano surcharge" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << StairsSurcharge << setw(4) << " - " << "stairs surcharge" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "$" << fixed << setw(11) << setprecision(2) << FinalCost << setw(4) << " - " << "TOTAL" << endl;
        
        
    }
    
    //final goodbye message
    cout << "Thank you so much for using the Bubba Hotep Moving and Storage, Inc. Calculator!" << endl; 
    return 0;
}
