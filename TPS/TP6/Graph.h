/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    int dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    int index;
    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    explicit Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    std::vector<std::vector<double>> floydDist;
    std::vector<std::vector<int>> floydPath;


public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &orig);
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;
    bool allVisited();

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (Vertex<T> *v: vertexSet){
      v->path = nullptr;
      v->dist = INT_MAX;
    }

    std::queue<Vertex<T>*> vertexQueue;

     Vertex<T>* vertexAux = findVertex(orig);
    vertexQueue.push(vertexAux);
    vertexAux->dist = 0;

    while(!vertexQueue.empty()){
      vertexAux = vertexQueue.front();
      vertexQueue.pop();
      for (Edge<T> edge: vertexAux->adj){
        if (edge.dest->dist == INT_MAX){
          vertexQueue.push(edge.dest);
          edge.dest->dist = vertexAux->dist + 1;
          edge.dest->path = vertexAux;
        }
      }
    }
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
  for (Vertex<T> *v: vertexSet) {
    v->path = nullptr;
    v->dist = INT_MAX;
  }
  MutablePriorityQueue<Vertex<T>> minQueue;
  Vertex<T>* vertexAux = findVertex(origin);
  vertexAux->dist = 0;
  minQueue.insert(vertexAux);

  while(!minQueue.empty()){
    vertexAux = minQueue.extractMin();
    for (Edge<T> edge: vertexAux->adj){
      if (edge.dest->dist > (vertexAux->dist + edge.weight)){
        edge.dest->dist = vertexAux->dist + edge.weight;
        edge.dest->path = vertexAux;
        if(edge.dest->queueIndex) minQueue.decreaseKey(edge.dest);
        else {
          minQueue.insert(edge.dest);
        }
      }
    }
  }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
  for (Vertex<T> *v: vertexSet){
    v->path = nullptr;
    v->dist = INT_MAX;
  }
  Vertex<T> *v = findVertex(orig);
  v->dist = 0;

  for (int i = 1; i < vertexSet.size(); i++){
    for (Vertex<T> *v: vertexSet) {
      for (Edge<T> edge : v->adj) {
        if (edge.dest->dist > (v->dist + edge.weight)) {
          edge.dest->dist = v->dist + edge.weight;
          edge.dest->path = v;
        }
      }
    }
  }
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    Vertex<T>* aux = findVertex(dest);

  while(aux != nullptr){
    res.insert(res.begin(),aux->info);
    aux = aux->getPath();
  }
  return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
  int n = vertexSet.size();
  std::vector<std::vector<double>> dists(n,std::vector<double>(n,INF));
  std::vector<std::vector<int>> path(n,std::vector<int>(n,-1));

  //Initializing matrix indexes
  for(int i = 0; i < vertexSet.size(); i++)
    vertexSet[i]->index = i;

  for(auto &u: vertexSet){
    dists[u->index][u->index] = 0;
    for(auto &e: u->adj){
        dists[u->index][e.dest->index] = e.weight;
        path[u->index][e.dest->index] = e.dest->index;
    }
  }

  for (int k = 0; k < n; k++){
    for (int i = 0; i < n; i++){
      for (int j = 0; j < n; j++){
        if (dists[i][j] > (dists[i][k] + dists[k][j])){
          dists[i][j] = dists[i][k] + dists[k][j];
          path[i][j] = path[i][k];
        }
      }
    }
  }
  floydPath = path;
  floydDist = dists;
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
  std::vector<T> res;
  Vertex<T>* start = findVertex(orig);
  Vertex<T>* end = findVertex(dest);

  int i,j;
  i = start->index;
  j = end->index;
  res.push_back(start->info);
  while(floydPath[i][j] != -1){
    res.push_back(vertexSet[floydPath[i][j]]->info);
    i = floydPath[i][j];
  }
  return res;
}


#endif /* GRAPH_H_ */
