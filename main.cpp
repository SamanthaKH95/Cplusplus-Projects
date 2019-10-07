//
//  main.cpp
//  SKH50P4
//
//  Created by Samantha Ho on 3/25/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * main.cpp
 *
 * COSC 051 Spring 2019
 * Project #4
 *
 * Due on: April 9, 2019
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

#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;

//this is main 2nd ver
// local file path on my computer /Users/sam/Downloads/P3West.dat
// local file path on my computer /Users/sam/Downloads/P3South.dat
// local file path on my computer /Users/sam/Downloads/P3North.dat
// local file path on my computer /Users/sam/Downloads/P3East.dat
// local file path on my computer /Users/sam/Downloads/P3Other.dat
// local file path on my computer /Users/sam/Downloads/P3All.dat

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
const int MIN_PIANOS = 0;
const double STAIRS_SURCHARGE_RATE = 132;
const int NO_STAIRS_PIANO_SURCHARGE = 275;
const int ONE_STAIRS_PIANO_SURCHARGE = 575;
const int TWO_STAIRS_PIANO_SURCHARGE = 1075;



const string PROMPT_FILE = "Please enter the file path and name: ";
const string ERROR_FILE_OPEN = "ERROR: File open error, please check path and name of: ";
const string SUCCESS_FILE_OPEN = "File opened successfully for input: ";


/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 class MoveOrder declaration                     **
 **                                                                 **
 **            This code is provided to students                    **
 **            in COSC 051 Spring 2019 to use in                    **
 **            part or in total for class projects.                 **
 **            Students may use this code as their                  **
 **            own, without any attribution.                        **
 **                                                                 **
 *********************************************************************
 *********************************************************************/

class MoveOrder
{
    //overloaded stream insertion operator, friend of the class
    friend ostream& operator<<( ostream &os, const MoveOrder &rhsObj );
    
    //overloaded stream extraction operator, friend of the class
    friend istream& operator>>( istream &is, MoveOrder &rhsObj );
    
private:
    //the data members below are required (you may change identifiers)
    //there is no need for additional data members
    int estimateYear;     /*!< the year the estimate was prepared */
    int estimateMonth;    /*!< the month the estimate was prepared */
    int estimateDay;      /*!< the day the estimate was prepared */
    int moveYear;         /*!< the year the move is scheduled to occur */
    int moveMonth;        /*!< the month the move is scheduled to occur */
    int moveDay;          /*!< the day the move is scheduled to occur */
    char type;            /*!< the move type */
    int givenDistance;    /*!< the distance value that was in the data file */
    int distance;         /*!< the distance value to use, may have been adjusted from given value*/
    int weight;           /*!< the weight of contents to move */
    int givenPianos;      /*!< the pianos value that was in the data file */
    int pianos;           /*!< the pianos value to use, may have been adjusted from given value */
    char stairsOrigin;         /*!< are there > 15 stairs at the origin? */
    char stairsDestination;    /*!< are there > 15 stairs at the destination? */
    string estimateNumber;     /*!< the estimate number */
    string region;             /*!< the region of the move origin */
    string customerNameEmail;  /*!< the customer's name and email address */
    
public:
    //required constructors
    //you may change parameter identifiers, but the order and types of the parameters
    //must be the same as shown in the prototypes
    
    //default constructor
    MoveOrder();
    
    //constructor with parameters
    MoveOrder(int eYYYY, int eMM, int eDD, int mYYYY, int mMM, int mDD,
              char typ, int dst, int wgt, int pno, char sO, char sD,
              string eNum, string reg, string nameEmail);
    
    //copy constructor
    MoveOrder( const MoveOrder &otherObj );
    
    //overloaded assignment operator
    MoveOrder& operator=( const MoveOrder &otherObj );
    
    //required basic mutator functions, in-line implementation is OK for most
    //you may change parameter identifiers but NOT the function identifiers
    void setEstimateYear( int value ) { estimateYear = value; }
    void setEstimateMonth( int value ) { estimateMonth = value; }
    void setEstimateDay( int value ) { estimateDay = value; }
    void setMoveYear( int value ) { moveYear = value; }
    void setMoveMonth( int value ) { moveMonth = value; }
    void setMoveDay( int value ) { moveDay = value; }
    void setType( char value ) { type = value; }
    
    void setDistance( int value ); // given value may be adjusted, may NOT implement in-line
    
    void setWeight( int value ) { weight = value; }
    
    void setPianos( int value );  // given value may be adjusted, may NOT implement in-line
    
