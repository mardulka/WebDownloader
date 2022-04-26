#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//Include tested file
#include "../src/CUrl.h"

TEST_CASE("1# Basic URL"){
    CUrl url1 = CUrl("www.fit.cvut.cz");
    CHECK(url1.getScheme() == "");
    CHECK(url1.getHost() == "www.fit.cvut.cz");
    CHECK(url1.getPort() == 80);
    CHECK(url1.getPath() == "/");
    CHECK(url1.getQuery() == "");
}

TEST_CASE("2# URL with http scheme"){
    CUrl url2 = CUrl("http://www.fit.cvut.cz");
    CHECK(url2.getScheme() == "http");
    CHECK(url2.getHost() == "www.fit.cvut.cz");
    CHECK(url2.getPort() == 80);
    CHECK(url2.getPath() == "/");
    CHECK(url2.getQuery() == "");
}

TEST_CASE("3# URL with https scheme"){
    CUrl url3 = CUrl("https://www.fit.cvut.cz");
    CHECK(url3.getScheme() == "https");
    CHECK(url3.getHost() == "www.fit.cvut.cz");
    CHECK(url3.getPort() == 80);
    CHECK(url3.getPath() == "/");
    CHECK(url3.getQuery() == "");
}

TEST_CASE("4# URL with port"){
    CUrl url4 = CUrl("www.fit.cvut.cz:666");
    CHECK(url4.getScheme() == "");
    CHECK(url4.getHost() == "www.fit.cvut.cz");
    CHECK(url4.getPort() == 666);
    CHECK(url4.getPath() == "/");
    CHECK(url4.getQuery() == "");
}

TEST_CASE("5# URL with scheme and port"){
    CUrl url5 = CUrl("http://www.fit.cvut.cz:666");
    CHECK(url5.getScheme() == "http");
    CHECK(url5.getHost() == "www.fit.cvut.cz");
    CHECK(url5.getPort() == 666);
    CHECK(url5.getPath() == "/");
    CHECK(url5.getQuery() == "");
}

TEST_CASE("6# URL with path"){
    CUrl url6 = CUrl("fit.cvut.cz/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url6.getScheme() == "");
    CHECK(url6.getHost() == "fit.cvut.cz");
    CHECK(url6.getPort() == 80);
    CHECK(url6.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url6.getQuery() == "");
}

TEST_CASE("7# URL with scheme and path"){
    CUrl url7 = CUrl("http://fit.cvut.cz/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url7.getScheme() == "http");
    CHECK(url7.getHost() == "fit.cvut.cz");
    CHECK(url7.getPort() == 80);
    CHECK(url7.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url7.getQuery() == "");
}

TEST_CASE("8# URL with port and path"){
    CUrl url8 = CUrl("fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url8.getScheme() == "");
    CHECK(url8.getHost() == "fit.cvut.cz");
    CHECK(url8.getPort() == 666);
    CHECK(url8.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url8.getQuery() == "");
}

TEST_CASE("9# URL with scheme, port and path"){
    CUrl url9 = CUrl("http://fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url9.getScheme() == "http");
    CHECK(url9.getHost() == "fit.cvut.cz");
    CHECK(url9.getPort() == 666);
    CHECK(url9.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url9.getQuery() == "");
}