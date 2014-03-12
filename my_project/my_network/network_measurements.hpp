#pragma once
#include "graph.hpp"
#include <vector>

namespace scn
{
   typedef std::vector<double>  Vector;
   typedef std::shared_ptr<Vector> pVector;

   typedef std::unordered_map<double, double>   Mapping;
   typedef std::shared_ptr<Mapping>          pMapping;

   typedef std::shared_ptr<std::vector<size_t>>    pDistance;

   double ComputeAverageDegree(scn::UGraph::pGraph graph);

   pVector ComputeSpectrum(scn::UGraph::pGraph graph);

   pMapping ComputeSpectralDensity(scn::UGraph::pGraph graph, double slide);

   size_t GetShortestDistance(scn::UGraph::pGraph graph,
			    size_t indexOfSource, size_t indexOfTarget);

   size_t GetDiameter(scn::UGraph::pGraph graph);
   
   double GetAverageDistance(scn::UGraph::pGraph graph);

   pDistance RunDjikstra(scn::UGraph::pGraph graph,
			 size_t indexOfSource);
};
