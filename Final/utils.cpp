/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = false;  // made global in utils.h
   int getTime() {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invlid time, try agian (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   
   int getInt(const char* prompt) {
       int integer = 0;
       bool valid = true;
       if (prompt)
           cout << prompt;
       do {
           valid = true;
           cin >> integer;
           if (cin.fail())
           {
               cout << "Bad integer value, try again: ";
               cin.clear();
               cin.ignore(1000, '\n');
               valid = false;
           }
           else
           {
               if (cin.get() != '\n')
               {
                   cout << "Enter only an integer, try again: ";
                   cin.clear();
                   cin.ignore(1000, '\n');
                   valid = false;
               }
           }
       } while (!valid);
       return integer;       
   }

   int getInt(int min, int max, const char* prompt, const char*errorMessage,bool showRangeAtError) {
       int intInRange = 0;
       intInRange = getInt(prompt);
       while (intInRange < min || intInRange > max)
       {
           if (errorMessage)
           {
               if(showRangeAtError)
                   cout << errorMessage << "[" << min << " <= value <= "<<max << "]: ";
               else
                   cout << errorMessage;
           }
           intInRange = getInt();            
       }
       return intInRange;
   }
   

   char* getcstr(const char* prompt, std::istream& istr, char delimiter) {
       string str;
       char* content;

       if (prompt)
           cout << prompt;
       getline(cin, str, delimiter);
       content = new char[str.length() + 1];
       strcpy(content, str.c_str());
       return content;
   }
   
}