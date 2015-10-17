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
typedef std::set<std::string> my_set;



void printSet(const std::set<std::string>&);
void printEdge(const Edge&);


class MyGraph{
private:
    int number_of_nodes;
    int number_of_edges;
    graph_hashmap thegraph;
    my_set set_of_vertices;
    my_set set_of_edges;
public:
    MyGraph(): number_of_nodes(0), number_of_edges(0) {} //using initialization list
    MyGraph(MyGraph const&);
    MyGraph copyUtil(const MyGraph&);
    my_set vertices() const;
    my_set edges() const;
    int countAllVertices() const;
    int countAllEdges() const;
    Edge getEdge(std::string, std::string) const;
    my_set incidentEdges(std::string v) const;
    std::string opposite(std::string, std::string) const;
    my_set endVertices(std::string edge) const;
    bool areAdjacent(std::string v, std::string w) const;
    void insertVertex(std::string);
    void removeVertex(std::string vertexname);
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
    void insertEdge(std::string v, std::string w);
    MyGraph copyGraph() const;
};

class DirectedMyGraph : MyGraph{

public:
    bool areAdjacent(std::string v, std::string w) const;
};



#endif
