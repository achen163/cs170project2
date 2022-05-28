#include <iostream>
#include <string>
#include <vector>

#include <time.h>
  
#include "algo.cpp"

using namespace std;

int main() {
    bool menu = true;
    
        string filename;
        int featureCount =0;
        int algorithmChoice = 0;
        cout<< "Hello, welcome to Alex Chen's Feature Selection Algorithm." << endl;
        cout << "Please enter the amount of features" << endl;
        cin >> featureCount;

        cout << "Type the file you want to test" << endl;
        cin >> filename;

        vector<vector<float>> inputdata;        
        inputdata = getData(filename);

        clock_t t;
        while (menu){
            cout << "Next, select the number of the algorithm you want to run:" << endl;
            cout << "1) Forward Selection" << endl;
            cout << "2) Backward Elimination" << endl;
            cin >> algorithmChoice;
            // cout << "Beginning Search";
            
            t = clock();
 
            if (algorithmChoice == 1){
                forward_selection(inputdata);
                break;
            }
            else if (algorithmChoice == 2){
                backward_elimination(inputdata);  
                break;   
            }
            else {
                cout << algorithmChoice << endl;
                cout << "Invalid Choice, restart menu" << endl;
            }
           
        }
        //time reference geeks for geeks how to measure time taken
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        cout << "It took a total of " << time_taken << " seconds to execute" << endl;
        return 0;
}