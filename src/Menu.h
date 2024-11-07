/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: menu.h
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
#ifndef MENU_H
#define MENU_H

#include <iostream> // Include the <iostream> header

namespace seneca
{
    class Menu
    {
    private:
        const char* m_text;
        int m_numOptions;
        int m_numTabs;

    public:
        //This constructor is designed to initialize a Menu object.
        Menu(const char* menuContent, int numberOfTabs = 0);
        //deallocates dynamically allocated memory
        ~Menu();
        //presenting the Menu content to the user.
        void display(std::ostream& ostr = std::cout) const;
        //disabling copy and assignment
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;
        // calls the display function and then receives the user's selection
        int& operator>>(int& Selection);

    };
    //to clear the input buffers
    void clearInputBuffer();
}
#endif
