#ifndef __PROGTEST__

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdint>
#include <cctype>
#include <cassert>

using namespace std;
#endif /* __PROGTEST__ */

template<typename T_>
class CSet{
private:
    struct SItem{
        T_ m_value;
        SItem * m_next;
        SItem * m_prev;

        SItem(T_ value) : m_value(value), m_next(nullptr), m_prev(nullptr){}
    };

    SItem * m_head;
    SItem * m_last;
    size_t m_size;


public:
    // default constructor
    CSet() : m_head(nullptr), m_last(nullptr), m_size(0){}

    // copy constructor
    CSet(CSet & src) : CSet(){
        SItem * current = src.m_head;
        while (current){
            Insert(current->m_value);
            current = current->m_next;
        }
    }

    // operator=
    CSet & operator =(CSet src){
        swap(m_size, src.m_size);
        swap(m_last, src.m_last);
        swap(m_head, src.m_head);

        return *this;
    }

    // destructor
    virtual ~CSet(){
        SItem * current = m_head;
        while (current){
            SItem * tmp = current->m_next;
            delete current;
            current = tmp;
        }
    }

    // Insert
    bool Insert(T_ value){
        if (Contains(value))
            return false;

        if (m_size == 0){
            m_head = new SItem(value);
            m_last = m_head;
        } else{
            m_last->m_next = new SItem(value);
            m_last->m_next->m_prev = m_last;
            m_last = m_last->m_next;
        }

        ++m_size;
        return true;
    }

    // Remove
    bool Remove(T_ value){
        SItem * current = m_head;
        while (current){
            if (current->m_value < value || value < current->m_value)
                current = current->m_next;
            else
                break;
        }

        if (current == nullptr)
            return false;

        if (current->m_prev)
            current->m_prev->m_next = current->m_next;
        if (current->m_next)
            current->m_next->m_prev = current->m_prev;
        if (m_head == current)
            m_head = current->m_next;
        if (m_last == current)
            m_last = current->m_prev;
        delete current;
        --m_size;
        return true;
    }

    // Contains
    [[nodiscard]] bool Contains(T_ value) const{
        SItem * current = m_head;
        while (current){
            if (current->m_value < value || value < current->m_value)
                current = current->m_next;
            else
                return true;
        }

        return false;
    }

    // Size
    [[nodiscard]] size_t Size() const{
        return m_size;
    }
};

#ifndef __PROGTEST__

#include <cassert>

struct CSetTester{
    static void test0(){
        CSet<string> x0;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
    }

    static void test1(){
        CSet<string> x0;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
        CSet<string> x1(x0);
        assert(x0.Insert("Vodickova Saskie"));
        assert(x1.Insert("Kadlecova Kvetslava"));
        assert(x0.Size() == 3);
        assert(x1.Size() == 3);
        assert(x0.Contains("Vodickova Saskie"));
        assert(!x1.Contains("Vodickova Saskie"));
        assert(!x0.Contains("Kadlecova Kvetslava"));
        assert(x1.Contains("Kadlecova Kvetslava"));
    }

    static void test2(){
        CSet<string> x0;
        CSet<string> x1;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
        x1 = x0;
        assert(x0.Insert("Vodickova Saskie"));
        assert(x1.Insert("Kadlecova Kvetslava"));
        assert(x0.Size() == 3);
        assert(x1.Size() == 3);
        assert(x0.Contains("Vodickova Saskie"));
        assert(!x1.Contains("Vodickova Saskie"));
        assert(!x0.Contains("Kadlecova Kvetslava"));
        assert(x1.Contains("Kadlecova Kvetslava"));
    }

    static void test4(){
        CSet<int> x0;
        assert(x0.Insert(4));
        assert(x0.Insert(8));
        assert(x0.Insert(1));
        assert(x0.Size() == 3);
        assert(x0.Contains(4));
        assert(!x0.Contains(5));
        assert(!x0.Remove(5));
        assert(x0.Remove(4));
    }

};

int main(){
    CSetTester::test0();
    CSetTester::test1();
    CSetTester::test2();
    CSetTester::test4();
    return 0;
}

#endif /* __PROGTEST__ */
