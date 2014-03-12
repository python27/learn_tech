#pragma once
#include "graph.hpp"
#include <string>
namespace scn
{
   namespace io
   {
/**
 * @name WriteToDotFile - write the structure of an undirected
 * graph into the dot form, which used as input of GraphViz
 * @param graph -  graph 
 * @param filename - Name of
 * @return void
 */
      void WriteToDotFile(Graph::pGraph graph, std::string filename);
   };
};
