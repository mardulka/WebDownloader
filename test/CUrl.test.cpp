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

TEST_CASE("10# URL with wrong scheme."){
    try{
        CUrl url10 = CUrl("ftp://fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL scheme is not valid. Supported URL schemes are http and https only, apparently could be omitted."));
    }
}

TEST_CASE("11# URL with empty host"){
    try{
        CUrl url11 = CUrl("http:///cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("URL has no host!"));
    }
}

TEST_CASE("12# URL with empty, 0 and negative port number"){
    try{
        CUrl url12 = CUrl("http://fit.cvut.cz:/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL has wrong port number!"));
    }

    try{
        CUrl url12 = CUrl("http://fit.cvut.cz:0/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL has wrong port number!"));
    }

    try{
        CUrl url12 = CUrl("http://fit.cvut.cz:-80/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL has wrong port number!"));
    }
}

TEST_CASE("13# URL with empty scheme"){
    try{
        CUrl url13 = CUrl("://fit.cvut.cz:/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL scheme is not valid. Supported URL schemes are http and https only, apparently could be omitted."));
    }
}

TEST_CASE("14# URL with wrong scheme delimiter"){
    try{
        CUrl url14 = CUrl("http:/fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL has wrong port number!"));
    }

    try{
        CUrl url14 = CUrl("http:fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL has wrong port number!"));
    }

    try{
        CUrl url14 = CUrl("http//fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    } catch (const std::invalid_argument & e){
        CHECK(std::string (e.what()) == std::string ("Given URL contains characters there are not valid!"));
    }
}

TEST_CASE("15# Copy testing"){
    CUrl * url15 = new CUrl("http://fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url15->getScheme() == "http");
    CHECK(url15->getHost() == "fit.cvut.cz");
    CHECK(url15->getPort() == 666);
    CHECK(url15->getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url15->getQuery() == "");

    CUrl url15a = (*url15);
    CUrl url15b(*url15);

    delete url15;

    CHECK(url15a.getScheme() == "http");
    CHECK(url15a.getHost() == "fit.cvut.cz");
    CHECK(url15a.getPort() == 666);
    CHECK(url15a.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url15a.getQuery() == "");

    CHECK(url15b.getScheme() == "http");
    CHECK(url15b.getHost() == "fit.cvut.cz");
    CHECK(url15b.getPort() == 666);
    CHECK(url15b.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url15b.getQuery() == "");

}

TEST_CASE("16# Move testing"){
    CUrl url16 = CUrl("http://fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url16.getScheme() == "http");
    CHECK(url16.getHost() == "fit.cvut.cz");
    CHECK(url16.getPort() == 666);
    CHECK(url16.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url16.getQuery() == "");

    CUrl url16a(std::move(url16));
    CHECK(url16.getScheme() == "");
    CHECK(url16.getHost() == "");
    CHECK(url16.getPort() == 666);
    CHECK(url16.getPath() == "/");
    CHECK(url16.getQuery() == "");
    CHECK(url16a.getScheme() == "http");
    CHECK(url16a.getHost() == "fit.cvut.cz");
    CHECK(url16a.getPort() == 666);
    CHECK(url16a.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url16a.getQuery() == "");

    CUrl url16b = CUrl("http://fit.cvut.cz:666/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url16b.getScheme() == "http");
    CHECK(url16b.getHost() == "fit.cvut.cz");
    CHECK(url16b.getPort() == 666);
    CHECK(url16b.getPath() == "/cs/uchazeci/programy-a-obory/bakalarske-studium");
    CHECK(url16b.getQuery() == "");

}

TEST_CASE("17# Empty URL"){
    CUrl url17 = CUrl();
    CHECK(url17.getScheme() == "");
    CHECK(url17.getHost() == "");
    CHECK(url17.getPort() == 80);
    CHECK(url17.getPath() == "/");
    CHECK(url17.getQuery() == "");

    CHECK(url17.empty());
}

TEST_CASE("18# Real URL from application test"){
    CUrl url18 = CUrl("http://silvercalmcoolplay.neverssl.com/online");
    CHECK(url18.getScheme() == "http");
    CHECK(url18.getHost() == "silvercalmcoolplay.neverssl.com");
    CHECK(url18.getPort() == 80);
    CHECK(url18.getPath() == "/online");
    CHECK(url18.getQuery() == "");

    CHECK_FALSE(url18.empty());
}

TEST_CASE("19# Real URL from application test"){
    CUrl url19 = CUrl("http://www.uro-care.cz/remote/imgprev.php?id=dXBsb2FkL2ZvdG8vbXVkcl9zbWVoaWxfbWFydGluLmpwZw%3D%3D&c&h=280");
    CHECK(url19.getScheme() == "http");
    CHECK(url19.getHost() == "www.uro-care.cz");
    CHECK(url19.getPort() == 80);
    CHECK(url19.getPath() == "/remote/imgprev.php");
    CHECK(url19.getQuery() == "id=dXBsb2FkL2ZvdG8vbXVkcl9zbWVoaWxfbWFydGluLmpwZw%3D%3D&c&h=280");

    CHECK_FALSE(url19.empty());
}

TEST_CASE("20# Real URL from application test"){
    CUrl url20 = CUrl("http://www.niszp.cz/?page=1");
    CHECK(url20.getScheme() == "http");
    CHECK(url20.getHost() == "www.niszp.cz");
    CHECK(url20.getPort() == 80);
    CHECK(url20.getPath() == "/");
    CHECK(url20.getQuery() == "page=1");

    CHECK_FALSE(url20.empty());
}


TEST_CASE("21# Real URL from application test"){
    CUrl url21 = CUrl("https://www.niszp.cz/cs/informace-pro-hospodarske-subjekty");
    CHECK(url21.getScheme() == "https");
    CHECK(url21.getHost() == "www.niszp.cz");
    CHECK(url21.getPort() == 80);
    CHECK(url21.getPath() == "/cs/informace-pro-hospodarske-subjekty");
    CHECK_FALSE(url21.empty());

    std::string link = "https://www.niszp.cz/sites/default/files/18062020/FS_Procurement%20ecosystem_CS.pdf";
    auto linkopt = url21.makeLinkAbsolute(link);
    REQUIRE(linkopt.has_value());
    CHECK(linkopt.value() == link);
}