#include <iostream>
#include <fstream>
#include "../lib/tm_usage.h"
#include "CycleBreaker.h"

using namespace std;

int main(int argc, char* argv[]){

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    if(argc != 3) {
       help_message();
       return 0;
    }

    char graphType;
    int numVertices, numEdges;
    fstream fin(argv[1]);

    //Read input
    fin >> graphType;
    fin >> numVertices >> numEdges;

    vector<Vertex> vertexArr;
    vector<Edge> edgeArr;

    //initialize edge
    int start, end, weight;
    int sumEdgeWeight;
    for (int i = 0; i < numEdges; i++){
        fin >> start >> end >> weight;
        sumEdgeWeight += weight;
        edgeArr.push_back(
            Edge(start, end, weight)
        );
    }

    //initialize vertex
    for (int i = 0; i < numVertices; i++){
        //set rank = 0, color = white
        vertexArr.push_back(Vertex(i, 0, 'W'));
    }
    fin.close();
    //Algorithm start
    Graph graph(vertexArr, edgeArr, numVertices, numEdges, graphType);
    vector<Edge> answer;
    int answerWeight = 0;
    switch (graphType){
    case 'u':      
        //sort weighted undirected graph
        if (sumEdgeWeight != numEdges){
            graph.doCountingSortOnEdge();
        }
        //graph.printGraph();
        graph.findMSTWithKruskalUndirected(answerWeight, answer);
        break;
    //directed graph
    case 'd':
        vector<Edge> notCollectedEdges;
        graph.doCountingSortOnEdge();
        graph.findMSTWithKruskalDirected();
        // graph.printAdjList();
        // graph.printNotCollectedEdges();
        graph.breakCycleInDirectedGraph(answerWeight, answer);
        break;
    }

    //write output
    fstream fout;
    fout.open(argv[2],ios::out);
    if (answer.size() == 0){
        fout << "0" << endl;
    }
    else{
        fout << answerWeight << endl;
        for (int i = 0; i < answer.size(); i++){
            fout << answer[i].getStartVertex() << " " << answer[i].getEndVertex()
            << " " << answer[i].getEdgeWeight() << endl;
        }
    }   
    fout.close();
    
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    return 0;
}