/* Citation and Sources...
Final Project Milestone ?
Module: IOAble
Filename: IOAble.h
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
#ifndef IOABLE_H
#define IOABLE_H
#include <iostream>
using namespace std;
namespace seneca
{

	class IOAble
	{
	public:


		virtual ostream& write(ostream& os) const = 0;
		virtual istream& read(istream& is) = 0;
		virtual ~IOAble();

	};
	ostream& operator<<(ostream& os, const IOAble& obj);
	istream& operator>>(istream& is, IOAble& obj);


}
#endif