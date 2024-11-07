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
//DATE-4/2/2024
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "TriagePatient.h"
#include "Time.h"
#include <limits>
#include <iomanip>

static int nextTriageTicket = 1;
using namespace std;
namespace seneca
{
	//default constructor
	//also pass nextTriageTicket++ to the base class
	TriagePatient::TriagePatient(): Patient(nextTriageTicket++)
	{
		symptoms = nullptr;

	}
	//virtual type const that returns a single char "T"
	char TriagePatient::type()const
	{
		return 'T';
	}
	//write to the ostream
	ostream& TriagePatient::write(ostream& os) const 
	{
		if (&os == &cout)
		{
			//print the header for triage
			os << "TRIAGE" << endl;
		}
			Patient::write(os);
			if (&os == &cout)
			{
				os << "Symptoms: " << symptoms << endl;

			}
		else if ((&os != &clog))
		{
				os << ','  << symptoms;
		}
		
		return os;
	}
	//extract info fro different instances of istream
	istream& TriagePatient::read(istream& is)
	{
		delete[]symptoms;
		symptoms = nullptr;
		Patient::read(is);
		//511+1
		char local[511 + 1];
		//check if not cin
		if (&is != &cin)
		{
			//to read the comma and ignire it
			char comma;
			is >> comma;
			//use get line to accept till '\n'
			is.getline(local, 511 + 1);
			delete[]symptoms;
			symptoms = new char[strlen(local) + 1];
			strcpy(symptoms, local);
			//increment nextTriageTicket
			nextTriageTicket = number() + 1;
		}
		else
		{
			//for symptoms
			cout << "Symptoms: ";
			is.getline(local, 511 + 1);
			delete[]symptoms;
			symptoms = new char[strlen(local) + 1];
			strcpy(symptoms, local);
		}
		//if failt
		if (is.fail())
		{
			delete[] symptoms;
			symptoms = nullptr;
		}
		//return the istream
		return is;
	}
	//Destructor
	TriagePatient::~TriagePatient()
	{
		delete[] symptoms;
		symptoms = nullptr;
	}

}

