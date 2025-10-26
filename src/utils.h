#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <unordered_map>



std::ifstream connect_instream_to_file(const std::string &);

// Convert all characters in the input string to lowercase.   
std::string string_to_lower(std::string);

void token_statistics(std::unordered_map<std::string, int> &);
