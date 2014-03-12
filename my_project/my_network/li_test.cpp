#include <ctime>
#include <iostream>
#include <cstdlib>
#include<algorithm>
#include<vector>
#include <numeric>
#include<cmath>
#include<fstream>
#include "graph.hpp"
#include "graphviz.hpp"
#include "network_measurements.hpp"
#include "network_generator.hpp"
using namespace std;
#define NUM_NODE  100
#define NUM_EDGE  10

int main()
{
   scn::UGraph::pGraph graph(new scn::UGraph());
   clock_t start, end;
   start = clock();

//   graph = scn::GenKNearestNetwork(NUM_NODE, NUM_EDGE);
//   graph = scn::GenSmallWorldNetworkByWS(3000, 25, 0.1);
//   graph = scn::GenSmallWorldNetworkByNW(NUM_NODE, NUM_EDGE, 0.5);
//   graph = scn::GenRandomNetwork(NUM_NODE, 0.2);
//   graph = scn::GenScaleFreeNetwork(NUM_NODE, NUM_EDGE);
   graph = scn::GenSmallWorldByEdgeIteration(1);
//   graph = scn::GenDURT(3);
//   graph = scn::GenSmallWorldNetworkFromDURT(10);
   end = clock();
   size_t degree_sum = 0;
   for(auto node = graph->begin(); node != graph->end(); node++)
   {
      degree_sum += node->GetDegree();
   }
   //degree_sum /= graph->GetNumberOfNodes();
   cout<<"The sum degree is "<<degree_sum<<endl;
	cout<<"Time Cost is "<<((double)(end - start))/CLOCKS_PER_SEC<<endl;
   cout<<"The Number of Edge is "<<graph->GetNumberOfEdges()<<endl;
   cout<<"The Number of Node is "<<graph->GetNumberOfNodes()<<endl;

   auto pmatrix=graph->GetAdjacencyMatrix();
   for(size_t i = 0; i < graph->GetNumberOfNodes();i++)
   {
		for(size_t j = 0; j < graph->GetNumberOfNodes(); j++)
		{
		cout<<pmatrix->GetElement(i,j)<<" ";
		}
		cout<<endl;
   }

   return 0;

}