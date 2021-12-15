/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>

namespace sdds {
	class Menu {
		char* m_text; // holds the menu content dynamically
		int m_noOfSel; // holds the number of options displayed in menu content
		void display()const;
	public:
		Menu(const char* MenuContent, int NoOfSelections);
		virtual ~Menu();
		int& operator>>(int& Selection);
		Menu(const Menu&);
		Menu& operator=(Menu&) = delete;// add safe copying logic
		operator bool()const;
	};


}

#endif