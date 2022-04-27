#define CATCH_CONFIG_MAIN

#include "catch.hpp"

//Include tested file
#include "../src/CHttpResponse.h"

using namespace std;

TEST_CASE("1# Basic Header"){
    string message1 = ("HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html>\n</html>\n");

    REQUIRE_NOTHROW(new CHttpResponse(message1));

    CHttpResponse response1(message1);

    CHECK(response1.getProtocol() == "HTTP/1.1");
    CHECK(response1.getStatus() == 200);
    CHECK(response1.getContentType() == "text/html");
    CHECK(response1.getContent() == "<html>\n</html>\n");
}

TEST_CASE("2# Full HTTPS Header"){
    string message2 = R"(
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
X-Frame-Options: DENY
Cache-Control: no-cache, no-store, max-age=0, must-revalidate
Pragma: no-cache
Expires: Mon, 01 Jan 1990 00:00:00 GMT
Date: Wed, 27 Apr 2022 18:53:16 GMT
Content-Security-Policy: base-uri 'self';object-src 'none';report-uri /_/view/cspreport;script-src 'report-sample' 'nonce-HihP+IxgeoTD2h6ukJq65A' 'unsafe-inline' 'unsafe-eval';worker-src 'self';frame-ancestors https://google-admin.corp.google.com/
Cross-Origin-Opener-Policy: unsafe-none
Referrer-Policy: origin
Server: ESF
X-XSS-Protection: 0
X-Content-Type-Options: nosniff
Content-Encoding: gzip
Transfer-Encoding: chunked

<html>
</html>
)";

    REQUIRE_NOTHROW(new CHttpResponse(message2));

    CHttpResponse response2(message2);

    CHECK(response2.getProtocol() == "HTTP/1.1");
    CHECK(response2.getStatus() == 200);
    CHECK(response2.getContentType() == "text/html");
    CHECK(response2.getContent() == "<html>\n</html>\n");
}