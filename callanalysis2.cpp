// Title: callanalysis2.cpp
// Assignment 3
// Purpose: Write a C++ program to read in alist of phone call records from a file into a “call database.’ Program will then allow the user to enter a prefix for a phone number in E164 format(refer to the previous lab for E164 details). Program will list out all calls to phone number which have that prefix.
// This is main class that will run the interface of the program.
// Program will ask to upload the phone call history with raw number.
// My program will load and user can search for the number start with prefix.
// Class: CSC 2430 Spring 2019
// Author: Nghi Vo

#include <iostream>
#include <ios>
#include <iomanip>
#include <cassert>
#include <fstream>
#include "calldb2.h"


using namespace std;

int main() {
    
    // Declare variable
    CALLDB db;
    CALL call;
    ifstream fin;
    string fileName;
    string str;
    string ret;
    
    // Ask user to type file name
    cout << "File Name:" << endl;
    cin >> fileName;
    
    // Try to open file
    fin.open(fileName);
    if (!fin.is_open()) {
        cout << "Can't open " << "'" << fileName << "'" << endl;
        return -1;
    }
    
    // Initializes call database to have store no calls
    int dropCall = db.load(fin);
    
    
    
    // Print out format
    cout << "Log successfully read into database, " << db.getCountCalls()  << " records added, " << dropCall << " dropped" << endl << endl;
    cout << "Contents of Call Database" << endl;
    
    // Test case if there is no call load in the data
    // Return: No records
    if (db.getCountCalls() == 0){
        cout << "No records" << endl << endl;
    }
    
    // Test case if there has data load in
    else {
        // Print the Contents of calls in database (db)
        cout << "Time      Country  Phone Number    Duration" << endl;
        // For loop to get all the call in the callbd
        for (int i = 0; i < db.getCountCalls(); i++){
            assert(db.getCall(i, call));
            cout << left << setw(10) << call.getFormattedStart();
            cout << left << setw(9) << call.getCountryCode() << left << setw(16) << call.getLocalPhone();
            cout << call.getFormattedDuration();
            cout << endl;
        }
        cout << endl;
    }
    
    // Ask user for the E164 prefix to check
    string choice;
    
    // Keep ask user for the E164 until
    // Using do, while
    do{
        // return false to break the do while
        bool isFound = false;
        cout << "E164 prefix for query:" << endl;
        // get user choice
        cin >> choice;
        
        // if choice != 1 (not exit)
        if(choice != "-1") {
            // for loop to run all the call
            for(int i = 0; i < db.getCountCalls(); i++) {
                // change i by the time prvious i find the prefix
                i = db.findByPrefix(i, choice);
                
                if (i != -1){
                    // if at i found the number with same prefix
                    if (!isFound)
                        cout << "Time      Country  Phone Number    Duration" << endl;
                    // print out call by format
                    assert(db.getCall(i, call));
                    cout << left << setw(10) << call.getFormattedStart();
                    cout << left << setw(9) << call.getCountryCode() << left << setw(16) << call.getLocalPhone();
                    cout << call.getFormattedDuration();
                    cout << endl;
                    isFound = true;
                }
                else break;
            }
            // there is no records
            if (isFound == false) {
                cout << "No Records" << endl;
            }
            cout << endl;
        }
    }while(choice != "-1"); // Out of loop when user put -1
    
    return 0;
}







