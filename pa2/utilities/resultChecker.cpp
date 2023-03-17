#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    fstream fin(argv[1]);
    int ansNum;
    fin >> ansNum;
    int beginOne, endOne, beginTwo, endTwo;
    fin >> beginOne >> endOne;
    beginOne = min(beginOne, endOne);
    endOne = max(beginOne, endOne);
    // cout << beginOne << " " << endOne << " ";
    for (int i = 0; i < ansNum - 1; i++){
        fin >> beginTwo >> endTwo;
        beginTwo = min(beginTwo, endTwo);
        endTwo = max(beginTwo, endTwo);
        // cout << beginTwo << " " << endTwo << endl;
        if (endOne > beginTwo && endTwo > endOne){
            cout << "Your answer is wrong" << endl;
            return 0;
        }
        else{
            beginOne = beginTwo;
            endOne = endTwo;
        }
        // cout << beginOne << " " << endOne << " ";
    }
    cout << "Right answer!" << endl;
    return 0;
}