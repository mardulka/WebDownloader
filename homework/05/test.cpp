#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

/**
 * Class wrapping date and all methods for it.
 */
class CDate{
    int year;
    int month;
    int day;
public:
    CDate(int year, int month, int day) : year(year), month(month), day(day){}

    bool operator ==(const CDate & date) const;
    bool operator >(const CDate & date) const;
    bool operator <(const CDate & date) const;
    bool operator >=(const CDate & date) const;
    bool operator <=(const CDate & date) const;

};

bool CDate::operator ==(const CDate & date) const{
    if (year == date.year && month == date.month && day == date.month)
        return true;
    return false;
}

bool CDate::operator >(const CDate & date) const{
    if (year > date.year)
        return true;
    if (year < date.year)
        return false;
    //year == date.year
    if (month > date.month)
        return true;
    if (month < date.month)
        return false;
    //month == date.month
    if (day > date.day)
        return true;
    //day<=date.day
    return false;
}

bool CDate::operator <(const CDate & date) const{
    if (year < date.year)
        return true;
    if (year > date.year)
        return false;
    //year == date.year
    if (month < date.month)
        return true;
    if (month > date.month)
        return false;
    //month == date.month
    if (day < date.day)
        return true;
    //day>=date.day
    return false;

}

bool CDate::operator >=(const CDate & date) const{
    if (*this > date || *this == date)
        return true;
    return false;
}

bool CDate::operator <=(const CDate & date) const{
    if (*this < date || *this == date)
        return true;
    return false;
}

/**
 * Class wrapping Supermarket storage and methods for work with Wares.
 */
class CSupermarket{
public:
    /**
     * Default constructor to initialize stock, destructor for its deleting.
     */
    CSupermarket() = default;
    ~CSupermarket() = default;

    /**
     * Deleted copy and move constructors - our Supermarket is unique and nobody is allowed to make its copy od even move it elsewhere.
     */
    CSupermarket(CSupermarket & old) = delete;
    CSupermarket(CSupermarket && old) = delete;

    /**
     * Interface method (name and parameters must stay as are).
     * Provides functionality for storing one supply of one ware.
     * @param string Name of ware
     * @param date Date class represents expiration date of this supply.
     * @param count Amount in this supply
     * @return Reference to Supermarket stock
     */
    CSupermarket & store(const char * string, CDate date, int count);

    /**
     * Interface method (name and parameters must stay as are).
     * Provides functionality for selling ware - decreases count of oll ware of shopping list from oldest ones.
     * @param shoppingList list of pairs name-count like in ordinary shopping lists.
     */
    void sell(list<pair<string, int>> & shoppingList);

    /**
     * Interface method (name and parameters must stay as are).
     * Provides functionality for getting list of all ware which would expired before given date.
     * @param date Date class represents expiration date for this check.
     * @return list of pairs name-count for all will-expired ware
     */
    list<pair<string, int> > expired(CDate date) const;

private:

    struct CWare;
    map<string, deque<shared_ptr<CWare>>> m_stock;

    /**
     * Finds ware section in stock. If
     * @param name Name of ware section which is wanted.
     * @return Optional value of Reference to ware section. Reference to end of stock if is not present.
     */
    optional<reference_wrapper<deque<shared_ptr<CSupermarket::CWare>>>> findWareSection(string name);

    /**
     * Adds new supply amount into stock.
     * @param queue Reference to section for this ware.
     * @param ware Ware which has to be stored. Expected shared pointer.
     */
    void addStock(deque<shared_ptr<CWare>> & section, shared_ptr<CWare> ware);

    /**
     * Adds new ware category into stock. Creates new section and call common method for storing ware into this section.
     * @param ware Ware which has to be stored.
     */
    void registerNewWare(shared_ptr<CWare> ware);

    /**
     * Removes specific count of ware from defined stock section.
     * @param section Section from the ware should be released.
     * @param count Number of ware which should be released.
     * @return How much was really released. Important if in stock is not enough count.
     */
    int releaseStock(deque<shared_ptr<CWare>> & section, int count);

};

struct CSupermarket::CWare{
    string name;
    CDate expDate;
    int cnt;

