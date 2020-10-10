
// Title calldb2.cpp
// Assignment 3
// Purpose: Write a C++ program to read in alist of phone call records from a file into a “call database.’ Program will then allow the user to enter a prefix for a phone number in E164 format(refer to the previous lab for E164 details). Program will list out all calls to phone number which have that prefix.
// This is CALL and CALLLDB implement all the function
// Class: CSC 2430 Spring 2019
// Author: Nghi Vo

#include <iostream>
#include <ios>
#include <iomanip>
#include <cassert>

#include "calldb2.h"
using namespace std;

// Formatted Getters. Returning formatted strings, not raw strings.
// Get formatted start time of call
// Put time in format and print
// Returns: a formatted (HH:MM:SS) duration string
string CALL::getFormattedStart() const {
    string hour, minute, second;
    string ret;
    
    hour = start.substr(0, 2);
    minute = start.substr(2, 2);
    second = start.substr(4, 2);
    
    return ret = hour + ":" + minute + ":" + second;;
}
// Formatted Getters. Returning formatted strings, not raw strings.
// Get country code of call
// Put country and code in format and print
// Returns: a 3-alpha country code string
string CALL::getCountryCode() const{
    string ret;
    
    // Declare country code
    if (phonenum.find("+1") == 0){
        ret = "NA";
    }
    else if (phonenum.find("+852") == 0){
        ret = "HK";
    }
    else {
        ret = "FR";
    }
    return ret;
}

// Formatted Getters. Returning formatted strings, not raw strings.
// Get local phone number of call
// Put country in format and print
// Returns: a formatted local phone number string
string CALL::getLocalPhone() const{
    string country = CALL::getCountryCode();
    string ret;
    
    // Format “(XXX)-XXX-XXXX”
    if (country == "NA"){
        ret = "(" + phonenum.substr(2, 3) + ")-" + phonenum.substr(5, 3) + "-" + phonenum.substr(8, 4);
    }
    // Format “0X XX XX XX XX”
    else if (country == "HK"){
        ret = phonenum.substr(4, 4) + " " + phonenum.substr(8, 4);
    }
    // Format “XXXX XXXX”
    else {
        ret = "0" + phonenum.substr(3, 1) + " " + phonenum.substr(4, 2) + " " + phonenum.substr(6, 2) + " " + phonenum.substr(8, 2) + " " + phonenum.substr(10, 2);
    }
    return ret;
}

// Formatted Getters. Returning formatted strings, not raw strings.
// Convert string time to number to calcutlate and print format
// Return: in minute follow by second
// Format: minute:second
string CALL::getFormattedDuration() const{
    int dur = stoi(duration);
    int min;
    int sec;
    string ret;
    
    // Minutue is divide to 60
    // The remainder when divide 60 is second
    min = dur / 60; // Minutue is divide to 60
    sec = dur % 60; // The remainder when divide 60 is second
    
    // There is no call so time = 0
    if (dur == 0){
        return "-1:-1";
    }
    // Using to_string to convert number to integer and print
    // If second is less than 10, adding one zero
    // If second is zero, will return "00"
    // Using to_string to convert back to string to print
    if (sec < 10){
        ret = to_string(min) + ":0" + to_string(sec);
    }
    else if (sec == 0){
        ret = to_string(min) + ":00";
    }
    else {
        ret = to_string(min) + ":" + to_string(sec);
    }
    
    return ret;
}

