#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <regex>

std::ifstream connect_instream_to_file(const std::string &);

// Convert all characters in the input string to lowercase.   
std::string string_to_lower(std::string);


void token_statistics(std::unordered_map<std::string, int> &);

std::regex create_regex_pattern();

std::vector<std::string> get_sequence_of_lines(std::ifstream &);