    void setStairsOrigin( char value ) { stairsOrigin = value; }
    void setStairsDestination( char value ) { stairsDestination = value; }
    void setEstimateNumber( string value ) { estimateNumber = value; }
    void setRegion( string value ) { region = value; }
    void setCustomerNameEmail( string value ) { customerNameEmail = value; }
    
    //required basic accessor functions, in-line implementation
    //you may change parameter identifiers but NOT the function identifiers
    int getEstimateYear() const { return estimateYear; }
    int getEstimateMonth() const { return estimateMonth; }
    int getEstimateDay() const { return estimateDay; }
    int getMoveYear() const { return moveYear; }
    int getMoveMonth() const { return moveMonth; }
    int getMoveDay() const { return moveDay; }
    char getType() const { return type; }
    int getGivenDistance() const { return givenDistance; }
    int getDistance() const { return distance; }
    int getWeight() const { return weight; }
    int getGivenPianos() const { return givenPianos; }
    int getPianos() const { return pianos; }
    char getStairsOrigin() const { return stairsOrigin; }
    char getStairsDestination() const { return stairsDestination; }
    string getEstimateNumber() const { return estimateNumber; }
    string getRegion() const { return region; }
    string getCustomerNameEmail() const { return customerNameEmail; }
    
    
    //required accessor functions that perform more detailed calculations
    //you may change parameter identifiers but NOT the function identifiers
    
    //these functions perform validation of the object's data values
    //same validation rules as project 1, project 2, and project 3
    //answer is set to true if validation test passes, false otherwise
    //message is set to the error message for that test
    void validDates( bool &answer, string &message, bool &tooSoon, bool &tooLate ) const;
    void validType( bool &answer, string &message ) const;
    void validDistance( bool &answer, string &message ) const;
    void validWeight( bool &answer, string &message ) const;
    void validPianoCount( bool &answer, string &message ) const;
    void validStairsOrigin( bool &answer, string &message ) const;
    void validStairsDestination( bool &answer, string &message ) const;
    
    //this function calls each of the other validation methods to
    //determine an overall validity check for this object
    //NOTE: the complete code for this method is given
    void validEstimate( bool &, string &, int & ) const;
    
    //this function outputs values and error messages (if applicable) for this object
    //NOTE: the complete code for this method is given
    void printWithMessages( ostream &os = cout ) const;
    
    //this function returns the calculated cost of this move object according to the
    //same calculation rules as project 1, project 2, and project 3
    double getTotalCost() const;
    
    
    //OPTIONAL
    //if you add any methods they should should go here
    //you may not add any member functions that supercede the required member functions
    //or the stand-alone functions, anything you add should enhance your solution
    
    //this function returns the full name of the move type:
    //     "Basic     " for b or B
    //     "Wall Pack " for w or W
    //     "Complete  " for c or C
    string getTypeName() const;
    
}; //END declaration class MoveOrder

/****************************************************************************
 ****************************************************************************
 **                                   Regular                              **
 **                          function prototypes                           **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
char displayMenu();
void loadFile(string fName, bool &loadSuccess, vector<MoveOrder> &vM);
void allDetails(const vector<MoveOrder> &vM);
void estimateDetails(const vector<MoveOrder> &vM);
void summaryByType(const vector<MoveOrder> &vM);
void summaryByRegion(const vector<MoveOrder> &vM);
void clearData (vector<MoveOrder> &vM);


/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Overloaded Stream Insertion                     **
 **                         Operator                                **
 *********************************************************************
 *********************************************************************/
ostream& operator<<( ostream &os, const MoveOrder &rhsObj )
{
    //have to overload because cin and cout are members of istream and ostream classes
    //it will not compile unless operator was overloaded to become a member of the left
    //hand side object class. Also this solves member assignment and memory issues
    
    char slash = '/';
    bool answer = true;
    string message = " ";
    int errors = 0; //accumulator
    //take formatting from other project
    //outputting the headings
    
    cout << setfill(' ');
    cout << setw(4) << " " << rhsObj.estimateYear << slash << setfill('0') << setw(2)
    << rhsObj.estimateMonth<< slash << setw(2) << rhsObj.estimateDay;
    cout << setfill(' ') << setw(10) << rhsObj.moveYear << slash << setfill('0') << setw(2)
    << rhsObj.moveMonth << slash << setw(2) << rhsObj.moveDay;
    cout << setfill(' ') << setw(9) << rhsObj.type;
    cout << setw(11) << rhsObj.distance;
    cout << setw(10) << rhsObj.weight;
    cout << setw(7) << rhsObj.pianos;
    cout << setw(8) << rhsObj.stairsOrigin;
    cout << setw(5) << rhsObj.stairsDestination;
    cout << setw(12) << rhsObj.getEstimateNumber();
    cout << setw(11) << rhsObj.getTotalCost();
    
    rhsObj.validEstimate(answer, message, errors);
    if (answer==false)
    {
        cout << "       E";
    }
    
    return os;
}

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Overloaded Stream Extraction                    **
 **                         Operator                                **
 *********************************************************************
 *********************************************************************/
