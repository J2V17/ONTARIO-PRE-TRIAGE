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
#ifndef SENECA_TEST_PATIENT_H
#define SENECA_TEST_PATIENT_H

#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#include "Patient.h"
using namespace std;
namespace seneca 
{
	class TestPatient : public Patient
	{
	public:
		//Default Constructor also passes nextTestTicket to base class
		TestPatient();
		//returns single char C
		 char type()const;
		 //write function
		 ostream& write(std::ostream& os) const override ;
		 //read function
		 istream& read(std::istream& is) override;
		//~TestPatient();

	};

}
#endif