#ifndef STUDENT_H
#define STUDENT_H

#include "personal.h"

class Student : public Personal
{
public:
	Student();
	Student(char*, char*, char*, int, long, char*);
	Student(const Student&);
	Student& operator=(const Student&);
	~Student()
	{
		delete[] major;
	}
	void writeToFile(fstream&) const;
	void readFromFile(fstream&);
	int size() const
	{
		return Personal::size() + majorLen;
	}
	bool operator<(const Student& sr) const
	{
		if (Personal::operator<(sr)) return true;
		if (*this == sr)
		{
			return strncmp(major, sr.major, majorLen) < 0;
		}
		return false;
	}
	bool operator>(const Student& sr) const
	{
		if (Personal::operator>(sr)) return true;
		if (*this == sr)
		{
			return strncmp(major, sr.major, majorLen) > 0;
		}
		return false;
	}
protected:
	char* major;
	const int majorLen;
	ostream& writeLegibly(ostream&);
	friend ostream& operator<<(ostream& out, Student& sr)
	{
		return sr.writeLegibly(out);
	}
	istream& readFromConsole(istream&);
	friend istream& operator>>(istream& in, Student& sr)
	{
		return sr.readFromConsole(in);
	}
};

#endif