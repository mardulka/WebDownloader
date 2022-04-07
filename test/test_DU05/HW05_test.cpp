#define CATCH_CONFIG_MAIN
#define __PROGTEST__

#include "../catch.hpp"

// include proper heading ----------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------------------------------

//Include tested file
#include "../../homework/05/test.cpp"




// TESTS ---------------------------------------------------------------------------------------------------------------

TEST_CASE("Default predefined tests." "[PREDEFINED]"){
    CSupermarket s;
    s.store("bread", CDate(2016, 4, 30), 100)
            .store("butter", CDate(2016, 5, 10), 10)
            .store("beer", CDate(2016, 8, 10), 50)
            .store("bread", CDate(2016, 4, 25), 100)
            .store("okey", CDate(2016, 7, 18), 5);

    list<pair<string, int> > l0 = s.expired(CDate(2018, 4, 30));
    REQUIRE(l0.size() == 4);
    REQUIRE((l0 == list<pair<string, int> >{{"bread",  200},
                                            {"beer",   50},
                                            {"butter", 10},
                                            {"okey",   5}}));

    list<pair<string, int> > l1{{"bread",  2},
                                {"Coke",   5},
                                {"butter", 20}};
    s.sell(l1);
    REQUIRE(l1.size() == 2);
    REQUIRE((l1 == list<pair<string, int> >{{"Coke",   5},
                                            {"butter", 10}}));

    list<pair<string, int> > l2 = s.expired(CDate(2016, 4, 30));
    REQUIRE(l2.size() == 1);
    REQUIRE((l2 == list<pair<string, int> >{{"bread", 98}}));

    list<pair<string, int> > l3 = s.expired(CDate(2016, 5, 20));
    REQUIRE(l3.size() == 1);
    REQUIRE((l3 == list<pair<string, int> >{{"bread", 198}}));

    list<pair<string, int> > l4{{"bread", 105}};
    s.sell(l4);
    REQUIRE(l4.size() == 0);
    REQUIRE((l4 == list<pair<string, int> >{}));

    list<pair<string, int> > l5 = s.expired(CDate(2017, 1, 1));
    REQUIRE(l5.size() == 3);
    REQUIRE((l5 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"okey",  5}}));

    s.store("Coke", CDate(2016, 12, 31), 10);

    list<pair<string, int> > l6{{"Cake",  1},
                                {"Coke",  1},
                                {"cake",  1},
                                {"coke",  1},
                                {"cuke",  1},
                                {"Cokes", 1}};
    s.sell(l6);
    REQUIRE(l6.size() == 3);
    REQUIRE((l6 == list<pair<string, int> >{{"cake",  1},
                                            {"cuke",  1},
                                            {"Cokes", 1}}));

    list<pair<string, int> > l7 = s.expired(CDate(2017, 1, 1));
    REQUIRE(l7.size() == 4);
    REQUIRE((l7 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  7},
                                            {"okey",  5}}));

    s.store("cake", CDate(2016, 11, 1), 5);

    list<pair<string, int> > l8{{"Cake", 1},
                                {"Coke", 1},
                                {"cake", 1},
                                {"coke", 1},
                                {"cuke", 1}};
    s.sell(l8);
    REQUIRE(l8.size() == 2);
    REQUIRE((l8 == list<pair<string, int> >{{"Cake", 1},
                                            {"coke", 1}}));

    list<pair<string, int> > l9 = s.expired(CDate(2017, 1, 1));
    REQUIRE(l9.size() == 5);
    REQUIRE((l9 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  6},
                                            {"okey",  5},
                                            {"cake",  3}}));

    list<pair<string, int> > l10{{"cake", 15},
                                 {"Cake", 2}};
    s.sell(l10);
    REQUIRE(l10.size() == 2);
    REQUIRE((l10 == list<pair<string, int> >{{"cake", 12},
                                             {"Cake", 2}}));

    list<pair<string, int> > l11 = s.expired(CDate(2017, 1, 1));
    REQUIRE(l11.size() == 4);
    REQUIRE((l11 == list<pair<string, int> >{{"bread", 93},
                                             {"beer",  50},
                                             {"Coke",  6},
                                             {"okey",  5}}));

    list<pair<string, int> > l12{{"Cake", 4}};
    s.sell(l12);
    REQUIRE(l12.size() == 0);
    REQUIRE((l12 == list<pair<string, int> >{}));

    list<pair<string, int> > l13 = s.expired(CDate(2017, 1, 1));
    REQUIRE(l13.size() == 4);
    REQUIRE((l13 == list<pair<string, int> >{{"bread", 93},
                                             {"beer",  50},
                                             {"okey",  5},
                                             {"Coke",  2}}));

    list<pair<string, int> > l14{{"Beer", 20},
                                 {"Coke", 1},
                                 {"bear", 25},
                                 {"beer", 10}};
    s.sell(l14);
    REQUIRE(l14.size() == 1);
    REQUIRE((l14 == list<pair<string, int> >{{"beer", 5}}));

    s.store("ccccb", CDate(2019, 3, 11), 100)
            .store("ccccd", CDate(2019, 6, 9), 100)
            .store("dcccc", CDate(2019, 2, 14), 100);

    list<pair<string, int> > l15{{"ccccc", 10}};
    s.sell(l15);
    REQUIRE(l15.size() == 1);
    REQUIRE((l15 == list<pair<string, int> >{{"ccccc", 10}}));

}

TEST_CASE("Additional tests." "[ADDITIONAL]"){
    CSupermarket sm;
    sm.store("bread", CDate(2016, 4, 30), 100)
            .store("butter", CDate(2016, 5, 10), 10)
            .store("beer", CDate(2016, 8, 10), 50)
            .store("bread", CDate(2016, 4, 25), 100)
            .store("okey", CDate(2016, 7, 18), 5);


}