istream& operator>>( istream &is, MoveOrder &rhsObj )
{

    
    //temp variables
    string State;
    string Region;
    string UniqueID;    //string with no spaces
    string NameAndEmail; //with space
    int DrivingDistance;
    int TotalWeightLBS;
    int NumPianos;
    char MoveType;
    char MoreThan15StairsOrigin;
    char MoreThan15StairsDest;
    int ESTyear = 0, ESTmonth= 0, ESTday= 0; //to store estimate date components
    int Moveyear = 0, Movemonth= 0, Moveday= 0; //to store estimate date components
    char slash = '?'; //to store slash in between date components
    
    is >> UniqueID >> ESTyear >> slash >> ESTmonth >> slash >> ESTday >>
    Moveyear >> slash >> Movemonth >> slash >> Moveday >> MoveType >>
    DrivingDistance >> TotalWeightLBS >> NumPianos >> MoreThan15StairsOrigin >>
    MoreThan15StairsDest >> State >> Region;
    getline(is, NameAndEmail);
    
    
    rhsObj.setEstimateYear(ESTyear);
    rhsObj.setEstimateMonth(ESTmonth);
    rhsObj.setEstimateDay(ESTday);
    rhsObj.setMoveYear(Moveyear);
    rhsObj.setMoveMonth(Movemonth);
    rhsObj.setMoveDay(Moveday);
    rhsObj.setType(MoveType);
    rhsObj.setDistance(DrivingDistance);
    rhsObj.setWeight(TotalWeightLBS);
    rhsObj.setPianos(NumPianos);
    rhsObj.setStairsOrigin(MoreThan15StairsOrigin);
    rhsObj.setStairsDestination(MoreThan15StairsDest);
    rhsObj.setEstimateNumber(UniqueID);
    rhsObj.setRegion(Region);
    rhsObj.setCustomerNameEmail(NameAndEmail);
 
    return is;
}


/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Default Constructor                             **
 *********************************************************************
 *********************************************************************/
MoveOrder::MoveOrder()
{
    //assigns all data members default values
    estimateYear = 2018;
    estimateMonth = 1;
    estimateDay = 1;
    moveYear = 2018;
    moveMonth = 1;
    moveDay = 1;
    type = 'C';
    distance = 0;
    weight = 0;
    pianos = 0;
    stairsOrigin = 'n';
    stairsDestination = 'n';
    estimateNumber = ' ';
    region = "Other";
    customerNameEmail = ' ';
}

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Constructor With Parameters                     **
 *********************************************************************
 *********************************************************************/
MoveOrder::MoveOrder(int eYYYY, int eMM, int eDD, int mYYYY, int mMM, int mDD,
                     char typ, int dst, int wgt, int pno, char sO, char sD,
                     string eNum, string reg, string nameEmail)
{
    //Sets all data members to values passed in to its parameters, the code in
    //this constructor shall call CLASS SETTER METHODS to make the actual
    //value initilization for each data member.
    
    setEstimateYear(eYYYY);
    setEstimateMonth(eMM);
    setEstimateDay(eDD);
    setMoveYear(mYYYY);
    setMoveMonth(mMM);
    setMoveDay(mDD);
    setType(typ);
    setDistance(dst);
    setWeight(wgt);
    setPianos(pno);
    setStairsOrigin(sO);
    setStairsDestination(sD);
    setEstimateNumber(eNum);
    setRegion(reg);
    setCustomerNameEmail(nameEmail);

}


/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Copy Constructor                                **
 *********************************************************************
 *********************************************************************/
MoveOrder::MoveOrder(const MoveOrder &otherObj)
{
    //called when a new object is created and initialized with the data
    //of another object of the same class
    
    this->setEstimateYear(otherObj.estimateYear);
    this->setEstimateMonth(otherObj.estimateMonth);
    this->setEstimateDay(otherObj.estimateDay);
    this->setMoveYear(otherObj.moveYear);
    this->setMoveMonth(otherObj.moveMonth);
    this->setMoveDay(otherObj.moveDay);
    this->setType(otherObj.type);
    this->setDistance(otherObj.distance);
    this->setWeight(otherObj.weight);
    this->setPianos(otherObj.pianos);
    this->setStairsOrigin(otherObj.stairsOrigin);
    this->setStairsDestination(otherObj.stairsDestination);
    this->setEstimateNumber(otherObj.estimateNumber);
    this->setRegion(otherObj.region);
    this->setCustomerNameEmail(otherObj.customerNameEmail);
    
}


