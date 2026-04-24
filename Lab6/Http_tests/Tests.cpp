#define CATCH_CONFIG_MAIN
#include "../Http/CHttpUrl.h"
#include "../Http/CUrlParsingError.h"
#include "../Http/Const.h"
#include "../../catch.hpp"

void CheckUrlString(std::string const& urlStr, std::string const& urlProtocol, std::string const& urlDomain, int urlPort, std::string const& urlDocument)
{
	CHttpUrl url(urlStr);
	CHECK(url.GetURL() == urlStr);
	CHECK(url.GetProtocolString() == urlProtocol);
	CHECK(url.GetDomain() == urlDomain);
	CHECK(url.GetPort() == urlPort);
	CHECK(url.GetDocument() == urlDocument);
}

void CheckUrlWithoutPort(std::string const& urlStr, Protocol urlProtocol, std::string const& urlDomain, std::string const& urlDocument)
{
	int urlPort;
	CHttpUrl url(urlDomain, urlDocument, urlProtocol);
	CHECK(url.GetURL() == urlStr);
	CHECK(url.GetProtocol() == urlProtocol);
	CHECK(url.GetDomain() == urlDomain);
	(urlProtocol == Protocol::HTTP) ? urlPort = HTTP_PORT : urlPort = HTTPS_PORT;
	CHECK(url.GetPort() == urlPort);
	CHECK(url.GetDocument() == urlDocument);
}

void CheckUrlWithPort(std::string const& urlStr, Protocol urlProtocol, std::string const& urlDomain, int urlPort, std::string const& urlDocument)
{
	CHttpUrl url(urlDomain, urlDocument, urlProtocol, urlPort);
	CHECK(url.GetURL() == urlStr);
	CHECK(url.GetProtocol() == urlProtocol);
	CHECK(url.GetDomain() == urlDomain);
	CHECK(url.GetPort() == urlPort);
	CHECK(url.GetDocument() == urlDocument);
}

