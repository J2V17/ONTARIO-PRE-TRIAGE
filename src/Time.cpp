/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: Time.cpp
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
#include "Time.h"
#include "Utils.h"
#include <iomanip>
using namespace std;
namespace seneca
{
	//resets the Time object to the current time using the U.getTime()
	Time& Time::reset()
	{
		minutes = U.getTime();
		return *this;
	}
	//initializes a Time object.
	Time::Time(unsigned int min)
	{
		minutes = min;
	}
	//writes the time into ostream in the HH:MM format
	void Time::write(ostream& os) const
	{
		unsigned int hours = minutes / 60;
		unsigned int mins = minutes % 60;
		os << setfill('0') << setw(2) << hours << ":" << setw(2) << mins;
	}
	//reads the time from istream in the H:M format
	istream& Time::read(std::istream& is)
	{
		char colon;
		unsigned int hours, mins;
		if (!(is >> hours))
		{
			// Set failbbit if the  reading of  hours fails
			is.setstate(std::ios::failbit);
			return is; // Exit the function
		}

		// Check if the next character is a colon
		//peek function peeks into the input stream  to check if the next characcter without 
		//removing it from there
		if (is.peek() != ':')
		{
			//Set failbit if colon
			is.setstate(std::ios::failbit);
			//exit
			return is;
		}
		//if it doesnt exit take the colon in
		is >> colon;
		// Attempt to read minutes
		if (!(is >> mins))
		{
			//set failbit if it fails to read mins
			is.setstate(std::ios::failbit);
			return is; // Exit the function
		}
		minutes = hours * 60 + mins;
		return is;
	}
	//if cast to an unsigned integer will return number of minutes
	Time::operator unsigned int() const
	{
		return minutes;
	}
	//multiplies the number of minutes held in the Time object by val,
	Time& Time::operator*= (int val)
	{
		minutes *= val;
		return *this;
	}
	//This operator overloads the subtraction assignment -= for the Time class.
	Time& Time::operator-= (const Time& D)
	{
		//handle the negative condiition
		if (minutes < D.minutes)
		{
			minutes += 1440;
		}
		minutes -= D.minutes;
		return *this;

	}
	//same as -= overload but does not modify current object
	Time Time::operator-(const Time& T)const
	{
		Time temp = *this;
		temp -= T;
		return temp;
	}
	// insert a Time object into an ostream object 
	ostream& operator <<(ostream& os, const Time& time)
	{
		time.write(os);
		return os;
	}
	//extract data from an istream object into the Time object 
	istream& operator >>(istream& is, Time& time)
	{
		time.read(is);
		return is;
	}
}