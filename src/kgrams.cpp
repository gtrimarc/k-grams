#include "kgrams.h"


char LETTERS[26] = {'a', 'b', 'c', 'd', 
                        'e', 'f', 'g', 'h', 'i', 'j', 
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 
        't', 'u', 'v', 'w', 'x', 'y', 'z'};


kgram::kgram(int k): k_{k} {};

kgram::~kgram(){};

void kgram::predict(std::string s){
    int V = prefix_vocabulary_.size();
    for(char c : LETTERS){
        std::cout << "D: " << s+c << " " << (kgram_vocabulary_[s+c]+1.)/(prefix_vocabulary_[s]+V) << std::endl;
    };
};


void kgram::fit(std::string fname){

    std::vector<std::string> lines;
    
    std::ifstream instream = connect_instream_to_file(fname);
    
    lines = process_text(instream);
    process_line_sequence(lines, kgram_vocabulary_, k_);
    process_line_sequence(lines, prefix_vocabulary_, k_-1);
};

