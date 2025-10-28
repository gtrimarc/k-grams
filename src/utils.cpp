#include "utils.h"

std::ifstream connect_instream_to_file(const std::string &fname)
{
    std::ifstream in_file;
    in_file.open(fname);
    if (!in_file)
    {
        std::cerr << "Unable to open inFile";
        exit(1);
    }
    return in_file;
}

// Convert all characters in the input string to lowercase.   
std::string string_to_lower(std::string str) {

    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // std::string::iterator c= lower.begin();
    for(auto c = str.begin(); c != str.end(); ++c){
        *c = std::tolower(*c);
    }
    return str; 
}


std::vector<std::string> get_sequence_of_lines(std::ifstream &infstream)
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



// void token_statistics(std::unordered_map<std::string, int> &dictk)
// {
//     // Create the vector `items` containing the key-value pairs
//     std::vector<std::pair<std::string, int>> items(dictk.begin(), dictk.end());
//     // Sort the vector `items`
//     std::sort(items.begin(), items.end(),
//           [](const auto& a, const auto& b) {
//               return a.second > b.second;
//           });
//     // for (const auto& [key, value] : items) {
//     //     std::cout << key << ": " << value << '\n';
//     // }
//     auto item = items.begin();
//     unsigned token_index = 1;
//     while(item != items.end()){
//         if(token_index <= 20){
//              std::cout << item->first << "  " << item->second << '\n';
//         }
//         token_index++;
//         item++;
//     }
// }
