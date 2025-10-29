#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../include/utils.h"

std::regex create_regex_pattern();

int tokenize_string(
    std::string, 
    std::unordered_map<std::string,int> &, 
    int
);

std::string get_regex_matches(
    std::string &,
    std::regex);

void sliding_window_tokenizer(
    std::vector<std::string> &,
    std::unordered_map<std::string, int> &, 
    unsigned
);


void regex_tokenizer(
    std::vector<std::string> &,
    std::unordered_map<std::string, int> &,
    unsigned k
);

void text_tokenizer(
    std::vector<std::string> &,
    std::unordered_map<std::string, int> &, 
    unsigned
    // unsigned
);

#endif // TOKENIZER_H