    CWare(const string & name, const CDate & exp_date, int cnt) : name{name}, expDate{exp_date}, cnt{cnt}{}

    bool operator <(const CWare & rhs) const{
        return expDate < rhs.expDate;
    }

    bool operator >(const CWare & rhs) const{
        return rhs < *this;
    }

    bool operator <=(const CWare & rhs) const{
        return !(rhs < *this);
    }

    bool operator >=(const CWare & rhs) const{
        return !(*this < rhs);
    }
};

CSupermarket & CSupermarket::store(const char * name, CDate expiryDate, int count){
    //create object for new ware
    auto newWare = make_shared<CWare>(string(name), expiryDate, count);
    //find in map and add count- if not present create new record
    auto wareSection = findWareSection(name);
    if (wareSection.has_value()){
        addStock(wareSection.value(), newWare);
    } else{
        registerNewWare(newWare);
    }
    return *this;
}

void CSupermarket::sell(list<pair<string, int>> & shoppingList){
    // find all and check if exists
    list<optional<reference_wrapper<deque<shared_ptr<CSupermarket::CWare>>>>> invoice;
    for (const auto & record: shoppingList){
        invoice.emplace_back(findWareSection(record.first));
    }

    //modify counts ind storage and list
    auto shopList_it = shoppingList.begin();
    auto invoice_it = invoice.begin();
    for (; shopList_it != shoppingList.end() ; ++shopList_it, ++invoice_it){
        if (!invoice_it->has_value())
            continue;
        int released = releaseStock(invoice_it->value(), shopList_it->second);
        shopList_it->second -= released;
    }

    //delete items from list if they was all released (cnt = 0)
    for (auto it = shoppingList.begin() ; it != shoppingList.end() ;){
        if (it->second == 0)
            it = shoppingList.erase(it);
        else
            ++it;
    }


}

list<pair<string, int> > CSupermarket::expired(CDate date) const{
    list<pair<string, int>> moldWare;
    for (const auto & record: m_stock){
        int count = 0;
        for (const auto & ware: record.second){
            if (ware->expDate > date)
                break;
            count += ware->cnt;
        }
        moldWare.emplace_back(record.first, count);
    }

    moldWare.sort([](pair<string, int> & left, pair<string, int> & right){return left.second > right.second;});
    return moldWare;
}

optional<reference_wrapper<deque<shared_ptr<CSupermarket::CWare>>>> CSupermarket::findWareSection(string name){
    auto it = m_stock.find(name);
    if (it == m_stock.end()){
        return nullopt;
    }
    return it->second;
}

void CSupermarket::addStock(deque<shared_ptr<CWare>> & section, shared_ptr<CWare> ware){
    //iterate through deque, if
    auto iter = section.begin();
    for (auto & record: section){

        if (record->expDate == ware->expDate){
            record->cnt += ware->cnt;
            return;
        }
        if (record->expDate > ware->expDate){
            section.emplace(iter, ware);
            return;
        }
        ++iter;
    }

    //if empty
    section.push_back(ware);

}

void CSupermarket::registerNewWare(shared_ptr<CWare> ware){
    // create shelf with label into store directly
    const auto[it, success] = m_stock.emplace(ware->name, deque<shared_ptr<CWare>>());
    // add ware into new shelf
    addStock(it->second, ware);

}

int CSupermarket::releaseStock(deque<shared_ptr<CWare>> & section, int count){
    int released = 0;
    string name = section.front()->name;
    while (count > 0 && !section.empty()){
        //access to oldest (first in front)
        auto shelf = section.front();
        //check if shelf has more pieces than requested -> if so, no problem, only decrease count
        if (shelf->cnt > count){
            shelf->cnt -= count;
            released += count;
            break;
        } else if (shelf->cnt == count){
            //exactly same number as requireq -> take all and clean shelf
            released += shelf->cnt;
            section.pop_front();
            break;
        } else{
            //not enough in this shelf, clean this shelf (pop) and decrease requested count, then go to next by the loop
            count -= shelf->cnt;
            released += shelf->cnt;
            section.pop_front();
        }
    }

    if (section.empty()){
        m_stock.erase(name);
    }

    return released;
}

