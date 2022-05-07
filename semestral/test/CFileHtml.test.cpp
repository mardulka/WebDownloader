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
    string content2 = R"(Header

 <p>Je tu neco predtim<p> </br>
<a href="https://www.w3schools.cz" target="peklo">Visit W3Schools.cz!</a>)";

    auto file1 = make_unique<CFileHtml>(url);
    auto file2 = make_unique<CFileHtml>(url);
    file1->setContent(content1);
    file2->setContent(content2);


    auto list1 = file1->readLinks();
    auto list2 = file2->readLinks();

    REQUIRE(list1.size() == 1);
    REQUIRE(list2.size() == 1);

    REQUIRE(list1.front().getUrl() == "https://www.w3schools.com");
    REQUIRE(list2.front().getUrl() == "https://www.w3schools.cz");
}

TEST_CASE("2# Parse IMG tag - simple"){
    CUrl url("http://www.fit.cvut.cz");
    string content1 = R"(<img src="img_girl.jpg" alt="Girl in a jacket" width="500" height="600">)";
    string content2 = R"(<p>Je tu neco predtim<p> </br>
<a href="https://www.w3schools.com" target="_blank">Visit W3Schools.com!</a>
<img src="img_girl.jpg" alt="Girl in the jacket" width="500" height="600">)";

    auto file1 = make_unique<CFileHtml>(url);
    auto file2 = make_unique<CFileHtml>(url);
    file1->setContent(content1);
    file2->setContent(content2);


    auto list1 = file1->readLinks();
    auto list2 = file2->readLinks();

    REQUIRE(list1.size() == 1);
    REQUIRE(list2.size() == 2);

    REQUIRE(list1.front().getUrl() == "http://www.fit.cvut.cz/img_girl.jpg");

    auto iter = list2.begin();
    REQUIRE(iter->getUrl() == "https://www.w3schools.com");
    REQUIRE((++iter)->getUrl() == "http://www.fit.cvut.cz/img_girl.jpg");
}

TEST_CASE("3# Parse LINK tag - simple"){
    CUrl url("http://www.fit.cvut.cz");
    string content1 = R"(<img src="img_girl.jpg" alt="Girl in a jacket" width="500" height="600">)";
    string content2 = R"(<p>Je tu neco predtim<p> </br>
<a href="https://www.w3schools.com" target="target">Visit W3Schools.com!</a>
<img src="img_girl.jpg" alt="Girl in the jacket" width="500" height="600">
<link rel="stylesheet" href="/lib/w3schools40.css">)";

    auto file1 = make_unique<CFileHtml>(url);
    auto file2 = make_unique<CFileHtml>(url);
    file1->setContent(content1);
    file2->setContent(content2);


    auto list1 = file1->readLinks();
    auto list2 = file2->readLinks();

    REQUIRE(list1.size() == 1);
    REQUIRE(list2.size() == 3);

    REQUIRE(list1.front().getUrl() == "http://www.fit.cvut.cz/img_girl.jpg");

    auto iter = list2.begin();
    REQUIRE(iter->getUrl() == "https://www.w3schools.com");
    REQUIRE((++iter)->getUrl() == "http://www.fit.cvut.cz/img_girl.jpg");
    REQUIRE((++iter)->getUrl() == "http://www.fit.cvut.cz/lib/w3schools40.css");
}