#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "CycleBreaker.h"

using namespace std;

void help_message() { 
    cout << "usage: ./bin/cb <input file> <output file>" << endl;
}

Vertex::Vertex(int par=0, int rank=0, char color='W'):parent(par), rank(rank), color(color){}

int Vertex::getParent(){
    return this->parent;
}

int Vertex::getRank(){
    return this->rank;
}

char Vertex::getColor(){
    return this->color;
}

void Vertex::increaseRank(){
    this->rank+=1;
}

void Vertex::setParent(int par){
    this->parent = par;
}

void Vertex::setColor(char color){
    this->color = color;
}

Edge::Edge(int startVertex=0, int endVertex=0, int edgeWeight=0):
startVertex(startVertex), endVertex(endVertex), edgeWeight(edgeWeight){}

int Edge::getStartVertex(){
    return this->startVertex;
}

int Edge::getEndVertex(){
    return this->endVertex;
}

int Edge::getEdgeWeight(){
    return this->edgeWeight;
}

void Edge::printEdge(){
    cout << "Start vertex: " << startVertex  
    << ", End vertex: " << endVertex << ", Weight: " << edgeWeight;
}

Graph::Graph(vector<Vertex> vertexArr, vector<Edge> edgeArr, int numVertices, int numEdges, char graphType): 
vertexArr(vertexArr), edgeArr(edgeArr), numVertices(numVertices), numEdges(numEdges), graphType(graphType){}

int Graph::findSet(int i){
    int j = this->vertexArr[i].getParent();
    if (j == i){
        return j;
    }
    else{
        //path compression
        this->vertexArr[i].setParent(this->findSet(j));
    }
    return this->vertexArr[i].getParent();
}

void Graph::unionSetbyRank(int i, int j){
    int rootI = this->findSet(i);
    int rootJ = this->findSet(j);
    if (this->vertexArr[rootI].getRank() > this->vertexArr[rootJ].getRank()){
        this->vertexArr[rootJ].setParent(rootI);
    }
    else if (this->vertexArr[rootI].getRank() < this->vertexArr[rootJ].getRank()){
        this->vertexArr[rootI].setParent(rootJ);
    }
    else{
        this->vertexArr[rootJ].setParent(rootI);
        this->vertexArr[rootI].increaseRank();
    }
}

void Graph::doCountingSortOnEdge(){
    int max = 100;
    int min = -100;
    int range = max - min + 1;

    vector<int> count(range);
    vector<Edge> output(this->edgeArr.size());
    for (int i = 0; i < this->edgeArr.size(); i++)
        count[this->edgeArr[i].getEdgeWeight() - min]++;

    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    int pos;
    for (int i = this->edgeArr.size() - 1; i >= 0; i--) {
        //sort in reverse order
        pos = this->edgeArr.size() - (count[this->edgeArr[i].getEdgeWeight() - min]);
        output[pos] = this->edgeArr[i];
        count[this->edgeArr[i].getEdgeWeight() - min]--;
    }

    //store the result in the original array
    for (int i = 0; i < this->edgeArr.size(); i++)
        this->edgeArr[i] = output[i];
}


void Graph::findMSTWithKruskalUndirected(int& answerWeight, vector<Edge>& answer){
    int rootI, rootJ;
    for (int i = 0; i < this->numEdges; i++){
        rootI = this->findSet(this->edgeArr[i].getStartVertex());
        rootJ = this->findSet(this->edgeArr[i].getEndVertex());
        // cout << rootI << " " << rootJ << endl;
        if (rootI != rootJ){
            this->unionSetbyRank(rootI, rootJ);
        }
        else{
            answer.push_back(this->edgeArr[i]);
            answerWeight+= this->edgeArr[i].getEdgeWeight();
        }
    }
}

void Graph::findMSTWithKruskalDirected(){
    int rootI, rootJ;
    for (int i = 0; i < this->numEdges; i++){
        rootI = this->findSet(this->edgeArr[i].getStartVertex());
        rootJ = this->findSet(this->edgeArr[i].getEndVertex());
        // cout << rootI << " " << rootJ << endl;
        if (rootI != rootJ){
            this->unionSetbyRank(rootI, rootJ);
            this->adjList[this->edgeArr[i].getStartVertex()].push_back(this->edgeArr[i].getEndVertex());
        }
        else{
            this->notCollectedEdges.push_back(this->edgeArr[i]);
        }
    }
}

void Graph::reinitializeGraph(){
    for (int i = 0; i < this->vertexArr.size(); i++){
        this->vertexArr[i].setColor('W');
        this->vertexArr[i].setParent(-1000);
    }
}

//DFS_Visit function in CLRS book
void Graph::DFS_Visit(int startVertex, bool& hasCycle){
    this->vertexArr[startVertex].setColor('G');
    int neighborVertexIdx;
    Vertex neighborVertex;
    for (int i = 0; i < this->adjList[startVertex].size(); i++){
        neighborVertexIdx = this->adjList[startVertex][i];
        neighborVertex = this->vertexArr[neighborVertexIdx];
        if (neighborVertex.getColor() == 'W'){
            neighborVertex.setParent(startVertex);
            this->DFS_Visit(neighborVertexIdx, hasCycle);
        }
        else if (neighborVertex.getColor() == 'G'){
            hasCycle = true;
        }
    }
    this->vertexArr[startVertex].setColor('B');
}

void Graph::breakCycleInDirectedGraph(int& answerWeight, vector<Edge>& answer){
    bool hasCycle;
    //iterate through each edge that is not collected by Kruskal algorithm
    for (int i = 0; i < this->notCollectedEdges.size(); i++){
        hasCycle = false;
        this->reinitializeGraph();
        // Push uncollected edge into graph
        this->adjList[this->notCollectedEdges[i].getStartVertex()].push_back(this->notCollectedEdges[i].getEndVertex());
        this->DFS_Visit(this->notCollectedEdges[i].getStartVertex(), hasCycle);
        // cout << hasCycle << endl;
        if (hasCycle == true || this->notCollectedEdges[i].getEdgeWeight() < 0){
            answerWeight += this->notCollectedEdges[i].getEdgeWeight();
            answer.push_back(this->notCollectedEdges[i]);
            this->adjList[this->notCollectedEdges[i].getStartVertex()].pop_back();
        }
    }
}
 
void Graph::printGraph(){
    for (int i = 0; i < this->numEdges; i++){
        this->edgeArr[i].printEdge();
        cout << endl; 
    }
}

void Graph::printAdjList(){
    for (int i = 0; i < numVertices; i++){
        cout << "Vertex " << i << ", Adjacency vertices: ";
        for (int j = 0; j < this->adjList[i].size(); j++){
            cout << this->adjList[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::printNotCollectedEdges(){
    cout << "Not collected Edges" << endl;
    for (int i = 0 ; i < this-> notCollectedEdges.size(); i++){
        this->notCollectedEdges[i].printEdge();
        cout << endl;
    }
}