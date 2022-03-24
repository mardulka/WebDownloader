#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument{
public:
    InvalidDateException()
            : invalid_argument("invalid date or format"){
    }
};

//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format([[maybe_unused]]const char * fmt))(ios_base & x){
    return [](ios_base & ios) -> ios_base &{return ios;};
}

//=================================================================================================
class CDate{
    int m_day;
    int m_mon;
    int m_year;
    bool m_step_year = false;
    int m_day_count = 0;

    constexpr static int m_mon_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    constexpr static int year_days = 365;

public:

    CDate();
    CDate(int year, int mon, int day);
    CDate(const CDate & date) = default;
    CDate(CDate && date) = default;
    ~CDate() = default;
    CDate & operator =(const CDate & date) = default;
    CDate & operator =(CDate && date) = default;

    static bool isValidDate(int year, int mon, int day);
    static bool isStepYear(int year);

    void dateToCount();
    void countToDate();
    CDate operator +(int days) const;
    CDate operator -(int days) const;
    int operator -(const CDate & date) const;
    CDate operator ++();
    CDate operator --();
    CDate operator ++(int);
    CDate operator --(int);
    bool operator ==(const CDate & date) const;
    bool operator !=(const CDate & date) const;
    bool operator >(const CDate & date) const;
    bool operator >=(const CDate & date) const;
    bool operator <(const CDate & date) const;
    bool operator <=(const CDate & date) const;
    friend istream & operator >>(istream & in, CDate & date);
    friend ostream & operator <<(ostream & out, const CDate & date);

};

CDate::CDate(){
    m_day = 1;
    m_mon = 1;
    m_year = 2000;
    m_day_count = 1;
    m_step_year = true;
}

CDate::CDate(int year, int mon, int day){
    if (!isValidDate(year, mon, day))
        throw InvalidDateException();

    m_year = year;
    m_mon = mon;
    m_day = day;
    m_step_year = isStepYear(year);
    dateToCount();
}

bool CDate::isStepYear(int year){
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

bool CDate::isValidDate(int year, int mon, int day){
    if (year < 2000 || year > 2030 || mon < 1 || mon > 12 || day < 1)
        return false;
    if (mon == 2){
        bool step = isStepYear(year);
        auto checkmon = m_mon_days[mon - 1];
        if (step) ++checkmon;
        if (day > checkmon) return false;
    }
    if (mon != 2 && day > m_mon_days[mon - 1])
        return false;

    return true;
}

void CDate::dateToCount(){
    int passed_years = 0;
    int passed_months = 0;
    for (int i = 2000 ; i < m_year ; ++i){
        passed_years += year_days;
        if (isStepYear(i)) ++passed_years;
    }
    for (int i = 0 ; i < m_mon ; ++i){
        passed_months += m_mon_days[i - 1];
    }

    if (isStepYear(m_year) && m_mon > 2) ++passed_months;

    m_day_count = passed_years + passed_months + m_day;
}

void CDate::countToDate(){
    int count = m_day_count;
    int year = 2000;
    int mon = 1;

    while (true){
        int days = year_days;
        if (isStepYear(year)) ++days;
        if (count <= days) break;
        ++year;
        count -= days;
    }

    while (true){
        int days = m_mon_days[mon - 1];
        if (isStepYear(year) && mon == 2)
            ++days;
        if (count <= days)
            break;
        ++mon;
        count -= days;
    }

    m_year = year;
    m_mon = mon;
    m_day = count;
}

CDate CDate::operator +(int days) const{
    CDate date;
    date.m_day_count = this->m_day_count + days;
    date.countToDate();
    return date;
}

CDate CDate::operator -(int days) const{
    CDate date;
    date.m_day_count = this->m_day_count - days;
    date.countToDate();
    return date;
}

int CDate::operator -(const CDate & date) const{
    return m_day_count - date.m_day_count;
}

CDate CDate::operator ++(){
    ++m_day_count;
    countToDate();
    return *this;
}

CDate CDate::operator --(){
    --m_day_count;
    countToDate();
    return *this;
}

CDate CDate::operator ++(int){
    auto date = *this;
    ++m_day_count;
    countToDate();
    return date;
}

CDate CDate::operator --(int){
    auto date = *this;
    --m_day_count;
    countToDate();
    return date;
}

bool CDate::operator ==(const CDate & date) const{
    if (m_day_count == date.m_day_count) return true;
    return false;
}

bool CDate::operator !=(const CDate & date) const{
    if (m_day_count != date.m_day_count) return true;
    return false;
}

bool CDate::operator >(const CDate & date) const{
    if (m_day_count > date.m_day_count) return true;
    return false;
}

bool CDate::operator >=(const CDate & date) const{
    if (m_day_count >= date.m_day_count) return true;
    return false;
}

bool CDate::operator <(const CDate & date) const{
    if (m_day_count < date.m_day_count) return true;
    return false;
}

bool CDate::operator <=(const CDate & date) const{
    if (m_day_count <= date.m_day_count) return true;
    return false;
}

istream & operator >>(istream & in, CDate & date){
    int year, mon, day;
    char delimiter;
    in >> year >> delimiter >> mon >> delimiter >> day;

    if (!CDate::isValidDate(year, mon, day)){
        in.setstate(ios::failbit);
        return in;
    }

    date.m_day = day;
    date.m_mon = mon;
    date.m_year = year;
    date.m_step_year = CDate::isStepYear(year);
    date.dateToCount();

    return in;
}

ostream & operator <<(ostream & out, const CDate & date){
    char delimiter = '-';
    return out << setfill('0')
               << setw(4) << date.m_year
               << setw(1) << delimiter
               << setw(2) << date.m_mon
               << setw(1) << delimiter
               << setw(2) << date.m_day;
}
