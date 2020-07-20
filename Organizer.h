#pragma once
#include<iostream>
#include<string>
#include<ctime>
#include<map>
#include<time.h>
#include <vector>
#include<fstream>
#include<Windows.h>
#include <iomanip>
#pragma warning (disable:4996)
using namespace std;
class Exception
{
	string message;
public:
	Exception() {}
	Exception(string message) { this->message = message; }
	string Get() { return message; }
};
class Organaizer
{
	multimap<time_t,string> organaizer;
	void Add();
	void Delete();
	void Redact();
	void TimeEntry(struct tm& time_);
	bool DayCheck(int m, int d, int y);
	void Show();
	void ShowDate();
	void Save();
	void Load();
	bool Figures(string str);
public:
	Organaizer();
	void Menu(bool &key);
	
};