/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Overloaded Assignment                           **
 **                       Operator                                  **
 *********************************************************************
 *********************************************************************/
MoveOrder& MoveOrder::operator=(const MoveOrder &otherObj)
{
    /*Sets all data members to the same values of an existing MoveOrder object.
     
     The overloaded assignment operator returns a reference to the left hand side operand
     (the object being copied to). Before making any changes to the object being copied
     to the overloade assignment operator must first test to ensure it is not an attempt
     at self-assignment. If it is self-assignment,
     then nothing should happen except for the return.
     
     If it is NOT self-assignment, then code in this constructor shall call class setter methods
     to make the actual value update for each data member.*/
    
    //checking for self assignment
    if (this != &otherObj)
    {

        
        //using setter methods
         setEstimateYear(otherObj.estimateYear);
         setEstimateMonth(otherObj.estimateMonth);
         setEstimateDay(otherObj.estimateDay);
         setMoveYear(otherObj.moveYear);
         setMoveMonth(otherObj.moveMonth);
         setMoveDay(otherObj.moveDay);
         setType(otherObj.type);
         setDistance(otherObj.distance);
         setWeight(otherObj.weight);
         setPianos(otherObj.pianos);
         setStairsOrigin(otherObj.stairsOrigin);
         setStairsDestination(otherObj.stairsDestination);
         setEstimateNumber(otherObj.estimateNumber);
         setRegion(otherObj.region);
         setCustomerNameEmail(otherObj.customerNameEmail);
         return *this;
    }
    else
    {
        return *this;
    }

}

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 SetDistance                                     **
 *********************************************************************
 *********************************************************************/

void MoveOrder::setDistance( int value )
{
    /*The givenDistance data member is set to the value parameter. The distance data member is set
     to the value parameter if it is at least 1 (the minimum distance). If the value parameter is
     less than 1, then the distance data member is set to 1. This adjustment is made silently
     meaning that there is no error message or other notification.*/

    if (value >= MIN_DRIVING_DISTANCE) //min driving distance = 1
    {
        givenDistance = value;
        distance = value;
    }
    else if (value < MIN_DRIVING_DISTANCE)
    {
        givenDistance = value;
        distance = MIN_DRIVING_DISTANCE;
    }
    
    
}

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 SetPiano                                        **
 *********************************************************************
 *********************************************************************/

void MoveOrder::setPianos(int value)
{
    /*The givenPianos data member is set to the value parameter. The pianos data member is set
    to the value parameter if it is at least zero. If the value parameter is less than zero,
     then the pianos data member is set to zero. This adjustment is made silently meaning that
     there is no error message or other notification.*/
    
    if (value >= MIN_PIANOS) //min pianos = 0
    {
        givenPianos = value;
        pianos = value;
    }
    else if (value < MIN_PIANOS)
    {
        givenPianos = value;
        pianos = MIN_PIANOS;
    }
}

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **these functions perform validation of the object's data values   **
 **same validation rules as project 1, project 2, and project 3     **
 **answer is set to true if validation test passes, false otherwise **
 **message is set to the error message for that test                **
 *********************************************************************
 *********************************************************************/


