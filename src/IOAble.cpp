/* Citation and Sources...
Final Project Milestone ?
Module: IOAble
Filename: IOAbl.cpp
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
#include "Utils.h"
#include "Utils.h"
#include <iomanip>
#include "IOAble.h"
using namespace std;
namespace seneca
{
    IOAble::~IOAble()
    {

    }
    ostream& operator<<(ostream& os, const IOAble& obj) {
        return obj.write(os);
    }

    // Extraction operator overload
    istream& operator>>(istream& is, IOAble& obj) {
        return obj.read(is);
    }
};
