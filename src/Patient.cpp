/***********************************************************************
// OOP244 Project ms3
//
// File  Patient.cpp
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
//NAME-JEEVAN VICTOR VARGHESE
//ID-1442216225
//DATE-3/31/2024
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "Time.h"
#include <limits>
#include <iomanip>

using namespace std;
namespace seneca
{

    //Constructor Instantiate a Patient object
    Patient::Patient(int ticketNumber) : p_ticket(ticketNumber)
    {
        p_name = nullptr;
        p_OHIP = 0;
    }

    // Copy constructor
    Patient::Patient(const Patient& src) : p_ticket(src.p_ticket)
    {
        p_name = new char[strlen(src.p_name) + 1];
        strcpy(p_name, src.p_name);
        p_OHIP = src.p_OHIP;
    }
    //copy assignment
    Patient& Patient::operator=(const Patient& source)
    {
        if (this != &source)
        {
            p_ticket = source.p_ticket;
            p_OHIP = source.p_OHIP;

            // Allocating memory then copying
            delete[] p_name;
            p_name = new char[strlen(source.p_name) + 1];
            strcpy(p_name, source.p_name);
        }
        return *this;
    }
    // Destructor
    Patient::~Patient()
    {
        delete[] p_name;
    }
    //compare a single charactrer to the current object
    bool Patient::operator==(char otherType) const
    {
        return type() == otherType;
    }
    //compare current object to another patien
    bool Patient::operator==(const Patient& other) const
    {
        return type() == other.type();
    }
    //modifier to set the arrival time within
    void Patient::setArrivalTime()
    {
        p_ticket.resetTime();
    }
    ///retrieve the time of patients ticket
    Time Patient::time() const
    {
        return p_ticket.time();
    }

    // Query method to retrieve ticket number
    int Patient::number() const
    {
        return p_ticket.number();
    }

    //return true if patient in valid state
    Patient::operator bool() const
    {
        if (p_name != nullptr && p_OHIP != 0)
        {
            return true;
        }
        return false;
    }
    //if patient is casted to const char* return the name address 
    Patient::operator const char* () const
    {
        return p_name;
    }
    //		//write to the ostream
    std::ostream& Patient::write(ostream& os) const
    {
        // Check if patient is invalid
        if (p_name == nullptr)
        {
            if (&os == &clog)
            {
                os << "Invalid Patient Record";
            }
            else
            {
                os << "Invalid Patient Record\n";
            }

        }
        else
        {   //check if the osstream is cout
            if (&os == &cout)
            {
                //ticket info
                os << p_ticket << "\n" << p_name << ", OHIP: " << p_OHIP << "\n";
            }
            else if (&os == &clog)
            {
                os << left << setw(53) << setfill('.') << p_name
                    << p_OHIP
                    //right justify tge num ticket
                    << setw(5) << setfill(' ') << std::right << p_ticket.number()
                    //adding the time
                    << " " << p_ticket.time();
            }
            else
            {
                //to make it comma seperated
                os << type() << "," << p_name << "," << p_OHIP << ",";
                p_ticket.write(os);
            }
        }
        return os;
    }
    //read functtion to read from file or user
    istream& Patient::read(istream& is)
    {
        char temp[51];
        // first check if its user input 
        if (&is == &cin)
        {
            cout << "Name: ";
            is.get(temp, 51);
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');

            // Delete existing
            delete[] p_name;
            // Allocating
            p_name = new char[strlen(temp) + 1];
            // Copying
            strcpy(p_name, temp);

            cout << "OHIP: ";
            bool validOHIP = false;
            while (!validOHIP)
            {
                if (!(is >> p_OHIP))
                {
                    std::cout << "Bad integer value, try again: ";
                    is.clear();
                    is.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (p_OHIP < 100000000 || p_OHIP > 999999999)
                {
                    // std::cout << "Invalid value entered, retry[100000000 <= value <= 999999999]: ";
                    std::cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";                    is.clear();
                    is.clear();
                    is.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    validOHIP = true;
                    is.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else
        {
            // Read from file
            is.get(temp, 51, ',');
            is.ignore(10000, ',');
            delete[] p_name;
            p_name = new char[strlen(temp) + 1];
            strcpy(p_name, temp);

            is >> p_OHIP;
            is.ignore(10000, ',');
            p_ticket.read(is);
        }
        return is;
    }

}