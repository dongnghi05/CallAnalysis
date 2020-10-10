//
// Title: calldb2.h
// Assignment 3
// Purpose: Write a C++ program to read in alist of phone call records from a file into a “call database.’ Program will then allow the user to enter a prefix for a phone number in E164 format(refer to the previous lab for E164 details). Program will list out all calls to phone number which have that prefix.
// This is header that store two classes: CALL and CALLDB.
// Each of classes have own public or private function
// CALL class is working with each phone number (with start time, phone number, duration)
// CALLDB class is using array to store all the call from text. 
// Class: CSC 2430 Spring 2019
// Author: Nghi Vo

#ifndef calldb2_h
#define calldb2_h
using namespace std;

class CALL{
public:
// Formatted Getters. Returning formatted strings, not raw strings.
string getFormattedStart() const;
string getCountryCode() const;
string getLocalPhone() const;
string getFormattedDuration() const;

// Phone Number Prefix Checker. Return true if call’s phone# starts with the parameter string.
bool phoneNumStartsWith(string prefix) const;

// Check if the data being set is valid before setting the value
// Return true ifthe data being set is valid, false otherwise, without setting the value.
bool setStart(string in);
bool setPhoneNum(string in);
bool setDuration(string in);

private:
string start;
string phonenum;
string duration;
};

class CALLDB{
private:
    static const int MAXCALLS = 15;// maximum number of calls
    CALL callLog[MAXCALLS];// Stores calls in database
    unsigned int numCalls;// Number of calls stored
public:
    // Contrsuctor
    CALLDB();
    // Load records from file into database. Return # of records that can’t be added
    unsigned int load(istream& fin);
    // Get count of call records
    unsigned int getCountCalls()const;
    // Retrieve call record
    bool getCall(unsigned int index, CALL& call)const;
    // Return first index >= of call w/ matching E164 prefix, or -1
    int findByPrefix(unsigned int startIndex, string prefix)const;
};


#endif /* calldb2_h */
