#ifndef _MPS_H
#define _MPS_H
#include <vector>
#include <fstream>

using namespace std; 

class MpsSolver{
    private:
        int num;
        vector<int> chords; //store chords position information
        vector< vector<int> > M;
        vector<int> answer;
    public:
        //constrcutor
        MpsSolver(int num): num(num){};
        void buildInformation(fstream&);
        int solveMpsTopDown(int, int);
        void findSolutions(int, int);
        void writeSolution(fstream&);
};

#endif