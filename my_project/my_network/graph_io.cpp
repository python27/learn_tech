#include "graph_io.hpp"
#include <fstream>

void scn::io::WriteToDotFile(scn::Graph::pGraph graph, std::string filename)
{
   using std::ofstream;
   using std::ios_base;
   using std::endl;

   ofstream out_file(filename + ".dot", ios_base::out | ios_base::trunc);
   //print the head
   out_file<<"graph G {"<<endl;
   //print edges list
// for(auto node = graph->begin(); node != graph->end(); node++)
	   for(size_t i = 0;i < graph->GetNumberOfNodes();i++)
   {
	   auto node = graph->GetNode(i);
	   size_t node_id = node.GetIndexOfNode();
	   for(auto other = node.in_degree.begin(); other != node.in_degree.end(); other++)
      {
	 if(node_id > *other && graph->HasEdge(node_id, *other))
	    continue;
	 
	 out_file<<"   "<<node_id<<" -- "<<*other<<endl;
      }
   }
   //print the tail
   out_file<<"}"<<endl;
   out_file.close();
}
