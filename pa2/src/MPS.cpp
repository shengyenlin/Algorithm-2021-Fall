#include <vector>
#include <fstream>
#include <algorithm>
#include "MPS.h"

using namespace std;

void MpsSolver::buildInformation(fstream& fin){
    chords.assign(num, 0);
    M.assign(num, vector<int>(num));
    int num1, num2;
    for (int i = 0; i < num/2; i++){
        fin >> num1 >> num2;
        chords[num1] = num2;
        chords[num2] = num1;
    }
}

void MpsSolver::findSolutions(int i, int j){
    if (j > i && M[i][j] > 0){
		if(M[i][j]>M[i][j-1] && chords[j]>=i){
			answer.push_back(j);
			findSolutions(i, chords[j]-1);
			findSolutions(chords[j]+1, j-1);
		}
		else{
			findSolutions(i, j - 1);
		}
	}
}

int MpsSolver::solveMpsTopDown(int i, int j){
    //base case
    if (i >= j){
        return 0;
    }
    //memoization
    if(M[i][j]!=0){
        return M[i][j];
    }
    
    int endPoint = max(j, chords[j]); //start point of a chord
    int startPoint = min(j, chords[j]); //end point of a chord
    if (endPoint == j){
        //CaseI: k is outside (i, j)
        if (startPoint < i){
            M[i][j] = solveMpsTopDown(i, j-1);
            return M[i][j];
        }
        //CaseII: k is i (i.e. kj == ij)
        else if (startPoint == i){
            M[i][j] = solveMpsTopDown(i+1, j-1) + 1;
            return M[i][j];
        }
        //CaseIII: k is inside (i, j)
        else{
            int leftSubSetChords = solveMpsTopDown(i, startPoint - 1);
            int rightSubSetChords = solveMpsTopDown(startPoint + 1, j - 1);
            int reducedSubSetChords = solveMpsTopDown(i, j-1);
            M[i][j] = max(reducedSubSetChords, leftSubSetChords + rightSubSetChords + 1);
            return M[i][j];
        }
    }
    else{
        M[i][j] = solveMpsTopDown(i, j-1);
        return M[i][j];
    }
}

void MpsSolver::writeSolution(fstream& fout){
    sort(this->answer.begin(), this->answer.end());
    fout << this->M[0][this->num-1] << endl;
    for (int i = 0; i < this->answer.size(); i++){
        fout << this->answer[i] << " " << this->chords[this->answer[i]] << endl;
    }    
}