#pragma once

#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <utility>
#include <type_traits>
#include "sym_matrix.hpp"

namespace scn //short for Su' Complex Networks
{

   template<class NodeType>
   class _node_iterator : public std::unordered_map<size_t, NodeType>::iterator
   {
   public:
      typedef NodeType   value_type;
      typedef size_t     reference;//dereference for the index of node
      typedef NodeType*  pointer;
   public:
      _node_iterator(){;}
      
      _node_iterator(typename std::unordered_map<size_t, NodeType>::iterator &&iter)
	 :iterator_base(iter){;}
   
      inline reference operator*() const
      {return iterator_base->second.GetIndexOfNode();}
      
      inline pointer operator->() const
      {return std::addressof(iterator_base->second);}
   
      inline _node_iterator& operator++()
      {
	 iterator_base++;
	 return *this;
      }
      
      inline _node_iterator& operator++(int)
      {
	 iterator_base++;
	 return *this;
      }
      
      inline bool operator==(const _node_iterator& other) const
      {
	 return iterator_base == other.iterator_base;
      }

      inline bool operator!=(const _node_iterator other) const
	  {

	 return iterator_base != other.iterator_base;
      }

      inline _node_iterator& operator=(const _node_iterator& other)
      {
	 iterator_base = other.iterator_base;
	 return *this;
      }
   protected:
      typename std::unordered_map<size_t, NodeType>::iterator iterator_base;
   };
//////////////////////////////////////////////////////////////
//////////////////////////

   class _node
   {
   public:
      typedef std::unordered_set<size_t>::const_iterator  inout_iterator;
   public:
      class iterator : public std::unordered_set<size_t>::const_iterator
      {
      public:
	 typedef size_t   value_type;
	 typedef const size_t&  reference;
	 typedef const size_t*  pointer;
	 typedef std::unordered_set<size_t>::const_iterator _base_type;
      public:
	 iterator(){}
	 
	 iterator(_base_type &in_degree_begin, _base_type &in_degree_end, 
		  _base_type &out_degree_begin)
	    :current(in_degree_begin), in_degree_end(in_degree_end),
	     out_degree_begin(out_degree_begin){}
	 
	 inline reference operator*() const
	 {return reference(*current);}
	 
	 inline pointer operator->() const
	 {return pointer(*current);}
	 
	 inline iterator& operator++()
	 {
	    current++;
	    if(current == in_degree_end)
	       current = out_degree_begin;
	    return *this;
	 }
	 
	 inline iterator& operator++(int)
	 {
	    current++;
	    if(current == in_degree_end)
	       current = out_degree_begin;
	    return *this;
	 }
	 
	 inline bool operator==(const iterator& other) const
	 { return current == other.current;}
	 
	 inline bool operator!=(const iterator& other) const
	 {
		
		 return current != other.current;}
	 
	 inline iterator& operator=(const iterator& other)
	 {
	    current = other.current;
	    in_degree_end = other.in_degree_end;
	    out_degree_begin = other.out_degree_begin;
	    return *this;
	 }
      protected:
	 _base_type current;
	 _base_type in_degree_end;
	 _base_type out_degree_begin;
      };      
   public:
      _node(size_t indexOfNode = -1) : index(indexOfNode){;}
      ~_node(){;}
   public:
      inline _node::iterator begin() const
      {
	 return _node::iterator(in_degree.begin(), in_degree.end(), 
				out_degree.begin());
      }
  
      inline bool Has(size_t other) const
	  {
		 if(in_degree.find(other) != in_degree.end() || out_degree.find(other) != out_degree.end())
				return true;
		 else
				return false;
			
	  }
	 
	  inline _node::inout_iterator in_begin() const
      {return in_degree.begin(); }
      
      inline _node::inout_iterator out_begin() const
      {return out_degree.begin(); }
      
      inline _node::iterator end() const
      {return _node::iterator(in_degree.end(), in_degree.end(), out_degree.begin());}
      
      inline _node::inout_iterator in_end() const
      {return in_degree.end(); }
      
      inline _node::inout_iterator out_end() const
      {return out_degree.end(); }
   public:
      inline size_t GetDegree(){return in_degree.size() + out_degree.size();}
      inline size_t GetInDegree(){return in_degree.size();}
      inline size_t GetOutDegree(){return out_degree.size();}
      inline size_t GetIndexOfNode(){return index;}
  
