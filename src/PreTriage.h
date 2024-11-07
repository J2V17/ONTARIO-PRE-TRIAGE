/***********************************************************************
// OOP244 Project ms3
//
// File  PreTriage.h
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
//NAME-JEEVAN VICTOR VARGHESE
//ID-1442216225
//MAIL- jvvarghese@myseneca.ca
//DATE-5/2/2024

#ifndef SENECA_PRETRIAGE_H
#define SENECA_PRETRIAGE_H

#define MAX_FILE 1000

#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#include "Time.h"
#include "Patient.h"
using namespace std;
namespace seneca
{
	//MAXIMUM NUM OF PATIENTS
	const int maxPatients = 100;

	class PreTriage
	{
		//contaigen test object
		Time m_contaigenTestWait;
		//time object for triage
		Time m_triageWait;
		//patient lineuo
		Patient* m_lineup[maxPatients];
		//data filename
		char m_filename[MAX_FILE] = { '\0' };
		//This number can not exceed the maximum lineup value.
		int m_lineupSize;
		//private methods
		//Receives a constant Patient Reference
		//  and returns the total estimated wait time 
		int getWaitTime(const Patient& p) const;
		//Receives the reference of the admitting patient and adjusts the average wait time
		void setAverageWaitTime(Patient& patient);
		//Receives a character representing the type of patient 
		int indexOfFirstInLine(char type)const;
		//Loads the average wait times and the patient records from the data file 
		void load();
		//query to open file for output and insert dataa record saved for each type
		void save();
		//modifier to register a new patient
		//unable to use 'register' as identifier 
		void registerPatient();
		//modifier to admit patient
		void admit();
		//modifier for the lineup
		void lineup();
	public:
		//This data file name is stored in the data filename attribute
		//  for load and save purposes. 
		// The constructor also initializes the two Time attributes
		//Contagion test and Triage, to 15 and 5 respectively.
		PreTriage(const char* fileName);
		//destructor
		~PreTriage();
		//modifier to handle and run the entire preTriage Module
		void run();

	};
}
#endif