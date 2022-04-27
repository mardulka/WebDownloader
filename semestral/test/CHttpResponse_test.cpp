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
    CHECK(response1.getContentType() == "text");
    CHECK(response1.getContentFormat() == "html");
    CHECK(response1.getContent() == "<html>\n</html>\n");
}

TEST_CASE("2# Full HTTPS Header"){
    string message2 = R"(HTTP/1.1 200 OK
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
    CHECK(response2.getContentType() == "text");
    CHECK(response2.getContentFormat() == "html");
    CHECK(response2.getContent() == "<html>\n</html>\n");
}


TEST_CASE("3# Basic Header and longer content"){
    string message3 = R"(HTTP/1.1 200 OK
Content-Type: text/html

<html>
	<head>
		<title>NeverSSL - helping you get online</title>

    </head>
    <!-- komentar -->

	<div class="header">
		<div class="container">
		<h1>NeverSSL</h1>
		</div>
	</div>

	<div class="content">
	<div class="container">

    <h2>What?</h2>
	<p>This website is for when you try to open Facebook, Google, Amazon, etc
	on a wifi network, and nothing happens. Type "http://neverssl.com"
	into your browser's url bar, and you'll be able to log on.</p>

	<h2>How?</h2>
	<p>neverssl.com will never use SSL (also known as TLS). No
	encryption, no strong authentication, no <a
	href="https://en.wikipedia.org/wiki/HTTP_Strict_Transport_Security">HSTS</a>,
	no HTTP/2.0, just plain old unencrypted HTTP and forever stuck in the dark
	ages of internet security.</p>

</html>
)";

    REQUIRE_NOTHROW(new CHttpResponse(message3));

    CHttpResponse response3(message3);

    CHECK(response3.getProtocol() == "HTTP/1.1");
    CHECK(response3.getStatus() == 200);
    CHECK(response3.getContentType() == "text");
    CHECK(response3.getContentFormat() == "html");

    string contentToCheck = R"(<html>
	<head>
		<title>NeverSSL - helping you get online</title>

    </head>
    <!-- komentar -->

	<div class="header">
		<div class="container">
		<h1>NeverSSL</h1>
		</div>
	</div>

	<div class="content">
	<div class="container">

    <h2>What?</h2>
	<p>This website is for when you try to open Facebook, Google, Amazon, etc
	on a wifi network, and nothing happens. Type "http://neverssl.com"
	into your browser's url bar, and you'll be able to log on.</p>

	<h2>How?</h2>
	<p>neverssl.com will never use SSL (also known as TLS). No
	encryption, no strong authentication, no <a
	href="https://en.wikipedia.org/wiki/HTTP_Strict_Transport_Security">HSTS</a>,
	no HTTP/2.0, just plain old unencrypted HTTP and forever stuck in the dark
	ages of internet security.</p>

</html>
)";

    CHECK(response3.getContent() == contentToCheck);

}


