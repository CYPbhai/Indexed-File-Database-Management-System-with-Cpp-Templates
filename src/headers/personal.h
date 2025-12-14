#ifndef PERSONAL_H
#define PERSONAL_H
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

class Personal
{
public:
	Personal();
	Personal(const Personal&);
	Personal(char*, char*, char*, int, long);
	Personal& operator=(const Personal&);
	~Personal()
	{
		delete[] name;
		delete[] city;
	}
	void writeToFile(fstream&) const;
	void writeNullToFile(fstream&) const;
	void readFromFile(fstream&);
	void readKey();
	bool isNull() const
	{
		return !isdigit(SSN[0]);
	}
	int size() const
	{
		return 9 + nameLen + cityLen + sizeof(year) + sizeof(salary);
	}
	bool operator==(const Personal& pr) const
	{
		return strncmp(pr.SSN, SSN, 9) == 0;
	}
	bool operator<(const Personal& pr) const
	{
		return strncmp(SSN, pr.SSN, 9) < 0;
	}
	bool operator>(const Personal& pr) const
	{
		return strncmp(SSN, pr.SSN, 9) > 0;
	}
protected:
	const int nameLen, cityLen;
	char SSN[10], * name, * city;
	int year;
	long salary;
	ostream& writeLegibly(ostream&);
	friend ostream& operator<<(ostream& out, Personal& pr)
	{
		return pr.writeLegibly(out);
	}
	istream& readFromConsole(istream&);
	friend istream& operator>>(istream& in, Personal& pr)
	{
		return pr.readFromConsole(in);
	}

};

#endif // PERSONAL_H