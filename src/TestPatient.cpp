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
//DATE-4/1/2024
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "TestPatient.h"
#include "Patient.h"
#include <limits>
#include <iomanip>

static int nextTestTicket = 1;

using namespace std;
namespace seneca
{
	//Default Constructor also passes nextTestTicket to base class
	TestPatient::TestPatient() : Patient(nextTestTicket++)
	{

	}
	//returns a single char C
	char TestPatient::type()const
	{
		return 'C';
	}
	//write function to insert contagion test
	ostream& TestPatient::write(std::ostream& os) const
	{
		//if os is cout then contagion test
		if (&os == &cout)
		{
			os << "Contagion TEST" << endl;
		}
		//call write function of base classs which is patient
		Patient::write(os);
		return os;
	}
	//read function to check if reading from file 
	istream& TestPatient::read(istream& is)
	{
		//call the read function of patient
		Patient::read(is);
		//check if reading from file
		if ((&is != &cin))
		{
			nextTestTicket = number() + 1;
		}
		return is;
		is.clear();
		is.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	//This class does not need a custom destructor.
	
}