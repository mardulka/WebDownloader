#define CATCH_CONFIG_MAIN

#include "catch.hpp"

//Include tested file
#include "../src/CFileHtml.h"
#include "../src/CFile.h"
#include "../src/CUrl.h"

using namespace std;

TEST_CASE("1# Parse A tag - simple"){
    CUrl url("http://www.fit.cvut.cz");
    string content1 = R"(<a href="https://www.w3schools.com" target="_blank">Visit W3Schools.com!</a>)";
    string content2 = R"(<p>Je tu neco predtim<p> </br> <a href="https://www.w3schools.com" target="_blank">Visit W3Schools.com!</a>)";

    auto file1 = make_shared<CFileHtml>(url);
    auto file2 = make_shared<CFileHtml>(url);
    file1->setContent(content1);
    file2->setContent(content2);


    auto list1 = file1->readLinks();
    auto list2 = file1->readLinks();

    REQUIRE(list1.size() == 1);
    REQUIRE(list2.size() == 1);

    REQUIRE(list1.front().getUrl() == "https://www.w3schools.com");
    REQUIRE(list1.front().getUrl() == "https://www.w3schools.com");

}