      friend class Graph;
      friend class UGraph;
      friend class DGraph;
      size_t index;
      std::unordered_set<size_t> in_degree;/**<in_degree set form a
					    * complete endge sets
					    * with out_degree in DGraph */
      std::unordered_set<size_t> out_degree;/**<In UGraph, these
					     * out_degree has any meanings */
   };
//////////////////////////////////////////////////////////////
//////////////////////////

   class Graph
   {
   public://constant numbers
      static const size_t NaF = -1;
      typedef _node_iterator<_node>   iterator;
      typedef std::shared_ptr<Graph>  pGraph;
   public://constructor and destructor
      
      Graph(){};

      Graph(size_t numberOfNodes)
      {
//	 reserve(numberOfNodes);
	 
	 for(size_t i = 0; i < numberOfNodes; i++)
	 {
	    AddNode(i);
	 }
      }
      
      ~Graph(){};

   public://public operation
      
      inline bool HasNode(size_t index)
      {
	 if(node_list.find(index) == node_list.end())
	    return false;
	 else
	    return true;
      }

      inline void AddNode(size_t index)
      {
	 assert(!HasNode(index));
	 node_list[index].index = index;
      }

      inline size_t AddNode()
      {
	 assert(!HasNode(node_list.size()));
	 
	 size_t index = node_list.size();
	 node_list[index].index = index;
	 return index;
      }
      
      inline void RemoveNode(size_t index)
      {
	 assert(HasNode(index));
	 auto iter = node_list.find(index);
	 
	 for(auto other = iter->second.begin(); 
	     other != iter->second.end(); other++)
	 {
	    node_list[*other].in_degree.erase(index);
	    node_list[*other].out_degree.erase(index);
	 }
	 node_list.erase(iter);
      }
	   inline virtual _node GetNode(size_t index)
	  {
		  return node_list.find(index)->second;
	  }
      inline size_t GetNumberOfEdges()
      {
	 size_t sum = 0;
	 for(auto iter = begin(); iter != end(); iter++)
	 {
	    sum += iter->GetDegree();
	 }
	 return sum / 2;
      }
      
      inline size_t GetNumberOfNodes(){return node_list.size();}


   public://edge operations, all of them are abstract virtual function

      virtual void AddEdge(size_t indexOfHead, size_t indexOfTail, bool reverse=false)=0;

      virtual void AddEdge(iterator& head, size_t indexOfTail, bool reverse = false)=0;

      virtual void AddEdge(iterator& head, iterator& tail, bool reverse = false) = 0;

      virtual void RemoveEdge(size_t indexOfHead, size_t indexOfTail, 
			      bool reverse = false)=0;

      virtual void RemoveEdge(iterator& head, size_t indexOfTail, 
			      bool reverse = false)=0;
      
      virtual void RemoveEdge(iterator& head, iterator& tail, bool reverse = false)=0;

      virtual bool HasEdge(size_t indexOfHead, size_t indexOfTail, bool reverse=false)=0;
      
      virtual bool HasEdge(iterator& head, size_t indexOfTail, bool reverse = false)=0;

      virtual bool HasEdge(iterator& head, iterator& tail, bool reverse = false)=0;

   public://STL pattern
      
//      void reserve(size_t size){node_list.reserve(size);}
/**
 * @name size - get the number of nodes and edges. If not all these
 * two data are needed, it's better to call GetNumberOf...() instead
 * of this function
 * @return std::pair(number of nodes, number of edges)
 */
      std::pair<size_t, size_t> size()
      {
	 size_t sum = 0;
	 for(auto iter = begin(); iter != end(); iter++)
	 {
	    sum += iter->GetDegree();
	 }
	 return std::make_pair(node_list.size(), sum / 2);
      }

      inline Graph::iterator begin(){return iterator(node_list.begin());}
      
      inline Graph::iterator end(){return iterator(node_list.end());}

      inline Graph::iterator find(size_t index){return iterator(node_list.find(index));}

   protected:
      std::unordered_map<size_t, _node> node_list;
   };
//////////////////////////////////////////////////////////////
//////////////////////////

   class UGraph : public Graph
   {
   public:
      typedef std::shared_ptr<UGraph>  pGraph;
/**
 * @name UGraph - default constructor
 * @return int
 */
      UGraph(){}

