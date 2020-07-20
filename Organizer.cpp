#include"Organizer.h"
Organaizer::Organaizer() { Load(); }
void Organaizer::Menu(bool &key)
{
	system("cls");
	int choice;
	cout << "1 - Add a reminder" << endl;
	cout << "2 - Delete a reminder" << endl;
	cout << "3 - Redact a reminder" << endl;
	cout << "4 - Show all reminders" << endl;
	cout << "5 - Save to file" << endl;
	//cout << "6 - Load from file" << endl;
	cout << "0 - Exit " << endl;
	while (true)
	{
		cout << "0 - 5 : ";
		if (!(cin >> choice))
		{
			cout << "0 - 5! : ";
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (choice == 0)key = false;
		if (choice >= 0 && choice < 6)break;
	}
	switch (choice)
	{
	case 1:Add(); break;
	case 2:Delete(); break;
	case 3:Redact(); break;
	case 4:Show(); break;
	case 5:Save(); break;
	case 0:break;
		break;
	}
}
void Organaizer::Add()
{
	system("cls");
	int key = 1;
	string remaind;
	time_t t = time(&t);
	struct tm* time_;
	time_ = localtime(&t);
	TimeEntry(*time_);
	cout << "\nEnter Reminder Text :";
	cin.ignore(247, '\n');
	getline(cin,remaind);
	t = mktime(time_);
	organaizer.emplace(t, remaind);
}

void Organaizer::Delete()
{
	system("cls");
	ShowDate();
	if (organaizer.empty())cout << "\nOrganaizer empty!" << endl;
	cout << "\nEnter date reminder :";
	time_t t= time(&t);
	struct tm* time_;
	time_ = localtime(&t);
	TimeEntry(*time_);
	t = mktime(time_);
	multimap<time_t, string>::iterator it = organaizer.find(t);
	if (it == organaizer.end())throw Exception("\nNot found!");
	organaizer.erase(it);
}
void Organaizer::Redact()
{
	system("cls");
	ShowDate();
	cin.clear();
	string str;
	if (organaizer.empty())
		cout << "\nOrganaizer empty!" << endl;
	else
	{
		cout << "\nEnter date reminder : ";
		time_t t = time(&t);
		struct tm* time_;
		time_ = localtime(&t);
		TimeEntry(*time_);
		t = mktime(time_);
		multimap<time_t, string>::iterator it = organaizer.find(t);
		if (it == organaizer.end())throw Exception("\nNot found!");
		system("cls");
		cout << "\nEnter reminder text : ";
		cin.ignore(247, '\n');
		getline(cin, str);
		it->second = str;
	}
}
void Organaizer::TimeEntry(struct tm&time_)
{
	int year, months,day, hours, minuts;
	cin.clear();
		cout << "\nEnter year (>2020) :";
		cin >> year;
		if (year < 2020)throw Exception("\nIncorrect year entry!");
		time_.tm_year= year - 1900;
		cout << "\nEnter months (1-12) :";
		cin >> months;
		if (months < 1 || 12 < months)throw Exception("\nIncorrect months entry!");
		time_.tm_mon = months-1;
		cout << "\nEnter the day of the month : ";
		cin >> day;
		if (day < 1 || !DayCheck(months, day, year))throw Exception("\nIncorrect day entry!");
		time_.tm_mday = day;
		cout << "\nEnter hour(0-24) :";
		cin >> hours;
		if (hours < 0 || 24 < hours)throw Exception("Incorrect time day");
		time_.tm_hour = hours;
		cout << "\nEnter minuts(0-59) :";
		cin >> minuts;
		if(minuts<0||59<minuts)throw Exception("Incorrect time day");
		time_.tm_min = minuts;
		time_.tm_sec = 00;
}
bool Organaizer::DayCheck(int m,int d,int y)
{
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 10 || m == 12)
		if (d <= 31)return true;
	if (m == 2)
	{
		if (y % 4 != 0)
			if (d <= 28)return true;
		if (y % 4 == 0)
			if (d <= 29)return true;
	}
	if (m == 4 || m == 6 || m == 8 || m == 9 || m == 11)
		if (d <= 30)return true;
	
	return false;
}
void Organaizer::Show()
{
	system("cls");
	multimap<time_t, string>::iterator it;
	for (auto a : organaizer)
		cout << ctime(&a.first)  << a.second << endl;
	system("pause");
	
}
void Organaizer::ShowDate()
{
	system("cls");
	multimap<time_t, string>::iterator it;
	for (auto a : organaizer)
		cout << ctime(&a.first) << endl;
	
}
void Organaizer::Save()
{
	ofstream fout("file.txt");
	if (!fout.is_open())throw Exception("\nCannot open file!");
	multimap<time_t, string>::iterator it;
	for (it=organaizer.begin();it!=organaizer.end();it++)
	{
		fout << ctime(&it->first);
		fout << it->first<<endl;
		fout << it->second<<endl;
	}
}
void Organaizer::Load()
{
	string str;
	unsigned long int time_;
	ifstream fin("file.txt");
	if(!fin.is_open())Save();
	while (!fin.eof())
	{
		getline(fin,str);
		if (str.empty())break;
		if (str[13]==':'&&str[16]==':')
			getline(fin, str);
		if (Figures(str))
			time_ = atoi(str.c_str());
		getline(fin, str);
			organaizer.emplace(time_, str);
		if (fin.eof())
			break;
	
	}
}
bool Organaizer::Figures(string str)
{
	for (int i = 0; i < str.size(); i++)
		if (!isdigit(str[i]))
			return false;
	
	return true;
}