#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <thread>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include <iterator>
#include <mutex>

using namespace std;

int no_threads,v;
list <int> *adj;
mutex *locks;
int *colours;
int *partition;
bool *vertex_type;
int no_colours = 0;
ofstream output;

// Add edge between vertices in graph
void add_edge(int v1, int v2)
{
	adj[v1].push_back(v2);
}

// Identify internal and external vertices
void identify()
{
	list<int>::iterator it;
	for(int i=0; i<v; i++){
		bool flag = true;
		for(it = adj[i].begin(); it!= adj[i].end(); ++it){
			if (partition[*it]!=partition[i]){
				flag = false;
				break;
			}
		}
		vertex_type[i] = flag;
	}
/*
cout<<endl<<"vertex types: "<<endl;
for(int i=0;i<v;i++)
	cout <<vertex_type[i]<<" ";
cout<<"(0-> external vertices; 1-> internal vertices)"<<endl; 
*/

// Initialise all colours to -1, indicating colour has not yet been assigned
	for (int i=0; i<v; i++)
		colours[i] = -1;
}

// Function to colour vertices in partition id
void colour(int id)
{   
	int i,j,c;
	list<int>::iterator it;
	bool available[v];
	for (i=0; i<v; i++)
		available[i] = false;

//internal vertices colouring

	for (j=0; j<v; j++){
		//if vertex belongs to current partition and is an internal vertex
		if(vertex_type[j])
			if(partition[j]==id){
				//apply greedy colouring
				for (it = adj[j].begin(); it!=adj[j].end(); ++it)
					if (colours[*it] != -1)
						available[colours[*it]] = true;
 
				for (c = 0; c < v; c++)
					if (available[c] == false) //find lowest numbered coloured not used
						break;

				colours[j] = c;

				if(c>no_colours)
		 			no_colours = c; //update total number of colours

				for (it = adj[j].begin(); it!= adj[j].end(); ++it)
					if (colours[*it] != -1)
						available[colours[*it]] = false; //reset for next iteration
	  		}
  	}

//external vertices colouring - critical section

	for (j=0; j<v; j++){
		//if vertex belongs to current partition and is a boundary vertex
		if(partition[j]==id)             
			if(!vertex_type[j]){
		  		list <int> v_list;
	  			for(it=adj[j].begin();it!=adj[j].end();++it)
					v_list.push_back(*it); //add the vertex and its neighbours to a list

		  		v_list.sort(); //sort the list in increasing order

				//acquire locks on vertices in order
		  		for(it=v_list.begin();it!=v_list.end();++it)
					locks[*it].lock(); 

        		//apply greedy colouring
				for (it = adj[j].begin(); it!=adj[j].end(); ++it)
					if (colours[*it] != -1)
						available[colours[*it]] = true;
 
				for (c = 0; c < v; c++)
					if (available[c] == false)
						break;

				colours[j] = c; 

				if(c>no_colours)
	  				no_colours = c;

				for (it = adj[j].begin(); it != adj[j].end(); ++it)
					if (colours[*it] != -1)
						available[colours[*it]] = false;

       			//release locks on vertices
				for(it=v_list.begin();it!=v_list.end();++it)
					locks[*it].unlock();
	  		}
	} 
}

// Function to check if the graph has valid colouring
void verify()
{
  	bool flag = true;
  	list<int>::iterator it;
  	for(int i=0; i<v; i++){
		for(it = adj[i].begin(); it!= adj[i].end(); ++it){
			if (colours[i]==colours[*it]){
		  		flag = false;
		  		break;
			}
		}
  	}
  	if(flag)
		cout << "valid colouring" <<endl;
  	else
		cout << "invalid colouring" <<endl;
}

// Function to output colour assigned to each vertex
void print()
{
  	output << "Colours:" <<endl;
  	for(int i = 0; i < v; i++){
		  if(i==v-1){
	  		output << "v" << i+1 << " - " << colours[i]+1 << endl;
	  		break;
		  }
	    output << "v" << i+1 << " - " << colours[i]+1 <<", ";
  	}
}

int main(){

	int temp, i, j, count=0;

	ifstream input("input-params.txt");
	input >> no_threads >> v;

	adj = new list <int> [v];
	colours = new int[v];
	partition = new int[v];
	vertex_type = new bool[v];
	locks = new mutex[v];

	for(i=0; i<v; ++i){
	  	for(j=0; j<v; ++j){
			input >> temp;
		  	if(temp)
				add_edge(i,j);   
	  	}
	}

	input.close();

	srand(time(0));
	
// Partitions are created by assigning a random number from 0 to (number of threads-1) 	
	for(int i=0;i<v;i++){
		temp = rand() % no_threads;
		partition[i] = temp;
	}

/*
cout << "vertices in partitions:"<<endl;
for(int i=0;i<v;i++)
	cout<<partition[i] << " ";
cout<<endl;
*/
	  
  	identify();

// Create k number of threads
  	thread threads[no_threads];

// Begin keeping track of time taken
  	clock_t begin = clock();
// Assign colouring of partition to each thread
  	for(i=0;i<no_threads;i++)
		threads[i] = thread(colour,i);
  	for(i=0;i<no_threads;i++)
		threads[i].join();
// End keeping track of time taken
  	clock_t end = clock();
  	clock_t clockTimeSpent = end - begin;
  	unsigned long long time_spent = 1000000*((double)clockTimeSpent/(unsigned long long)CLOCKS_PER_SEC);

    output.open("output-fine.txt");

  	output << "No. of colours used: " << no_colours+1 << endl;
  	output << "Time taken by fine-grained lock algorithm: " << (double)time_spent/(double)1000 << " milliseconds"<< endl;
    print();
    output.close();

  	//verify();
	  
  	return 0;
}