      UGraph(size_t numberOfNodes):Graph(numberOfNodes){}
/**
 * @name UGraph - destructor
 * @return void
 */
      ~UGraph(){}

   public://implementation of virtual function

      inline virtual void AddEdge(size_t indexOfHead, size_t indexOfTail, 
				  bool reverse = false)
      {
	 assert(HasNode(indexOfHead));
	 assert(HasNode(indexOfTail));
	 assert(indexOfHead != indexOfTail);
	 
	 node_list[indexOfHead].in_degree.insert(indexOfTail);
	 node_list[indexOfTail].in_degree.insert(indexOfHead);
      }

      inline virtual void AddEdge(iterator& head, size_t indexOfTail,
				  bool reverse = false)
      {
	 assert(HasNode(indexOfTail));
	 assert(*head != indexOfTail);
	 
	 head->in_degree.insert(indexOfTail);
	 node_list[indexOfTail].in_degree.insert(*head);
      }

      inline virtual void AddEdge(iterator& head, iterator& tail,
				  bool reverse = false)
      {
	 assert(head != tail);
	 
	 head->in_degree.insert(*tail);
	 tail->in_degree.insert(*head);
      }


      inline virtual void RemoveEdge(size_t indexOfHead, size_t indexOfTail, 
				     bool reverse = false)
      {
	 assert(HasNode(indexOfHead));
	 assert(HasNode(indexOfTail));
	 
	 node_list[indexOfHead].in_degree.erase(indexOfTail);
	 node_list[indexOfTail].in_degree.erase(indexOfHead);
      }


      inline virtual void RemoveEdge(iterator& head, size_t indexOfTail, 
				     bool reverse = false)
      {
	 assert(HasNode(indexOfTail));
	 
	 head->in_degree.erase(indexOfTail);
	 node_list[indexOfTail].in_degree.erase(*head);
      }
      
      inline virtual void RemoveEdge(iterator& head, iterator& tail,
				     bool reverse = false)
      {
	 head->in_degree.erase(*tail);
	 tail->in_degree.erase(*head);
      }
      

      inline virtual bool HasEdge(size_t indexOfHead, size_t indexOfTail, 
				  bool reverse = false)
      {
	 assert(HasNode(indexOfHead));
	 assert(HasNode(indexOfTail));
	 if(node_list[indexOfHead].in_degree.find(indexOfTail) == 
	    node_list[indexOfHead].in_degree.end())
	    return false;
	 else
	    return true;
      }
     
      inline virtual bool HasEdge(iterator& head, size_t indexOfTail, 
				  bool reverse = false)
      {
	 assert(HasNode(indexOfTail));
	 
	 if(head->in_degree.find(indexOfTail) == 
	    head->in_degree.end())
	    return false;
	 else
	    return true;
      }


      inline virtual bool HasEdge(iterator& head, iterator& tail, 
			   bool reverse = false)
      {
	 if(head->in_degree.find(*tail) == 
	    head->in_degree.end())
	    return false;
	 else
	    return true;
      }

      
   public://special operations

      SymMatrix::pMatrix GetAdjacencyMatrix()
      {
	 SymMatrix::pMatrix matrix(new SymMatrix(GetNumberOfNodes()));
	 
	 //write '1'
	 for(size_t node = 0; node<this->GetNumberOfNodes(); node++)
	 {
		auto node_value = node_list[node];
		for(auto other = node_value.in_degree.begin(); other != node_value.in_degree.end(); other++)
		{
	       matrix->SetElement(node, *other, 1.0);
	    }
	 }
	 return matrix;
      }
   };

//////////////////////////////////////////////////////////////
//////////////////////////

/** DGraph
 *
 * directed edge graph. The number of edges between any pair of nodes
 * is no more than 2.
 */

   class DGraph : public Graph
   {
   public:
      typedef std::shared_ptr<DGraph>  pGraph;

      DGraph(){}

      DGraph(size_t numberOfNodes):Graph(numberOfNodes){}
      
      ~DGraph(){}

   public://implementation of virtual function

