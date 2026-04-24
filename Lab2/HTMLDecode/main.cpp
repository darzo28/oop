#include <iostream>
#include "HTMLDecode.h"

using namespace std;

int main()
{
	string str;
	while (getline(cin, str))
	{
		cout << HtmlDecode(str) << endl;
	}
}
