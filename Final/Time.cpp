/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {
    Time& Time::setToNow() {
        m_min = getTime();
        return *this;
    }

    Time::Time(unsigned int min) {
        m_min = min;
    }
    std::ostream& Time::write(std::ostream& ostr) const {
        int hour = 0, minute = 0;
        hour = m_min / 60;
        minute = m_min % 60;
        ostr.fill('0');
        ostr.width(2);
        ostr << hour << ":";
        ostr.width(2);
        ostr<< minute;
        return ostr;
    }
    std::istream& Time::read(std::istream& istr) {
        int hour = 0, minute = 0;
        istr.clear();
        istr >> hour;
        if (hour < 0)
            istr.setstate(ios::failbit);
        else
        {
            if(istr.get() != ':')
                istr.setstate(ios::failbit);
            else
            {
                istr >> minute;
                if (minute < 0)
                    istr.setstate(ios::failbit);
                else m_min = hour * 60 + minute;
            }
        }
        return istr;
    }

    Time& Time::operator-=(const Time& D) {
        if (m_min < D.m_min)
            m_min += 1440;
        m_min -= D.m_min;
        return *this;
    }
    Time Time::operator-(const Time& D)const {
        Time Tmp;
        Tmp.m_min = m_min;
        while (Tmp.m_min < D.m_min)
            Tmp.m_min += 1440;
        Tmp.m_min -= D.m_min;
        return Tmp;
    }
    Time& Time::operator+=(const Time& D) {
        m_min += D.m_min;
        return *this;
    }
    Time Time::operator+(const Time& D)const {
        return Time(m_min + D.m_min);
    }
    
    Time& Time::operator=(unsigned int val) {
        m_min = val;
        return *this;
    }

    Time& Time::operator *= (unsigned int val) {
        m_min *= val;
        return *this;
    }
    Time& Time:: operator /= (unsigned int val)
    {
        m_min /= val;
        return *this;
    }
    Time Time::operator *(unsigned int val)const 
    {
        return Time(m_min * val);
    }
    Time Time::operator /(unsigned int val)const {
        return Time(m_min / val);
    }

    Time::operator unsigned int()const {
        unsigned temp;
        temp = int(m_min);
        return temp;
    }
    Time::operator int()const {
        return int(m_min);
    }

    std::ostream& operator<<(std::ostream& ostr, const Time& D) {
        D.write(ostr);
        return ostr;
    }
    std::istream& operator>>(std::istream& istr, Time& D) {
        D.read(istr);
        return istr;
    }
}