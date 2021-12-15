/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<iostream>
#include<fstream>
#include"IOAble.h"

using namespace std;
namespace sdds {

	std::ostream& operator<<(std::ostream& ostr, const IOAble& ioable) {
		ioable.write(ostr);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, IOAble& ioable) {
		ioable.read(istr);
		return istr;
	}
}

