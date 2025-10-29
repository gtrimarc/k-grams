#include "../include/char_seq.h"


// Transform a list of characters to a string
std::string CharSeq::string_from_seq(std::list<char> seq)
{
    char c;
    std::string str = "";

    // Instantiate an iterator over the sequence of characters
    auto p = seq.begin();
    while (p != seq.end())
    {
        c = *p;
        str.push_back(c);
        p++;
    }

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


// Add one character to the back of the character sequence. 
CharSeq CharSeq::add(char c)
{
    cseq_.push_back(c);
    return *this;
};


// Transform a character sequence to a string
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
        // Return the full sequence if it is at most
        // k character long.
        return string_from_seq(cseq_);
    } else {
        
        char c;
        std::list<char> sub_seq;

        // Traverse the sequence backward from the end
        // and push k characters iteratively to the front
        // of the list sub_seq.
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


// Modifies the character set generating a completion of the requested length 
// with the input kgram_set model.
void CharSeq::generate_completion(
    kgram_set model,   // Input kgram model
    int length         // Requested character length of the completion
)
{
    int k = model.get_k();
    
    // Modify the sequence by iteratively adding characters
    // generated with the kgram model.
    int ic = 0;
    while(ic < length){

        std::string str = get_tail_substring(k-1);
        char c = model.predict(str);
        cseq_.push_back(c);

        ic++;
    };
};