void MoveOrder::validDates( bool &answer, string &message, bool &tooSoon, bool &tooLate ) const
{
    int tempmovemonth = moveMonth; //dummy variable since function is const
    
    if (tempmovemonth < estimateMonth)
        tempmovemonth += 12;
    
    if (tempmovemonth-estimateMonth < 2)
    {
        tooSoon = true;
        answer = false;
        tooLate = false;
        message = "\nERROR: The move date is too soon after the estimate date.";
    }
    if (tempmovemonth-estimateMonth > 6)
    {
        tooLate = true;
        tooSoon = false;
        answer= false;
        message = "\nERROR: The move date is too long after the estimate date.";

    }
}
void MoveOrder::validType( bool &answer, string &message ) const
{
    if (type != 'B' && type != 'b' && type != 'W' && type != 'w' &&
        type != 'C' && type != 'c')
    {
        message = "\nERROR: Move type invalid";
        answer = false;
    }
}
void MoveOrder::validDistance( bool &answer, string &message ) const
{
    if (distance > MAX_DRIVING_DISTANCE)
    {
        message = "\nERROR: Distance exceeded max distance of 3200";
        answer = false;
    }
}
void MoveOrder::validWeight( bool &answer, string &message ) const
{
    int DoubleDistance;
    int MinWeight;
    //computing min weight value
    DoubleDistance = 2 * distance;
    if (DoubleDistance < WEIGHT_LOWER_BOUND)
    {
        MinWeight = WEIGHT_LOWER_BOUND;
    }
    else
    {
        MinWeight = DoubleDistance;
    }
    if(weight < MinWeight)
    {
        message = "\nERROR: Weight entered less than minimum allowed";
        answer = false;
 
    }
    if (weight > WEIGHT_UPPER_BOUND)
    {
        message = "\nERROR: Weight entered exceeds max of 18000";
        answer = false;
     
    }
}
void MoveOrder::validPianoCount( bool &answer, string &message ) const
{
    if (pianos > MAX_PIANOS)
    {
        message = "\nERROR: Maximum number of pianos exceeded.";
        answer = false;
    }
}
void MoveOrder::validStairsOrigin( bool &answer, string &message ) const
{
    if (stairsOrigin != 'y' && stairsOrigin != 'Y' &&
        stairsOrigin != 'n' && stairsOrigin != 'N')
    {
        message = "\nERROR: answer of stairs at origin invalid";
        answer= false;
    }
    
}
void MoveOrder::validStairsDestination( bool &answer, string &message ) const
{
    if (stairsDestination != 'y' && stairsDestination != 'Y' &&
        stairsDestination != 'n' && stairsDestination != 'N')
    {
        message = "\nERROR: answer of stairs at destination invalid";
        answer =false;
    }
    
}


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +                                                                          +
 +                  MoveOrder class validEstimate method                    +
 +                                                                          +
 +                                                                          +
 +                 This code is provided to students                        +
 +                 in COSC 051 Spring 2019 to use in                        +
 +                 part or in total for class projects.                     +
 +                 Students may use this code as their                      +
 +                 own, without any attribution.                            +
 +                                                                          +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

//this function calls each of the other validation methods to
//determine an overall validity check for this object
//NOTE: the complete code for this method is given

void MoveOrder::validEstimate( bool &answer, string &message, int &errorCount ) const
{
    // an estimate is valid overall if ALL of the individual validation tests pass
    
    // assume estimate is valied prior to testing
    errorCount = 0;
    
    // define variables to store error messages from the individual validation tests
    string messageDates = "";
    string messageType = "";
    string messageDistance = "";
    string messageWeight = "";
    string messagePiano = "";
    string messageStairsO = "";
    string messageStairsD = "";
    
    string overallMessage = "";  // store messages from all individual tests
    bool testGood = true;        // reuse this for each individual test function call
    bool overallGood = true;     // this is overall record validity
    bool moveTooSoon = false;    // true if there is not enough time between the estimate/move
    bool moveTooLate = false;    // true if there is too much enough time between the estimate/move
    
    // combine results from the individual validation test methods
    //     - call each individual validation test
    //     - update variable to keep count of errors found
    //     - update overallGood boolean
    //     - update overallMessage string
    
    validDates( testGood, messageDates, moveTooSoon, moveTooLate );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageDates;
    
    validType( testGood, messageType );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageType;
    
    validDistance( testGood, messageDistance );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageDistance;
    
    validWeight( testGood, messageWeight );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageWeight;
    
    validPianoCount( testGood, messagePiano );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messagePiano;
    
    validStairsOrigin( testGood, messageStairsO );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageStairsO;
    
    validStairsDestination( testGood, messageStairsD );
    if (!testGood)
        errorCount++;
    overallGood = overallGood && testGood;
    overallMessage += messageStairsD;
    
    if (errorCount > 0)
    {
        overallMessage += "\tContact customer to resolve issues: ";
        overallMessage += customerNameEmail;
        overallMessage += "\n";
    }
    
    // update the parameters with final values that will be returned
    answer = overallGood;
    message = overallMessage;
    
} // END validEstimate method for MoveOrder class



/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +                                                                          +
 +                MoveOrder class printWithMessages method                  +
 +                                                                          +
 +                                                                          +
 +                 This code is provided to students                        +
 +                 in COSC 051 Spring 2019 to use in                        +
 +                 part or in total for class projects.                     +
 +                 Students may use this code as their                      +
 +                 own, without any attribution.                            +
 +                                                                          +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */


//this function outputs values and error messages (if applicable) for this object
//NOTE: the complete code for this method is given

