#ifndef _CYCLEBREAKER_H
#define _CYCLEBREAKER_H
#include <vector>
#include <fstream>

using namespace std; 

class Vertex{
    private:
        int parent;
        int rank;
        char color;
    public:
        int getParent();
        int getRank();
        char getColor();
        void increaseRank();
        void setParent(int);
        void setColor(char);
        Vertex(int, int, char);
};

class Edge{
    private:
        int startVertex;
        int endVertex;
        int edgeWeight;
    public:
        int getStartVertex();
        int getEndVertex();
        int getEdgeWeight();
        void printEdge();
        Edge(int, int, int);
};

class Graph{
    private:
        char graphType;
        int numVertices;
        int numEdges;
        vector<Vertex> vertexArr;
        vector<Edge> edgeArr;
        vector<Edge> notCollectedEdges;
        vector<int> adjList[10000];
        int findSet(int); //Get representative of a disjoint set
        void unionSetbyRank(int, int); //Union two disjoint set
    public:
        Graph(vector<Vertex>, vector<Edge>, int, int, char);
        void findMSTWithKruskalUndirected(int&, vector<Edge>&);
        void findMSTWithKruskalDirected();
        void doCountingSortOnEdge();
        void breakCycleInDirectedGraph(int&, vector<Edge>&);
        void DFS_Visit(int, bool&);
        void reinitializeGraph();
        void printNotCollectedEdges();
        void printGraph();
        void printAdjList();
};

void help_message();

#endif