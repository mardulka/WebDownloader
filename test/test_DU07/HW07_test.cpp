#define CATCH_CONFIG_MAIN
#define __PROGTEST__

#include "../catch.hpp"

// include proper heading ----------------------------------------------------------------------------------------------
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <optional>
#include <variant>
#include <any>

using namespace std;

// ---------------------------------------------------------------------------------------------------------------------

//Include tested file
#include "../../homework/07/test.cpp"


//Help classes

class CStrComparator{
public:
    CStrComparator(bool caseSensitive) : m_CaseSensitive(caseSensitive){}

    bool operator ()(const string & a, const string & b) const{
        return m_CaseSensitive? strcasecmp(a.c_str(), b.c_str()) < 0 : a < b;
    }

    bool m_CaseSensitive;
};

bool upperCaseCompare(const char & a, const char & b){
    return toupper(a) < toupper(b);
}



// TESTS ---------------------------------------------------------------------------------------------------------------

TEST_CASE("String - basic #1" "[PREDEFINED]"){
    CIndex<string> t0("abcabcabc");
    set<size_t> r0 = t0.search("a");
    REQUIRE (r0 == (set<size_t>{0, 3, 6}));
    set<size_t> r1 = t0.search("abc");
    REQUIRE (r1 == (set<size_t>{0, 3, 6}));
    set<size_t> r2 = t0.search("abcabc");
    REQUIRE (r2 == (set<size_t>{0, 3}));
}

TEST_CASE("String - basic #2" "[PREDEFINED]"){
    CIndex<string> t1("abcababc");
    set<size_t> r3 = t1.search("a");
    REQUIRE (r3 == (set<size_t>{0, 3, 5}));
    set<size_t> r4 = t1.search("abc");
    REQUIRE (r4 == (set<size_t>{0, 5}));
    set<size_t> r5 = t1.search("abcabc");
    REQUIRE (r5 == (set<size_t>{}));
}

TEST_CASE("String - basic #3" "[PREDEFINED]"){
    CIndex<string> t2("kokokokoskokosokos");
    set<size_t> r6 = t2.search("kos");
    REQUIRE (r6 == (set<size_t>{6, 11, 15}));
    set<size_t> r7 = t2.search("kokos");
    REQUIRE (r7 == (set<size_t>{4, 9}));
}

TEST_CASE("String basic #4" "[PREDEFINED]"){
    CIndex<string> t3("aaaaaaau aaauaaaau");
    set<size_t> r8 = t3.search("aa");
    REQUIRE (r8 == (set<size_t>{0, 1, 2, 3, 4, 5, 9, 10, 13, 14, 15}));
    set<size_t> r9 = t3.search("aaa");
    REQUIRE (r9 == (set<size_t>{0, 1, 2, 3, 4, 9, 13, 14}));
    set<size_t> r10 = t3.search("aaaa");
    REQUIRE (r10 == (set<size_t>{0, 1, 2, 3, 13}));
}

TEST_CASE("String - sentence" "[PREDEFINED]"){
    CIndex<string> t4("automatIc authentication automotive auTOmation raut");
    set<size_t> r11 = t4.search("auto");
    REQUIRE (r11 == (set<size_t>{0, 25}));
    set<size_t> r12 = t4.search("aut");
    REQUIRE (r12 == (set<size_t>{0, 10, 25, 48}));
    set<size_t> r13 = t4.search("tic");
    REQUIRE (r13 == (set<size_t>{16}));
    set<size_t> r14 = t4.search("trunk");
    REQUIRE (r14 == (set<size_t>{}));
    set<size_t> r15 = t4.search("a");
    REQUIRE (r15 == (set<size_t>{0, 5, 10, 19, 25, 36, 41, 48}));
    set<size_t> r16 = t4.search("");
    REQUIRE (r16 ==
             (set<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                          26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
                          49,
                          50}));
}
/*
TEST_CASE("String + comparator pointer" "[PREDEFINED]"){
   CIndex<string, bool (*)(const char &, const char &)> t5("automatIc authentication automotive auTOmation raut",
                                                           upperCaseCompare);
   set<size_t> r17 = t5.search("auto");
   REQUIRE (r17 == (set<size_t>{0, 25, 36}));
   set<size_t> r18 = t5.search("aut");
   REQUIRE (r18 == (set<size_t>{0, 10, 25, 36, 48}));
   set<size_t> r19 = t5.search("tic");
   REQUIRE (r19 == (set<size_t>{6, 16}));
   set<size_t> r20 = t5.search("trunk");
   REQUIRE (r20 == (set<size_t>{}));
   set<size_t> r21 = t5.search("a");
   REQUIRE (r21 == (set<size_t>{0, 5, 10, 19, 25, 36, 41, 48}));
   set<size_t> r22 = t5.search("");
   REQUIRE (r22 ==
            (set<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                         26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
                         49,
                         50}));

TEST_CASE("String + functor" "[PREDEFINED]"){
   CIndex<list<string>, CStrComparator> t6(
           list<string>{"Hello", "world", "test", "this", "foo", "TEsT", "this", "done"}, CStrComparator(false));
   set<size_t> r23 = t6.search(list<string>{"test", "this", "foo"});
   REQUIRE (r23 == (set<size_t>{2}));
   set<size_t> r24 = t6.search(list<string>{"test", "this"});
   REQUIRE (r24 == (set<size_t>{2}));
}
TEST_CASE("String + functor" "[PREDEFINED]"){
   CIndex<list<string>, CStrComparator> t7(
           list<string>{"Hello", "world", "test", "this", "foo", "TEsT", "this", "done"}, CStrComparator(true));
   set<size_t> r25 = t7.search(list<string>{"test", "this", "foo"});
   REQUIRE (r25 == (set<size_t>{2}));
   set<size_t> r26 = t7.search(list<string>{"test", "this"});
   REQUIRE (r26 == (set<size_t>{2, 5}));
}
*/





