#include "network_measurements.hpp"
#include "sym_matrix.hpp"
#include <cassert>
#include <cmath>
#include <queue>
#include <iostream>
#include <algorithm>
#include <list>
#include <functional>
using namespace scn;
using namespace std;
double scn::ComputeAverageDegree(UGraph::pGraph graph)
{
   size_t sum = 0;
   for(auto node = graph->begin(); node != graph->end(); node++)
   {
      sum += node->GetDegree();
   }
   return double(sum) / graph->GetNumberOfNodes();
}

pVector scn::ComputeSpectrum(UGraph::pGraph graph)
{
   SymMatrix::pMatrix adjacency =dynamic_pointer_cast<SymMatrix>(graph->GetAdjacencyMatrix());

   pVector result = adjacency->GetEigenvalueList();

   return result;
}

pMapping scn::ComputeSpectralDensity(UGraph::pGraph graph, double slide)
{
   pVector lambdas = ComputeSpectrum(graph);

   //get the mapping
   pMapping result(new Mapping);
   int start = floor(*(lambdas->begin()));
   int end = ceil(*(lambdas->rbegin()));
   for(int i = 0; i < (end - start) / slide; i++)
   {
      (*result)[double(start) + i * slide] = 0;
   }
   for(auto iter = lambdas->begin(); iter != lambdas->end(); iter++)
   {
      (*result)[floor(*iter / slide) * slide]++;
   }
   //normalized
   for(auto iter = result->begin(); iter != result->end(); iter++)
   {
      iter->second /= graph->GetNumberOfNodes();
   }
   return result;
}

size_t scn::GetShortestDistance(scn::UGraph::pGraph graph,
					size_t indexOfSource, size_t indexOfTarget)
{
   pDistance distance = RunDjikstra(graph, indexOfSource);
   return (*distance)[indexOfTarget];
}

pDistance scn::RunDjikstra(scn::UGraph::pGraph graph, size_t indexOfSource)
{
   //distance, stored the distance information of each node
   pDistance distance(new vector<size_t>(graph->GetNumberOfNodes(), Graph::NaF));
   (*distance)[indexOfSource] = 0;

   list<size_t> queue;
   //fill index of nodes into queue
   for(size_t i = 0; i < graph->GetNumberOfNodes(); i++)
   {
      queue.push_back(i);
   }
   //begin
   size_t next_distance;
   while(!queue.empty())
   {
      //get min one
      auto min = min_element(queue.begin(), queue.end(), 
			     [&](const size_t &one, const size_t &two)->bool
			     {
				if((*distance)[one] < (*distance)[two])
				   return true;
				else
				   return false;
			     });
      auto node = graph->find(*min);  

      if((*distance)[*node] < Graph::NaF)
	 next_distance = (*distance)[*node] + 1;
      else
	 next_distance = Graph::NaF;
      
      //relax neighbors
	  for(auto other = node->in_degree.begin();  other != node->in_degree.end(); other++)
      {
	 if((*distance)[*other] > next_distance)
	 {
	    (*distance)[*other] = next_distance;
	 } 
      }
	min=queue.erase(min);
   }
   return distance;
}

size_t scn::GetDiameter(scn::UGraph::pGraph graph)
{
   size_t diameter = 0;
   pDistance distance;
   for(size_t i = 0; i < graph->GetNumberOfNodes(); i++)
   {
      distance = RunDjikstra(graph, i);
      //search for the max distance except NaF
      for(size_t j = 0; j < graph->GetNumberOfNodes(); j++)
      {
	 if((*distance)[j] > diameter && (*distance)[j] < Graph::NaF)
	    diameter = (*distance)[j];
      }
   }
   return diameter;
}

double scn::GetAverageDistance(scn::UGraph::pGraph graph)
{
   size_t sum = 0;
   size_t count = 0;
   pDistance distance;
   for(size_t i = 0; i < graph->GetNumberOfNodes(); i++)
   {
      distance = RunDjikstra(graph, i);
      //add distance except NaF
      for(size_t j = 0; j < graph->GetNumberOfNodes(); j++)
      {
	 if(i == j)
	    continue;

	 if((*distance)[j] < Graph::NaF)
	 {
	    sum += (*distance)[j];
	    count++;
	 }
      }
   }
   return double(sum) / count;
}
