//#include <ctime>
//#include <iostream>
//#include <cstdlib>
//#include<algorithm>
//#include<vector>
//#include <numeric>
//#include<cmath>
//#include<fstream>
//#include "graph.hpp"
//#include "graphviz.hpp"
//#include "network_measurements.hpp"
//#include "network_generator.hpp"
//using namespace std;
//#define NUM_NODE  100
//#define NUM_EDGE  10
//////*********************************************************************
//////模拟退火算法定义子函数BEGIN
//////**********************************************************************
////double T_min = 0.0001;
////double T = 0.85;
////double r = 0.98;
////bool IsConnectedGraph(scn::UGraph::pGraph pgraph);
//////该函数返回一个图的的拉普拉斯矩阵的lambdaN与lambada2的比值
////double RatioOfEigenvalue(scn::UGraph::pGraph graph)
////{
////	SymMatrix::pMatrix pmatrix = graph->GetAdjacencyMatrix();
////	for(int i = 0;i < graph->GetNumberOfNodes();i++)
////	{
////		Matrix::pVector pvector = pmatrix->GetRow(i);
////		int tempsum = accumulate(pvector->begin(),pvector->end(),0);
////		pmatrix->SetElement(i, i, -tempsum);
////	}
////	auto result = pmatrix->GetEigenvalueList();
////	auto length = result->size();
////	//cout<<"the fenzi is:"<<(*result)[0]<<endl;
////	//cout<<"the fenmu is:"<<(*result)[length-2]<<endl;
////	return (*result)[0]/(*result)[length-2];
////}
////
//////该函数生成一个图，改图由原始图随机去掉一条边，然后再加上一条边而生成
//////同时保证生成的图是连通图
////scn::UGraph::pGraph GenNextGraph(scn::UGraph::pGraph curGraph)
////{
////	scn::UGraph::pGraph nextGraph;
////	nextGraph =  curGraph;
////	srand( (unsigned int)time( NULL ));
////
////	do
////	{
////		auto pmatrix = curGraph->GetAdjacencyMatrix();
////		auto size = pmatrix->GetSize();
////		int row1,col1,row0,col0;
////		do{
////			row1=rand()%size;
////			col1=rand()%size;
////			row0=rand()%size;
////			col0=rand()%size;
////		}while(!(row1 != col1 && row0 != col0 && abs(pmatrix->GetElement(row1,col1) -1)<1.0e-3 && abs(pmatrix->GetElement(row0,col0)-0)<1.0e-3));
////
////		pmatrix->SetElement(row1,col1,0);
////		//pmatrix->SetElement(col1,row1,0);
////		pmatrix->SetElement(row0,col0,1);
////		//pmatrix->SetElement(col0,row0,1);
////
////		nextGraph.reset (new scn::UGraph(size));
////		for(size_t i = 0;i < size;i++)
////		{
////			for(size_t j = 0; j < size && j != i; j++)
////			{
////				if(abs(pmatrix->GetElement(i,j) - 1) < 1.0e-4)
////				{
////					nextGraph->AddEdge(i,j);
////					//nextGraph->GetAdjacencyMatrix()->SetElement(i,j,1);
////				}
////			}
////		}
////		
////		SymMatrix::pMatrix ppmatrix = nextGraph->GetAdjacencyMatrix();
////
////		Matrix::pMatrix ppnewmatrix(new Matrix(ppmatrix->GetHeight(),ppmatrix->GetWidth()));
////		for(size_t i=0;i<ppnewmatrix->GetHeight();i++)
////		{
////			for(size_t j=0;j<ppnewmatrix->GetWidth();j++)
////			{
////				ppnewmatrix->SetElement(i,j,ppmatrix->GetElement(i,j));
////			}
////		}
////
////		Matrix::pMatrix sumpmatrix(new Matrix(ppnewmatrix->GetHeight(),ppnewmatrix->GetWidth()));
////
////		for(size_t index = 1;index <sumpmatrix->GetHeight();index++)
////		{
////			sumpmatrix += ppnewmatrix^index;
////		}
////
////		if(sumpmatrix->IsNonZeros())
////			break;
////
////	}while(true);
////	//cout<<"=========="<<endl;
////
////	return nextGraph;
////}
////
//////该函数判定给定的一个图是不是连通的图，返回bool值
////bool IsConnectedGraph(scn::UGraph::pGraph pgraph)
////{
////	auto pmatrix = pgraph->GetAdjacencyMatrix();
////	auto size = pmatrix->GetSize();
////	Matrix::pMatrix tempmatrix (new Matrix(size,size));
////	for(size_t i = 0;i < size;i++)
////	{
////		for(size_t j = 0;j < size;j++)
////		{
////			tempmatrix->SetElement(i,j,0);
////		}
////	}
////
////	for(size_t i = 1;i < size; i++)
////	{		
////		tempmatrix += pmatrix^i;
////	}	
////	if(tempmatrix->IsNonZeros())
////		return true;
////	else
////		return false;
////}
////
//////该函数用来计算一个图的集聚系数
////double GetClusterCoefficient(scn::UGraph::pGraph graph)
////{
////	SymMatrix::pMatrix pmatrix = graph->GetAdjacencyMatrix();
////	Matrix::pMatrix ppmatrix(new Matrix(pmatrix->GetHeight(),pmatrix->GetWidth()));
////	for(size_t i=0;i<ppmatrix->GetHeight();i++)
////	{
////		for(size_t j=0;j<ppmatrix->GetWidth();j++)
////		{
////			ppmatrix->SetElement(i,j,pmatrix->GetElement(i,j));
////		}
////	}
////
////	cout<<"ppmatrix:"<<endl;
////	for(size_t i = 0;i < ppmatrix->GetHeight();i++)
////	{
////		for(size_t j = 0;j < ppmatrix->GetWidth();j++)
////		{
////			cout<<ppmatrix->GetElement(i,j)<<" ";
////		}
////		cout<<endl;
////	}
////	Matrix::pMatrix ppmatrixPow2 = ppmatrix * ppmatrix;
////	Matrix::pMatrix ppmatrixPow3 = ppmatrixPow2 * ppmatrix;
////
////	//得到A^2的对角线元素
////	double *pPow2 = new double[ppmatrixPow2->GetHeight()];
////	for(size_t i = 0;i < ppmatrixPow2->GetHeight();i++)
////	{
////		pPow2[i] = ppmatrixPow2->GetElement(i,i);
////	}
////
////	//得到A^3的对角线元素
////	double *pPow3 = new double[ppmatrixPow3->GetHeight()];
////	for(size_t i = 0;i < ppmatrixPow3->GetHeight();i++)
////	{
////		pPow3[i]=ppmatrixPow3->GetElement(i,i);
////	}
////
////	//得到所有节点的聚类系数，放在result数组中
////	double *result = new double[ppmatrix->GetHeight()];
////	for(size_t i=0;i<ppmatrix->GetHeight();i++)
////	{
////		result[i] = pPow3[i]/(pPow2[i]*(pPow2[i]-1));
////	}
////
////	size_t length = ppmatrix->GetHeight();
////	double tempsum = 0;
////	for(size_t i = 0;i < length;i++)
////	{
////		tempsum += result[i];
////	}
////
////	delete [] pPow2;
////	delete [] pPow3;
////	delete [] result;
////
////	return tempsum / length;
////}
////
//////*********************************************************************
//////模拟退火算法定义子函数END
//////**********************************************************************
//
//int main()
//{
//   scn::UGraph::pGraph graph(new scn::UGraph());
//   clock_t start, end;
//   start = clock();
//
//  // graph->reserve(NUM_NODE);
//  // for(size_t i = 0; i < NUM_NODE; i++)
//  // {
//  //    graph->AddNode(i);
//  // }
//  // for(auto iter = graph->begin(); iter != graph->end(); iter++)
//  // {
//  //    for(size_t i = 0; i < NUM_EDGE; i++)
//  //    {
//	 //size_t index = rand() % NUM_NODE;
//	 //if(index == *iter)
//	 //   continue;
//	 //
//	 //graph->AddEdge(iter, index);
//  //    }
//  // }
//
//////   graph = scn::GenKNearestNetwork(NUM_NODE, NUM_EDGE);
//////   graph = scn::GenSmallWorldNetworkByWS(3000, 25, 0.1);
//////   graph = scn::GenSmallWorldNetworkByNW(NUM_NODE, NUM_EDGE, 0.5);
//////   graph = scn::GenRandomNetwork(NUM_NODE, 0.2);
//////   graph = scn::GenScaleFreeNetwork(NUM_NODE, NUM_EDGE);
//   graph = scn::GenSmallWorldByEdgeIteration(2);
//////   graph = scn::GenDURT(3);
//////   graph = scn::GenSmallWorldNetworkFromDURT(10);
//  end = clock();
//   size_t degree_sum = 0;
//   for(auto node = graph->begin(); node != graph->end(); node++)
//   {
//      degree_sum += node->GetDegree();
//   }
//   degree_sum /= graph->GetNumberOfNodes();
//   cout<<"The sum degree is "<<degree_sum<<endl;
//	cout<<"Time Cost is "<<((double)(end - start))/CLOCKS_PER_SEC<<endl;
//   cout<<"The Number of Edge is "<<graph->GetNumberOfEdges()<<endl;
//   cout<<"The Number of Node is "<<graph->GetNumberOfNodes()<<endl;
//   cout<<"The average degree is "<<scn::ComputeAverageDegree(graph)<<endl;
// //  cout<<"The Cluster Cofficient is "<<GetClusterCoefficient(graph)<<endl;
//////**********************************************************************************
//////此段用于模拟退火算法BEGIN
//////**********************************************************************************
////	SymMatrix::pMatrix pmatrix = graph->GetAdjacencyMatrix();
////	for(int i = 0;i < graph->GetNumberOfNodes();i++)
////	{
////		Matrix::pVector pvector = pmatrix->GetRow(i);
////		int tempsum = accumulate(pvector->begin(),pvector->end(),0);
////		pmatrix->SetElement(i, i, -tempsum);
////	}
////
////	auto result = pmatrix->GetEigenvalueList();
////	  for (int i = 0;i < result->size();i++)
////	{
////		cout<<(*result)[i]<<endl;
////	}
////
////	cout<<"The second largest eigvalue is:"<<endl;
////	auto length = result->size();
////	cout<<(*result)[length-2]<<endl;
////
////	cout<<"The ratio of the minimum eigenvalue and the second largest eigenvalue is:"<<endl;
////	cout<<(*result)[0]/(*result)[length-2]<<endl;
////
////   //fstream fout("data_iteration_6.txt");
////   cout<<"the ratio is:"<<endl;
////   cout<<RatioOfEigenvalue(graph)<<endl;
////   auto curGraph = graph;
////	auto nextGraph = GenNextGraph(curGraph);
////	srand( (unsigned int)time( NULL ));
////   while(T > T_min)
////   {
////		double dE = RatioOfEigenvalue(nextGraph) - RatioOfEigenvalue(curGraph);
////		if(dE <= 0)
////		{
////			curGraph = nextGraph;
////		}
////		else 
////		{
////			if(exp(dE / T) <( (double)(rand() % 10) / 10))
////				curGraph = nextGraph;
////		}
////		//cout<<"the ratio is:"<<endl;
////		//double result = RatioOfEigenvalue(curGraph);
////		//cout<<result<<endl;
////		//fout<<result<<endl;
////		T = r * T;
////		nextGraph = GenNextGraph(curGraph);
////   }
////   //fout.close();
////   cout<<"After the SA algorithm,the ratio is:"<<endl;
////   cout<<RatioOfEigenvalue(curGraph)<<endl;
////   cout<<"After the SA algorithm, the Cluster Coefficient is:"<<endl;
////   cout<<GetClusterCoefficient(curGraph)<<endl;
////   fstream ffout("data_matrix_5.txt");
////   ffout<<"Hello,world!"<<endl;
////   auto matrix_ptr = curGraph->GetAdjacencyMatrix();
////   auto node_number = matrix_ptr->GetHeight();
////   for(size_t i = 0; i < node_number; i++)
////   {
////		for(size_t j = 0; j < node_number; j++)
////		{
////			ffout<<matrix_ptr->GetElement(i,j)<<"\t";
////		}
////		ffout<<endl;
////   }
////   ffout.close();
////
//////********************************************************************************************
//////模拟退火算法END
//////**********************************************************************************************
////
////
////
//////shorest distance
////   size_t source = 0;
////   size_t target = 4;
////   // cout<<"Distance of "<<source<<" between "<<target<<" is "<<
////   //    GetShortestDistance(graph, source, target)<<endl;
////   cout<<"Diameter of this graph is "<<GetDiameter(graph)<<endl;
////
////
////   //cout<<"After the SA, Diameter of this graph is:"<<GetDiameter(curGraph)<<endl;
////    //cout<<"Average Distance of graph is "<<GetAverageDistance(graph)<<endl;
//scn::plot::DrawCircleForm(graph, "graph_dsw_interation_2test");
////
////
//// 
////   //SymMatrix::pMatrix adjacency = graph->GetAdjacencyMatrix();
////  // Matrix::pVector result = adjacency->GetEigenvalueList();
////   //for(int i = 0;i < result->size();i++)
////  // {
////	//	cout<<(*result)[i]<<endl;
//// //  }
////
////
////
//   return 0;
////
//}
//
