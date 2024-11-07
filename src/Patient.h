/***********************************************************************
// OOP244 Project ms3
//
// File  Patient.h
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
#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H
#define MAX_NAME_LENGTH 51
#define OHIP_NUMBER 10

#include <iostream>
#include "IOAble.h"
#include "Ticket.h"

using namespace std;
namespace seneca {
	class Patient : public IOAble
	{
		char* p_name;
		int p_OHIP;
		Ticket p_ticket;

	public:
		//Constructor Instantiate a Patient object
		Patient(int ticketNumber);
		//copy constructor
		Patient(const Patient& src);
		//copy assignment
		Patient& operator=(const Patient& source);
		//destructor
		~Patient();
		//return single char to identify type of patient
		virtual char type() const = 0;
		//compare a single charactrer to the current object
		bool operator==(char otherType) const;
		//compare current object to another patient
		bool operator==(const Patient& other) const;
		//modifier to set the arrival time within
		void setArrivalTime();
		///retrieve the time of patients ticket
		Time time() const;
		//query number that returns ticket 
		int number() const;
		//return true if patient in valid state
		operator bool() const;
		//if patient is casted to const char* retyrn address
		operator const char* () const;
		//write to the ostream
		std::ostream& write(std::ostream& os) const;
		//read from file and user
		std::istream& read(std::istream& is);
	};
}



#endif