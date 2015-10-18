#include <utility> // declares std, but not std::cout

#include "librisk.h"
#include "GraphADT.h"

using namespace std;

int main() {
	cout << "This is a call to the library function: \n";
	librisk_print_todo();

    /*std::cout<<"Starting GraphADT code:"<<std::endl;
    MyGraph g1;
    printSet(g1.vertices());

    g1.insertVertex("France");
    std::cout<<"Vertices: "<<g1.countAllVertices()<<std::endl;
    printSet(g1.vertices());

    g1.insertVertex("Spain");
    std::cout<<"Vertices: "<<g1.countAllVertices()<<std::endl;

    printSet(g1.vertices());

    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    g1.insertEdge("Spain","France","E1");
    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    printSet(g1.edges());

    g1.removeEdge("Spain","France");
    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    printSet(g1.edges());

    g1.insertEdge("France","Spain","E2");
    std::cout<<"Edges: "<<g1.countAllEdges()<<std::endl;

    g1.printGraph();
    printSet(g1.edges());

    std::cout<<g1.getEdgeElem("E1")<<std::endl;
    std::cout<<g1.getEdgeElem("E2")<<std::endl;
    g1.replaceEdgeElem("E2","Ex2");
    std::cout<<g1.getEdgeElem("E2")<<std::endl;


    printSet(g1.edges());
    printSet(g1.vertices());
    g1.removeVertex("France");

    printSet(g1.edges());
    printSet(g1.vertices());

    g1.removeVertex("Spain");

    g1.printGraph();
    */

	return 0;
}
