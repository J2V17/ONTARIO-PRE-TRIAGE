/***********************************************************************
// OOP244 Project ms3
//
// File  TestPatient.h
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
#ifndef SENECA_TRIAGE_PATIENT_H
#define SENECA_TRIAGE_PATIENT_H

#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#include "Patient.h"
using namespace std;
namespace seneca
{
	class TriagePatient : public Patient
	{
		char* symptoms;

	public:
		//default constructor
		TriagePatient();
		//virtual type const that returns a single char "T"
		 char type()const;
		 //write to the ostream
		 ostream& write(std::ostream& os) const override;
		 //extract info fro different instances of istream
		 istream& read(std::istream& is)override;
		 //destructor
		~TriagePatient();



	};
}
#endif