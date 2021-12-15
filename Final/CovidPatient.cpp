/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#include "CovidPatient.h"
namespace sdds {
   int nextCovidTicket = 1;

   CovidPatient::CovidPatient(int ticketNumber, bool fileIO) :
	   Patient(nextCovidTicket, fileIO) { 
	   nextCovidTicket++;
   }

   char CovidPatient::type()const {
	   return 'C';
   }
   std::istream& CovidPatient::csvRead(std::istream& istr) {
	   Patient::csvRead(istr);
	   nextCovidTicket = Patient::number() + 1;
	   istr.ignore(1000, '\n');
	   return istr;
   }
   std::ostream& CovidPatient::write(std::ostream& ostr)const {
	   if (Patient::fileIO())
	   {
		   Patient::csvWrite(ostr);
	   }
	   else
	   {
		   ostr << "COVID TEST" << std::endl;
		   Patient::write(ostr);
		   ostr << std::endl;
	   }
	   return ostr;
   }
   std::istream& CovidPatient::read(std::istream& istr) {
	   if (Patient::fileIO())
	   {
		   csvRead(istr);
	   }
	   else
	   {
		   Patient::read(istr);
	   }
	   return istr;
   }
}