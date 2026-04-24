#include <iostream>
#include <string>
#include <sstream>
#include "FindMax.h"
#include "Sportsman.h"

using namespace std;

int main()
{
	string str;
	vector<Sportsman> sportsmanVector;

	while (getline(cin, str))
	{
		istringstream stream(str);
		string name;
		string height;
		string weight;

		stream >> name >> height >> weight;
		
		if (name != "" && height != "" && weight != "")
		{
			try
			{
				sportsmanVector.push_back({name, stod(height), stod(weight)});
			}
			catch(exception&)
			{
				cout << "Invalid values" << endl;
			}
		}
	}

	if (sportsmanVector.empty())
	{
		cout << "No sportsmen found" << endl;
	}
	else
	{
		Sportsman sportsman;
		FindMax(sportsmanVector, sportsman, CompareName);
		cout << sportsman.name << ' ' << sportsman.height << ' ' << sportsman.weight << endl;
		FindMax(sportsmanVector, sportsman, CompareHeight);
		cout << sportsman.name << ' ' << sportsman.height << ' ' << sportsman.weight << endl;
		FindMax(sportsmanVector, sportsman, CompareWeight);
		cout << sportsman.name << ' ' << sportsman.height << ' ' << sportsman.weight << endl;
	}

	return 0;
}