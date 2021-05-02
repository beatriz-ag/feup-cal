#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex1() {
  GraphViewer gv;
  gv.setCenter(sf::Vector2f(300, 300));
  gv.createWindow(600, 600);

  ;

  Node &node1 = gv.addNode(1, sf::Vector2f(400, 300));
  node1.setColor(GraphViewer::BLUE);

  Node &node2 = gv.addNode(2, sf::Vector2f(500, 300));
  node2.setColor(GraphViewer::GREEN);

  Edge &edge1 = gv.addEdge(1,node1,node2,
                           GraphViewer::Edge::EdgeType::DIRECTED);



  for(Edge *edge: gv.getEdges())
    edge->setColor(GraphViewer::YELLOW);

  gv.setBackground("../TP7_graphviewer/resources/background.png");

  gv.join();


}
