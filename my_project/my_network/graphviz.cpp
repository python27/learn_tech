#include "graphviz.hpp"
#include "graph_io.hpp"
#include<string>
#include<cassert>

void scn::plot::DrawCircleForm(scn::Graph::pGraph graph, std::string filename)
{
   scn::io::WriteToDotFile(graph, filename);

   std::string temp("dot -Tpng ");
   temp += filename + ".dot";
   temp += " -o " + filename +".png";
   
   int result = std::system(temp.c_str());
}
