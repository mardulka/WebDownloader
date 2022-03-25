#define CATCH_CONFIG_MAIN
#define __PROGTEST__

#include "../catch.hpp"

// include proper heading ----------------------------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

// ---------------------------------------------------------------------------------------------------------------------

//Include tested file
#include "../../homework/03/test.cpp"


TEST_CASE("Basic tests"){
    ostringstream oss;
    istringstream iss;

    CDate a(2000, 1, 2);
    CDate b(2010, 2, 3);
    CDate c(2004, 2, 10);
    oss.str("");
    oss << a;
    REQUIRE (oss.str() == "2000-01-02");
    oss.str("");
    oss << b;
    REQUIRE (oss.str() == "2010-02-03");
    oss.str("");
    oss << c;
    REQUIRE (oss.str() == "2004-02-10");
    a = a + 1500;
    oss.str("");
    oss << a;
    REQUIRE (oss.str() == "2004-02-10");
    b = b - 2000;
    oss.str("");
    oss << b;
    REQUIRE (oss.str() == "2004-08-13");
    REQUIRE (b - a == 185);
    REQUIRE ((b == a) == false);
    REQUIRE ((b != a) == true);
    REQUIRE ((b <= a) == false);
    REQUIRE ((b < a) == false);
    REQUIRE ((b >= a) == true);
    REQUIRE ((b > a) == true);
    REQUIRE ((c == a) == true);
    REQUIRE ((c != a) == false);
    REQUIRE ((c <= a) == true);
    REQUIRE ((c < a) == false);
    REQUIRE ((c >= a) == true);
    REQUIRE ((c > a) == false);
    a = ++c;
    oss.str("");
    oss << a << " " << c;
    REQUIRE (oss.str() == "2004-02-11 2004-02-11");
    a = --c;
    oss.str("");
    oss << a << " " << c;
    REQUIRE (oss.str() == "2004-02-10 2004-02-10");
    a = c++;
    oss.str("");
    oss << a << " " << c;
    REQUIRE (oss.str() == "2004-02-10 2004-02-11");
    a = c--;
    oss.str("");
    oss << a << " " << c;
    REQUIRE (oss.str() == "2004-02-11 2004-02-10");
    iss.clear();
    iss.str("2015-09-03");
    REQUIRE ((iss >> a));
    oss.str("");
    oss << a;
    REQUIRE (oss.str() == "2015-09-03");
    a = a + 70;
    oss.str("");
    oss << a;
    REQUIRE (oss.str() == "2015-11-12");

    CDate d(2000, 1, 1);
    try{
        CDate e(2000, 32, 1);
        REQUIRE ("No exception thrown!" == nullptr);
    }
    catch (...){}
    iss.clear();
    iss.str("2000-12-33");
    REQUIRE (!(iss >> d));
    oss.str("");
    oss << d;
    REQUIRE (oss.str() == "2000-01-01");
    iss.clear();
    iss.str("2000-11-31");
    REQUIRE (!(iss >> d));
    oss.str("");
    oss << d;
    REQUIRE (oss.str() == "2000-01-01");
    iss.clear();
    iss.str("2000-02-29");
    REQUIRE ((iss >> d));
    oss.str("");
    oss << d;
    REQUIRE (oss.str() == "2000-02-29");
    iss.clear();
    iss.str("2001-02-29");
    REQUIRE (!(iss >> d));
    oss.str("");
    oss << d;
    REQUIRE (oss.str() == "2000-02-29");
}

TEST_CASE("Progtest error for basic tests"){
    ostringstream oss;
    istringstream iss;

    CDate zz(2004, 03, 1);
    zz = --zz;
    oss.str("");
    oss << zz;
    REQUIRE(oss.str() == "2004-02-29");
}

TEST_CASE("Bonus test examples"){
    ostringstream oss;
    istringstream iss;

    CDate f(2000, 5, 12);
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2000-05-12");
    oss.str("");
    oss << date_format("%Y/%m/%d") << f;
    REQUIRE (oss.str() == "2000/05/12");
    oss.str("");
    oss << date_format("%d.%m.%Y") << f;
    REQUIRE (oss.str() == "12.05.2000");
    oss.str("");
    oss << date_format("%m/%d/%Y") << f;
    REQUIRE (oss.str() == "05/12/2000");
    oss.str("");
    oss << date_format("%Y%m%d") << f;
    REQUIRE (oss.str() == "20000512");
    oss.str("");
    oss << date_format("hello kitty") << f;
    REQUIRE (oss.str() == "hello kitty");
    oss.str("");
    oss << date_format("%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%") << f;
    REQUIRE (oss.str() == "121212121212050505200020002000%%%%%");
    oss.str("");
    oss << date_format("%Y-%m-%d") << f;
    REQUIRE (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-01-1");
    REQUIRE (!(iss >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-1-01");
    REQUIRE (!(iss >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-001-01");
    REQUIRE (!(iss >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2000-05-12");
    iss.clear();
    iss.str("2001-01-02");
    REQUIRE ((iss >> date_format("%Y-%m-%d") >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2001-01-02");
    iss.clear();
    iss.str("05.06.2003");
    REQUIRE ((iss >> date_format("%d.%m.%Y") >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2003-06-05");
    iss.clear();
    iss.str("07/08/2004");
    REQUIRE ((iss >> date_format("%m/%d/%Y") >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2004-07-08");
    iss.clear();
    iss.str("2002*03*04");
    REQUIRE ((iss >> date_format("%Y*%m*%d") >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2002-03-04");
    iss.clear();
    iss.str("C++09format10PA22006rulez");
    REQUIRE ((iss >> date_format("C++%mformat%dPA2%Yrulez") >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2006-09-10");
    iss.clear();
    iss.str("%12%13%2010%");
    REQUIRE ((iss >> date_format("%%%m%%%d%%%Y%%") >> f));
    oss.str("");
    oss << f;
    REQUIRE (oss.str() == "2010-12-13");

    CDate g(2000, 6, 8);
    iss.clear();
    iss.str("2001-11-33");
    REQUIRE (!(iss >> date_format("%Y-%m-%d") >> g));
    oss.str("");
    oss << g;
    REQUIRE (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("29.02.2003");
    REQUIRE (!(iss >> date_format("%d.%m.%Y") >> g));
    oss.str("");
    oss << g;
    REQUIRE (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("14/02/2004");
    REQUIRE (!(iss >> date_format("%m/%d/%Y") >> g));
    oss.str("");
    oss << g;
    REQUIRE (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("2002-03");
    REQUIRE (!(iss >> date_format("%Y-%m") >> g));
    oss.str("");
    oss << g;
    REQUIRE (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("hello kitty");
    REQUIRE (!(iss >> date_format("hello kitty") >> g));
    oss.str("");
    oss << g;
    REQUIRE (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("2005-07-12-07");
    REQUIRE (!(iss >> date_format("%Y-%m-%d-%m") >> g));
    oss.str("");
    oss << g;
    REQUIRE (oss.str() == "2000-06-08");
    iss.clear();
    iss.str("20000101");
    REQUIRE ((iss >> date_format("%Y%m%d") >> g));
    oss.str("");
    oss << g;
    REQUIRE (oss.str() == "2000-01-01");
}