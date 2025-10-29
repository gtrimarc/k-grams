#include "../include/kgrams.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>


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

std::string SLETTERS[27]=    
    {"a", "b", "c", "d",
     "e", "f", "g", "h",
     "i", "j", "k", "l",
     "m", "n", "o", "p",
     "q", "r", "s", "t",
     "u", "v", "w", "x",
     "y", "z"
    //  ",",
    //  ".", "\"", ";"
    };


const unsigned V = 27;


// Initialize the random number generator
std::random_device rd;                           // Seed source
std::mt19937 gen(rd());                          // Mersenne Twister engine
std::uniform_real_distribution<> dist(0.0, 1.0); // Range [0, 1)



// Calculate the transition probability of character c given the string s.
float kgram_set::transition_probability(std::string s, char c){
    // The transition probability for the empty string is estimated
    // by the frequency of the unigrams in the corpus.
    int s_length = s.size();
    std::string ic({c});
    if(s_length == 0){
        // The transition probability for the empty string is estimated
        // by the frequency of the unigrams in the corpus.
        float sum = 0.;
        for (std::string ic : SLETTERS){
            sum += kgram_vocabulary_[1][ic];
        }
        std::string ic({c});
        return kgram_vocabulary_[1][ic]/sum;
    } else {
        // Transition probabilty for character c given the prefix s calculated
        // applying Laplace smoothing.
        return (kgram_vocabulary_[s_length+1][s + ic] + 1.) / (kgram_vocabulary_[s_length][s] + V);
    }
};

std::vector<float> kgram_set::next_char_probabilities(std::string s){
    
    std::vector<float> prob;
    float cdf = 0.; // cumulative distribution function
    for (char c : LETTERS)
    {
        cdf += kgram_set::transition_probability(s, c);
        prob.push_back(cdf);
    };
    return prob;
}

char kgram_set::sample_next_char_probabilities(std::vector<float> prob){

    double random_value = dist(gen);
    // std::cout << random_value << '\n';
    unsigned index = 0;
    while (prob.at(index) < random_value && index < V-1)
    {
        index++;
    }

    return LETTERS[index];
};


// Construrctor
kgram_set::kgram_set(int k) : k_{k} {};

// Destructor
kgram_set::~kgram_set() {};

int kgram_set::get_k() {return k_;};

// Train a kgrams model on the text corpus in the input file 
void kgram_set::fit(std::string fname)
{
    // Create an input file stream connected to file fname
    std::ifstream instream = connect_instream_to_file(fname);

    // Read the lines in the input file in to a string vector 
    std::vector<std::string> lines;
    lines = get_sequence_of_lines(instream);

    // Create the kgram vocabularies for strings 
    // of length comprised between 1 and k_ characters
    int k = 1;
    while(k <= k_){

        std::unordered_map<std::string, int> kgram;        
        text_tokenizer(lines, kgram, k);
        kgram_vocabulary_[k] = kgram;
        
        k++;
    }
};

// Predict the next character given the input kgram
char kgram_set::predict(std::string in_str)
{
    std::vector<float> prob = kgram_set::next_char_probabilities(in_str);
    
    return kgram_set::sample_next_char_probabilities(prob);
};

