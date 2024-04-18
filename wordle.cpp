#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(size_t n, std::string& floating, std::string& word, size_t loc, std::set<std::string>& combos, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> combos;
    std::string floating_temp = floating;
    std::string in_temp = in;
    wordle_helper(in.length(), floating_temp, in_temp, 0, combos, dict);
    return combos;
}

// Define any helper functions here
void wordle_helper(size_t n, std::string& floating, std::string& word, size_t loc, std::set<std::string>& combos, const std::set<std::string>& dict) {
    if (floating.length() == 0) {
        while (word[loc] != '-' && loc < word.length()) {
            loc++;
        }
        if (loc == n) {
            if (dict.find(word) != dict.end()) { //if found in dictionary
                combos.insert(word);
            }
            return;
        }
        if (word[loc] == '-') {
            for (char c = 'a'; c <= 'z'; c++) {
                    word[loc] = c;
                    wordle_helper(n, floating, word, loc+1, combos, dict);
                    word[loc] = '-';
            }
            return;
        }
    }
    
    else {
        if (floating.length() > 0) {
            std::string floating_temp = floating.substr(1, floating.length());
            for (size_t i = 0; i < word.length(); i++) {
                if (word[i] == '-') {
                        word[i] = floating[0];
                        wordle_helper(n, floating_temp, word, 0, combos, dict);
                        word[i] = '-';
                }
            }
        } 
    }
    
}