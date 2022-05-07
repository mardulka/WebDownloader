#define CATCH_CONFIG_MAIN
#define __PROGTEST__

#include "../catch.hpp"

// include proper heading ----------------------------------------------------------------------------------------------
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>

using namespace std;

// ---------------------------------------------------------------------------------------------------------------------

//Include tested file since no header is allowed for PROGTEST
#include "../../homework/04/test.cpp"


//Help classes

bool writeTest(CFile & x, const initializer_list<uint8_t> & data, uint32_t wrLen){
    return x.write(data.begin(), data.size()) == wrLen;
}
bool readTest(CFile & x, const initializer_list<uint8_t> & data, uint32_t rdLen){
    uint8_t tmp[100];
    uint32_t idx = 0;

    if (x.read(tmp, rdLen) != data.size())
        return false;
    for (auto v: data)
        if (tmp[idx++] != v)
            return false;
    return true;
}



// TESTS ---------------------------------------------------------------------------------------------------------------

TEST_CASE("Default predefined tests." "[PREDEFINED]"){
    CFile f0;

        REQUIRE (writeTest(f0, {10, 20, 30}, 3));
        REQUIRE (f0.fileSize() == 3);
        REQUIRE (writeTest(f0, {60, 70, 80}, 3));
        REQUIRE (f0.fileSize() == 6);
        REQUIRE (f0.seek(2));
        REQUIRE (writeTest(f0, {5, 4}, 2));
        REQUIRE (f0.fileSize() == 6);
        REQUIRE (f0.seek(1));
        REQUIRE (readTest(f0, {20, 5, 4, 70, 80}, 7));
        REQUIRE (f0.seek(3));
        f0.addVersion();
        REQUIRE (f0.seek(6));
        REQUIRE (writeTest(f0, {100, 101, 102, 103}, 4));
        f0.addVersion();
        REQUIRE (f0.seek(5));
        CFile f1(f0);
        f0.truncate();
        REQUIRE (f0.seek(0));
        REQUIRE (readTest(f0, {10, 20, 5, 4, 70}, 20));
        REQUIRE (f0.undoVersion());
        REQUIRE (f0.seek(0));
        REQUIRE (readTest(f0, {10, 20, 5, 4, 70, 80, 100, 101, 102, 103}, 20));
        REQUIRE (f0.undoVersion());
        REQUIRE (f0.seek(0));
        REQUIRE (readTest(f0, {10, 20, 5, 4, 70, 80}, 20));
        REQUIRE (!f0.seek(100));
        REQUIRE (writeTest(f1, {200, 210, 220}, 3));
        REQUIRE (f1.seek(0));
        REQUIRE (readTest(f1, {10, 20, 5, 4, 70, 200, 210, 220, 102, 103}, 20));
        REQUIRE (f1.undoVersion());
        REQUIRE (f1.undoVersion());
        REQUIRE (readTest(f1, {4, 70, 80}, 20));
        REQUIRE (!f1.undoVersion());

}



