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

using namespace std;

string sortAndRemoveDuplicates(string word){
    string key = "";
    std::sort(word.begin(), word.end());
    for(int i = 1; i < word.size(); ++i){
        if(word[i] != word[i-1]){
            key += word[i];
        }
    }
    return key;
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
        input = sortAndRemoveDuplicates(input);
        if(wordSet.find(input) != wordSet.end() ){
            cout << "Word exists" << endl;
        }
        vector<string> words = wordMap[input];
        for(int i = 0; i < words.size(); ++i){
            cout << words[i] << endl;
        }
        
    }
    
    return 0;
}
