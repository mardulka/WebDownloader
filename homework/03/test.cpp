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


#ifndef __PROGTEST__

int main(void){
    ostringstream oss;
    istringstream iss;

    CDate a(2000, 1, 2);
    CDate b(2010, 2, 3);
    CDate c(2004, 2, 10);
    oss.str("");
    oss << a;
    assert (oss.str() == "2000-01-02");
    oss.str("");
    oss << b;
    assert (oss.str() == "2010-02-03");
    oss.str("");
    oss << c;
    assert (oss.str() == "2004-02-10");
    a = a + 1500;
    oss.str("");
    oss << a;
    assert (oss.str() == "2004-02-10");
    b = b - 2000;
    oss.str("");
    oss << b;
    assert (oss.str() == "2004-08-13");
    assert (b - a == 185);
    assert ((b == a) == false);
    assert ((b != a) == true);
    assert ((b <= a) == false);
    assert ((b < a) == false);
    assert ((b >= a) == true);
    assert ((b > a) == true);
    assert ((c == a) == true);
    assert ((c != a) == false);
    assert ((c <= a) == true);
    assert ((c < a) == false);
    assert ((c >= a) == true);
    assert ((c > a) == false);
    a = ++c;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-11 2004-02-11");
    a = --c;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-10 2004-02-10");
    a = c++;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-10 2004-02-11");
    a = c--;
    oss.str("");
    oss << a << " " << c;
    assert (oss.str() == "2004-02-11 2004-02-10");
    iss.clear();
    iss.str("2015-09-03");
    assert ((iss >> a));
    oss.str("");
    oss << a;
    assert (oss.str() == "2015-09-03");
    a = a + 70;
    oss.str("");
    oss << a;
    assert (oss.str() == "2015-11-12");

    CDate d(2000, 1, 1);
    try{
        CDate e(2000, 32, 1);
        assert ("No exception thrown!" == nullptr);
    }
    catch (...){
    }
    iss.clear();
    iss.str("2000-12-33");
    assert (!(iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-01-01");
    iss.clear();
    iss.str("2000-11-31");
    assert (!(iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-01-01");
    iss.clear();
    iss.str("2000-02-29");
    assert ((iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-02-29");
    iss.clear();
    iss.str("2001-02-29");
    assert (!(iss >> d));
    oss.str("");
    oss << d;
    assert (oss.str() == "2000-02-29");


    //-----------------------------------------------------------------------------
    // progtest errors check
    //-----------------------------------------------------------------------------

    CDate zz(2004, 03, 1);
    zz = --zz;
    oss.str("");
    oss << zz;
    assert (oss.str() == "2004-02-29");

    //-----------------------------------------------------------------------------
    // bonus test examples
    //-----------------------------------------------------------------------------
    CDate f(2000, 5, 12);
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    oss.str("");
    oss << date_format("%Y/%m/%d") << f;
    assert (oss.str() == "2000/05/12");
    oss.str("");
    oss << date_format("%d.%m.%Y") << f;
    assert (oss.str() == "12.05.2000");
    oss.str("");
    oss << date_format("%m/%d/%Y") << f;
    assert (oss.str() == "05/12/2000");
    oss.str("");
    oss << date_format("%Y%m%d") << f;
    assert (oss.str() == "20000512");
    oss.str("");
    oss << date_format("hello kitty") << f;
    assert (oss.str() == "hello kitty");
    oss.str("");
    oss << date_format("%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%") << f;
    assert (oss.str() == "121212121212050505200020002000%%%%%");
    oss.str("");
    oss << date_format("%Y-%m-%d") << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-01-1");
    assert (!(iss >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-1-01");
    assert (!(iss >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-001-01");
    assert (!(iss >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-01-02");
    assert ((iss >> date_format("%Y-%m-%d") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2001-01-02");
    iss.clear();
    iss.str("05.06.2003");
    assert ((iss >> date_format("%d.%m.%Y") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2003-06-05");
    iss.clear();
    iss.str("07/08/2004");
    assert ((iss >> date_format("%m/%d/%Y") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2004-07-08");
    iss.clear();
    iss.str("2002*03*04");
    assert ((iss >> date_format("%Y*%m*%d") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2002-03-04");
    iss.clear();
    iss.str("C++09format10PA22006rulez");
    assert ((iss >> date_format("C++%mformat%dPA2%Yrulez") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2006-09-10");
    iss.clear();
    iss.str("%12%13%2010%");
    assert ((iss >> date_format("%%%m%%%d%%%Y%%") >> f));
    oss.str("");
    oss << f;
    assert (oss.str() == "2010-12-13");

    CDate g(2000, 6, 8);
    iss.clear();
    iss.str("2001-11-33");
    assert (!(iss >> date_format("%Y-%m-%d") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("29.02.2003");
    assert (!(iss >> date_format("%d.%m.%Y") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("14/02/2004");
    assert (!(iss >> date_format("%m/%d/%Y") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("2002-03");
    assert (!(iss >> date_format("%Y-%m") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("hello kitty");
    assert (!(iss >> date_format("hello kitty") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("2005-07-12-07");
    assert (!(iss >> date_format("%Y-%m-%d-%m") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("20000101");
    assert ((iss >> date_format("%Y%m%d") >> g));
    oss.str("");
    oss << g;
    assert (oss.str() == "2000-01-01");

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
