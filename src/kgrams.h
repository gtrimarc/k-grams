#ifndef KGRAMS_H
#define KGRAMS_H

#include "utils.h"
#include "tokenizer.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>


// Class representing transition probabilities for k-grams 
// of up to length k. 
class kgram_set {
    private:
        int k_;
        std::vector<std::unordered_map<std::string, int>> kgram_vocabulary_;

        // Helper functions
        float transition_probability(std::string , char );
        std::vector<float> next_char_probabilities(std::string);
        char sample_next_char_probabilities(std::vector<float>);

    public:
        // kgram(int, std::unordered_map<std::string, int>,
        //     std::unordered_map<std::string, int>);

        kgram_set(int);
        int get_k();

        char predict(std::string);
        void fit(std::string);
        ~kgram_set();
};

#endif