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
#include <cmath>

using namespace std;

class Dictionary {
private:
    set<string> wordSet;
    unordered_map<string, vector<string> > wordMap;
    
public:
    
    vector<string> powerset(string set) {
        unsigned int size = 1 << set.size();
        vector<string> result;
        
        for (size_t counter = 0; counter < size; counter++) {
            string subset;
            for (size_t j = 0; j < set.size(); j++) {
                if (counter & (1 << j)) {
                    subset += set[j];
                }
            }
            result.push_back(subset);
        }
        
        return result;
    }
    
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
    
    void read(){
        ifstream file("dictionary.txt");
        if (!file.is_open()) {
            cerr << "Error opening file" << endl;
            return;
        }
        
        string word;
        while (getline(file, word)) {
            wordSet.insert(word);
            string key = sortAndRemoveDuplicates(word);
            wordMap[key].push_back(word);
        }
        file.close();
    }
    
    void write(vector<string> data){
        for (string word : data) {
            wordSet.insert(word);
            string key = sortAndRemoveDuplicates(word);
            wordMap[key].push_back(word);
        }
    }
    
    vector<string> search(string s){
        vector<string> permutations = powerset(sortAndRemoveDuplicates(s));
        vector<string> allWords;
        
        for(string key : permutations){
            if(wordMap.find(key) != wordMap.end()){
                vector<string> words = wordMap[key];
                allWords.insert(allWords.end(), words.begin(), words.end());
            }
        }
        
        return allWords;
    }
    
    bool find(string s){
        return wordSet.find(s) != wordSet.end();
    }
    
};


int main(){
    Dictionary dict;
    dict.read();
    
    while(true){
        string input;
        cout << "Input:" << endl;
        cin >> input;
        
        vector<string> matches = dict.search(input);
        cout << matches.size() << endl;
        for(string m : matches){
            cout << m << endl;
        }
    }
    
}
