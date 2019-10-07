//
//  DateTime.cpp
//  P1
//
//  Created by Samantha Ho on 7/15/19.
//  Copyright © 2019 Samantha Ho. All rights reserved.
//
/*
 * DateTime.cpp
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

#include "DateTime.h"
#include "Exceptions.h"
using namespace std;

using std::cout;
using std::endl;





/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                 class Date implementation code                         **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

std::istream& operator>>(std::istream& in, Date& dt) //extraction to cin things for storage
{
    try
    {
        if (!in)
        {
            throw invalid_argument(failedInitialStream); //output failed initial stream message
            
        }
        
        else
        {
            //assuming input format to be yyyy/mm/dd
            char dash = '?'; //to store dash in between date components
            
            int year;
            int month;
            int day;
            string rest_of_line;
            
            in >> day >> dash >> month >> dash >> year;
            getline(in, rest_of_line); //to read in rest of line but not use
            
            
            if (!in)
            {
                throw runtime_error(REinsertmessage); 
            }
            
            dt.setDate(year, month, day); //setting object date with read in values
        }
    
    }
    catch(invalid_argument &e)
    {
        cout << "caught invalid_argument exception in Date class operator >>\n";
        cout << e.what();
        throw; //throw back in main
    }
    
    catch(runtime_error &e)
    {
        cout << "caught runtime_error exception in Date class operator >>\n";
        cout << e.what();
        //not rethrown 
    }
    
    catch(...)
    {
        cout << "Unknown Exception Caught in Date class >> operator\n";
    }
    
    
    return in;
}
std::ostream& operator<<(std::ostream& out, const Date& dt) //insertion to cout things
{
    char slash = '/';
    out << setw(4) << " " << dt.yyyy << slash << setfill('0') << setw(2)
    << dt.mm << slash << setfill('0') << setw(2) << dt.dd; //padding month and day less than 10
    
    return out;
}

//constructor with parameters, if no parameters then uses default values in the default constructor
Date::Date (int yyyy, int mm, int dd)
{
    setDate(yyyy, mm, dd);
}

//constructor with another date object parameter
Date::Date(const Date& dt)
{
    setDate(dt);
}

//setDate with passed parameters
void Date::setDate(int yyyy, int mm, int dd)
{
    try
    {
        if (yyyy > YEAR_MAX || yyyy < YEAR_MIN)
        {
            this->yyyy = YEAR_DEFAULT;
            throw bad_date_component ("The year value inputs are not within valid range\n");
        }
        
        if (mm > MONTH_MAX || mm < MONTH_MIN)
        {
            this->mm = MONTH_DEFAULT;
            throw bad_date_component ("The month value inputs are not within valid range\n");
        }
        
        if ((mm == FEB_MONTH_INT && dd > MAX_DAY_29) || (mm == FEB_MONTH_INT && dd < DAY_MIN))
        {
            this->dd = DAY_DEFAULT;
            throw bad_date_component("The day value inputs are not within valid range for month\n");
        }
        
        if (((mm == APRIL_MONTH_INT || mm == JUNE_MONTH_INT || mm == SEPT_MONTH_INT ||
              mm == NOV_MONTH_INT) && dd > MAX_DAY_30) ||
            ((mm == APRIL_MONTH_INT || mm == JUNE_MONTH_INT || mm == SEPT_MONTH_INT ||
              mm == NOV_MONTH_INT) && dd < DAY_MIN))
        {
            this->dd = DAY_DEFAULT;
            throw bad_date_component("The day value inputs are not within valid range for month\n");
        }
        
        else if (dd > DAY_MAX || dd < DAY_MIN)
        {
            this->dd = DAY_DEFAULT;
            throw bad_date_component("The day value inputs are not within valid range for month\n");
        }
                 
    }
    catch (bad_date_component &e)
    {
        cout << "bad_date_component invalid argument caught in Date::setDate" << endl;
        cout << e.what();
        throw;
    }
    catch(invalid_argument &e)
    {
        cout << "Invalid Argument Exception caught in Date::setDate\n" << endl;
        cout << e.what();
        throw; //rethrows into invalid arg catch within mine-> rethrown into main load function
        //matching catch block in load function, but because its a while loop nested try block
        //it goes to next iteration, does not stop the enter while loop 
    }
    
    
    this->yyyy = yyyy;
    this->mm = mm;
    this->dd = dd;
    
    
}

//setDate using an object passed by reference
void Date::setDate(const Date& dt)
{
    this->yyyy = dt.yyyy;
    this->mm = dt.mm;
    this->dd = dt.dd;
}

//getter functions
int Date::getYear() const
{
    return yyyy;
}
int Date::getMonth() const
{
    return mm;
}
int Date::getDay() const
{
    return dd;
}

//overloaded relational operators

const Date& Date::operator=(const Date& dt)
{
    //assigning new object to values of existing object
    this->yyyy = dt.yyyy;
    this->mm = dt.mm; 
    this->dd = dt.dd;
    
    return dt; 
}

bool Date::operator ==(const Date& dt) const
{
    bool answer = false;
    if (this->yyyy == dt.yyyy && this->mm == dt.mm && this->dd == dt.dd)
    {
        answer = true;
    }
    return answer;
}
bool Date::operator !=(const Date& dt) const
{
    //the problem happens when one or two are actually equal
    //should be OR statements not AND
    bool answer = false;
    if (this->yyyy != dt.yyyy || this->mm != dt.mm || this->dd != dt.dd)
    {answer = true;}
    return answer;
}
bool Date::operator <=(const Date& dt) const
{
    //problem happens when rhs has either one or two values less than lfs
    bool answer = false;
    if ((this->yyyy < dt.yyyy) ||
        ((this->yyyy == dt.yyyy) && (this->mm <= dt.mm && this->dd <= dt.dd)))
    {answer = true;}
    
    return answer;
}
bool Date::operator <(const Date& dt) const
{
    bool answer = false;
    if ((this->yyyy < dt.yyyy) ||
        ((this->yyyy == dt.yyyy) && (this->mm < dt.mm)) ||
        ((this->yyyy == dt.yyyy) && (this->mm == dt.mm) && (this->dd < dt.dd)))
    {answer = true;}
    return answer;
}
bool Date::operator >=(const Date& dt) const
{
    //problem happens when rhs has either one or two values greather than lfs
    //did not make it >= just because the day and month were less than despite year being >
    //so need to separate the validation of the year to short circuit it
    bool answer = false;
    if ((this->yyyy > dt.yyyy) ||
        ((this->yyyy == dt.yyyy) && (this->mm >= dt.mm && this->dd >= dt.dd)))
    {answer = true;}
    return answer;
}
bool Date::operator >(const Date& dt) const
{
    bool answer = false;
    if ((this->yyyy > dt.yyyy) ||
        ((this->yyyy == dt.yyyy) && (this->mm > dt.mm)) ||
        ((this->yyyy == dt.yyyy) && (this->mm == dt.mm) && (this->dd > dt.dd)))
    {answer = true;}
    return answer;
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Time implementation code                         **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/



/****************************************************************************
 *                    Time class default constructor                        *
 ****************************************************************************/

