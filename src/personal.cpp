#include "personal.h"

Personal::Personal() :nameLen(10), cityLen(10)
{
	name = new char[nameLen + 1];
	city = new char[cityLen + 1];
}

Personal::Personal(char* ssn, char* n, char* c, int y, long s) :
	nameLen(10), cityLen(10)
{
	name = new char[nameLen + 1];
	city = new char[cityLen + 1];
	strncpy(SSN, ssn, 9);
	SSN[9] = '\0';
	strncpy(name, n, nameLen);
	name[nameLen] = '\0';
	strncpy(city, c, cityLen);
	city[cityLen] = '\0';
	year = y;
	salary = s;
}

void Personal::writeToFile(fstream& out) const
{
	out.write(SSN, 9);
	out.write(name, nameLen);
	out.write(city, cityLen);
	out.write(reinterpret_cast<const char*> (&year), sizeof(int));
	out.write(reinterpret_cast<const char*> (&salary), sizeof(long));
}

void Personal::writeNullToFile(fstream& out) const
{
	Personal nullRec = *this;
	nullRec.SSN[0] = '#';
	nullRec.writeToFile(out);
}

void Personal::readFromFile(fstream& in)
{
	in.read(SSN, 9);
	in.read(name, nameLen);
	in.read(city, cityLen);
	in.read(reinterpret_cast<char*> (&year), sizeof(int));
	in.read(reinterpret_cast<char*> (&salary), sizeof(long));
}

void Personal::readKey()
{
	cout << "Enter SSN: ";
	cin.getline(SSN, 10);
}

Personal::Personal(const Personal& other)
	: nameLen(other.nameLen), cityLen(other.cityLen), year(other.year), salary(other.salary)
{
	strncpy(SSN, other.SSN, 9);
	name = new char[nameLen + 1];
	city = new char[cityLen + 1];
	strncpy(name, other.name, nameLen);
	strncpy(city, other.city, cityLen);
}

Personal& Personal::operator=(const Personal& other)
{
	if (this != &other)
	{
		strncpy(SSN, other.SSN, 9);
		year = other.year;
		salary = other.salary;

		delete[] name;
		delete[] city;

		name = new char[other.nameLen + 1];
		city = new char[other.cityLen + 1];
		strncpy(name, other.name, nameLen);
		strncpy(city, other.city, cityLen);
	}
	return *this;
}

ostream& Personal::writeLegibly(ostream& out)
{
	SSN[9] = name[nameLen] = city[cityLen] = '\0';
	out << "SSN = " << SSN << ", Name = " << name
		<< ", City = " << city << ", Year = " << year
		<< ", Salary = " << salary;
	return out;
}

istream& Personal::readFromConsole(istream& in)
{
	SSN[9] = name[nameLen] = city[cityLen] = '\0';
	cout << "SSN: ";
	in.getline(SSN, 10);
	cout << "Name: ";
	in.getline(name, nameLen);
	cout << "City: ";
	in.getline(city, cityLen);
	cout << "Birthyear: ";
	in >> year;
	cout << "Salary: ";
	in >> salary;
	in.ignore();
	return in;
}