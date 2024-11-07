/* Citation and Sources...
Final Project Milestone ?
Module: Menu
Filename: menu.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <cstring>
#include "Utils.h"
#include <ctype.h>
#include <string>
using namespace std;
using namespace seneca;
namespace seneca
{
    //This constructor is designed to initialize a Menu object.
    Menu::Menu(const char* menuContent, int numberOfTabs)
    {
        m_text = new char[strlen(menuContent) + 1];
        strcpy(const_cast<char*>(m_text), menuContent);
        m_numTabs = numberOfTabs;
        m_numOptions = 0;
        //const char* i = menuContent;
        for (const char* p = menuContent; *p != '\0'; p++)
        {
            if (*p == '\n')
            {
                m_numOptions++;
            }
        }
    }

    //deallocate dynamic memory
    Menu::~Menu()
    {
        delete[]m_text;
    }
    //presenting the Menu content to the user.
    void Menu::display(std::ostream& ostr) const
    {
        // Output menu text with proper indentation
        const char* p = m_text;
        while (*p != '\0')
        {
            // Output indentation 
            if (m_numTabs > 0)
            {
                ostr << std::string(m_numTabs * 3, ' '); // Indentation for submenu
            }

            // Output current line
            while (*p != '\0' && *p != '\n')
            {
                ostr << *p;
                ++p;
            }

            // Move to the next line
            if (*p == '\n')
            {
                ostr << '\n';
                ++p;

            }
            //when reaching end
            if (*p == '\0')
            {
                ostr << '\n';
            }

        }

        // Output exit option with proper indentation
        if (m_numTabs > 0)
        {
            //  ostr << "\n";
            ostr << std::string(m_numTabs * 3, ' ');
        }
        ostr << "0- Exit\n";

        // Output prompt with proper indentation
        if (m_numTabs > 0)
        {
            ostr << std::string(m_numTabs * 3, ' ');
        }
        ostr << "> ";
    }

    //clear the input buffer
    void clearInputBuffer()
    {
        while (cin.get() != '\n'); // read characters until newline character is encountered
    }


    //calls the display function and then receives the user's selection
    int& Menu::operator>>(int& Selection)
    {
        int userInput;
        bool validInput = false;
        //calling display function to display options
        display();
        //flag for re entry
        int flag = 1;
        while (!validInput)
        {
            //peek function peeks into the input stream  to check if the next characcter without 
            //removing it from there
            if (!(cin >> userInput) || cin.peek() != '\n')
            {
                if (flag == 1)
                {
                    cout << "Bad integer value, try again: ";
                    cin.clear();
                    clearInputBuffer();
                    flag = 0;
                }
                else
                {
                    cout << "Only enter an integer, try again: ";
                    cin.clear();
                    clearInputBuffer();

                }

            }

            else if (userInput >= 0 && userInput <= m_numOptions)
            {
                Selection = userInput;

                validInput = true;
            }
            else {
                std::cout << "Invalid value entered, retry[0 <= value <= " << m_numOptions << "]: ";
                cin.clear();
                clearInputBuffer();

            }
        }

        return Selection;
    }

}