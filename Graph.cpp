//
// Created by pj on 4/3/18.
//

#include "Graph.h"


// Allocates memory for adjacency list
Graph::Graph(int n) {

    // Graph member graph is STL container, list
    this->n = n;
    graph = new std::list<std::tuple<int, int> >[n];

    ConnMtx = new bool*[n];
    for (int i = 0; i<n; ++i){
        ConnMtx[i] = new bool[n];
    }

    //initalize Conn Matrix
    for (int i = 0; i<n; ++i)
        for (int j = 0; j<n; ++j)
        ConnMtx[i][j] = false;

}




void Graph::addEdge(int srcNode, int targNode, int weight) {
    bool E;
    E = Graph::EdgeCheck(srcNode, targNode);
    if (!E) {
        std::tuple<int, int> tmpPair_src(targNode, weight);
        graph[srcNode].push_back(tmpPair_src);
        ConnMtx[srcNode][targNode] = true;
    }
    else
        std::cout<<"Edge from "<<srcNode<<" to "<<targNode<<" already exists! "<<std::endl;
    std::cout<<std::endl;

}


void Graph::addNode(std::tuple<int, int> newNode) {

    int NodeY = std::get<1>(newNode);
    int NodeX = std::get<0>(newNode);

    Graph::ConnMtx[NodeX][NodeY] = true;

}


void Graph::delNode(std::tuple<int, int> newNode) {
    int NodeY = std::get<1>(newNode);
    int NodeX = std::get<0>(newNode);

    Graph::ConnMtx[NodeX][NodeY] = false;
}

void Graph::delEdge(int srcNode, int targNode) {
    std::tuple<int, int> tmpPair_targ(srcNode, INT16_MAX);
    std::tuple<int, int> tmpPair_src(targNode, INT16_MAX);

    graph[targNode].push_back(tmpPair_src);
    graph[srcNode].push_back(tmpPair_targ);

    // virtually inf
}


bool Graph::EdgeCheck(int srcNode, int targNode) const {
    return ConnMtx[srcNode][targNode];
}

int Graph::getEdge(int srcNode, int targNode) const {

    std::tuple<int, int> newNode(0, 0);
    int edgeWeight = INT16_MAX;

    // Get  child nodes of srcNode  <childNode,weight> pair
    std::list<std::tuple<int, int>>::iterator i;
    for (i = graph[srcNode].begin(); i != graph[srcNode].end(); ++i) {
        int Y = std::get<1>(newNode); // weight of edge
        int X = std::get<0>(newNode); //child Node

        if (X == targNode) {
            edgeWeight = Y;
            return edgeWeight;
        } else
            edgeWeight = INT16_MAX;  // Edge Does Not Exist
    }

    return edgeWeight;
}

// Return tuple
//std::tuple<int,int> getNode(int srcNode) const;

int Graph::getClosestNode(int srcNode) const {
    // Declare a set of tuple pairs to store and pre-sort node list
    std::set<std::tuple<int, int> > pointSet;

    int closestNode = -1;  //Return -1 if there is no closest point

    // declare a temporary pair variable with our
    // user defined type "point"initialize to (0,0)
    std::tuple<int, int> tmpPair(0, 0);

    //
    // the neighbors list
    std::vector<int> neigh = Graph::neighbors(srcNode);
    if (!neigh.empty()) {
        // put all child points of srcNode ( <childNode,weight> pair ) into the a set. .
        std::list<std::tuple<int, int>>::iterator i;
        for (i = graph[srcNode].begin(); i != graph[srcNode].end(); ++i) {

            //pointSet.insert(*i);
        }

        // The first node in Set presorted  container is the minimum distance
        tmpPair = *(pointSet.begin());

        int X = std::get<0>(tmpPair); // child Node is 1st of pair

        closestNode = X;
    }
    return closestNode;

};


std::vector<int> Graph::neighbors(int srcNode) const {
    std::vector<int> adjacent;     // list of adjacent edges -1=NC 0=self  Edge=distance
    bool neigh;

    for (int i = 0; i < n; i++) {
        neigh = Graph::ConnMtx[srcNode][i];
        if (neigh) {
            adjacent.push_back(i);
        }
    }

    return adjacent;

}

// Dijkstra Function
// Returns shortest paths from srcNode to all other vertices
std::set<std::tuple<int, int> > Graph::Dijkstra(int srcNode) {
    // Declare a set of tuple pairs to store and pre-sort node list
    std::set<std::tuple<int, int> > pointSet;

    // Create a vector for distances and initialize to INT16MAX)
    std::vector<int> dist(n, INT16_MAX);

    // declare a temporary pair variable with our
    // user defined type "point"initialize to (0,0)
    //std::tuple<int, int> tmpPair(0, 0);

    // Insert source itself in Set and initialize its
    // distance as 0.

    pointSet.insert(std::make_tuple(0, srcNode));
    dist[srcNode] = 0;

    // Loop until all shortest distances are complete
    //   this is indicated by pointSet being empty
    while (!pointSet.empty()) {
        // The first point in Set is the minimum distance
        //  grab it and delete it from set.
        auto tmpPair = *(pointSet.begin());
        pointSet.erase(pointSet.begin());

        // Node label is stored in y element of the (x,y) pair  to keep the points
        // sorted by distance distance (distance must be first item in the pair)
        int U = std::get<1>(tmpPair);

        // 'i' is used to index all child nodes of a point
        std::list<std::tuple<int, int> >::iterator i;

        for (i = graph[U].begin(); i != graph[U].end(); ++i)
        {
            // Get point label and weight of current child of Node U.

            auto V = std::get<0>(*i); // child node Vi
            auto weight = std::get<1>(*i); // Edge weight node U <-> Vi

            //  If there is shorter path to V through U
            if (dist[V] > dist[U] + weight) {
                //  If distance of V is not virtual Infinity then it exists in the set
                // so replace it with the shorter distance.
                if (dist[V] != INT16_MAX) {
                    tmpPair = std::make_tuple(dist[V], V);
                    pointSet.erase(pointSet.find(tmpPair));
                }

                // Update distance of point from source point
                dist[V] = dist[U] + weight;

                tmpPair = std::make_tuple(dist[V], V);
                pointSet.insert(tmpPair);
            }
        }
    }

    std::cout << "Vertex   Distance from Source " << std::endl;
    for (int i = 0; i < n; ++i)
        std::cout << " \t" << i << "\t " << dist[i] << std::endl;

    return pointSet;

}

Graph::~Graph() {



    for (int i = 0; i < n; ++i) {
        delete [] ConnMtx[i];
    }

    delete [] ConnMtx;
}