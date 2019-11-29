//Email : cerro005@cougars.csusm.edu
//Name: William Cerros
//Student ID: Cerro005
//Email : cerro005@cougars.csusm.edu

#include <iostream>
#include <cstdlib>

using namespace std;

/* Structure for Adjacency List Node */
/* Also serves as node for Queue class */
struct Edge {
	int adj_vtx;
	Edge* next;
};

/* Structure for Adjacency List */
/* Adjlist consists of Edge* nodes */
struct AdjList  {
	struct Edge* head;
	struct Edge* tail;
};

/* Queue Class will serve as a queue for BSF function*/
class Queue {
public: 
	struct Edge* head;
	int size;

	Queue() {
		head = NULL;
		size = 0;
	}

	//Nodes will be added at the tail.
	void push_back(int v) {

		//increment size of list
		size++;

		//Creating a new Edge node
		Edge* newEdge = new Edge;
		newEdge->adj_vtx = v;
		newEdge->next = NULL;

		//Empty list so newEdge is head
		if (head == NULL) {
			head = newEdge;
			return;
		}

		//curr will iterate through our queue
		Edge* curr = head;
		
		//curr will iterate to the last node in our queue
		while (curr && curr->next) {
			curr = curr->next;
		}

		//add the newEdge to the end of the list
		curr->next = newEdge;
	}

	//Function will return the top node in our queue
	Edge* front() {
		return head;
	}

	void pop_front() {

		//List is empty;
		if (head == NULL) {
			return;
		}

		//Move head pointer to the next node
		Edge* tmp = head;
		head = head->next;

		//decrement size variable
		size--;
		delete tmp;
	}


	//Function will check to see if the queue is empty.
	//Checks size variable
	bool empty() {
		if (size == 0)
			return true;
		else
			return false;
	}
};


/* Graph class will implement a Directed Graph */
class Graph {

private:
	int V;
	void DFSUtil(int v, bool visited[]) {

		//Marking current node as visited
		visited[v] = true;
		cout << v << " ";

		//Recur for all the vertices adjacent to this vertex
		Edge* itr = array[v].head;
		do {
			int i = itr->adj_vtx;
			if (!visited[i])
			{
				DFSUtil(i, visited);
			}
			itr = itr->next;
		} while (itr != NULL);
	}

public:

	//the array of linked lists is made public so the BFS method which is a
	//public method has access to the adjacent vertices of a desired node
	struct AdjList* array;

	Graph(int V) {
		this->V = V;
		array = new AdjList[V];
		for (int i = 0; i < V; ++i)
			array[i].head = NULL;
	}

	/* Function creates a new Edge node for destination W and links it array list of source v
	   Nodes are added in a push back manner */
	void addEdge(int v, int w) {
		Edge* newNode = new Edge;
		newNode->adj_vtx = w;
		newNode->next = NULL;

		if (array[v].head == NULL) {
			array[v].head = newNode;
			array[v].tail = newNode;
		}

		else {
			array[v].tail->next = newNode;
			array[v].tail = newNode;
		}
	}

	void BFS(int s) {

		//Marking all the vertices as not visited
		bool* visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;

		//Create a queue for BFS
		Queue queue;

		//Marking the current node as visited and adding it to queue
		visited[s] = true;
		queue.push_back(s);

		do {
			//Removing the top node from the queue and printing
			Edge* tmp = queue.front();
			s = tmp->adj_vtx;
			cout << s << " ";
			queue.pop_front();

			//Getting all adjacent vertices 
			//If they have not been visited then they will be marked and queue'd
			Edge* itr = array[s].head;
			do {
				int i = itr->adj_vtx;
				if (!visited[i])
				{
					visited[i] = true;
					queue.push_back(i);
				}
				itr = itr->next;
			} while (itr != NULL);

		} while (!queue.empty());
	}
	
	void DFS(int v) {
		//Marking all vertices as not visited
		bool* visited = new bool[V];

		for (int i = 0; i < V; i++)
			visited[i] = false;
		//Calling DFSUtil recursively to print DFS
		DFSUtil(v, visited);
	}

	//printing directed graph
	void printGraph()
	{
		int v;
		for (v = 0; v < V; ++v)
		{
			Edge* tmp = array[v].head;		//tmp has the address of (0,1..)vertex head 
			cout << "\n Adjacency list of vertex " << v << "\n head ";
			while (tmp)
			{
				cout << "-> " << tmp->adj_vtx;
				tmp = tmp->next;
			}
			cout << endl;
		}
	}
};

int main()
{
	Graph gh(4);
	gh.addEdge(0, 1);
	gh.addEdge(0, 2);
	gh.addEdge(1, 2);
	gh.addEdge(2, 0);
	gh.addEdge(2, 3);
	gh.addEdge(3, 3);

	cout << "Printing Directed Graph" << endl;
	gh.printGraph();

	cout << "\nDepth First Traversal" << endl;
	cout << "Starting Vertex: 2" << endl;
	gh.DFS(2);

	cout << "\n\nBreadth First Traversal" << endl;
	cout << "Starting Vertex: 2" << endl;
    gh.BFS(2);
}