#include "../include/tokenizer.h"

// Create the regular expression pattern used to match 
// whole words in the corpus text provided by the user
std::regex create_regex_pattern(){

    // Pattern that matches whole words, including hypheneated words
    std::regex pattern("\\w+(?:-\\w+)*", std::regex::icase);
    
    return pattern;
}

// Tokenize the input string str. The unordered map dictk passed
// by reference accumulates the counts of the unique substrings
// of length k within the corpus text.
int tokenize_string(
    std::string str,
    std::unordered_map<std::string, int> &dictk,
    int k)
{
    // Extract tokens from word.
    int cursor = 0;
    std::string substr = "";
    int strsz = str.size();

    // std::cout << str.size() << " " << k << " " << strsz - k << std::endl;
    while (cursor < strsz - k)
    {
        substr = str.substr(cursor, k);
        if (dictk.count(substr) != 0)
        {
            dictk[substr] += 1;
        }
        else
        {
            dictk[substr] = 1;
        }
        cursor++;
        // if(k==3){
        //       std::cout << "Puppa: " << substr << " " << dictk[substr] << std::endl;
        // }

    }
    return cursor;
}

std::string get_regex_matches(
    std::string &str,
    std::regex rgx)
{
    std::string word_sequence="";

    // extract the substrings in str that match rgx
    auto words_begin =
        std::sregex_iterator(str.begin(), str.end(), rgx);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        std::string match_str = match.str();

        // add space as end of a word
        match_str = match_str + " ";

        word_sequence += match_str;
    }

    return word_sequence;
}


void regex_tokenizer(
    std::vector<std::string> & text_lines,       // Input: vector of (non-empty) lines in the text
    std::unordered_map<std::string, int> &dictk, // Dictionary that accumulates the token counts
    unsigned k                                   // Token length
)
{
    std::regex rgx = create_regex_pattern();

    // The substrings that match the regex pattern 
    // are accumuated in this string
    std::string word_sequence = "";

    // Iterate through the bector of lines and add
    // the words matched in each line to the word_sequence string
    for(unsigned i = 0; i < text_lines.size(); i++)
    {
        // Append to the word_sequence string a string of words that match
        // the regex pattern in the current text line.  
        word_sequence += get_regex_matches(text_lines.at(i), rgx);
        // for (auto w : word_sequence)
        // {
        //     // std::cout << w << "\n";
        // }
    }

    // tokenize the word_sequence string and accumulate in dictk
    // the counts of the unique tokens
    tokenize_string(word_sequence, dictk, k); // tokenize each word in the sequence
};


// Tokenize the corpus text stored as a vector of lines.
void text_tokenizer(
    std::vector<std::string> &text_lines,         // Input: vector of (non-empty lines in the text)
    std::unordered_map<std::string, int> &dictk, // On return: dictionary of token counts
    unsigned k                                  // Token length
)
{
    regex_tokenizer(text_lines, dictk, k);
}



// void sliding_window_tokenizer(
//     std::vector<std::string> & text_lines,         // Input: vector of (non-empty lines in the text)
//     std::unordered_map<std::string, int> &dictk, // On return: dictionary of token counts
//     unsigned k                                   // Token length
// )
// {
//     int cursor = 0;
//     std::string buffer_string = text_lines.at(0);
//     for (unsigned i = 1; i < text_lines.size(); i++)
//     {
//         // std::cout << buffer_string << "\n";
//         cursor = tokenize_string(buffer_string, dictk, k);
//         buffer_string = buffer_string.substr(cursor, k - 1) + text_lines.at(i);
//     }
// };



// // Tokenize a vector of lines. Two approaches to tokenization are available:
// // i) sliding window, ii) regex matching.
// void text_tokenizer(
//     std::vector<std::string> &text_lines,         // Input: vector of (non-empty lines in the text)
//     std::unordered_map<std::string, int> &dictk, // On return: dictionary of token counts
//     unsigned k,                                  // Token length
//     unsigned tokenizer                           //
// )
// {
//     if (tokenizer == 0)
//     {
//         sliding_window_tokenizer(text_lines, dictk, k);
//     }
//     else
//     {
//         regex_tokenizer(text_lines, dictk, k);
//     }
// }
