#define CATCH_CONFIG_MAIN

#include "catch.hpp"

//Include tested file
#include "../src/CFileCss.h"
#include "../src/CFile.h"
#include "../src/CUrl.h"

using namespace std;

TEST_CASE("1# Parse one line - simple"){
    CUrl url("http://www.fit.cvut.cz");
    string content1 = R"(url(https://example.com/images/myImg.jpg);)";
    string content2 = R"(background-image: url("star.gif");)";

    auto file1 = make_unique<CFileCss>(url);
    auto file2 = make_unique<CFileCss>(url);
    file1->setContent(content1);
    file2->setContent(content2);


    auto list1 = file1->readLinks();
    auto list2 = file2->readLinks();

    REQUIRE(list1.size() == 1);
    REQUIRE(list2.size() == 1);

    REQUIRE(list1.front().getUrl() == "https://example.com/images/myImg.jpg");
    REQUIRE(list2.front().getUrl() == "http://www.fit.cvut.cz/star.gif");
}

TEST_CASE("2# Parse more complex css"){
    CUrl url("http://www.fit.cvut.cz");
    string content1 = R"(
.topbanner {
    background: url("topbanner.png") #00D no-repeat fixed;
}
)";
    string content2 = R"(
ul {
    list-style: square url(http://www.example.com/redball.png);
}
)";

    auto file1 = make_unique<CFileCss>(url);
    auto file2 = make_unique<CFileCss>(url);
    file1->setContent(content1);
    file2->setContent(content2);


    auto list1 = file1->readLinks();
    auto list2 = file2->readLinks();

    REQUIRE(list1.size() == 1);
    REQUIRE(list2.size() == 1);

    REQUIRE(list1.front().getUrl() == "http://www.fit.cvut.cz/topbanner.png");
    REQUIRE(list2.front().getUrl() == "http://www.example.com/redball.png");
}


TEST_CASE("3# Parse complex css with more links"){
    CUrl url("http://www.fit.cvut.cz");
    string content1 = R"(
.topbanner {
    background: url("topbanner.png") #00D no-repeat fixed;
}

ul {
    list-style: square url(http://www.example.com/redball.png);
}
)";
    string content2 = R"(
ul {
    list-style: square url(http://www.example.com/redball.png);
}

.topbanner {
    background: url("topbanner.png") #00D no-repeat fixed;
}
)";

    auto file1 = make_unique<CFileCss>(url);
    auto file2 = make_unique<CFileCss>(url);
    file1->setContent(content1);
    file2->setContent(content2);


    auto list1 = file1->readLinks();
    auto list2 = file2->readLinks();

    REQUIRE(list1.size() == 2);
    REQUIRE(list2.size() == 2);

    auto iter1 = list1.begin();
    auto iter2 = list2.begin();

    REQUIRE(iter1->getUrl() == "http://www.fit.cvut.cz/topbanner.png");
    REQUIRE((++iter1)->getUrl() == "http://www.example.com/redball.png");

    REQUIRE(iter2->getUrl() == "http://www.example.com/redball.png");
    REQUIRE((++iter2)->getUrl() == "http://www.fit.cvut.cz/topbanner.png");
}