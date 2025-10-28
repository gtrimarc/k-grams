#include "char_seq.h"


// Helper method: transform a list of characters to a string
std::string CharSeq::string_from_seq(std::list<char> seq)
{
    char c;
    std::string str = "";

    auto p = seq.begin();
    while (p != seq.end())
    {
        c = *p;
        str.push_back(c);
        p++;
    }

    std::cout << "debug: " << str << "\n";

    return str;
};


// Construct a character sequence object from a string
CharSeq::CharSeq(std::string str)
{
    char c;
    for (unsigned i = 0; i < str.size(); i++)
    {
        c = str[i];
        cseq_.push_back(c);
    };
};


// Construct an empty character sequence object
CharSeq::CharSeq(){};


// Add one character to back of the character sequence. 
CharSeq CharSeq::add(char c)
{
    cseq_.push_back(c);
    return *this;
};


// Transform the character sequence to a string
std::string CharSeq::to_string()
{
    return string_from_seq(cseq_);
};


// Get a string with the last k characters in a character sequence.
// If the sequence contains at most k characters, return a string
// containing the full sequence.
std::string CharSeq::get_tail_substring(unsigned k)
{
    if(cseq_.size() <= k){
        return string_from_seq(cseq_);
    } else {
        char c;
        std::list<char> sub_seq;

        auto p = cseq_.end();
        unsigned str_len = 0;
        while (p != cseq_.begin() && str_len < k)
        {
            p--;
            c = *p;
            sub_seq.push_front(c);
            str_len++;
        }
        return string_from_seq(sub_seq);
    }
};


// Generate a completion of the requested length with the input 
// kgram set and return a string with the new character sequence.
void CharSeq::generate_completion(kgram_set model, int completion_length){
    int k = model.get_k();
    int ic = 0;
    while(ic < completion_length){
        std::string str = get_tail_substring(k);
        std::cout << "Debug: " << str << "\n";
        
        char c = model.predict(str);

        cseq_.push_back(c);

        ic++;
    };
};