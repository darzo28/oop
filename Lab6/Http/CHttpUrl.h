#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};
//учесть кейсы HttPs

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	std::string GetProtocolString() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	unsigned short GetDefaultPort(Protocol protocol);
	void ValidDomain(std::string const& strDomain); //Validate
	void ValidDocument(std::string const& strDocument);
	void ValidProtocol(std::string const& strProtocol); // Parse - возвращает исключение (может быть записан в любом регистре)
	void ValidPort(std::string const& strPort); // сделать свободными функциями, Parse - проверка диапазона и возврат числа

	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
// заглавные буквы в схеме, domain не пустой, ':' корректно парсится (/:81 - документ, :81/ - порт), переполнение в номере порта, дефолтный порт не должен добавляться
