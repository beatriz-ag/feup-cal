/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <queue>
#include <vector>

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

/****************** Provided structures  ********************/

template <class T> class Vertex {
  T info;                   // contents
  std::vector<Edge<T>> adj; // list of outgoing edges
  bool visited;             // auxiliary field used by dfs and bfs
  bool processing;          // auxiliary field used by isDAG
  int indegree;             // auxiliary field used by topsort

  void addEdge(Vertex<T> *dest, double w);
  bool removeEdgeTo(Vertex<T> *d);

public:
  Vertex(T in);
  friend class Graph<T>;
};

template <class T> class Edge {
  Vertex<T> *dest; // destination vertex
  double weight;   // edge weight
public:
  Edge(Vertex<T> *d, double w);
  friend class Graph<T>;
  friend class Vertex<T>;
};

template <class T> class Graph {
  std::vector<Vertex<T> *> vertexSet; // vertex set

  void dfsVisit(Vertex<T> *v, std::vector<T> &res) const;
  Vertex<T> *findVertex(const T &in) const;
  bool dfsIsDAG(Vertex<T> *v) const;

public:
  int getNumVertex() const;
  bool addVertex(const T &in);
  bool removeVertex(const T &in);
  bool addEdge(const T &sourc, const T &dest, double w);
  bool removeEdge(const T &sourc, const T &dest);
  std::vector<T> dfs() const;
  std::vector<T> bfs(const T &source) const;
  std::vector<T> topsort() const;
  int maxNewChildren(const T &source, T &inf) const;
  bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T> Vertex<T>::Vertex(T in) : info(in) {}

template <class T> Edge<T>::Edge(Vertex<T> *d, double w) : dest(d), weight(w) {}

template <class T> int Graph<T>::getNumVertex() const {
  return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T> Vertex<T> *Graph<T>::findVertex(const T &in) const {
  for (auto v : vertexSet)
    if (v->info == in)
      return v;
  return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already
 * exists.
 */
template <class T> bool Graph<T>::addVertex(const T &in) {
  // TODO (4 lines)
  // HINT: use the findVertex function to check if a vertex already exists
  if (findVertex(in) == NULL) {
    vertexSet.push_back(new Vertex<T>(in));
    return true;
  }
  return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex
 * does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
  // TODO (6 lines)
  // HINT: use findVertex to obtain the actual vertices
  if (findVertex(sourc) == NULL || findVertex(dest) == NULL)
    return false;
  // HINT: use the next function to actually add the edge

  Vertex<T> *src = findVertex(sourc);
  Vertex<T> *des = findVertex(dest);
  src->addEdge(des, w);
  return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T> void Vertex<T>::addEdge(Vertex<T> *d, double w) {
  // TODO (1 line)
  adj.push_back(Edge<T>(d, w));
}

/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T> bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
  // TODO (5 lines)
  // HINT: Use "findVertex" to obtain the actual vertices.
  if (findVertex(sourc) == NULL || findVertex(dest) == NULL)
    return false;
  // HINT: Use the next function to actually remove the edge.
  Vertex<T> *src = findVertex(sourc);
  Vertex<T> *des = findVertex(dest);
  return src->removeEdgeTo(des);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T> bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
  // TODO (6 lines)
  // HINT: use an iterator to scan the "adj" vector and then erase the edge.
  for (auto it = adj.begin(); it != adj.end(); it++) {
    if (it->dest->info == d->info) {
      adj.erase(it);
      return true;
    }
  }
  return false;
}

/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T> bool Graph<T>::removeVertex(const T &in) {
  // TODO (10 lines)
  // HINT: use an iterator to scan the "vertexSet" vector and then erase the
  // vertex. HINT: take advantage of "removeEdgeTo" to remove incoming edges.
  typename std::vector<Vertex<T> *>::iterator it;
  typename std::vector<Vertex<T> *>::iterator itRemove;
  bool found = false;
  for (it = vertexSet.begin(); it != vertexSet.end(); it++) {
    Vertex<T> *v = *it;
    if (v->info == in) {
      itRemove = it;
      found = true;
    } else
      v->removeEdgeTo(new Vertex<T>(in));
  }
  if (found)
    vertexSet.erase(itRemove);
  return found;
}

/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T> std::vector<T> Graph<T>::dfs() const {
  // TODO (7 lines)
  std::vector<T> res;
  for (Vertex<T> *v : vertexSet) {
    v->visited = false;
  }
  for (Vertex<T> *v : vertexSet) {
    if (!v->visited)
      dfsVisit(v, res);
  }
  return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited,
 * recursively. Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, std::vector<T> &res) const {
  v->visited = 1;
  res.push_back(v->info);
  for (Edge<T> e : v->adj) {
    if (!e.dest->visited)
      dfsVisit(e.dest, res);
  }
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T> std::vector<T> Graph<T>::bfs(const T &source) const {
  // TODO (22 lines)
  // HINT: Use the flag "visited" to mark newly discovered vertices .
  // HINT: Use the "queue<>" class to temporarily store the vertices.
  std::vector<T> res;
  for (Vertex<T> *v : vertexSet) {
    v->visited = false;
  }
  std::queue<Vertex<T>*> q;
  q.push(vertexSet[0]);
  res.push_back(q.front()->info);
  Vertex<T> * auxV;
  q.front()->visited= true;
  while(!q.empty())
  {
    auxV = q.front();
    q.pop();
    for (Edge<T> e : auxV->adj)
    {
      if (!e.dest->visited){
        q.push(e.dest);
        e.dest->visited = true;
        res.push_back(e.dest->info);
      }
    }
  }

  return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template <class T> std::vector<T> Graph<T>::topsort() const {
  // TODO (26 lines)
  std::vector<T> res;
  //Set up
  for(Vertex<T> *v: vertexSet)
    v->indegree = 0;
  //Calculate degrees
  for (Vertex<T> *v: vertexSet){
    for (Edge<T> e: v->adj)
    e.dest->indegree++;
  }
  //Gather vertexes w degree 0
  std::queue<Vertex<T>*> q;
  for (Vertex<T>* v: vertexSet){
    if (!v->indegree)
      q.push(v);
  }

  Vertex<T> *auxV;
  while(!q.empty()){
    auxV = q.front();
    res.push_back(auxV->info);
    q.pop();
    for (Edge<T> e: auxV->adj){
      e.dest->indegree--;
      if (!e.dest->indegree){
        q.push(e.dest);
      }
    }
  }
  if (res.size() == vertexSet.size()) return res;
  else return std::vector<int>();
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T> int Graph<T>::maxNewChildren(const T &source, T &inf) const {
  // TODO (28 lines, mostly reused)
  Vertex<T> * v;
  Vertex<T>* max;
  int news = 0;
  for (Vertex<T> *auxV: vertexSet){
    auxV->visited = false;
    if (auxV->info == source)
      v = auxV;
  }
  std::queue<Vertex<T>*> q;
  q.push(v);
  //Go through connections
  while(!q.empty()){
    v = q.front();
    q.pop();
    int newsEdge = 0;
    //Calculate to how many connections a Person is giving news
    for (Edge<T> e: v->adj){
      //if news, add && register
      if (!e.dest->visited) {
        newsEdge++;
        e.dest->visited = true;
        q.push(e.dest);
      }
    }
    if (newsEdge>news){
      news = newsEdge;
      max = v;
    }
  }
  inf = max->info;
  return news;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical
 * classes). Returns true if the graph is acyclic, and false otherwise.
 */

template <class T> bool Graph<T>::isDAG() const {
  // TODO (9 lines, mostly reused)
  // HINT: use the auxiliary field "processing" to mark the vertices in the
  // stack.

  for (Vertex<T> *v : vertexSet) {
    v->visited = false;
    v->processing = false;
  }
  for (Vertex<T> *v : vertexSet) {
    if (!v->visited) {
      if (!dfsIsDAG(v)) return false;
    }
  }
  return true;

}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited,
 * recursively. Returns false (not acyclic) if an edge to a vertex in the stack
 * is found.
 */
template <class T> bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
  v->visited = 1;
  v->processing = 1;
  for (Edge<T> e : v->adj) {
    if (e.dest->processing) return false;
    if (!e.dest->visited)
      if (!dfsIsDAG(e.dest)) return false;
  }
  v->processing = 0;
  return true;
}

#endif /* GRAPH_H_ */
