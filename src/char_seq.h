#include "kgrams.h"
#include <iostream>
#include <list>
#include <string>

class CharSeq
{
private:
    std::list<char> cseq_;
    // std::list<char> iniit_cseq_;

    std::string string_from_seq(std::list<char>);

public:
    CharSeq(std::string);
    CharSeq(); // empty seque

    CharSeq add(char);

    std::string to_string();

    void generate_completion(kgram_set, int);

    std::string get_tail_substring(unsigned);
};