TEST_CASE("Check Url String")
{
	SECTION("Port default HTTPS")
	{
		std::string urlStr = "HTTPS://drive.google.com/drive/folders/0B8c4dq91MwITUk1RU1ZwWjFsWUk";
		CheckUrlString(urlStr, "https", "drive.google.com", HTTPS_PORT, "/drive/folders/0B8c4dq91MwITUk1RU1ZwWjFsWUk");
	}

	SECTION("Port default HTTP")
	{
		std::string urlStr = "HTTP://lks.volgatech.net/ExamList";
		CheckUrlString(urlStr, "http", "lks.volgatech.net", HTTP_PORT, "/ExamList");
	}

	SECTION("Port 73 HTTPS")
	{
		std::string urlStr = "https://www.youtube.com:73/?gl=RU&hl=ru";
		CheckUrlString(urlStr, "https", "www.youtube.com", 73, "/?gl=RU&hl=ru");
	}

	SECTION("Valide document")
	{
		std::string urlStr = "https://www.youtube.com:34/doc";
		CheckUrlString(urlStr, "https", "www.youtube.com", 34, "/doc");
	}

	SECTION("Port installed HTTP port MIN_NUMBER_PORT")
	{
		std::string urlStr = "HTTP://www.my-site-time.com:1/docs/document1.html?page=3450&lang=en#zero17";
		CheckUrlString(urlStr, "http", "www.my-site-time.com", MIN_NUMBER_PORT, "/docs/document1.html?page=3450&lang=en#zero17");
	}

	SECTION("Port installed HTTP port MAX_NUMBER_PORT")
	{
		std::string urlStr = "HTTP://www.mysite-time.com:65535/docs/document1.html?page=3450&lang=en#zero17";
		CheckUrlString(urlStr, "http", "www.mysite-time.com", MAX_NUMBER_PORT, "/docs/document1.html?page=3450&lang=en#zero17");
	}

	SECTION("Port less MIN_NUMBER_PORT")
	{
		std::string urlStr = "https://www.google.com:0/doc";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Port more MAX_NUMBER_PORT")
	{
		std::string urlStr = "https://www.google.com:65536/doc";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Url empty")
	{
		std::string urlStr = "";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Invalid URL input")
	{
		std::string urlStr = "https://www.google.com:hello/doc";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Invalid URL port")
	{
		std::string urlStr = "https://www.google.com:-1/doc";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Invalid URL domain")
	{
		std::string urlStr = "https://www.?%google.com/doc";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Invalid URL document")
	{
		std::string urlStr = "https://drive.google.com/ument1.html?page=3450&lang={{{{{{{}}}}[]en#zero";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Invalid Url Protocol")
	{
		std::string urlStr = "https::/www.google.com:hello/doc";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}

	SECTION("Unknown Protocol type")
	{
		std::string urlStr = "hello://www.google.com/doc";
		CHECK_THROWS_AS(CHttpUrl(urlStr), CUrlParsingError);
	}
}

TEST_CASE("Check Url Without Port")
{
	SECTION("HTTP not empty document")
	{
		std::string urlStr = "http://mathhelpplanet.com/static.php?p=onlain-reshit-treugolnik";
		CheckUrlWithoutPort(urlStr, Protocol::HTTP, "mathhelpplanet.com", "/static.php?p=onlain-reshit-treugolnik");
	}

	SECTION("HTTP empty document")
	{
		std::string urlStr = "http://mathhelpplanet.com/";
		CheckUrlWithoutPort(urlStr, Protocol::HTTP, "mathhelpplanet.com", "/");
	}

	SECTION("HTTPS not empty document")
	{
		std::string urlStr = "https://mathhelpplanet.com/document";
		CheckUrlWithoutPort(urlStr, Protocol::HTTPS, "mathhelpplanet.com", "/document");
	}

	SECTION("HTTPS empty document")
	{
		std::string urlStr = "https://mathhelpplanet.com/";
		CheckUrlWithoutPort(urlStr, Protocol::HTTPS, "mathhelpplanet.com", "/");
	}

	SECTION("Invalid URL document")
	{
		CHECK_THROWS_AS(CHttpUrl("mathhelpplanet.com", "////", Protocol::HTTP), CUrlParsingError);
	}

	SECTION("Invalid URL domain")
	{
		CHECK_THROWS_AS(CHttpUrl("www.googl^e.com", "/doc", Protocol::HTTPS), CUrlParsingError);
	}
}

TEST_CASE("Check Url With Port")
{
	SECTION("HTTP not empty document")
	{
		std::string urlStr = "http://vk.com:832/audios62352g721709";
		CheckUrlWithPort(urlStr, Protocol::HTTP, "vk.com", 832, "/audios62352g721709");
	}

	SECTION("HTTP empty document")
	{
		std::string urlStr = "http://vk.com:214/";
		CheckUrlWithPort(urlStr, Protocol::HTTP, "vk.com", 214, "/");
	}

	SECTION("HTTPS not empty document")
	{
		std::string urlStr = "https://www.instagram.com:345/qwerty_12354/";
		CheckUrlWithPort(urlStr, Protocol::HTTPS, "www.instagram.com", 345, "/qwerty_12354/");
	}

	SECTION("HTTPS empty document")
	{
		std::string urlStr = "https://www.instagram.com:452/";
		CheckUrlWithPort(urlStr, Protocol::HTTPS, "www.instagram.com", 452, "/");
	}

	SECTION("Port installed HTTPS port MIN_NUMBER_PORT")
	{
		std::string urlStr = "https://www.youtube.com:1/channel/UClJtObQ9SXkMZH2+#a9oNnrQg/videos";
		CheckUrlWithPort(urlStr, Protocol::HTTPS, "www.youtube.com", MIN_NUMBER_PORT, "/channel/UClJtObQ9SXkMZH2+#a9oNnrQg/videos");
	}

	SECTION("Port installed HTTPS port MAX_NUMBER_PORT")
	{
		std::string urlStr = "https://www.youtube.com:65535/channel/UClJtObQ9SXkMZH2+#a9oNnrQg/videos";
		CheckUrlWithPort(urlStr, Protocol::HTTPS, "www.youtube.com", MAX_NUMBER_PORT, "/channel/UClJtObQ9SXkMZH2+#a9oNnrQg/videos");
	}

	SECTION("Port installed HTTP port MIN_NUMBER_PORT")
	{
		std::string urlStr = "http://docs.google.com:1/document/d/1dNLLhQuncX2M6xmuEz94WBhJvPlN0tGuTMCl4yxvdlU/edit#heading=h.1bvo66paeh0j";
		CheckUrlWithPort(urlStr, Protocol::HTTP, "docs.google.com", MIN_NUMBER_PORT, "/document/d/1dNLLhQuncX2M6xmuEz94WBhJvPlN0tGuTMCl4yxvdlU/edit#heading=h.1bvo66paeh0j");
	}

	SECTION("Port installed HTTP port MAX_NUMBER_PORT")
	{
		std::string urlStr = "http://docs.google.com:65535/document/d/1dNLLhQuncX2M6xmuEz94WBhJvPlN0tGuTMCl4yxvdlU/edit#heading=h.1bvo66paeh0j";
		CheckUrlWithPort(urlStr, Protocol::HTTP, "docs.google.com", MAX_NUMBER_PORT, "/document/d/1dNLLhQuncX2M6xmuEz94WBhJvPlN0tGuTMCl4yxvdlU/edit#heading=h.1bvo66paeh0j");
	}

	SECTION("Port less MIN_NUMBER_PORT")
	{
		CHECK_THROWS_AS(CHttpUrl("www.google.com", "/doc", Protocol::HTTPS, 0), CUrlParsingError);
	}

	SECTION("Port more MAX_NUMBER_PORT")
	{
		CHECK_THROWS_AS(CHttpUrl("www.google.com", "/doc", Protocol::HTTPS, 65536), CUrlParsingError);
	}

	SECTION("Invalid URL document")
	{
		CHECK_THROWS_AS(CHttpUrl("www.instagram.com", "///", Protocol::HTTPS, 452), CUrlParsingError);
	}

	SECTION("Invalid URL domain")
	{
		CHECK_THROWS_AS(CHttpUrl("www.googl^e.com", "/doc", Protocol::HTTPS, 23), CUrlParsingError);
	}
}