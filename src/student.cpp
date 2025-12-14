#include "student.h"

Student::Student() : Personal(), majorLen(10)
{
	major = new char[majorLen + 1];
}

Student::Student(char* ssn, char* n, char* c, int y, long s, char* mj) :
	Personal(ssn, n, c, y, s), majorLen(10)
{
	major = new char[majorLen + 1];
	strncpy(major, mj, majorLen);
	major[majorLen] = '\0';
}

Student::Student(const Student& other)
	: Personal(other), majorLen(other.majorLen)
{
	major = new char[majorLen + 1];
	strncpy(major, other.major, majorLen);
}

Student& Student::operator=(const Student& other)
{
	if (this != &other)
	{
		Personal::operator=(other);
		delete[] major;
		major = new char[other.majorLen + 1];
		strncpy(major, other.major, majorLen);
	}
	return *this;
}

void Student::writeToFile(fstream& out) const
{
	Personal::writeToFile(out);
	out.write(major, majorLen);
}

void Student::readFromFile(fstream& in)
{
	Personal::readFromFile(in);
	in.read(major, majorLen);
}

ostream& Student::writeLegibly(ostream& out)
{
	Personal::writeLegibly(out);
	major[majorLen] = '\0';
	out << ", Major = " << major;
	return out;
}

istream& Student::readFromConsole(istream& in)
{
	Personal::readFromConsole(in);
	cout << "Enter Major: ";
	in.getline(major, majorLen);
	return in;
}