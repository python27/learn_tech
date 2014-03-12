#include "network_apps.hpp"
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<stack>
using namespace scn;
using namespace std;

size_t scn::RandomWalkByURW(UGraph::pGraph graph,
			  size_t indexOfSource, size_t indexOfTarget)
{
   unordered_set<size_t> neighbors_of_target(graph->find(indexOfTarget)->begin(),
					   graph->find(indexOfTarget)->end());
   vector<size_t> neighbors;
   size_t steps = 0;
   size_t next = indexOfSource;
   srand(size_t(time(00)));
   do
   {
      neighbors.assign(graph->find(next)->begin(), graph->find(next)->end());
      next = neighbors[rand() % neighbors.size()];
      steps++;
   }while(neighbors_of_target.find(next) == neighbors_of_target.end());

   return steps;
}

size_t scn::RandomWalkByNRRW(UGraph::pGraph graph,
			   size_t indexOfSource, size_t indexOfTarget)
{
   unordered_set<size_t> neighbors_of_target(graph->find(indexOfTarget)->begin(),
					   graph->find(indexOfTarget)->end());
   vector<size_t> neighbors;
   size_t steps = 0;
   size_t next = indexOfSource;
   size_t previous = indexOfSource;
   srand(size_t(time(00)));
   do
   {
      neighbors.assign(graph->find(next)->begin(), graph->find(next)->end());
      do
      {
	 next = neighbors[rand() % neighbors.size()];
      }while(next == previous);
      steps++;
      previous = next;
   }while(neighbors_of_target.find(next) == neighbors_of_target.end());

   return steps;
}

size_t scn::RandomWalkBySARW(UGraph::pGraph graph,
			   size_t indexOfSource, size_t indexOfTarget)
{
   unordered_set<size_t> neighbors_of_target(graph->find(indexOfTarget)->begin(),
					   graph->find(indexOfTarget)->end());
   vector<size_t> neighbors;
   size_t steps = 0;
   size_t next = indexOfSource;
   unordered_set<size_t> history;
   stack<size_t> precessors;
   history.insert(indexOfSource);
   precessors.push(indexOfSource);

   srand(size_t(time(00)));
   do
   {
      auto other = graph->find(next);
      neighbors.clear();
      for(auto iter = other->begin(); iter != other->end(); iter++)
      {
	 if(history.find(*iter) == history.end())
	    neighbors.push_back(*iter);
      }
      if(neighbors.empty())
      {
	 precessors.pop();
	 next = precessors.top();
	 steps++;
	 continue;
      }
      do
      {
	 next = neighbors[rand() % neighbors.size()];
      }while(history.find(next) != history.end());
      steps++;
      history.insert(next);
      precessors.push(next);
   }while(neighbors_of_target.find(next) == neighbors_of_target.end());

   return steps;
}
