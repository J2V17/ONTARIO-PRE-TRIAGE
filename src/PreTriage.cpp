/* Citation and Sources...
Final Project Milestone 5
Module: IOAble
Filename: PreTriage.cpp
Version 1.0
Author   John Doe
Revision History
-----------------------------------------------------------
Date      Reason
-----------------------------------------------------------
4/8/2024   Forgot to change return type of a function

Name-Jeevan Victor Varghese
Id-14216225
email-jvvarghese@myseneca.ca
Section- NII
//DATE-5/2/2024
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "TriagePatient.h"
#include "Time.h"
#include "Menu.h"
#include <limits>
#include <iomanip>
#include "TestPatient.h"
#include "PreTriage.h"
#include "Utils.h"
#include <fstream>

using namespace std;
namespace seneca
{
	//constructor for the pre triage module
	PreTriage::PreTriage(const char* dataFileName)
	{

		m_lineupSize = 0;
		strcpy(m_filename, dataFileName);
		//loop to allocate
		for (int i = 0; i < maxPatients; ++i)
		{
			m_lineup[i] = nullptr;
		}
		//initialize to respective values
		//Time objects
		m_contaigenTestWait = Time(15);
		m_triageWait = Time(5);
		load();
	}
	//destructor
	PreTriage::~PreTriage()
	{
		// Save data before deleting lineup
		save();
		for (int i = 0; i < m_lineupSize; i++)
		{
			delete m_lineup[i];
			m_lineup[i] = nullptr; // Set deleted pointers to nullptr to avoid dangling pointers
		}
	}
	//Receives a constant Patient Reference
		//  and returns the total estimated wait time
	int PreTriage::getWaitTime(const Patient& pat) const
	{
		//char type = pat.type();
		int numPatient = 0;
		int totalWait = 0;

		for (int i = 0; i < m_lineupSize; i++)
		{
			if (m_lineup[i]->type() == pat.type())
			{
				numPatient++;
			}
		}
		for (int i = 0; i < numPatient; i++)
		{
			//check for the type of test
			if (pat.type() == 'C')
			{
				totalWait += m_contaigenTestWait;
			}
			else if (pat.type() == 'T')
			{
				totalWait += m_triageWait;
			}
		}
		// Return totalWait at the end of the function
		return totalWait;
	}
	//Receives the reference of the admitting patient and adjusts the average wait time
	void PreTriage::setAverageWaitTime(Patient& patient)
	{
		Time currentTime;
		//reset
		currentTime.reset();
		//get time of ticket
		Time patientTime = patient.time();
		//ticket number
		int patientNumber = patient.number();
		// Update the average wait time based on the patient's type
		if (patient.type() == 'C')
		{
			m_contaigenTestWait = ((currentTime - patientTime) + (m_contaigenTestWait * (patientNumber - 1))) / (patientNumber);
		}
		else
		{
			m_triageWait = ((currentTime - patientTime) + (m_triageWait * (patientNumber - 1))) / (patientNumber);
		}
	}

	//Receives a character representing the type of patient 

	int PreTriage::indexOfFirstInLine(char type) const
	{
		for (int i = 0; i < m_lineupSize; i++)
		{
			if (m_lineup[i]->type() == type)
			{
				return i;
			}
		}
		return -1;
	}
	//Loads the average wait times and the patient records from the data file 

	void PreTriage::load()
	{
		cout << "Loading data..." << endl;
		ifstream file(m_filename);
		//check if file 
		if (!file.is_open())
		{
			//if condition true display message and return
			cout << "No data or bad data file!" << endl << endl;
			return;
		}

		file >> m_contaigenTestWait;
		// Ignore until comma
		file.ignore(numeric_limits<streamsize>::max(), ',');
		//file.ignore();
		file >> m_triageWait;
		//file.ignore();
		// Ignore until newline
		file.ignore(numeric_limits<streamsize>::max(), '\n');
		//create a pointer locally
		Patient* newPatient;
		newPatient = nullptr;
		//iterate over the data
		for (int i = 0; i < maxPatients; i++)
		{
			char type;
			file >> type;
			//file.ignore();
			file.ignore(numeric_limits<streamsize>::max(), ','); // Ignore until comma
			//when reaching end of file
			if (file.eof())
			{
				break;
			}
			//check if contaigen
			if (type == 'C')
			{
				newPatient = new TestPatient;
			}
			//triage
			else if (type == 'T')
			{
				newPatient = new TriagePatient;
			}
			//if not pointing to null value then store
			if (newPatient != nullptr)
			{
				file >> *newPatient;
				m_lineup[m_lineupSize++] = newPatient;
			}
		}

		if (m_lineupSize >= maxPatients)
		{
			cout << "Warning: number of records exceeded " << maxPatients << endl;
			cout << m_lineupSize << " Records imported..." << endl << endl;

		}
		else if (m_lineupSize > 0)
		{
			//m_lineupSize = m_lineupSize - 1;
			cout << m_lineupSize << " Records imported..." << endl << endl;
		}
		else
		{
			cout << "No data or bad data file!" << endl << endl;
		}
		file.close();
	}

	//query to open file for output and insert dataa record saved for each type
	void PreTriage::save()
	{

		cout << "Saving lineup..." << endl;
		ofstream file(m_filename);
		if (!file)
		{
			cout << "Error: Cannot create data file!" << endl;
			return;
		}
		file << m_contaigenTestWait << ',' << m_triageWait << endl;

		int contagionTestsSaved = 0;
		int triageRecordsSaved = 0;

		for (int i = 0; i < m_lineupSize; i++)
		{
			file << *m_lineup[i] << endl;
			if (m_lineup[i]->type() == 'C')
			{
				contagionTestsSaved++;
			}
			else if (m_lineup[i]->type() == 'T')
			{
				triageRecordsSaved++;
			}
		}

		//when exitiing
		cout << contagionTestsSaved << " Contagion Tests and " << triageRecordsSaved << " Triage records were saved!" << endl;
		//close the file
		file.close();
	}
	//modifier to handle and run the entire preTriage Module

	void PreTriage::run()
	{
		int option;
		Menu menu("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup", 0);

		do
		{
			//menu.display();
			menu >> option;

			//switch case for the main menu
			//will call individual function as user chooses
			switch (option)
			{
			case 1:
				registerPatient();
				break;
			case 2:
				admit();
				break;
			case 3:
				lineup();
				break;
			case 0:
				return;
			default:
				cout << "Invalid selection, please try again." << endl;
				break;
			}
		} while (option != 0);
	}
	//modifier to register a new patient
	void PreTriage::registerPatient()
	{
		if (m_lineupSize >= maxPatients)
		{
			cout << "Line up full!" << endl;
			return;
		}

		Menu registration("Select Type of Registration:\n1- Contagion Test\n2- Triage", 1);
		int option = 0;
		//registration.display();
		registration >> option;

		switch (option)
		{
		case 0:
		{
			return;
		}
		case 1:
		{
			m_lineup[m_lineupSize] = new TestPatient();
			break;
		}
		case 2:
		{
			m_lineup[m_lineupSize] = new TriagePatient();
			break;
		}
		default:
			cout << "Invalid choice. Please try again." << endl;
			return;
		}

		// Set patient's arrival time
		m_lineup[m_lineupSize]->setArrivalTime();

		//output
		cout << "Please enter patient information: " << endl;
		//tilll '\n'
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> *m_lineup[m_lineupSize];
		cout << endl;
		cout << "******************************************" << endl;
		cout << *m_lineup[m_lineupSize];
		cout << "Estimated Wait Time: ";
		Time waitTime = getWaitTime(*m_lineup[m_lineupSize]);
		cout << waitTime << endl;
		cout << "******************************************" << endl << endl;
		//cout << "******************************************" << endl << endl;

		m_lineupSize++; // Increment lineup size after registering a patient
	}

	//modifier to admit patient
	void PreTriage::admit()
	{
		Menu admission("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 1);
		int option;
		//admission.display();
		admission >> option;
		char type;
		Time t;

		switch (option)
		{
		case 0:
		{
			return;
		}
		case 1:
		{
			type = 'C';
			break;
		}
		case 2:
			type = 'T';
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
			return;
		}
		int index = indexOfFirstInLine(type);

		if (index == -1) {
			cout << "Lineup is empty!" << endl;
			return;
		}

		cout << endl << "******************************************" << endl;
		cout << "Call time: [" << t.reset() << "]";
		//Time::now().write(cout);
		cout << endl;
		cout << "Calling at for " << *m_lineup[index];
		cout << "******************************************" << endl << endl;

		setAverageWaitTime(*m_lineup[index]);

		removeDynamicElement(m_lineup, index, m_lineupSize);
		//delete m_lineup[index];
	}
	//modifier for the lineup
	void PreTriage::lineup()
	{
		Menu lineup("Select The Lineup:\n1- Contagion Test\n2- Triage", 1);
		int option = 0;
		//lineup.display();
		//getting selection
		lineup >> option;

		cout << "Row - Patient name                                          OHIP     Tk #  Time" << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		int index = 1;
		switch (option)
		{
		case 1: // Contagion Test
			for (int i = 0; i < m_lineupSize; ++i)
			{
				if (m_lineup[i]->type() == 'C')
				{
					clog << index << "   - " << *m_lineup[i] << endl;
					index = index + 1;
				}
			}
			break;
		case 2: // Triage
			for (int i = 0; i < m_lineupSize; ++i)
			{
				if (m_lineup[i]->type() == 'T')
				{
					//use clog or else data will be different
					clog << index << "   - " << *m_lineup[i] << endl;
					index = index + 1;

				}
			}
			break;
		case 0: // Exit
			return;
		default:
			cout << "Invalid selection!" << endl;
			break;
		}

		cout << "-------------------------------------------------------------------------------" << endl;
	}

}