TEST_CASE("4# Real response"){
    string message4 = R"(HTTP/1.1 200 OK
Content-Type: text/html
Transfer-Encoding: chunked
Connection: keep-alive
Last-Modified: Thu, 04 Nov 2021 16:34:59 GMT
Server: AmazonS3
Content-Encoding: gzip
Date: Wed, 27 Apr 2022 15:39:20 GMT
ETag: W/"1727356907f2ef9c00e6d0d3c44fd95b"
Vary: Accept-Encoding
Cache-Control: public, max-age=86400
X-Cache: Hit from cloudfront
Via: 1.1 1f4c9bd672bb89060a69b305de06ad0e.cloudfront.net (CloudFront)
X-Amz-Cf-Pop: EWR53-C2
X-Amz-Cf-Id: BTC9JTNI2Jtg2Fa7swhv0NVlvE_OnpdM3GPKTp-ip0gwikCibnTuIA==
Age: 21221

<html>
	<head>
		<title>NeverSSL - helping you get online</title>

		<style>
		body {
			font-family: Montserrat, helvetica, arial, sans-serif;
			font-size: 16x;
			color: #444444;
			margin: 0;
		}
		h2 {
			font-weight: 700;
			font-size: 1.6em;
			margin-top: 30px;
		}
		p {
			line-height: 1.6em;
		}
		.container {
			max-width: 650px;
			margin: 20px auto 20px auto;
			padding-left: 15px;
			padding-right: 15px
		}
		.header {
			background-color: #42C0FD;
			color: #FFFFFF;
			padding: 10px 0 10px 0;
			font-size: 2.2em;
		}
		<!-- CSS from Mark Webster https://gist.github.com/markcwebster/9bdf30655cdd5279bad13993ac87c85d -->
		</style>
	</head>
	<body>

	<div class="header">
		<div class="container">
		<h1>NeverSSL</h1>
		</div>
	</div>

	<div class="content">
	<div class="container">

	<h2>What?</h2>
	<p>This website is for when you try to open Facebook, Google, Amazon, etc
	on a wifi network, and nothing happens. Type "http://neverssl.com"
	into your browser's url bar, and you'll be able to log on.</p>

	<h2>How?</h2>
	<p>neverssl.com will never use SSL (also known as TLS). No
	encryption, no strong authentication, no <a
	href="https://en.wikipedia.org/wiki/HTTP_Strict_Transport_Security">HSTS</a>,
	no HTTP/2.0, just plain old unencrypted HTTP and forever stuck in the dark
	ages of internet security.</p>

	<h2>Why?</h2>
	<p>Normally, that's a bad idea. You should always use SSL and secure
	encryption when possible. In fact, it's such a bad idea that most websites
	are now using https by default.</p>

	<p>And that's great, but it also means that if you're relying on
	poorly-behaved wifi networks, it can be hard to get online.  Secure
	browsers and websites using https make it impossible for those wifi
	networks to send you to a login or payment page. Basically, those networks
	can't tap into your connection just like attackers can't. Modern browsers
	are so good that they can remember when a website supports encryption and
	even if you type in the website name, they'll use https.</p>

	<p>And if the network never redirects you to this page, well as you can
	see, you're not missing much.</p>

	<a href="https://twitter.com/neverssl">Follow @neverssl</a>

	</div>
	</div>
	</body>
</html>
)";

    REQUIRE_NOTHROW(new CHttpResponse(message4));

    CHttpResponse response4(message4);

    CHECK(response4.getProtocol() == "HTTP/1.1");
    CHECK(response4.getStatus() == 200);
    CHECK(response4.getContentType() == "text");
    CHECK(response4.getContentFormat() == "html");

    string contentToCheck = R"(<html>
	<head>
		<title>NeverSSL - helping you get online</title>

		<style>
		body {
			font-family: Montserrat, helvetica, arial, sans-serif;
			font-size: 16x;
			color: #444444;
			margin: 0;
		}
		h2 {
			font-weight: 700;
			font-size: 1.6em;
			margin-top: 30px;
		}
		p {
			line-height: 1.6em;
		}
		.container {
			max-width: 650px;
			margin: 20px auto 20px auto;
			padding-left: 15px;
			padding-right: 15px
		}
		.header {
			background-color: #42C0FD;
			color: #FFFFFF;
			padding: 10px 0 10px 0;
			font-size: 2.2em;
		}
		<!-- CSS from Mark Webster https://gist.github.com/markcwebster/9bdf30655cdd5279bad13993ac87c85d -->
		</style>
	</head>
	<body>

	<div class="header">
		<div class="container">
		<h1>NeverSSL</h1>
		</div>
	</div>

	<div class="content">
	<div class="container">

	<h2>What?</h2>
	<p>This website is for when you try to open Facebook, Google, Amazon, etc
	on a wifi network, and nothing happens. Type "http://neverssl.com"
	into your browser's url bar, and you'll be able to log on.</p>

	<h2>How?</h2>
	<p>neverssl.com will never use SSL (also known as TLS). No
	encryption, no strong authentication, no <a
	href="https://en.wikipedia.org/wiki/HTTP_Strict_Transport_Security">HSTS</a>,
	no HTTP/2.0, just plain old unencrypted HTTP and forever stuck in the dark
	ages of internet security.</p>

	<h2>Why?</h2>
	<p>Normally, that's a bad idea. You should always use SSL and secure
	encryption when possible. In fact, it's such a bad idea that most websites
	are now using https by default.</p>

	<p>And that's great, but it also means that if you're relying on
	poorly-behaved wifi networks, it can be hard to get online.  Secure
	browsers and websites using https make it impossible for those wifi
	networks to send you to a login or payment page. Basically, those networks
	can't tap into your connection just like attackers can't. Modern browsers
	are so good that they can remember when a website supports encryption and
	even if you type in the website name, they'll use https.</p>

	<p>And if the network never redirects you to this page, well as you can
	see, you're not missing much.</p>

	<a href="https://twitter.com/neverssl">Follow @neverssl</a>

	</div>
	</div>
	</body>
</html>
)";

    CHECK(response4.getContent() == contentToCheck);

}