Time::Time(int hour, int minute)
{
#ifdef DEBUG_DATE
    std::cout << "Entered constructor Time::Time(int, int)" << std::endl;
#endif
    
    // call method setTime where data validation will be accomplished
    
    setTime(hour, minute);
    
#ifdef DEBUG_DATE
    std::cout << "Exiting constructor Time::Time(int, int)" << std::endl;
#endif
    
} //END constructor with parameters for Time class



/****************************************************************************
 *                  Time class member function setTime                      *
 ****************************************************************************/

void Time::setTime(int hour, int minute)
{
    // use string stream to generate message with heterogeneous data types
    // see code in if(badArguments) block
    std::ostringstream errStrm;
    
    // set data members to default values, if values passed
    // in to the parameters pass validation, then the
    // data members will be updated
    hh = MIN_HOUR;
    mm = MIN_MINUTE;
    
    bool badArguments = false;
    
    if ( hour < MIN_HOUR || minute < MIN_MINUTE || hour > MAX_HOUR || minute > MAX_MINUTE )
    {
        // one on more of the values passed in are not valid
        badArguments = true;
    }
    else if ( hour == MAX_HOUR && minute > 0 )
    {
        // if the value passed for hour is 24, then the only valid value for minutes is 0
        badArguments = true;
    }
    
    if (badArguments)
    {
        // one or more parameters are not valid, throw an exception
        // note that we do not need a try block to throw the exception since
        // we do not plan to handle the exception within Time::setTime
        // control will immediately return to the calling function
        
        errStrm << "ERROR: in method Time::setTime( " << hour << ", " << minute << " )\n";
        errStrm << "hour set to MIN_HOUR (" << MIN_HOUR << "), ";
        errStrm << "minute set to MIN_MINUTE (" << MIN_MINUTE << ")\n";
        std::string errTime = errStrm.str();
        
        std::invalid_argument ia1(errTime);
        throw ia1;
    }
    
    // both parameters are valid, update object's data members
    
    hh = hour;
    mm = minute;
    
} //END member function Time::setTime



/****************************************************************************
 *                 Time class stream extraction operator                    *
 ****************************************************************************/

