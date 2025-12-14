#include <iostream>
#include <algorithm>
#include "student.h"
#include "database.h"

template <typename T>
Database<T>::Database()
{

}

template <typename T>
Database<T>::~Database()
{
	database.open(fName, std::ios::in | std::ios::binary);
	if (!database) {
		return;
	}

	char tempFName[4] = "tmp";
	std::fstream tempFile(tempFName, std::ios::out | std::ios::binary);
	if (!tempFile) {
		database.close();
		std::cerr << "Error: Could not create temporary file for cleanup.\n";
		return;
	}

	T tmp;
	while (database.peek() != std::char_traits<char>::eof())
	{
		tmp.readFromFile(database);
		if (database.good() && !tmp.isNull())
		{
			tmp.writeToFile(tempFile);
		}
	}

	database.close();
	tempFile.close();

	if (std::remove(fName) != 0) {
		std::cerr << "Error: Could not delete the old data file (" << fName << ").\n";
		std::remove(tempFName);
		return;
	}

	if (std::rename(tempFName, fName) != 0) {
		std::cerr << "Error: Could not rename the temporary file to the original name.\n";
	}
}

template <typename T>
void Database<T>::buildIndices()
{
	indices.clear();
	database.open(fName, ios::in | ios::binary);
	if (!database) return;

	while (database.peek() != EOF)
	{
		streampos pos = database.tellg();
		T tmp;
		tmp.readFromFile(database);
		if (!tmp.isNull())
			indices.push_back(pos);
	}
	database.close();

	sort(indices.begin(), indices.end(),
		[this](streampos pos1, streampos pos2) {
			return this->compareIDs(pos1, pos2);
		});
}

template <typename T>
void Database<T>::add(T& d)
{
	database.open(fName, ios::out | ios::app | ios::binary);
	streampos pos = database.tellp();
	d.writeToFile(database);
	database.close();
	buildIndices();
}

template <typename T>
void Database<T>::modify(const T& d)
{
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	while (true)
	{
		tmp.readFromFile(database);
		if (!database) break;
		if (tmp == d)
		{
			cin >> tmp;
			database.seekp(-d.size(), ios::cur);
			tmp.writeToFile(database);
			database.close();
			return;
		}
	}
	database.close();
	cout << "The record to be modified is not in the database.\n" << endl;
}

template <typename T>
void Database<T>::remove(const T& d)
{
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	while (true)
	{
		tmp.readFromFile(database);
		if (!database) break;
		if (tmp == d)
		{
			database.seekp(-d.size(), ios::cur);
			tmp.writeNullToFile(database);
			database.close();
			buildIndices();
			return;
		}
	}
	database.close();
	cout << "The record to be removed is not in the database.\n" << endl;
}

template <typename T>
bool Database<T>::find(const T& d)
{
	if (indices.empty()) 
	{
		database.open(fName, ios::in | ios::binary);
		database.close();
		return false;
	}
	int low = 0;
	int high = indices.size() - 1;
	T currentRec;

	while(low <= high)
	{
		int mid = low + (high - low)/2;
		currentRec = readAt(indices[mid]);
		if (currentRec == d)
			return true;
		else if (currentRec < d)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return false;
}

template <typename T>
T Database<T>::readAt(streampos pos)
{
	std::fstream in(fName, ios::in | ios::binary);
	if (!in) {
		throw std::runtime_error("Cannot open database file");
	}

	in.seekg(pos);
	T tmp;
	tmp.readFromFile(in);
	return tmp;
}

template <typename T>
bool Database<T>::compareIDs(streampos pos1, streampos pos2)
{
	T tmp1 = readAt(pos1);
	T tmp2 = readAt(pos2);
	return tmp1 < tmp2;
}

template <typename T>
ostream& Database<T>::print(ostream& out)
{
	std::vector<T> records;
	database.open(fName, ios::in | ios::binary);
	for (auto pos : indices)
	{
		T tmp;
		database.seekg(pos);
		tmp.readFromFile(database);
		out << tmp << endl;
	}

	database.close();

	return out;
}

template <typename T>
void Database<T>::run()
{
	cout << "File name: ";
	cin >> fName;
	cin.ignore();
	buildIndices();
	char option[6];
	T rec;
	cout << "1. Add 2. Find 3. Modify a record; 4. Remove 5. Exit\n" << endl;
	cout << "Enter an option: ";
	while (cin.getline(option, 4))
	{
		if (*option == '1')
		{
			cin >> rec;
			add(rec);
		}
		else if (*option == '2')
		{
			rec.readKey();
			cout << "The record is ";
			if (find(rec) == false)
				cout << "not ";
			cout << "in the database.\n";
		}
		else if (*option == '3')
		{
			rec.readKey();
			modify(rec);
		}
		else if (*option == '4')
		{
			rec.readKey();
			remove(rec);
		}
		else if (*option != '5')
			cout << "Wrong option. Try again.\n";
		else return;
		cout << *this;
		cout << "Enter an option: ";
	}
}

int main()
{
	Database<Student>().run();
	return 0;
}