void MoveOrder::printWithMessages( ostream &os ) const
{
    // local variables that are necessary to call the validEstimate method
    string errMsgs = "";
    bool allOK = true;
    int totalErrors = 0;
    
    // call the validEstimate member function
    // this will store any error messages in the
    // local variable errMsgs, it will also store
    // zero (false) in the local variable allOK if
    // the object has any errors (fails any of the
    // various validation tests)
    validEstimate(allOK, errMsgs, totalErrors);
    
    // send the object to the stream defined in the parameter list
    os << *this;
    
    // if any validation tests failed, then also print out
    // the error messages
    if (!allOK)
    {
        os << endl;
        os << errMsgs;
    }
    
    os << endl;
    
} // END printWithMessages method for MoveOrder class

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Total Cost                                      **
 *********************************************************************
 *********************************************************************/

double MoveOrder::getTotalCost() const
{

        double TotalCost = 0;
        double PianoSurcharge = 0;
        double StairsSurcharge = 0;
        int SetofStairs = 0;
    
        // calculating total cost
        //calculating total number of stairs exceeding 15 steps
        if (stairsOrigin == 'Y' || stairsOrigin == 'y')
        {
            SetofStairs++;
        }
        if (stairsDestination == 'Y' || stairsDestination == 'y')
        {
            SetofStairs++;
        }
        
        
        StairsSurcharge = STAIRS_SURCHARGE_RATE * SetofStairs;
        
        //figuring out piano surcharge based on sets of stairs
        if (SetofStairs == 0)
        {
            PianoSurcharge = pianos * NO_STAIRS_PIANO_SURCHARGE;
        }
        if (SetofStairs == 1)
        {
            PianoSurcharge = pianos * ONE_STAIRS_PIANO_SURCHARGE;
        }
        if (SetofStairs == 2)
        {
            PianoSurcharge = pianos * TWO_STAIRS_PIANO_SURCHARGE;
        }
        
        //final calculations of cost depending on move type
        if (type == 'B' || type == 'b')
        {
            TotalCost = (B_PACK_LOAD*weight) +
            (B_PER_LB_MILE*weight*distance) + StairsSurcharge +
            PianoSurcharge;
     
        }
        
        if (type == 'C' ||type == 'c')
        {
            TotalCost = (C_PACK_LOAD*weight) +
            (C_PER_LB_MILE*weight*distance) + StairsSurcharge +
            PianoSurcharge;

        }
        
        if (type == 'W'||type == 'w')
        {
            TotalCost = (W_PACK_LOAD*weight) +
            (W_PER_LB_MILE*weight*distance) + StairsSurcharge +
            PianoSurcharge;

        }
    return TotalCost;
}

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 GetType                                         **
 *********************************************************************
 *********************************************************************/

string MoveOrder::getTypeName() const
{
    string name = "invalid";
    
    if (type == 'B' || type == 'b')
    {
        name = "Basic";
        
    }
    
    if (type == 'C' ||type == 'c')
    {
        name = "Complete";
        
    }
    
    if (type == 'W'||type == 'w')
    {
        name = "Wall Pack";
    }
    
    return name;
}

