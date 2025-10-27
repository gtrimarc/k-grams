#include "kgrams.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>

char LETTERS[27] =
    {'a', 'b', 'c', 'd',
     'e', 'f', 'g', 'h',
     'i', 'j', 'k', 'l',
     'm', 'n', 'o', 'p',
     'q', 'r', 's', 't',
     'u', 'v', 'w', 'x',
     'y', 'z', ' ' 
    //  ',',
    //  '.', '\'', ';'
    };

const unsigned V = 27;

// Construrctor
kgram::kgram(int k) : k_{k} {
    std::random_device rd;                           // Seed source
    std::mt19937 gen(rd());                          // Mersenne Twister engine
    std::uniform_real_distribution<> dist(0.0, 1.0); // Range [0, 1)
};

// Destructor
kgram::~kgram() {};

float kgram::prob_mass_func(std::string s, char c){
    int s_length = s.size();
    return (kgram_vocabulary_[s_length+1][s + c] + 1.) / (kgram_vocabulary_[s_length][s] + V);
};


std::vector<float> kgram::next_char_probabilities(std::string s){
    std::vector<float> prob;
    float cdf = 0.;
    for (char c : LETTERS)
    {
        cdf += kgram::prob_mass_func(s, c);
        std::cout << "D: " << s + c << " " << cdf << std::endl;
        prob.push_back(cdf);
    };
    return prob;
}

char kgram::sample_next_char_probabilities(std::vector<float> prob){
    
    std::random_device rd;                           // Seed source
    std::mt19937 gen(rd());                          // Mersenne Twister engine
    std::uniform_real_distribution<> dist(0.0, 1.0); // Range [0, 1)

    double random_value = dist(gen);
    std::cout << random_value << '\n';
    unsigned index = 0;
    while (prob.at(index) < random_value && index < V-1)
    {
        index++;
    }

    // auto max_c = std::max_element(prob.begin(),prob.end());
    // int index = std::distance(prob.begin(), max_c);
    // std::cout << prob[index] << " " << LETTERS[index] << " " << *max_c << " " <<"\n";
    return LETTERS[index];
};


char kgram::predict(std::string s)
{
    std::vector<float> prob = kgram::next_char_probabilities(s);
    // std::sort(prob)

    // auto max_c = std::max_element(prob.begin(),prob.end());
    // int index = std::distance(prob.begin(), max_c);
    // std::cout << prob[index] << " " << LETTERS[index] << " " << *max_c << " " <<"\n";
    return kgram::sample_next_char_probabilities(prob);
};

void kgram::fit(std::string fname)
{
    std::vector<std::string> lines;

    std::ifstream instream = connect_instream_to_file(fname);

    lines = get_sequence_of_lines(instream);
    
    // Insert empty string kgram
    // int k = 0;
    std::unordered_map<std::string, int> kgram;
    kgram[""]=0;
    kgram_vocabulary_.push_back(kgram);

    // Create the kgram vocabularies for strings 
    // of up to k_ characters
    int k = 1;
    while(k <= k_){
        std::unordered_map<std::string, int> kgram;
        text_tokenizer(lines, kgram, k, 1);
        kgram_vocabulary_.push_back(kgram);
        k++;
    }
};
