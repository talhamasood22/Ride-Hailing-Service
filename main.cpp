#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include "graph.h"
#include "edge.h"
#include "user.h"
using namespace std;

Graph<edge>* fileinput()
{
	string filename;
	cout<<"Enter the name of the file\n";
	cin>>filename;
	ifstream input;
	input.open(filename);
	if (!input.is_open())
	{
		cout << "file corrupted.\n";
		return 0;
	}
	cout << "File Exported! \n";
	int nofcities;
	input >> nofcities;
	Graph<edge> *g;
	g = new Graph<edge>(nofcities);
	string location, destination;
	double distance, cost;
	input.ignore();
	cout << "\n---------------------------------------------------------------------------------\n";
	while (!input.eof())
	{
		getline(input, location, '\t');
		getline(input, destination, '\t');
		input >> distance >> cost;
		edge *e = new edge(distance, cost);
		input.ignore();
		g->insertEdge(location, destination, e);
		cout << "( " << location << ", " << destination;
		cout << " ) distance " << distance;
		cout << "km and cost/passenger is " << cost << " for Bus Service" << endl;
	}
	cout << "\n---------------------------------------------------------------------------------\n";
	cout << endl;
	input.close();
	return g;
}

queue<user>* userinput()
{
	ifstream input;
	cout<<"Enter the name of the file that contains the user data\n";
	string userdata;
	cin>>userdata;
	input.open(userdata);
	if (!input.is_open())
	{
		cout << "file corrupted or does not exist!\n";
		return 0;
	}
	cout << "File Exported! \n";
	int nofusers;
	input >> nofusers;
	user *u = new user[nofusers];
	string location, destination, type;
	int id, i = 0;
	input.ignore();
	while (!input.eof())
	{
		input >> id;
		input.ignore();
		getline(input, location, '\t');
		getline(input, destination, '\t');
		getline(input, type, '\n');
		user *t = new user(id, location, destination, type);
		u[i] = t;
		i++;
	}
	queue<user> *q = new queue<user>();
	for (int j = 0; j < i; j++)
	{
		if (u[j].gettype() == "Premium User")
			q->push(u[j]);
	}
	for (int j = 0; j < i; j++)
	{
		if (u[j].gettype() == "Normal User")
			q->push(u[j]);
	}
	input.close();
	delete[]u;
	return q;
}

int main()
{
	cout << "\n---------------------------------------------------------------------------------\n";
	cout << "Welcome to Uber Services.\nPress 1 to input the data.\n";
	cout << "\n---------------------------------------------------------------------------------\n";
	char menu;
	int *cars=NULL;
	cin >> menu;
	cin.ignore();
	Graph<edge>* g = fileinput();
	if (!g)
		return 0;
	cout << endl;
	int index = 0;
	string city;
	queue<user> *q=NULL;
	do
	{
		cout << "\n---------------------------------------------------------------------------------\n";
		cout << "Enter 1 to find the minimum number of hops from one city to all the other cities.\n";
		cout << "Enter 2 to find and store the shortest paths between the cities.\n";
		cout << "Enter 3 to find shortest paths from a city to all other cities.\n";
		cout << "Enter 4 to read the data from the user data file\n";
		cout << "Enter 5 to assign cars to users and calculate the cost for travels.\n";
		cout << "Enter 6 to enter the bus service \n";
		cout << "Enter e to exit\n";
		cout << "\n---------------------------------------------------------------------------------\n";
		cin >> menu;
		cin.ignore();
		switch (menu)
		{
		case '1':
		{
			cout << "\n---------------------------------------------------------------------------------\n";
			cout << "Enter the city name\n";
			getline(cin, city, '\n');
			while (city != g->getcities()[index])
				index++;
			for (int j = 0; j < g->GetNumVertices(); j++)
			{
				if (index != j)
				{
					cout << "Minimum hops from " << city << " to " << g->getcities()[j] << " are ";
					g->breadthfirstSearch(index, j);
					cout << "\n";
				}
			}
			index = 0;
			cout << "\n---------------------------------------------------------------------------------\n";
			break;
		}
		case '2':
		{	
			for (int i = 0; i < g->GetNumVertices(); i++)
				g->dijkstra(i);
			cout << "\n---------------------------------------------------------------------------------\n";
			cout << "The shortest paths have been stored.\n"; 
			cout << "\n---------------------------------------------------------------------------------\n";
			break;
		}

		case '3':
		{
			cout << "\n---------------------------------------------------------------------------------\n";
			cout << "Enter the city you wish to see the shortest paths from.\n";
			getline(cin, city, '\n');
			while (city != g->getcities()[index])
				index++;
			for (int i = 0; i < g->GetNumVertices(); i++)
			{
				if (i == index)
					continue;
				cout << "The distance between " << g->getcities()[index] << " and " << g->getcities()[i];
				cout << " is: " << g->getdist()[index][i] << "\nAnd the path is \n";
				for (string current : g->getpath()[index][i])
					cout << current << "\t";
				cout << endl;
			}
			cout << "\n---------------------------------------------------------------------------------\n";
			break;
		}
		case '4':
		{
			q = userinput();
			if (!q)
				menu='e';
			else
			{
				cout << "\n---------------------------------------------------------------------------------\n";
				cout << "user data stored.\n";
				cars = new int[g->GetNumVertices()];
				for (int i = 0; i < g->GetNumVertices(); i++)
					cars[i] = 0;
				cout << "\n---------------------------------------------------------------------------------\n";
			}
			break;
		}
		case '5':
		{
			cout << "\n---------------------------------------------------------------------------------\n";
			while (!q->empty())
			{
				user temp = q->front();
				int l = 0;
				while (g->getcities()[l] != temp.getloc())
					l++;
				int d = 0;
				while (g->getcities()[d] != temp.getdest())
					d++;
				if (cars[l] <= 5)
				{
					cars[l]++;
					cout << "Uber Car has been assigned to the user " << temp.getid() << " \n";
					cout << "The shortest path from location to the destination is:\n";
					for (string current : g->getpath()[l][d])
						cout << current << "\t";
					cout << "with distance: " << g->getdist()[l][d] << " km and cost ";
					if (temp.gettype() == "Premium User")
						cout << g->getdist()[l][d] * 15 << endl << endl;
					if (temp.gettype() == "Normal User")
						cout << "Rs " << g->getdist()[l][d] * 10 << endl << endl;
				}
				else
				{
					cout << "User " << temp.getid()
						<< " could not be assigned a car as all cars in the city "
						<< g->getcities()[l] << " have been booked.\n";
				}
				q->pop();
			}
			cout << "\n---------------------------------------------------------------------------------\n";
			break;
		}

		case '6':
		{
			cout << "\n---------------------------------------------------------------------------------\n";
			cout << "Welcome to the Uber Bus Service!\n\nOur route is as follows\n";
			g->prim();
			cout << "\n---------------------------------------------------------------------------------\n";
			break;
		}
		case 'e':
		{
			cout << "\n---------------------------------------------------------------------------------\n";
			cout << "Goodbye!\nHope you liked our customer service.\n";
			cout << "\n---------------------------------------------------------------------------------\n";
			break;
		}
			
		default:
		{
			cout << "Invalid choice\nEnter again\n" << endl;
			break;
		}	
		}
	} while (menu != 'e');
	delete[]cars;
	delete q;
	delete g;
	return 0;
}