/**********************************************************
 * Name: Xuewei Sheng
 * Student ID: 061745121
 * Seneca email: xsheng3@myseneca.ca
 * Section: NFF
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include<iostream>
#include <fstream>
#include"PreTriage.h"
#include"Ticket.h"
#include"TriagePatient.h"
#include"CovidPatient.h"
#include"utils.h"

using namespace std;
namespace sdds {
    void PreTriage::reg() {
        if (m_lineupSize >= maxNoOfPatients)
        {
            cout << "Line up full!" << endl;
        }
        else
        {
            int selection;
            if (m_pMenu >> selection) 
            {
                if (selection == 1)
                {
                    m_lineup[m_lineupSize] = new CovidPatient();
                }
                else if (selection == 2)
                {
                    m_lineup[m_lineupSize] = new TriagePatient();
                }
                m_lineup[m_lineupSize]->setArrivalTime();
                m_lineup[m_lineupSize]->fileIO(false);
                cout << "Please enter patient information: " << endl;
                m_lineup[m_lineupSize]->read(cin);
                cout << endl << "******************************************" << endl;
                m_lineup[m_lineupSize]->write(cout);
                cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]);
                cout << endl << "******************************************" << endl << endl;
                m_lineupSize++;
            }
        }

    }
    void PreTriage::admit() {
        int selection = 0, idx = 0;
        
        if (m_pMenu >> selection)
        {
            if (selection == 1)
            {
                
                idx = indexOfFirstInLine('C');
            }
            else if (selection == 2)
            {
              
                idx = indexOfFirstInLine('T');
            }
            cout << endl << "******************************************" << endl;
            m_lineup[idx]->fileIO(false);
            cout << "Calling for ";
            m_lineup[idx]->write(cout);
            cout << "******************************************" << endl << endl;
            setAverageWaitTime(*m_lineup[idx]);
            removeDynamicElement(m_lineup, idx, m_lineupSize);
        }
    }
    const Time PreTriage::getWaitTime(const Patient& p)const {
        char type = p.type();
        unsigned int patientNo = 0;
        Time averWait = type == 'C' ? m_averCovidWait : m_averTriageWait;
        for (int i = 0; i < m_lineupSize; i++)
        {
            if (m_lineup[i]->type() == type)
            {
                patientNo++;
            }
            i++;
        }
        Time waitTime = averWait* patientNo;
        return waitTime;
    }
    void PreTriage::setAverageWaitTime(const Patient& p) {
        Time CT;
        unsigned PTN = p.number();
        char type = p.type();
        if (type == 'C')
        {
            m_averCovidWait = ((CT.setToNow() - p.operator Time()) + (m_averCovidWait * (PTN - 1))) / PTN;
        }
        else
        {
            m_averTriageWait = ((CT.setToNow() - p.operator Time()) + (m_averTriageWait * (PTN - 1))) / PTN;
        }
    }
    void PreTriage::removePatientFromLineup(int index) {
        removeDynamicElement(m_lineup, index, m_lineupSize);
    }
    int PreTriage::indexOfFirstInLine(char type) const {
        bool found = false;
        int idx = 0;
        for (int i = 0; i < m_lineupSize && found == false; i++)
        {
            if (m_lineup[i]->type() == type)
            {
                idx = i;
                found = true;
            }
        }
        return idx;
    }
    void PreTriage::load() {
        cout << "Loading data..." << endl;
        ifstream fin(m_dataFilename);
        fin >> m_averCovidWait;
        fin.ignore();
        fin >> m_averTriageWait;
        fin.ignore(1000, '\n');
        Patient* p = nullptr;
        for (int i = 0; i < maxNoOfPatients && fin; i++)
        {
            char type = fin.get();
            if (type == 'C')
            {
                p = new CovidPatient();
            }
            else if(type == 'T')
            {
                p = new TriagePatient();
            }
            if (p)
            {
                fin.ignore();
                p->fileIO(true);
                fin >> *p;
                p->fileIO(false);
                m_lineup[i] = p;
                m_lineupSize++;
                p = nullptr;
                delete p;
            }
        }

        if (fin) 
        {
            cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
        }
        if (m_lineupSize == 0)
        {
            cout << "No data or bad data file!" << endl<< endl;
        }
        else
        {
            cout << m_lineupSize  << " Records imported..." << endl << endl;
        }
    }

    PreTriage::PreTriage(const char* dataFilename) :m_averCovidWait(15),
    m_averTriageWait(5), m_appMenu{ "General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2 }, m_pMenu{ "Select Type of Admittance:\n1- Covid Test\n2- Triage", 2 } {
        
        if (dataFilename)
        {
            m_dataFilename = new char[strlen(dataFilename) + 1];
            strcpy(m_dataFilename, dataFilename);
        }
        else m_dataFilename = nullptr;
        load();
    }

    PreTriage::~PreTriage() {
    //The data file is opened for output, overwriting the content of the file if it already exists.
    //The average COVID wait timeand the average Triage wait time is written in the first line of the file, comma - separated and also on the screen
    //All the patients are written into the file, comma - separated in individual lines.
    // Simultaneously the patient records are printed on the screen(comma separated) with a row number.
        cout << "Saving Average Wait Times," << endl;
        ofstream fout(m_dataFilename);
        fout << m_averCovidWait << ',' << m_averTriageWait << endl;
        cout << "   COVID Test: " << m_averCovidWait << endl;
        cout << "   Triage: " << m_averTriageWait << endl;

        cout << "Saving m_lineup..." << endl;
        for (int i = 0; i < m_lineupSize; i++)
        {
            m_lineup[i]->csvWrite(fout);
            //if (m_lineup[i]->type() == 'T')
            //{
                
            //}
            fout << endl;
            cout << i + 1 << "- ";
            m_lineup[i]->csvWrite(cout);
            cout << endl;
        }


        //delete [] m_lineup;
        for (int i = 0; i < m_lineupSize; i++)
        {
            delete m_lineup[i];
        }
        delete[] m_dataFilename;
        m_dataFilename = nullptr;
        cout << "done!" << endl;
    }
    void PreTriage::run(void) {
        int selection = 0;
        while (m_appMenu >> selection)
        {
            if (selection == 1)
            {
                reg();
            }
            else if (selection == 2)
            {
                admit();
            }
        }       
    }
}