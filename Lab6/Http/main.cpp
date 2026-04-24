#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <iostream>

using namespace std;

const std::string HINT = "Valid URL: <protocol>://<domain>(:<port>)(/<document>)";
const std::string URL = "URL: ";
const std::string PROTOCOL_URL = "PROTOCOL: ";
const std::string DOMAIN_URL = "DOMAIN: ";
const std::string PORT_URL = "PORT: ";
const std::string DOCUMENT_URL = "DOCUMENT: ";

int main()
{
	string urlStr;

	cout << HINT << endl;

	while (getline(cin, urlStr))
	{
		try
		{
			CHttpUrl url(urlStr);

			cout << URL << url.GetURL() << endl;
			cout << PROTOCOL_URL << url.GetProtocolString() << endl;
			cout << DOMAIN_URL << url.GetDomain() << endl;
			cout << PORT_URL << url.GetPort() << endl;
			cout << DOCUMENT_URL << url.GetDocument() << endl;
		}
		catch (const CUrlParsingError& err)
		{
			cout << err.what() << endl;
		}
		cout << endl;
	}

	return 0;
}
