#include <vector>
#include <iostream>
#include <string>

using namespace std;

//getrand later will be cross validation?
float getRand() {
    return rand() % 100 +1;

}

//duplicateChecker to check if feature has already been added already, since we consider adding if not already added only
bool duplicateChecker(vector<int> features, int val){
    for (int i = 0; i < features.size(); i++){
        if (features.at(i) == val){
            return false;
        }
    }
    return true;
    
}
//NOTE: followed the matlab pseudocode provided in discussion slides!
void forward_selection(int featureCount){
    
    cout << "Beginning Search" << endl;
    vector<int> current_set_of_features;
    
    //traversing the levels of the tree
    for (int i = 1; i < featureCount + 1; i++){
        
        cout << "Currently on the " << i << "th level of the search tree" << endl;
        vector<int> feature_to_add_at_this_level;
        int best_so_far_accuracy = 0;

        for (int k = 1; k < featureCount + 1 ; k++){
            //only add IF it is not already added
            if (duplicateChecker(current_set_of_features, k)){
                int accuracy = getRand();
                cout << "Consider adding the " << k << " feature, accuracy is " << accuracy << endl;
                //need to get highest accuracy and update 
                if (accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level.push_back(k);
                }
                // else{
                //     cout << "(Warning, Accuracy has decreased!)" << endl;
                // }
            }
        }
        //adding highest accuracy to current_set_of_features
        current_set_of_features.push_back(feature_to_add_at_this_level.back());
        cout << "On Level " << i << " i added feature " << feature_to_add_at_this_level.back() << " to current set "<< endl;
    }
   

};
//NOTE: followed the matlab pseudocode provided in discussion slides!
//this is the same thing but starting from other end. just had to switch for loops where to start and end.
void backward_elimination(int featureCount) {
     cout << "Beginning Elimination" << endl;
    vector<int> current_set_of_features;
    
    //traversing the levels of the tree
    for (int i = featureCount; i > 0; i--){
        
        cout << "Currently on the " << i << "th level of the search tree" << endl;
        vector<int> feature_to_elim_at_this_level;
        int best_so_far_accuracy = 0;
        

        for (int k = featureCount; k > 0 ; k--){
            //only add IF it is not already added
            if (duplicateChecker(current_set_of_features, k)){
                int accuracy = getRand();
                cout << "Consider eliminating the " << k << " feature, that has accuracy " << accuracy << endl;
                //need to get highest accuracy and update
                if (accuracy > best_so_far_accuracy){
                    best_so_far_accuracy = accuracy;
                    feature_to_elim_at_this_level.push_back(k);
                }
                // else{
                //     cout << "(Warning, Accuracy has decreased!)" << endl;
                // }
            }

        }
        //adding highest accuracy to current_set_of_features
        current_set_of_features.push_back(feature_to_elim_at_this_level.back());
        cout << "On Level " << i << " I eliminated feature " << feature_to_elim_at_this_level.back() << " to current set "<< endl;
    }

};