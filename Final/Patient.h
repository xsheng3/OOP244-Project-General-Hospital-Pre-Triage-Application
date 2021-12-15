/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "Ticket.h"
#include "IOAble.h"
namespace sdds {
    class Patient :public IOAble {
        char* m_name{ nullptr };
        int m_OHIPNo{ 0 };
        Ticket m_ticket;
        bool m_fileIO;
    public:
        Patient(int ticketNo = 0, bool fileIO = false);
        Patient(const Patient&) = delete;
        Patient& operator=(const Patient&) = delete;
        ~Patient();
        virtual char type(void)const = 0;
        bool fileIO()const;
        void fileIO(bool fileIO);
        bool operator==(char type)const;
        bool operator==(const Patient&)const;
        void setArrivalTime();
        operator Time()const;
        int number()const;
        std::ostream& csvWrite(std::ostream& ostr)const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
    };
}
#endif // !SDDS_TICKET_H_
