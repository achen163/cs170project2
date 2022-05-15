#include <iostream>
#include <string>
#include <vector>
#include "algo.cpp"

using namespace std;

int main() {
    bool menu = true;
    
        
        int featureCount =0;
        int algorithmChoice = 0;
        cout<< "Hello, welcome to Alex Chen's Feature Selection Algoithm." << endl;
        cout << "Please enter the amount of features" << endl;
        cin >> featureCount;
        while (menu){
            cout << "Next, select the number of the algorithm you want to run:" << endl;
            cout << "1) Forward Selection" << endl;
            cout << "2) Backward Elimination" << endl;
            cin >> algorithmChoice;
            if (algorithmChoice == 1){
                forward_selection(featureCount);
                break;
            }
            else if (algorithmChoice == 2){
                backward_elimination(featureCount);  
                break;   
            }
            else {
                cout << algorithmChoice << endl;
                cout << "Invalid Choice, restart menu" << endl;
            }


    }
}