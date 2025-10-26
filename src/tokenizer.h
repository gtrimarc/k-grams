#include "utils.h"


int scan_buffer_string(
    std::string, 
    std::unordered_map<std::string,int> &, 
    int);

std::vector<std::string> process_text(std::ifstream &);

void process_line_sequence(
    std::vector<std::string>, 
    std::unordered_map<std::string, int> &, 
    unsigned);


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