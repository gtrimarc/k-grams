#include <iostream>
#include <list>
#include <string>

class CharSeq
{
private:
    std::list<char> cseq_;

public:
    CharSeq(std::string str);

    CharSeq add(char c);

    CharSeq slide(char c);

    std::string get_string();
};