      inline virtual void AddEdge(size_t indexOfHead, size_t indexOfTail,
				  bool reverse = false)
      {
	 assert(HasNode(indexOfHead));
	 assert(HasNode(indexOfTail));
	 assert(indexOfHead != indexOfTail);
	 if(reverse)
	 {
	    node_list[indexOfHead].out_degree.insert(indexOfTail);
	    node_list[indexOfTail].in_degree.insert(indexOfHead);
	 }
	 else
	 {
	    node_list[indexOfHead].in_degree.insert(indexOfTail);
	    node_list[indexOfTail].out_degree.insert(indexOfHead);
	 }
      }


      inline virtual void AddEdge(iterator& head, size_t indexOfTail,
				  bool reverse = false)
      {
	 assert(HasNode(indexOfTail));
	 if(reverse)
	 {
	    head->out_degree.insert(indexOfTail);
	    node_list[indexOfTail].in_degree.insert(*head);
	 }
	 else
	 {
	    head->in_degree.insert(indexOfTail);
	    node_list[indexOfTail].out_degree.insert(*head);
	 }
      }


      inline virtual void AddEdge(iterator& head, iterator& tail,
				  bool reverse = false)
      {
	 if(reverse)
	 {
	    head->out_degree.insert(*tail);
	    tail->in_degree.insert(*head);
	 }
	 else
	 {
	    head->in_degree.insert(*tail);
	    tail->out_degree.insert(*head);
	 }
      }


      inline virtual void RemoveEdge(size_t indexOfHead, size_t indexOfTail, 
				     bool reverse = false)
      {
	 assert(HasNode(indexOfHead));
	 assert(HasNode(indexOfTail));
	 if(reverse)
	 {
	    node_list[indexOfHead].out_degree.erase(indexOfTail);
	    node_list[indexOfTail].in_degree.erase(indexOfTail);
	 }
	 else
	 {
	    node_list[indexOfHead].in_degree.erase(indexOfTail);
	    node_list[indexOfTail].out_degree.erase(indexOfTail);
	 }
      }


      inline virtual void RemoveEdge(iterator& head, size_t indexOfTail,
				     bool reverse = false)
      {
	 assert(HasNode(indexOfTail));
	 if(reverse)
	 {
	    head->out_degree.erase(indexOfTail);
	    node_list[indexOfTail].in_degree.erase(*head);
	 }
	 else
	 {
	    head->in_degree.erase(indexOfTail);
	    node_list[indexOfTail].out_degree.erase(*head);
	 }
      }

      
      inline virtual void RemoveEdge(iterator& head, iterator& tail,
				     bool reverse = false)
      {
	 if(reverse)
	 {
	    head->out_degree.erase(*tail);
	    tail->in_degree.erase(*head);
	 }
	 else
	 {
	    head->in_degree.erase(*tail);
	    tail->out_degree.erase(*head);
	 }
      }

      inline virtual bool HasEdge(size_t indexOfHead, size_t indexOfTail, 
			   bool reverse = false)
      {
	 assert(HasNode(indexOfHead));
	 assert(HasNode(indexOfTail));
	 if(reverse)
	 {
	    if(node_list[indexOfHead].out_degree.find(indexOfTail) ==
	       node_list[indexOfHead].out_degree.end())
	       return false;
	    else
	       return true;
	 }
	 else
	 {
	    if(node_list[indexOfHead].in_degree.find(indexOfTail) ==
	       node_list[indexOfHead].in_degree.end())
	       return false;
	    else
	       return true;
	 }
      }

      
      inline virtual bool HasEdge(iterator& head, size_t indexOfTail,
			   bool reverse = false)
      {
	 assert(HasNode(indexOfTail));

	 if(reverse)
	 {
	    if(head->out_degree.find(indexOfTail) == 
	       head->out_degree.end())
	       return false;
	    else
	       return true;
	 }
	 else
	 {
	    if(head->in_degree.find(indexOfTail) == 
	       head->in_degree.end())
	       return false;
	    else
	       return true;
	 }
      }

      virtual bool HasEdge(iterator& head, iterator& tail, 
			   bool reverse = false)
      {
	 if(reverse)
	 {
	    if(head->out_degree.find(*tail) ==
	       head->out_degree.end())
	       return false;
	    else
	       return true;
	 }
	 else
	 {
	    if(head->in_degree.find(*tail) ==
	       head->in_degree.end())
	       return false;
	    else
	       return true;
	 }
      }
   };

};