/*********************************************************************
 *********************************************************************
 **                 Regular                                         **
 **                 Functions                                       **
 *********************************************************************
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
 **               this function loads the data                             **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
void loadFile(string fName, bool &loadSuccess, vector<MoveOrder> &vM)
{
    //initializing variables
    string State;
    string Region;
    string UniqueID;    //string with no spaces
    string NameAndEmail; //with space
    string fileName = "";
    ifstream inFile;
    string headings = "";
    string oneRow = "";
    
    
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
    
    else //processes data
    {
        
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
        cout << "-----------------------------------";
        cout << "----------------------------" << endl;
        
        
        bool answer = true;
        string message = " ";
        int errors = 0; //accumulator
        double totalsales = 0.0;
        int alterrors = 0;
        
        MoveOrder mO;
        unsigned int initialmOsize = vM.size();
        //reading all the data in
        while(inFile >> mO)
        {
            vM.push_back(mO);
            mO.printWithMessages(cout);
            mO.validEstimate(answer, message, errors);
            if (answer == false)
            {
                alterrors++;
            }
            totalsales += mO.getTotalCost();
            
        }//END while loop for reading lines and outputting data
        
        if (vM.size() > initialmOsize)
        {
            loadSuccess = true;
        }
        else
        {
            loadSuccess = false;
        }
        
        
        cout << endl;
        cout << "Total Records: " << vM.size() << "  ";
        cout << "Total Records With Errors: " << alterrors << "  ";
        cout << "Total Records Without Errors: "<< vM.size() - alterrors << "  ";
        cout << "Total Sales: $" << setprecision(2) << fixed << showpoint << totalsales  <<
        endl << endl;
        
        summaryByType(vM); //will print out summary by type
        cout << "Thank you for using the BHMSI move cost calculator (Object Oriented Version)."
        << endl;
        
        
    } // end ELSE and data processing
    
    return; //END return to main for menu to display again
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function allDetails                           **
 **               this function displays a listing of file data            **
 **                 and calculated data!!                                  **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
void allDetails(const vector<MoveOrder> &vM)
{

    //outputting the headings
    cout << setw(12) << "Move" << setw(15) << "Dist." << setw(13) <<
    "Weight"<<setw(10) << "Number" << setw(10) <<
    "Stairs" << setw(15)<<"Move"<<setw(15) << "Total" << endl;
    
    cout << setw(12) << "Type" << setw(15) << "(Miles)" << setw(13) <<
    "(Pounds)"<<setw(10) << "Pianos" << setw(5) << "O" << setw(5) <<
    "D" << setw(15)<<"Number"<< setw(15) << "Cost ($)" << endl;
    
    cout << "----------------------------------------------------------";
    cout << "-----------------------------------";
    cout << "-------------------------" << endl;
    
    //initializing a count variable
    int count = 0;
    int totalRecords = 0;
    double total_cost = 0;
    
    
    //for loop to print out everything stored in the object vectors
    {
        for (count = 0; count < vM.size(); count++)
        {
            bool answer = true;
            string message = "";
            int errors =0;
            vM[count].validEstimate(answer, message, errors);
            if (answer == true)
            {
                cout << left;
                cout << setw(12) << vM[count].getType();
                
                cout << setw(15) << vM[count].getDistance();
                cout << setw(13) << vM[count].getWeight();
                cout << setw(10) << vM[count].getPianos();
                cout << setw(5) << vM[count].getStairsOrigin();
                cout << setw(5) << vM[count].getStairsDestination();
                cout << setw(15) << vM[count].getEstimateNumber();
                cout << right << setw(10) << vM[count].getTotalCost();
                cout << endl;
                totalRecords++;
                total_cost = total_cost + vM[count].getTotalCost();
            }

        }
        
    }
    
    cout << endl;
    cout << totalRecords << " total records." << endl;
    cout << total_cost << " total of all move charges" << endl;
    double averageMoveCharges = total_cost/ totalRecords;
    cout << averageMoveCharges << " average of all move charges" << endl;
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                          function estimateDetails                      **
 **               this function displays a listing of file data            **
 **                 and calculated data, same as allDetails                **
 **                  but prompts user for estimate number                  **
 ****************************************************************************
 ****************************************************************************/
