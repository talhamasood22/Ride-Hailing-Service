#ifndef EDGE_H
#define EDGE_H
class edge
{
private:
	double distance;
	double cost;
public:
	edge()
	{
		distance = 0;
		cost = 0;
	}

	edge(double a,double b)
	{
		distance = a;
		cost = b;
	}

	double getdist()
	{
		return distance;
	}

	void operator=(edge *e)
	{
		distance = e->getdist();
		cost = e->getcost();
	}

	friend ostream& operator<<(ostream& out, edge x)
	{
		out<<x.getdist();
		return out;
	}

	bool operator==(double a)
	{
		return (distance == a);
	}

	bool operator!=(double a)
	{
		return (distance != a);
	}

	void operator=(double a)
	{
		distance = a;
		cost = a;
	}

	double getcost()
	{
		return cost;
	}
};
#endif