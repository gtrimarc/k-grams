#include "char_seq.h"

CharSeq::CharSeq(std::string str)
{
    char c;
    for (unsigned i = 0; i < str.size(); i++)
    {
        c = str[i];
        cseq_.push_back(c);
    };
};

CharSeq CharSeq::add(char c)
{
    cseq_.push_back(c);
    return *this;
};

std::string CharSeq::get_string()
{
    char c;
    std::string str = "";

    auto p = cseq_.begin();
    while (p != cseq_.end())
    {
        c = *p;
        str.push_back(c);
        p++;
    }
    return str;
};

CharSeq CharSeq::slide(char c)
{
    cseq_.pop_front();
    cseq_.push_back(c);
    return *this;
};