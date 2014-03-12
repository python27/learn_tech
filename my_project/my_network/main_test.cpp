#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <set>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "graph.hpp"
#include "graphviz.hpp"
#include "network_measurements.hpp"
#include "network_generator.hpp"
using namespace std;
#define NUM_NODE  100
#define NUM_EDGE  10

int main()
{
    for (int i = 1; i <= 8; ++i)
    {
        scn::UGraph::pGraph graph(new scn::UGraph());
        graph = scn::GenTriangleExtendedDSWN(i);
        cout << "Gen Triangle Extended DSWN: " << i << "th  iteration !" << endl;
        cout << "Number of Nodes: " << graph->GetNumberOfNodes() << endl;
        cout << "Number of Edges: " << graph->GetNumberOfEdges() << endl;
        cout << "*****************" << endl;

        string filename("result/triangleExtended/triangle");
        filename += std::to_string(long long(i)) + string(".mat");
        ofstream fout(filename, std::ofstream::out);

        auto pMatrix = graph->GetAdjacencyMatrix();
        for (int i = 0; i < pMatrix->GetWidth(); i++)
        {
            bool isFirstElem = true;
            for (int j = 0; j < pMatrix->GetHeight(); j++)
            {
                if (isFirstElem == true)
                {
                    fout << pMatrix->GetElement(i, j);
                    isFirstElem = false;
                }
                else
                {
                    fout << " " << pMatrix->GetElement(i, j);
                }
            }
            fout << endl;
        }
        fout.close();
    }
    return 0;
}