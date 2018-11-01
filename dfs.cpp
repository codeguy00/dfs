// For simplicity, assume 
//      1. V = {0, 1, 2, ..., n-1}
//      2. Edges input as unordered pairs (from stdin)
//      3. The graph is an undirected graph
//      4. Adjacency list representation to be used

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Node
{ 
  public:
  
   unsigned visited = 0; //not yet visited
   int component = -1;//component not assigned
};


using Edges=vector<list<int>>;
using Nodes=vector<Node>;

class Graph
{
  public:
    Nodes V;
    Edges E;      	
};

//read edges in "edge-list" format 
Edges getEdges( )
{ 
	unsigned u, v;
	Edges adj_list;
	
	 while (cin>>u>>v)
	 {
		 adj_list.resize(max({adj_list.size(),u+1,v+1}));
		 adj_list[u].push_back(v);
		 adj_list[v].push_back(u);		 
	  } 
	  
	  return adj_list;

}

void dfs(unsigned v, Graph& g, unsigned& count, unsigned& compCounter)
{
	count++;
	g.V[v].visited = count;
	g.V[v].component = compCounter;
	
  	for(auto w: g.E[v])//iterate over neighbours of node v
  	  if ( g.V[w].visited == 0 )
		dfs(w, g, count, compCounter);
	
}

void mainDFS(const Edges& E)
{
  Graph G;
  //Code Added
  	 unsigned compCounter = 0;
  //
  G.V.resize(E.size());
  G.E = E; //Hopefully the compiler optimizes this 
  unsigned counter = 0;
  
  for(unsigned i = 0; i < G.V.size(); i++)//iterate over nodes
    {
	   if(G.V[i].visited == 0)
	     {	
		   compCounter += 1; //Code Added Componet Counter incremented
	       dfs(i, G, counter, compCounter);		
	      }  
     }  	
      	
  cerr<<"DFS Ranks:"<<endl;
   
  for(unsigned i =0; i < G.V.size();i++)
  {
    cerr << i<<" visited "<< G.V[i].visited << " is in component "<< G.V[i].component << endl;
   }
    
}
	
	


int main()
{
  Edges edges = getEdges();
  unsigned m = 0;
  
  cerr<<"Read "<<edges.size()<<" nodes "<<endl;
  
  
  for(auto e: edges)
    m+= e.size(); 


 cerr<<"Read "<<m<<" edges "<<endl;
 
 mainDFS(edges);
}



