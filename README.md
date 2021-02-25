# Ride-Hailing-Service
Problem statement:
1.	Reading input from the file and storing it in the graph, representing the cities as the vertices and edges as the distance and cost. 
2.	To calculate the shortest path from each city to another city and storing it an adjacency list.
3.	Finding the path from each city to all the other cities while hopping the least number of cities. 
4.	Reading the user data from the while keeping the priorities in check. 
5.	Minimizing the bus service operational costs. 
Algorithms used:
•	Dijkstra’s algorithm for calculating the single source shortest path and storing it in a graph of integers representing distances. 
•	BFS to find the minimum number of cities to hop while reaching the destination, and storing it in an adjacency matrix / list. 
•	Priority Queue (Heaps) to sort the user according to their user profiles/types.
•	Prim’s / Kruskal’s algorithm to find minimize the bus service operational costs. 
Data Structures used: 
•	Struct edge containing the distances and cost
•	Hash maps to map cities onto the vertices.
•	Graph of integers 
•	Adjacency list/matrix
•	Queues for BFS
•	Class of users containing user information. 
•	Max Heap (Priority Queue) to store the user according to their priorities.
