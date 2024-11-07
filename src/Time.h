/* Citation and Sources...
Final Project Milestone 1
Module: TIME
Filename: Time.h
Version 1.0
Author   John Doe
Revision History
-----------------------------------------------------------
Date      Reason
-----------------------------------------------------------
Name-Jeevan Victor Varghese
Id-14216225
email-jvvarghese@myseneca.ca
Section- NII
*/

#ifndef TIME_H
#define TIME_H

#include <iostream>
using namespace std;
namespace seneca
{
	class Time
	{
		unsigned int minutes;

	public:
		//resets the Time object to the current time using the U.getTime()
		Time& reset();
		//initializes a Time object.
		Time(unsigned int min = 0u);
		//reads the time from istream in the H:M format
		istream& read(std::istream& is);
		//if cast to an unsigned integer will return number of minutes
		operator unsigned int() const;
		//writes the time into ostream in the HH:MM format
		void write(ostream& os) const;
		//multiplies the number of minutes held in the Time object by val,
		Time& operator*= (int val);
		//This operator overloads the subtraction assignment -= for the Time class.
		Time& operator-= (const Time& D);
		//same as -= overload but does not modify current object
		Time operator-(const Time& T)const;
		// insert a Time object into an ostream object 
		friend ostream& operator<<(ostream& os, const Time& t);
		//extract data from an istream object into the Time object 
		friend istream& operator>>(istream& os, Time& time);
	};
}
#endif
