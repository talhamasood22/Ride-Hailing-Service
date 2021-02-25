#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include <string>
#include <list>
using namespace std;
const double INF = 999999;
template <typename T>
class Graph
{
public:
	Graph(int numVertex)
	{
		numVertices = numVertex;
		adj_matrix = new T*[numVertices];
		for (int i = 0; i< numVertices; i++)
		{
			adj_matrix[i] = new T[numVertices];
			for (int j = 0; j<numVertices; j++)
				adj_matrix[i][j] = 0.0;
		}
		cities = new string[numVertices];
		for (int i = 0;i < numVertices; i++)
			cities[i] = "empty";
		Pathlist = new list<string>*[numVertices]();
		for (int i = 0; i<numVertices; i++)
			Pathlist[i] = new list<string>[numVertices];
		distance = new double* [numVertices];
		for (int i = 0; i<numVertices; i++)
			distance[i] = new double[numVertices];
	}

	int GetNumVertices()
	{
		return numVertices;
	}

	void insertEdge(string frmVertex, string toVertex, T *e)
	{
		int l1 = frmVertex.length();
		int l2 = toVertex.length();
		l1 = l1%numVertices;
		l2 = l2%numVertices;
		bool exist = false;
		for (int i = 0;i < numVertices;i++)
		{
			if (cities[i] == frmVertex)
				exist = true;
		}
		if (!exist)
		{
			while (cities[l1] != "empty")
			{
				l1++;
				if (l1 == numVertices)
					l1 = 0;
			}
			cities[l1] = frmVertex;
		}
		while (cities[l1] != frmVertex)
		{
			l1++;
			if (l1 == numVertices)
				l1 = 0;
		}

		exist = false;
		for (int i = 0;i < numVertices;i++)
		{
			if (cities[i] == toVertex)
				exist = true;
		}
		if (!exist)
		{
			while (cities[l2] != "empty")
			{
				l2++;
				if (l2 == numVertices)
					l2 = 0;
			}
			cities[l2] = toVertex;
		}
		while (cities[l2] != toVertex)
		{
			l2++;
			if (l2 == numVertices)
				l2 = 0;
		}
		adj_matrix[l1][l2] = e;
		adj_matrix[l2][l1] = e;
	}

	void print()
	{
		for (int i=0;i<numVertices;i++)
		{
			for (int j=0;j<numVertices;j++)
			{
				cout<<adj_matrix[i][j]<<"\t";
			}
			cout<<endl;
		}
	}

	string *getcities()
	{
		return cities;
	}

	void breadthfirstSearch(int s, int t)
	{
		int x = s;
		queue<int> *Q = new queue<int>();
		bool *visited = new bool[numVertices];
		for (int i = 0; i<numVertices; i++)
			visited[i] = false;
		Q->push(x);
		visited[x] = true;
		bool goal = false;
		int *parent = new int[numVertices];
		for (int i = 0; i < numVertices; i++)
			parent[i] = -1;
		while (!Q->empty())
		{
			x = Q->front();
			Q->pop();
			for (int i = 0; i<numVertices; i++)
			{
				if (adj_matrix[x][i] != 0.0)
				{
					if (!visited[i])
					{
						visited[i] = true;
						if (i == t)
						{
							parent[i] = x;
							goal = true;
							break;
						}
						else
						{
							Q->push(i);
							parent[i] = x;
						}
					}
				}
			}
			if (goal == true)
			{
				while (!Q->empty())
					Q->pop();
				break;
			}
		}
		int j = t;
		stack<string> output;
		output.push(cities[j]);
		while (parent[j] != s)
		{
			j = parent[j];
			output.push(cities[j]);
		}
		output.push(cities[s]);
		cout << output.size()-1 << endl;
		while (true)
		{
			cout << output.top();
			output.pop();
			if (!output.empty())
				cout<<" -> ";
			else break;
		}
		cout << endl;
		delete[]parent;
		delete[]visited;
		delete Q;
	}

	void dijkstra(int start)
	{
		bool *set=new bool [numVertices];
		int *parent = new int[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			distance[start][i] = INF;
			set[i] = false;
			parent[i] = -1;
		}
		distance[start][start] = 0;
		for (int count = 0; count < numVertices - 1; count++)
		{
			int x;
			double min = INF;
			for (int i = 0; i < numVertices; i++)
			{
				if (set[i] == false && distance[start][i] <= min)
				{
					min = distance[start][i];
					x = i;
				}
			}
			set[x] = true;
			for (int i = 0; i < numVertices; i++)
			{
				if (!set[i] && adj_matrix[x][i].getdist() && distance[start][x] != INF
					&& distance[start][x] + adj_matrix[x][i].getdist() < distance[start][i])
				{
					distance[start][i] = distance[start][x] + adj_matrix[x][i].getdist();
					parent[i] = x;
				}
			}
		}
		for (int i = 0; i < numVertices; i++)
		{
			if (i == start)
				continue;
			Pathlist[start][i].push_front(cities[i]);
			int j = i;
			while (parent[j] != start)
			{
				Pathlist[start][i].push_front(cities[parent[j]]);
				j = parent[j];
			}
			Pathlist[start][i].push_front(cities[parent[j]]);
		}
		delete[]parent;
		delete[]set;
	}

	void prim()
	{
		Graph<double> *costgraph = new Graph<double>(numVertices);
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
				costgraph->getmatrix()[i][j] = adj_matrix[i][j].getcost();
		}
		int *parent = new int[numVertices];
		double *key = new double[numVertices];
		bool *set = new bool[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			key[i] = INF;
			set[i] = false;
		}
		key[0] = 0;
		parent[0] = -1;
		double minkey;
		for (int count = 0; count < numVertices - 1; count++)
		{
			int x;
			minkey = INF;
			for (int i = 0; i < numVertices; i++)
			{
				if (set[i] == false && key[i] < minkey)
				{
					minkey = key[i];
					x = i;
				}
			}
			set[x] = true;
			for (int i = 0; i < numVertices; i++)
			{
				if (costgraph->getmatrix()[x][i] && set[i] == false && costgraph->getmatrix()[x][i] < key[i])
				{
					parent[i] = x;
					key[i] = costgraph->getmatrix()[x][i];
				}
			}
		}
		cout << setw(25) << left << "Start\t\t\t" << setw(25) << left << "End\t\t" << "Cost(Rs)\n";
		for (int i = 1; i < numVertices; i++)
		{
			cout << setw(25) << left << cities[parent[i]] << "\t\t" << setw(25) << left << cities[i];
			cout << "\t\t" << costgraph->getmatrix()[i][parent[i]] << endl;
		}
		cout << "\n\n";
		delete[]parent;
		delete[]set;
		delete costgraph;
		delete[]key;
	}

	list<string> **getpath()
	{
		return Pathlist;
	}

	double **getdist()
	{
		return distance;
	}

	T **getmatrix()
	{
		return adj_matrix;
	}

	~Graph()
	{
		delete[]cities;
		for (int i = 0; i < numVertices; i++)
			delete [] adj_matrix[i]; 
		delete [] adj_matrix;
		for (int i = 0; i < numVertices; i++)
			delete [] distance[i]; 
		delete [] distance;
		for (int i = 0; i < numVertices; i++)
			delete [] Pathlist[i]; 
		delete [] Pathlist;
	}
private:
	T **adj_matrix;
	int numVertices;
	string *cities;
	list<string> **Pathlist;
	double **distance;
};
#endif