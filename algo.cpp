#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <cmath>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

//getrand later will be cross validation?
float getRand() {
    return rand() % 100 +1;

}


void printSet(const set<int>& set) {
    //googled set iterator
    for (auto iterator = set.begin(); iterator != set.end(); iterator++) {
        auto copy = iterator;
        cout << *iterator;
        if ( ++copy != set.end()) {
            cout << ", ";
        }
    }
    
}


float getDefaultRate(int classNumber, const vector<vector<float>>& data) {

    int actual = 0;
    int total = data.size();

    for (const vector<float>& row : data) {
        actual = classNumber == static_cast<int>(row.at(0)) ? actual+1 : actual;
    }

    return actual / static_cast<float>(total);
}


//duplicateChecker to check if feature has already been added already, since we consider adding if not already added only
bool duplicateChecker(set<int> features, int val){
    set<int>::iterator it;
    it = features.begin();
    //set iterator referenced geeks for geeks
    for (it; it != features.end(); it++){
        if (*it == val){
            return false;
        }
    }
    return true;
    
}

double Euclidian_Dist(const vector<float> r1, const vector<float> r2, vector<float> data){
    double distance = 0.0;
    for (int i = 0; i < data.size(); i ++){
        distance += pow(r1.at(i) - r2.at(i), 2);
    }
    return sqrt(distance);
}

float nearest_neighbor(const vector<vector<float>>& data, const set<int>& currSet){
  
  int number_correctly_classified = 0;
 
//   double label_object_to_classify = data.at(i).at(0);
  float dist = 0.0; 
  int nearest_neighbor_label = -1;
  float accuracy = 0.0;
  for (int i = 0; i < data.size(); i++){
      float nearest_neighbor_distance = INT_MAX;
      float nearest_neighbor_location = INT_MAX;
      int object_to_classify = static_cast<int>(data.at(i).at(0));
      
      for (int k = 0; k < data.size(); k++){
          if (k != i){
              const vector<float>& one = data.at(i);
              const vector<float>& two = data.at(k);
              
              
              dist = Euclidian_Dist(one, two, data.at(0));
           // don't compare to self
            if (dist < nearest_neighbor_distance){
                nearest_neighbor_distance =  dist;
                nearest_neighbor_location = k;
                nearest_neighbor_label = static_cast<int>(data.at(k).at(0)); //nearestneighbor location first column
            }
          }
      }
    if (object_to_classify == nearest_neighbor_label){
        number_correctly_classified++;
    }
  } 
  accuracy = number_correctly_classified/static_cast<float>(data.size());

  return accuracy;
};

