/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include "TriagePatient.h"
using namespace std;

namespace sdds {
	int nextTriageTicket = 1;

	TriagePatient::TriagePatient(int ticketNo, bool fileIO) : Patient(nextTriageTicket, fileIO) {
		m_symptoms = nullptr;
		nextTriageTicket++;
	}
	
	TriagePatient::~TriagePatient()
	{
		delete[] m_symptoms;
		m_symptoms = nullptr;
	}

	char TriagePatient::type()const {
		return 'T';
	}

	std::ostream& TriagePatient::csvWrite(std::ostream& ostr)const {
		Patient::csvWrite(ostr);
		ostr << ',' << m_symptoms;
		return ostr;
	}

	std::istream& TriagePatient::csvRead(std::istream& istr) {
		if (m_symptoms != nullptr)
			delete[] m_symptoms;
		Patient::csvRead(istr);
		istr.ignore();
		string symptom;
		getline(istr, symptom, '\n');
		int len = strlen(symptom.c_str());
		m_symptoms = new char[len + 1];
		strcpy(m_symptoms, symptom.c_str());

		nextTriageTicket = Patient::number() + 1;
		return istr;
	}

	std::ostream& TriagePatient::write(std::ostream& ostr)const{
		if (Patient::fileIO())
		{
			csvWrite(ostr);
		}
		else
		{
			ostr << "TRIAGE" << endl;
			Patient::write(ostr);
			ostr << endl;
			ostr << "Symptoms: " << m_symptoms << endl;
		}
		return ostr;
	}

	std::istream& TriagePatient::read(std::istream& istr) {
		if (Patient::fileIO())
		{
			csvRead(istr);
		}
		else
		{	
			if (m_symptoms != nullptr)
				delete[] m_symptoms;
			Patient::read(istr);
			cout << "Symptoms: ";
			string symptom;
			getline(istr, symptom, '\n');
			int len = strlen(symptom.c_str());
			m_symptoms = new char[len + 1];
			strcpy(m_symptoms, symptom.c_str());
		}
		return istr;
	}
}