void estimateDetails(const vector<MoveOrder> &vM)
{
    string estimateNumber;
    int count = 0;
    int position = 0;
    bool truth = false;
    cout << "Enter the estimate number to display: " << endl;
    cin >> estimateNumber;
    
    
    //for loop to find the subscript of the corresponding estimate number
    for (count = 0; count < vM.size(); count++)
    {
        if (vM[count].getEstimateNumber() == estimateNumber)
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
    cout << "----------------------------";
    cout << "----------------------------" << endl;
    
    cout << setw(12) << vM[position].getType();
    cout << setw(15) << vM[position].getDistance();
    cout << setw(13) << vM[position].getWeight();
    cout << setw(10) << vM[position].getPianos();
    cout << setw(5) << vM[position].getStairsOrigin();
    cout << setw(5) << vM[position].getStairsDestination();
    cout << setw(15) << vM[position].getEstimateNumber();
    cout << setw(10) << vM[position].getTotalCost();
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
void summaryByType(const vector<MoveOrder> &vM)
{
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
    
    
    
    for (count = 0; count < vM.size(); count++)
    {
        
        bool answer = true;
        string message = "";
        int errors = 0;
        vM[count].validEstimate(answer, message, errors);
        
        if (answer == true)
        {
            total_records++;
            total_distance = total_distance + vM[count].getDistance();
            total_weight = total_weight + vM[count].getWeight();
            total_cost = total_cost + vM[count].getTotalCost();
            
            if (vM[count].getType() == 'B' || vM[count].getType() == 'b')
            {
                
                total_B_count++;
                total_B_distance += vM[count].getDistance();
                total_B_weight += vM[count].getWeight();
                total_B_cost += vM[count].getTotalCost();
            }
            
            if (vM[count].getType() == 'W' || vM[count].getType() == 'w')
            {
                
                total_W_count++;
                total_W_distance += vM[count].getDistance();
                total_W_weight += vM[count].getWeight();
                total_W_cost += vM[count].getTotalCost();
            }
            
            if (vM[count].getType() == 'C' || vM[count].getType() == 'c')
            {
                total_C_count++;
                total_C_distance += vM[count].getDistance();
                total_C_weight += vM[count].getWeight();
                total_C_cost += vM[count].getTotalCost();
                
            } //END of if statements
        }
        
        
    }//END of for loop
    
    cout << setw(25) << right << "TOTALS ( Correct " << total_records << " records )" << endl;
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
void summaryByRegion(const vector<MoveOrder> &vM)
{
    int errors = 0;
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
    
    for (count = 0; count < vM.size(); count++)
    {
        bool answer = true;
        string message = "";
        
        total_records++;
        
        vM[count].validEstimate(answer, message, errors);
        if (answer == true)
        {
            if (vM[count].getRegion() == "South")
            {
                
                total_distance = total_distance + vM[count].getDistance();
                total_weight = total_weight + vM[count].getWeight();
                total_cost = total_cost + vM[count].getTotalCost();
                
                total_South_count++;
                total_South_distance += vM[count].getDistance();
                total_South_weight += vM[count].getWeight();
                total_South_cost += vM[count].getTotalCost();
            }
            
            if (vM[count].getRegion() == "West")
            {
                
                total_distance = total_distance + vM[count].getDistance();
                total_weight = total_weight + vM[count].getWeight();
                total_cost = total_cost + vM[count].getTotalCost();
                
                total_West_count++;
                total_West_distance += vM[count].getDistance();
                total_West_weight += vM[count].getWeight();
                total_West_cost += vM[count].getTotalCost();
            }
            
            if (vM[count].getRegion() == "North")
            {
                
                total_distance = total_distance + vM[count].getDistance();
                total_weight = total_weight + vM[count].getWeight();
                total_cost = total_cost + vM[count].getTotalCost();
                
                total_North_count++;
                total_North_distance += vM[count].getDistance();
                total_North_weight += vM[count].getWeight();
                total_North_cost += vM[count].getTotalCost();
            }
            
            if (vM[count].getRegion() == "East")
            {
                
                total_distance = total_distance + vM[count].getDistance();
                total_weight = total_weight + vM[count].getWeight();
                total_cost = total_cost + vM[count].getTotalCost();
                
                total_East_count++;
                total_East_distance += vM[count].getDistance();
                total_East_weight += vM[count].getWeight();
                total_East_cost += vM[count].getTotalCost();
            }
            
            if (vM[count].getRegion() == "Other")
            {
                
                total_distance = total_distance + vM[count].getDistance();
                total_weight = total_weight + vM[count].getWeight();
                total_cost = total_cost + vM[count].getTotalCost();
                
                total_Other_count++;
                total_Other_distance += vM[count].getDistance();
                total_Other_weight += vM[count].getWeight();
                total_Other_cost += vM[count].getTotalCost();
            }
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
void clearData (vector<MoveOrder> &vM)
{
    vM.clear();
}

/*********************************************************************
 *********************************************************************
 **                                                                 **
 **                 Main                                            **
 *********************************************************************
 *********************************************************************/

int main()
{
    //initializing variables
    vector<MoveOrder> vM; //initializing the vector to store all the objects
    string FilePathAndName; //string to store file path and name
    char menuInput; //to store user menu input choice
    //initializing variables to send to functions
    bool loadSuccess;
    
    
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
                    loadFile(FilePathAndName, loadSuccess, vM);
                    //testing to see if vector size increased properly, works!!
                    //cout << "The size of the new vector is" << vTyp.size();
                    break;
                case 'A': cout << "The User Asked To Do:" << menuInput << endl;
                    if (loadSuccess == false) //testing for previous load file
                    {
                        cout << "ERROR: need at least one successfully loaded file" << endl;
                        cout << "Please try again" << endl;
                        break;
                    }
                    else
                    {
                        allDetails(vM);
                        break;
                    }
                case 'E': cout << "The User Asked To Do:" << menuInput << endl;
                    if (loadSuccess == false) //testing for previous load file
                    {
                        cout << "ERROR: need at least one successfully loaded file" << endl;
                        cout << "Please try again" << endl;
                        break;
                    }
                    else
                    {
                        estimateDetails(vM);
                        break;
                    }
                case 'T': cout << "The User Asked To Do:" << menuInput << endl;
                    if (loadSuccess == false) //testing for previous load file
                    {
                        cout << "ERROR: need at least one successfully loaded file" << endl;
                        cout << "Please try again" << endl;
                        break;
                    }
                    else
                    {
                        summaryByType(vM);
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
                        summaryByRegion(vM);
                        break;
                    }
                case 'C': cout << "The User Asked To Do:" << menuInput << endl;
                    clearData (vM);
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
