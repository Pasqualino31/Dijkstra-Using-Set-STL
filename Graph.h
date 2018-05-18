//
// Created by pj on 4/3/18.
//

#ifndef DIJKSTRA_MASTER_GRAPH_H
#define DIJKSTRA_MASTER_GRAPH_H


#include<bits/stdc++.h>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include <utility>
#include <iterator>
#include <list>
#include <functional>
#include <tuple>


class Graph {

private:

    int n;
    std::list<std::tuple<int, int> > *graph;  // graph is an array of lists of edges
    bool **ConnMtx;

public:

    Graph() : n(), graph(), ConnMtx() {};

    explicit Graph(int n);

    ~Graph();

    //void initGraph(int n);

    //    add_edge(G, x, y): adds the edge from the vertex x to the vertex y, if it is not there;
    void addEdge(int srcNode, int targNode, int weight);

    //    addNode(G, x): adds the vertex x, if it is not there;
    void addNode(std::tuple<int, int> newNode);

    //    deledge(G, x, y): removes the edge from the vertex x
    // to the vertex y, if it is there (or not);
    void delEdge(int srcNode, int targNode);

    //    delNode(G, x): removes the Node (x,y), if it is there;
    void delNode(std::tuple<int, int> newNode);

    // getNode_value(G, x): returns the point associated with
    // the NodeList index x  ( Nodelist(x) );
    std::tuple<int, int> getNode(int srcNode) const;

    //    getEdge(G: x, y): returns the value associated with the edge (x, y);
    int getEdge(int srcNode, int targNode) const;

    int getClosestNode(int srcNode) const;

    //EdgeCheck(G: x, y): tests whether there is an edge
    // from the vertex x to the vertex y
    bool EdgeCheck(int srcNode, int targNode) const;

    //neighbors(G: x): lists all vertices y such that there is
    // an edge from the vertex x to the vertex y;
    std::vector<int> neighbors(int srcNode) const;

    // Dijkstra Funtion
    // Returns shortest paths from srcNode to all other vertices
    std::set<std::tuple<int, int>> Dijkstra(int srcNode);


};

#endif //DIJKSTRA_MASTER_GRAPH_H
