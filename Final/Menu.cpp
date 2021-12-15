/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<iostream>
#include"Menu.h"
#include"utils.h"

using namespace std;

namespace sdds {
	Menu::Menu(const char* MenuContent, int NoOfSelections) :m_noOfSel{ NoOfSelections } {
		m_text = nullptr;
		int len = strlen(MenuContent);
		m_text = new char[len + 1];
		strcpy(m_text, MenuContent);
	}

	Menu::~Menu() {
		delete[] m_text;
		m_text = nullptr;
	}

	Menu::Menu(const Menu& src)  {
		if (src)
		{
			m_noOfSel = src.m_noOfSel;
			m_text = nullptr;
			int len = strlen(src.m_text);
			m_text = new char[len + 1];
			strcpy(m_text, src.m_text);
		}
    }



	void Menu::display()const {
		cout << m_text << endl << "0- Exit" << endl;
	}

	int& Menu::operator>>(int& Selection) {
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ");
		return Selection;
	}

	Menu::operator bool()const{
		return (m_text != nullptr && m_noOfSel > 0);
	}

}