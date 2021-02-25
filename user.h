#ifndef USER_H
#define USER_H
#include <iostream>
#include<string>
using namespace std;
class user
{
private:
	int id;
	string location;
	string destination;
	string type;
public:
	user(int x, string loc, string dest, string typ)
	{
		id = x;
		location = loc;
		destination = dest;
		type = typ;
	}

	user()
	{
		id = 0;
		location = "empty";
		destination = "empty";
		type = "empty";
	}

	void operator=(user *e)
	{
		id = e->getid();
		location = e->getloc();
		destination = e->getdest();
		type = e->gettype();
	}

	string getdest()
	{
		return destination;
	}

	string getloc()
	{
		return location;
	}

	string gettype()
	{
		return type;
	}

	int getid()
	{
		return id;
	}
};
#endif