std::istream& operator>>(std::istream &in, Time &t)
{
    // input format is expected to be hh:mm
    // examples:
    // 24:00 or 00:00 or 24:0 or 0:0 for midnight
    // 2:45
    // 02:45
    // 15:30
    // 18:05
    
    char ch;
    int hour = -1;
    int minute = -1;
    
    // if stream is originally in a failed throw an exception
    // this is thrown outside of the try block so it will not be
    // handled locally, but will immediately pass control back
    // to the calling function
    
    std::string errInStream = "ERROR: in Time class overloaded operator>>\n";
    errInStream += "the input stream is in a failed state, no processing can take place...\n";
    if (!in)
    {
        throw std::invalid_argument(errInStream);
    }
    
    try
    {
        bool streamFailed = false;
        
        in >> hour; //extract the hours and store them in local variable
        if (!in) { streamFailed = true; }
        
        in >> ch; //extract and discard the dilimiting character
        if (!in) { streamFailed = true; }
        
        in >> minute; //extract the minutes and store them in local variable
        if (!in) { streamFailed = true; }
        
        // if stream entered a failed state while extracting values
        // throw an exception
        // this is thrown inside of the try block so it will be
        // handled locally
        // in this case, local processing does not rethrow
        
        if(streamFailed)
        {
            std::string errInStream = "WARNING: in Time class overloaded operator>>\n";
            errInStream += "the input stream is in a failed state, ";
            errInStream += "possible attempt to read past end of file, ";
            errInStream += "time object data members not updated ...\n";
            throw std::runtime_error(errInStream);
        }
        
        t.setTime(hour, minute); // call setTime method where validation will take place
    }
    catch (std::runtime_error &e)
    {
        std::cout << "WARNING: ";
        std::cout << "caught runtime_error exception in Time class overloaded operator>>\n";
        std::cout << e.what() << endl;
        // allow processing to continue, do not re-throw
    }
    catch (std::invalid_argument &e)
    {
        std::cout << "ERROR: ";
        std::cout << "caught invalid_argument exception in Time class overloaded operator>>\n";
        std::cout << e.what() << endl;
        // allow processing to continue, do not re-throw
    }
    catch (...)
    {
        std::cout << "unknown exception caught in Time class overloaded operator>>\n";
        throw;
    }
    
    return in;
    
} //END overloaded stream extraction operator for Time class



/****************************************************************************
 *                 Time class stream insertion operator                     *
 ****************************************************************************/

std::ostream& operator<<(std::ostream &os, const Time &t)
{
    os << std::setfill('0');
    
    os << std::setw(2) << t.hh << ":";
    os << std::setw(2) << t.mm;
    
    os << std::setfill(' ');
    
    return os;
    
} //END overloaded stream insertion operator for Time class



/****************************************************************************
 *                     Time class assignment operator                       *
 ****************************************************************************/

Time Time::operator=(const Time &rhsObj)
{
    if (this != &rhsObj)
    {
        // not a self assignment, OK to proceed
        // call method setTime where validation will be accomplished
        
        setTime(rhsObj.hh, rhsObj.mm);
    }
    
    return *this;
    
} //END overloaded assignment operator for Time class







/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class ProcessTimer implementation                      **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Summer 2019 to use in                      **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 **                 (Copy and paste into DateTime.cpp)                     **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

ProcessTimer::ProcessTimer()

{
    
    timeStart = 0;
    
    timeEnd = 0;
    
}



ProcessTimer::ProcessTimer(clock_t tmSt)

{
    
    timeStart = tmSt;
    
    timeEnd = 0;
    
}



ProcessTimer::~ProcessTimer()

{
    
    std::cout << "Inside destructor for ProcessTimer object" << std::endl;
    
}



std::ostream& operator<<(std::ostream &os, const ProcessTimer &tmStmp)

{
    
    std::cout << "Start time:\t" << tmStmp.timeStart << "\n";
    
    std::cout << "End time:\t" << tmStmp.timeEnd << "\n";
    
    std::cout << "Elapsed time:\t";
    
    std::cout << (tmStmp.timeEnd - static_cast<double>(tmStmp.timeStart))/CLOCKS_PER_SEC;
    
    std::cout << "\n";
    
    std::cout << std::endl;
    
    
    
    return os;
    
}



void ProcessTimer::setTimeStart(clock_t tmStart)

{
    
    timeStart = tmStart;
    
}



void ProcessTimer::setTimeEnd(clock_t tmEnd)

{
    
    timeEnd = tmEnd;
    
}



clock_t ProcessTimer::getTimeStart()

{
    
    return timeStart;
    
}



clock_t ProcessTimer::getTimeEnd()

{
    
    return timeEnd;
    
}



double ProcessTimer::getTimeElapsed()

{
    
    return static_cast<double>( (timeEnd - static_cast<double>(timeStart))/CLOCKS_PER_SEC );
    
}
