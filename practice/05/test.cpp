#ifndef __PROGTEST__

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

class CTimeTester;

#endif /* __PROGTEST__ */

class CTime{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;

public:

    // constructor, destructor
    CTime(int hour, int minute, int second);

    CTime(int hour, int minute);

    virtual ~CTime() = default;

    // arithmetic operators
    CTime operator +(int add);
    CTime operator -(int sub);
    CTime & operator ++();
    CTime operator ++(int);
    CTime & operator --();
    CTime operator --(int);

    int operator -(CTime & sub) const;

    // comparison operators
    bool operator ==(const CTime & rhs) const;
    bool operator !=(const CTime & rhs) const;
    bool operator <(const CTime & rhs) const;
    bool operator >(const CTime & rhs) const;
    bool operator <=(const CTime & rhs) const;
    bool operator >=(const CTime & rhs) const;

    // output operator
    friend ostream & operator <<(ostream & out, const CTime & time);

    friend class ::CTimeTester;
};

CTime::CTime(int hours, int minutes, int seconds) : m_Hour(hours), m_Minute(minutes), m_Second(seconds){
    if (hours < 0 || hours > 23)
        throw invalid_argument("Hours number is not valid!"s);
    if (minutes < 0 || minutes > 59)
        throw invalid_argument("Minutes number is not valid!"s);
    if (seconds < 0 || seconds > 59)
        throw invalid_argument("Seconds number is not valid!"s);
}

CTime::CTime(int hours, int minutes) : CTime(hours, minutes, 0){}

CTime CTime::operator +(int add){
    int seconds = m_Second + (add % 60);
    add /= 60;
    int minutes = m_Minute + (add % 60);
    int hours = m_Hour + (add / 60);
    return {hours, minutes, seconds};
}

CTime CTime::operator -(int sub){
    return operator +(-sub);
}

CTime & CTime::operator ++(){
    m_Second++;
    if (m_Second / 60 > 0){
        m_Minute += m_Second / 60;
        m_Second %= 60;
    }
    if (m_Minute / 60 > 0){
        m_Hour += m_Minute / 60;
        m_Minute %= 60;
        m_Hour %= 24;
    }

    return *this;
}

CTime CTime::operator ++(int){
    const CTime tmp = *this;
    ++(*this);
    return tmp;
}

CTime & CTime::operator --(){
    m_Second--;
    if (m_Second < 0){
        m_Second %= 60;
        --m_Minute;
    }
    if (m_Minute < 0){
        m_Minute %= 60;
        (--m_Hour);
        m_Hour %= 24;
    }

    return *this;
}

CTime CTime::operator --(int){
    const CTime tmp = *this;
    --(*this);
    return tmp;
}

int CTime::operator -(CTime & sub) const{
    return (m_Second - sub.m_Second) + 60 * (m_Minute - sub.m_Minute + 60 * (m_Hour - sub.m_Hour));
}

bool CTime::operator ==(const CTime & rhs) const{
    return m_Hour == rhs.m_Hour &&
           m_Minute == rhs.m_Minute &&
           m_Second == rhs.m_Second;
}

bool CTime::operator !=(const CTime & rhs) const{
    return !(rhs == *this);
}

bool CTime::operator <(const CTime & rhs) const{
    if (m_Hour < rhs.m_Hour)
        return true;
    if (rhs.m_Hour < m_Hour)
        return false;
    if (m_Minute < rhs.m_Minute)
        return true;
    if (rhs.m_Minute < m_Minute)
        return false;
    return m_Second < rhs.m_Second;
}

bool CTime::operator >(const CTime & rhs) const{
    return rhs < *this;
}

bool CTime::operator <=(const CTime & rhs) const{
    return !(rhs < *this);
}

bool CTime::operator >=(const CTime & rhs) const{
    return !(*this < rhs);
}

ostream & operator <<(ostream & out, const CTime & time){
    return out << setw(2) << time.m_Hour << ":"s << setfill('0') << setw(2) << time.m_Minute << ":"s << setw(2)
               << time.m_Second;
}

#ifndef __PROGTEST__

struct CTimeTester{
    static bool test(const CTime & time, int hour, int minute, int second){
        return time.m_Hour == hour
               && time.m_Minute == minute
               && time.m_Second == second;
    }
};


#include <cassert>
#include <sstream>

int main(){
    CTime a{12, 30};
    assert(CTimeTester::test(a, 12, 30, 0));

    CTime b{13, 30};
    assert(CTimeTester::test(b, 13, 30, 0));

    assert(b - a == 3600);

    assert(CTimeTester::test(a + 60, 12, 31, 0));
    assert(CTimeTester::test(a - 60, 12, 29, 0));

    assert(a < b);
    assert(a <= b);
    assert(a != b);
    assert(!(a > b));
    assert(!(a >= b));
    assert(!(a == b));

    while (++a != b);
    assert(a == b);

    std::ostringstream output;
    assert(static_cast<bool>( output << a ));
    assert(output.str() == "13:30:00");

    assert(a++ == b++);
    assert(a == b);

    assert(--a == --b);
    assert(a == b);

    assert(a-- == b--);
    assert(a == b);

    return 0;
}

#endif /* __PROGTEST__ */
