#include "utils.h"


int scan_buffer_string(std::string str, 
    std::unordered_map<std::string, int> &dictk, int k)
{
    // Extract tokens from word.
    int i = 0;
    std::string substr = "";
    int strsz = str.size();

    // std::cout << str.size() << " " << k << " " << wdsz - k << std::endl;
    while (i < strsz - k)
    {
        substr = str.substr(i, k);
        if (dictk.count(substr) != 0)
        {
            dictk[substr] += 1;
        } else {
            dictk[substr] = 1;
        }
        i++;
    }

    return i;
}


std::vector<std::string> process_text(std::ifstream &infstream)
{
    std::vector<std::string> text_lines;

    std::string line;
    
    while (std::getline(infstream, line))
    {
        if (line != "")
        {   
            std::string lower_case_line = string_to_lower(line);
            lower_case_line += " ";
            text_lines.push_back(lower_case_line);
        }
    }
    return text_lines;
}


void process_line_sequence(
    std::vector<std::string> text_lines,
    std::unordered_map<std::string, int> &dictk, unsigned k){
        int cursor = 0;
        std::string buffer_string = text_lines.at(0);
        for (unsigned i=1; i < text_lines.size(); i++){
            // std::cout << "> " << text_lines.at(i) << std::endl;
            cursor = scan_buffer_string(buffer_string, dictk, k);
            buffer_string = buffer_string.substr(cursor,k-1) + text_lines.at(i);
        }
    }


void predict(std::string s, 
    std::unordered_map<std::string, int> & kgrams,
    std::unordered_map<std::string, int> & prefixes){
    char letters[26] = {'a', 'b', 'c', 'd', 
                        'e', 'f', 'g', 'h', 'i', 'j', 
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 
        't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int V =  prefixes.size();
    for(char c : letters){
        std::cout << s+c << " " << (kgrams[s+c]+1.)/(prefixes[s]+V) << std::endl;
    };
    // return (kgrams[s]+1.)/(prefixes[s]+V);
}



// int main(int argc, char *argv[])
// {
//     if (argc > 1)
//     {

//         std::vector<std::string> lines;
               
//         std::string fname = argv[1];
//         std::ifstream instream = connect_instream_to_file(fname);

//         lines = process_text(instream);

//         int k;
//         std::string arg2 = argv[2];
//         k = stoi(arg2);

//         std::unordered_map<std::string, int> kgram_vocabulary;
//         std::unordered_map<std::string, int> prefix_vocabulary;

//         process_line_sequence(lines, kgram_vocabulary, k);
//         process_line_sequence(lines, prefix_vocabulary, k-1);

//         std::string kgram = "he v";

//         // std::cout << prefix_vocabulary["book"] << std::endl;
//         predict(kgram, kgram_vocabulary, prefix_vocabulary);

//     }
//     return 0;
// }