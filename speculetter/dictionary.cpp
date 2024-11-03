//
//  dictionary.cpp
//  speculetter
//
//  Created by Anuj Ketkar on 11/2/24.
//

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

string sortAndRemoveDuplicates(string word){
    std::stringstream stream;
    std::sort(word.begin(), word.end());
    
    stream << word[0];
    for(int i = 1; i < word.size(); ++i){
        if(word[i] != word[i-1]){
            stream << word[i];
        }
    }
    return stream.str();
}

int main(){
    set<string> wordSet;
    unordered_map<string, vector<string> > wordMap;
    
    ifstream file("dictionary.txt");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    
    string word;
    while (getline(file, word)) {
        wordSet.insert(word);
        string key = sortAndRemoveDuplicates(word);
        if(wordMap.find(key) != wordMap.end() ){
            vector<string> list;
            wordMap[key] = list;
        }
        wordMap[key].push_back(word);
    }
    file.close();
    
    while(true){
        cout << "Letters: ";
        string input;
        cin >> input;
        
        if(wordSet.find(input) != wordSet.end() ){
            cout << "Word exists" << endl;
        }
        
        input = sortAndRemoveDuplicates(input);
        vector<string> words = wordMap[input];
        for(int i = 0; i < words.size(); ++i){
            cout << words[i] << endl;
        }
        
    }
    
    return 0;
}