//NOTE: followed the matlab pseudocode provided in discussion slides!
void forward_selection(vector<vector<float>> inputdata){
    
    cout << "Beginning Search" << endl;
    set<int> current_set_of_features;
    set<int> best;
    float defaultRate = max(getDefaultRate(1,inputdata), getDefaultRate(2,inputdata));
    float bestAccuracy = defaultRate;
    
    //traversing the levels of the tree
    for (int i = 1; i < inputdata.at(0).size() + 1; i++){
        
        cout << "Currently on the " << i << "th level of the search tree" << endl;
        int feature_to_add_at_this_level = 0;
        float best_so_far_accuracy = 0;


        for (int k = 1; k < inputdata.at(0).size() + 1 ; k++){
            //only add IF it is not already added
            if (duplicateChecker(current_set_of_features, k)){
                float accuracy = nearest_neighbor(inputdata, current_set_of_features);
                // cout << "Consider adding the " << k << " feature, accuracy is " << accuracy << endl;
                //need to get highest accuracy and update 
                if (accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }

                set<int> holder = current_set_of_features;
                holder.insert(k);
                printSet(holder);
                cout << " was best with accuracy of " << accuracy << " %" << endl;
                
            }
        
        }

        //adding highest accuracy to current_set_of_features
        current_set_of_features.insert(feature_to_add_at_this_level);
        // cout << "On Level " << i << " i added feature " << feature_to_add_at_this_level << " to current set "<< endl;
        if (best_so_far_accuracy > bestAccuracy){
            bestAccuracy = best_so_far_accuracy;
            printSet(current_set_of_features);
            best = current_set_of_features;
            cout << " was best, accuracy is " << best_so_far_accuracy << "%" << endl;
        }
        else{
            cout << "Warning, accuracy has decreased!!!!" << endl;
        }
    }
    cout << "Finished search and the best feature subset is {" ;
    //referenced geeks for geeks
    for (auto iterator = best.begin(); iterator != best.end(); iterator++) {
        auto copy = iterator;
        cout << *iterator;
        if ( ++copy != best.end() ) {
            cout << ", ";
        }
    }
    cout << "}" << endl;
    cout << "It had an accuracy of " << bestAccuracy << "%" << endl;
   
};
//NOTE: followed the matlab pseudocode provided in discussion slides!
//this is the same thing but starting from other end. just had to switch for loops where to start and end.
void backward_elimination(vector<vector<float>> inputdata) {
     cout << "Beginning Elimination" << endl;
     set<int> current_set_of_features;
     
    set<int> best;
    vector<int> answer;
    for (int i = 1; i <= inputdata.at(0).size()-1; ++i) {
        current_set_of_features.insert(i);
    }
    float defaultRate = nearest_neighbor(inputdata, current_set_of_features );
    float bestAccuracy = defaultRate;
    //traversing the levels of the tree
    for (int i = inputdata.at(0).size(); i > 0; i--){
        
        cout << "Currently on the " << i << "th level of the search tree" << endl;
        int feature_to_elim_at_this_level;
        float best_so_far_accuracy = 0;
        float accuracy = 0;
        
        for (int k = inputdata.at(0).size(); k > 0 ; k--){
            //only add IF it is not already added
            if (duplicateChecker(current_set_of_features, k)){
                
                set<int> temp = current_set_of_features;
                temp.erase(k);
                
                accuracy = nearest_neighbor(inputdata, current_set_of_features);
                // cout << "Consider eliminating the " << k << " feature, that has accuracy " << accuracy << endl;
                //need to get highest accuracy and update
                if (accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_elim_at_this_level = k;
                }

                cout << "Using features: ";
                printSet(temp);
                cout << " was best with accuracy of " << accuracy << endl;
                // else{
                //     cout << "(Warning, Accuracy has decreased!)" << endl;
                // }
            }

        }
        if (current_set_of_features.size() > 1) {
            
            current_set_of_features.erase(feature_to_elim_at_this_level);
            cout << endl;

            if (best_so_far_accuracy > bestAccuracy) {
                bestAccuracy = best_so_far_accuracy;
                best = current_set_of_features;

                cout <<  "Feature set ";
                printSet(current_set_of_features);
                cout << " was best, accuracy is " << best_so_far_accuracy << "%" << endl;
            }
            else {
                cout << "Warning, accuracy has decreased!!!" << endl;
                cout <<  "Feature set ";
                printSet(current_set_of_features);
                cout << " was best, accuracy is " << best_so_far_accuracy  << "%" << endl;
            }
        }
        
     
    }
    cout << "Done with search, best feature subset is {";
     for (auto iterator = best.begin(); iterator != best.end(); iterator++) {
        auto copy = iterator;
        cout << *iterator;
        if ( ++copy != best.end() ) {
            cout << ", ";
        }
    }
    cout << "}" << endl;
    cout << "It had an accuracy of " << bestAccuracy << "%" << endl;

};





vector<vector<float>> getData(const string& fileName){
    vector<vector<float>> data;
    ifstream ifs(fileName);
    string currLine;
    if (!ifs.is_open()){

        cout << "Cannot open file: " << fileName <<endl;
        exit(0);

    }
    else {
        while (getline(ifs, currLine)){
            istringstream iss(currLine);
            vector<float> currRow;
            string s;
            while (iss >> s) {
                currRow.push_back(stof(s));
            }
            data.push_back(currRow);
        }
    }
 
      
    
    ifs.close();
    return data;
}

