#include "Organizer.h"
#pragma once
#include<vector>
int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool key = true;
	Organaizer o;
	while (key)
	{
		try
		{
			o.Menu(key);
		}
		catch (Exception message_)
		{
			cout << message_.Get();
			cout << "\nAdd date again ? 1 - Yes , 0 - Exit" << endl;
			if (!(cin >> key))
			{
				cout << "\n1 or 0 !" << endl;
				cin.clear();
				cin.ignore(50, '\n');
				if (!key)exit(0);
			}
		}
	}
   
}