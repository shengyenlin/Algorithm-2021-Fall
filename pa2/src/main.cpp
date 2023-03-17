#include <iostream>
#include <fstream>
#include "../lib/tm_usage.h"
#include "MPS.h"

using namespace std;

int main(int argc, char* argv[]){

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    fstream fin(argv[1]);

    int num;
    fin >> num;
    
    //read input
    MpsSolver solver(num);
    solver.buildInformation(fin);
    fin.close();

    //start solving MPS
    solver.solveMpsTopDown(0, num - 1);
    solver.findSolutions(0, num - 1);

    //write output
    fstream fout;
    fout.open(argv[2],ios::out); 
    solver.writeSolution(fout);
    fout.close();

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    return 0;
}