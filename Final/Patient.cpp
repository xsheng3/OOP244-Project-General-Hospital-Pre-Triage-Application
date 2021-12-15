/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include"Patient.h"
#include"utils.h"
#include<string>
#include<cstring>

namespace sdds {
    Patient::Patient(int ticketNo, bool fileIO) :m_ticket{ ticketNo } {
        m_fileIO = fileIO;
    }

    Patient::~Patient() {
        delete[] m_name;
        m_name = nullptr;
    }
  
    bool Patient::fileIO()const {
        return m_fileIO;
    }

    void Patient::fileIO(bool fileIO) {
        m_fileIO = fileIO;
    }


    bool Patient::operator==(char type)const {
       return(this->type() == type);
    }

    bool Patient::operator==(const Patient& src)const {
        return(type() == src.type());
    }
    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }
    Patient::operator Time()const {
        return Time(m_ticket);
    }
    int Patient::number()const {
        return m_ticket.number();
    }
    std::ostream& Patient::csvWrite(std::ostream& ostr)const {
        ostr << type() << ',' << m_name << ',' << m_OHIPNo << ',';
        m_ticket.csvWrite(ostr);
        return ostr;
    }
    std::istream& Patient::csvRead(std::istream& istr) {
        std::string name;
        getline(istr, name, ',');
        int len = strlen(name.c_str());
        delete[] m_name;
        m_name = new char[len + 1];
        strcpy(m_name, name.c_str());       
      
        istr >> m_OHIPNo;
        istr.ignore();
        m_ticket.csvRead(istr);
        return istr;        
    }

    std::ostream& Patient::write(std::ostream& ostr)const {
        ostr << m_ticket << std::endl;
        for(int i = 0; m_name[i] && i < 25; i++)
        {
            ostr << m_name[i];
        }
        ostr << ", OHIP: " << m_OHIPNo;
        return ostr;
    }

    std::istream& Patient::read(std::istream& istr) {
        std::cout << "Name: ";
        std::string name;
        getline(istr, name, '\n');
        int len = strlen(name.c_str());
        delete[] m_name;
        m_name = new char[len + 1];
        strcpy(m_name, name.c_str());

        m_OHIPNo = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);

        return istr;      

    }
}