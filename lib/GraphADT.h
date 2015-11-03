#ifndef GRAPHADT_H
#define GRAPHADT_H

#include <string>
#include <unordered_map>
#include <set>
#include <iostream>

struct Edge{
	std::string edgename;
	std::string element;
	int weight;
};


typedef std::unordered_map<std::string, Edge> node_hashmap;
typedef std::unordered_map<std::string, node_hashmap> graph_hashmap;
typedef std::set<std::string> string_set;
typedef std::unordered_map< std::string, std::set< std::string> > subgraph;


void printSet(const std::set<std::string>&);
void printEdge(const Edge&);


class MyGraph{
private:
	int number_of_nodes;
	int number_of_edges;
	graph_hashmap thegraph;
	string_set set_of_vertices;
	string_set set_of_edges;
public:
	MyGraph(): number_of_nodes(0), number_of_edges(0) {} //using initialization list
	MyGraph(MyGraph const&);
	MyGraph copyUtil(const MyGraph&);
	string_set nodes() const;
	string_set edges() const;
	int countAllNodes() const;
	int countAllEdges() const;
	Edge getEdge(std::string, std::string) const;
	string_set incidentEdges(std::string v) const;
	std::string opposite(std::string, std::string) const;
	string_set endNodes(std::string) const;
	bool areAdjacent(std::string, std::string) const;
	void insertNode(std::string);
	void removeNode(std::string);
	void insertEdge(std::string, std::string, std::string);
	void removeEdge(std::string, std::string);
	std::string getEdgeElem (std::string) const;
	void replaceEdgeElem(std::string, std::string);
	bool isEqual(const MyGraph&) const;
	bool emptyGraph();
	MyGraph graph_intersection(const MyGraph&) const;
	MyGraph graph_difference(const MyGraph&) const;
	MyGraph graph_union(const MyGraph&) const;
	MyGraph graph_complement() const;
	void printGraph() const;
	void insertEdge(std::string, std::string);
	MyGraph copyGraph() const;
};

class DirectedMyGraph : MyGraph{

public:
	bool areAdjacent(std::string, std::string) const;
};


class MySubGraph : public MyGraph{
	subgraph allSubgraphs;
	std::unordered_map <std::string, std::string> countries_continents;

public :
	void insertNode(std::string, std::string);
	string_set subgraphContents(const std::string&);
	std::string getSubgraphName(const std::string&);
};

#endif // GRAPHADT_H
