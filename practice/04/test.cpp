#ifndef __PROGTEST__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>

using namespace std;
#endif /* __PROGTEST__ */

/**
 * Class storing simple timestamp
 */
struct CTimeStamp{
    int year, month, day, hour, min, sec;
    time_t julianTime;

    CTimeStamp(int year, int month, int day, int hour, int min, int sec)
            : year{year}, month{month}, day{day}, hour{hour}, min{min}, sec{sec}{
        tm time = {};
        time.tm_sec = sec;
        time.tm_min = min;
        time.tm_hour = hour;
        time.tm_mday = day;
        time.tm_mon = month - 1;
        time.tm_year = year - 1900;
        julianTime = mktime(&time);
    }

    bool isBetween(const CTimeStamp & from, const CTimeStamp & until) const{
        if (julianTime >= from.julianTime && julianTime <= until.julianTime)
            return true;
        return false;
    }

};

/**
 * Class storing contact - timestamp and two telephone numbers
 */
class CContact{
    CTimeStamp timestamp;
    int con1;
    int con2;

public:
    CContact(CTimeStamp timestamp, int tel1, int tel2)
            : timestamp{timestamp}, con1{tel1}, con2{tel2}{}

    /**
     * Returning opposite number from given, unless they are same, or neither of them is same as the given one.
     *
     * @param tel Phone number of ill person.
     * @param ret Returning value of his contact.
     * @return True if is valid returning number. False if ret is not valid and should be skipped.
     */
    bool printOpposite(int tel, int & ret) const{
        if (con1 == con2) return false;
        if (con1 == tel){
            ret = con2;
            return true;
        }
        if (con2 == tel){
            ret = con1;
            return true;
        }
        return false;
    }

    /**
     * Returning opposite number from given, unless they are same, or neither of them is same as the given one.
     *
     * @param tel Phone number of ill person.
     * @param ret Returning value of his contact.
     * @param from start of time interval
     * @param until end of time interval
     * @return True if is valid returning number. False if ret is not valid and should be skipped.
     */
    bool printOpposite(int tel, int & ret, const CTimeStamp & from, const CTimeStamp & until) const{
        if (con1 == con2 || !timestamp.isBetween(from, until)) return false;
        if (con1 == tel){
            ret = con2;
            return true;
        }
        if (con2 == tel){
            ret = con1;
            return true;
        }
        return false;
    }


};

/**
 * Class storing all contacts
 */
class CEFaceMask{

    vector<CContact> storage;

public:
    CEFaceMask & addContact(CContact contact){
        storage.push_back(contact);
        return *this;
    }

    bool alreadyPresent(const vector<int> & vector, const int & tel) const{
        return any_of(vector.cbegin(), vector.cend(), [tel](int i){return i == tel;});
    }

    auto listContacts(int tel) const{
        vector<int> result;

        for (auto contact: storage){
            int tel2;
            if (contact.printOpposite(tel, tel2) && !alreadyPresent(result, tel2)){
                result.push_back(tel2);
            }
        }
        return result;
    }

    auto listContacts(int tel, const CTimeStamp & from, const CTimeStamp & until) const{
        vector<int> result;
        for (auto contact: storage){
            int tel2;
            if (contact.printOpposite(tel, tel2, from, until) && !alreadyPresent(result, tel2)){
                result.push_back(tel2);
            }
        }

        return result;
    }

};

#ifndef __PROGTEST__

    int main(){
        CEFaceMask test;

        test.addContact(CContact(CTimeStamp(2021, 1, 10, 12, 40, 10), 123456789, 999888777));
        test.addContact(CContact(CTimeStamp(2021, 1, 12, 12, 40, 10), 123456789, 111222333))
                .addContact(CContact(CTimeStamp(2021, 2, 5, 15, 30, 28), 999888777, 555000222));
        test.addContact(CContact(CTimeStamp(2021, 2, 21, 18, 0, 0), 123456789, 999888777));
        test.addContact(CContact(CTimeStamp(2021, 1, 5, 18, 0, 0), 123456789, 456456456));
        test.addContact(CContact(CTimeStamp(2021, 2, 1, 0, 0, 0), 123456789, 123456789));
        assert (test.listContacts(123456789) == (vector<int>{999888777, 111222333, 456456456}));
        assert (test.listContacts(999888777) == (vector<int>{123456789, 555000222}));
        assert (test.listContacts(191919191) == (vector<int>{}));
        assert (test.listContacts(123456789, CTimeStamp(2021, 1, 5, 18, 0, 0), CTimeStamp(2021, 2, 21, 18, 0, 0)) ==
                (vector<int>{999888777, 111222333, 456456456}));
        assert (test.listContacts(123456789, CTimeStamp(2021, 1, 5, 18, 0, 1), CTimeStamp(2021, 2, 21, 17, 59, 59)) ==
                (vector<int>{999888777, 111222333}));
        assert (test.listContacts(123456789, CTimeStamp(2021, 1, 10, 12, 41, 9), CTimeStamp(2021, 2, 21, 17, 59, 59)) ==
                (vector<int>{111222333}));
        return 0;
    }

#endif /* __PROGTEST__ */
