#ifndef DATABASE_H
#define DATABASE_H
#include <vector>

template <typename T>
class Database
{
public:
	Database();
	~Database();
	void run();
private:
	fstream database;
	char fName[20];
	vector<streampos> indices;
	ostream& print(ostream&);
	void buildIndices();
	void add(T&);
	bool find(const T&);
	void modify(const T&);
	void remove(const T&);
	T readAt(streampos);
	bool compareIDs(streampos, streampos);
	friend ostream& operator<<(ostream& out, Database<T>& db)
	{
		return db.print(out);
	}
};

#endif