// Phone Number Prefix Checker.
// Take string from user to compare
// Return true if call’s phone# starts with the parameter string.
bool CALL::phoneNumStartsWith(string prefix) const{
    // Check when user type empty string
    if (prefix == "") {
        return false;
    }
    else { // Check if the string prefix is start at index 0
        if (phonenum.find(prefix) == 0){
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

// Check if the data being set is valid before setting the value
// Return true ifthe data being set is valid, false otherwise, without setting the value.
bool CALL::setStart(string in){
    int hour;
    int minute;
    int second;
    // Check size of time (must have 6 indexes)
    // Check hour valiation, hour is digit number
    // Check minute validation, minute is digit number
    // Check second validation, second is digit number
    
    if ((in.size() != 6) ||
        (!isdigit(in.at(0)) || !isdigit(in.at(1))) ||
        (!isdigit(in.at(2)) || !isdigit(in.at(3))) ||
        (!isdigit(in.at(4)) || !isdigit(in.at(5)))){
        return false;
    }
    else {
        // Convert time (string) to integer to test
        
        hour = stoi(in.substr(0, 2));
        minute = stoi(in.substr(2, 2));
        second = stoi(in.substr(4, 2));
        
        if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60 || second < 0 || second >= 60){
            return false;
        }
        else {
            start = in;
            return true;
        }
    }
}

// Check if the data being set is valid before setting the value
// Return true ifthe data being set is valid, false otherwise, without setting the value.
bool CALL::setPhoneNum(string in){
    // Phone numbers have 12 digits
    // Check if the numbers have right country code (using NA, FR, HK)
    
    if ((in.size() != 12) && (in.find("+1") != 0 || in.find("+852") != 0 || in.find("+33") != 0)){
        return false;
    }
    else {
        phonenum = in;
        return true;
    }
}

// Check if the data being set is valid before setting the value
// Return true ifthe data being set is valid, false otherwise, without setting the value.
bool CALL::setDuration(string in){
    // Check all the numbers in string duration are digits
    
    for (int i = 0; i < in.size(); i++){
        if (!isdigit(in[i])){
            return false;
        }
    }
    // Time is no more than 10 digits
    if (in.size() <= 10){
        duration = in;
        return true;
    }
    else {
        return false;
    }
}

CALLDB::CALLDB(){
    numCalls = 0;
}

// Load records from file into database. Return # of records that can’t be added
unsigned int CALLDB::load(istream& fin){
    unsigned int dropCount = 0;
    CALL call;
    
    // Out of loop when there is no more line to read
    while (!fin.eof()){
        string time, number, dur;
        
        // Using fin to read in file
        // Fin read each part in the line
        fin >> time >> number >> dur;
        
        // Read until out of word in the line
        if (fin.fail()){
            break;
        }
        else{
            if ((call.setStart(time)) == true && (call.setPhoneNum(number)) == true && (call.setDuration(dur)) == true){
                // Check all the information are valid (time, number and duration)
                if (numCalls < MAXCALLS){
                    // Set the raw information in to categories by order
                    callLog[numCalls] = call;
                    numCalls++;
                    
                }
                else {
                    // The database is out of space (only 15 spaces)
                    dropCount++;
                }
            }
            else {
                // Increase dropCount when one of the information is not valid
                dropCount++;
            }
            
        }
    }
    return dropCount;
}

// Get count of call records
unsigned int CALLDB::getCountCalls()const{
    return numCalls;
}
// Retrieve call record
bool CALLDB::getCall(unsigned int index, CALL& call)const{
    if (index < numCalls){
        call = callLog[index];
        return true;
    }
    else{
        return false;
    }
}
// Return first index >= of call w/ matching E164 prefix, or -1
int CALLDB::findByPrefix(unsigned int startIndex, string prefix) const{
    CALL call;
    
    // Check when user type empty string
    if (prefix == "") {
        return 0;
    }
    
    // Return -1 if reach the last call
    else if (startIndex > MAXCALLS  || prefix == "+")
    {
        return -1;
    }
    else {
        // Run while loop until it reach the max calls
        while (startIndex < MAXCALLS){
            // if the startIndex in the callLog is same with prefix
            if (callLog[startIndex].phoneNumStartsWith(prefix)){
                return startIndex;
            }
            else {
                // Increase index for checking if did not find the same prfix
                startIndex++;
            }
        }
        return -1;
    }
}

