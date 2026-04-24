#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>

const unsigned short HTTP_PORT = 80;
const unsigned short HTTPS_PORT = 443;

const unsigned short MIN_NUMBER_PORT = 1;
const unsigned short MAX_NUMBER_PORT = 65535;

const unsigned short MATCH_PROTOCOL_URL = 1;
const unsigned short MATCH_DOMAIN_URL = 2;
const unsigned short MATCH_PORT_URL = 3;
const unsigned short MATCH_DOCUMENT_URL = 4;

const std::string URL_REGULAR_EXPRESSION = R"((http|HTTP|https|HTTPS)://([[:alnum:]-\\.]+)(?:\:([[:digit:]]+))?(?:\/(\S*))?$)";
const std::string DOMAIN_REGULAR_EXPRESSION = R"(^([[:alnum:]-\\.]+)$)";

const std::string HTTP_STRING = "http";
const std::string HTTPS_STRING = "https";

const std::string URL_INPUT_ERROR = "Invalid URL input";
const std::string URL_PORT_ERROR = "Invalid URL port";
const std::string URL_DOMAIN_ERROR = "Invalid URL domain";
const std::string URL_DOCUMENT_ERROR = "Invalid URL document";
const std::string URL_PROTOCOL_UNKNOWN_ERROR = "Unknown Protocol type";
const std::string URL_EMPTY_ERROR = "Url is empty";

const std::string SLASH_STRING = "/";
const char SLASH_CHAR = '/';

CHttpUrl::CHttpUrl(std::string const& url)
{
	if (url.empty())
	{
		throw CUrlParsingError(URL_EMPTY_ERROR);
	}

	std::regex strRegex(URL_REGULAR_EXPRESSION);

	std::smatch match;

	if (!regex_match(url, match, strRegex))
	{
		throw CUrlParsingError(URL_INPUT_ERROR);
	}

	m_protocol = ValidProtocol(match.str(MATCH_PROTOCOL_URL));
	m_domain = ValidDomain(match.str(MATCH_DOMAIN_URL));

	if (!match.str(MATCH_PORT_URL).empty())
	{
		m_port = ValidPort(match.str(MATCH_PORT_URL));
	}
	else
	{
		m_port = GetDefaultPort(m_protocol);
	}

	m_document = ValidDocument(match.str(MATCH_DOCUMENT_URL));
	m_url = url;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = Protocol::HTTP)
	: m_domain(ValidDomain(domain))
	, m_document(ValidDocument(document))
	, m_protocol(protocol)
{
	m_port = GetDefaultPort(protocol);
	m_url = GetProtocolString() + "://" + m_domain + m_document;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_domain(ValidDomain(domain))
	, m_document(ValidDocument(document))
	, m_protocol(protocol)
{
	if (port < MIN_NUMBER_PORT || port > MAX_NUMBER_PORT)
	{
		throw CUrlParsingError(URL_PORT_ERROR);
	}

	m_port = port;
	m_url = GetProtocolString() + "://" + m_domain + ":" + std::to_string(m_port) + m_document;
}

Protocol CHttpUrl::ValidProtocol(std::string const& strProtocol)
{
	if (ToLowerCase(strProtocol) == HTTPS_STRING)
	{
		return Protocol::HTTPS;
	}
	else if (ToLowerCase(strProtocol) == HTTP_STRING)
	{
		return Protocol::HTTP;
	}
	else
	{
		throw CUrlParsingError(URL_PROTOCOL_UNKNOWN_ERROR);
	}
}

void CHttpUrl::ValidDomain(std::string const& strDomain)
{
	std::regex regex(DOMAIN_REGULAR_EXPRESSION);
	std::smatch match;
	if (!regex_match(strDomain, match, regex))
	{
		throw CUrlParsingError(URL_DOMAIN_ERROR);
	}
}

void CHttpUrl::ValidPort(std::string const& strPort)
{
	int port = std::stoi(strPort);
	if (port < MIN_NUMBER_PORT || port >= MAX_NUMBER_PORT)
	{
		throw CUrlParsingError(URL_PORT_ERROR);
	}
}

std::string CHttpUrl::ValidDocument(std::string const& strDocument)
{
	for (size_t i = 0; i < strDocument.length(); ++i)
	{
		if (strDocument[i] == SLASH_CHAR)
		{
			if (strDocument[i + 1] == SLASH_CHAR)
			{
				throw CUrlParsingError(URL_DOCUMENT_ERROR);
			}
		}

		if (strDocument[i] == '~' || strDocument[i] == '\'' || strDocument[i] == '"'
			|| strDocument[i] == ';' || strDocument[i] == '^' || strDocument[i] == '*' || strDocument[i] == '(' || strDocument[i] == ')'
			|| strDocument[i] == '[' || strDocument[i] == ']' || strDocument[i] == '{' || strDocument[i] == '}' || strDocument[i] == '|'
			|| strDocument[i] == '<' || strDocument[i] == '>')
		{
			throw CUrlParsingError(URL_DOCUMENT_ERROR);
		}
	}

	if (strDocument.empty())
	{
		return SLASH_STRING;
	}
	else if (strDocument[0] == SLASH_CHAR)
	{
		return strDocument;
	}
	else
	{
		return SLASH_STRING + strDocument;
	}
}

std::string ToLowerCase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return HTTP_PORT;
	case Protocol::HTTPS:
		return HTTPS_PORT;
	default:
		throw CUrlParsingError(URL_PROTOCOL_UNKNOWN_ERROR);
	}
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetProtocolString() const
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		return HTTP_STRING;
	case Protocol::HTTPS:
		return HTTPS_STRING;
	default:
		throw CUrlParsingError(URL_PROTOCOL_UNKNOWN_ERROR);
	}
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
