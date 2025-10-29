#include "../include/tokenizer.h"

// Create the regular expression pattern used to match 
// whole words in the corpus text provided by the user
std::regex create_regex_pattern(){

    // Pattern that matches whole words, including hypheneated words
    std::regex pattern("\\w+(?:-\\w+)*", std::regex::icase);
    
    return pattern;
}

// tokenizes an input string and accumulates in dictk the 
// counts of the unique k-grams of length k
int tokenize_string(
    std::string str,
    std::unordered_map<std::string, int> &dictk,
    int k)
{
    // Extract tokens from word.
    int cursor = 0;
    std::string substr = "";
    int strsz = str.size();

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

    }
    return cursor;
}

// Extract the substrings that match the regular 
// expression rgx in the input string
std::string get_regex_matches(
    std::string &str,
    std::regex rgx)
{
    std::string word_sequence="";

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
    std::unordered_map<std::string, int> &dictk, // Dictionary that accumulates the kgram counts
    unsigned k                                   // kgram length
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
    }

    // tokenize the word_sequence string and accumulate in dictk
    // the counts of the unique tokens
    tokenize_string(word_sequence, dictk, k); // tokenize each word in the sequence
};


// Tokenize the corpus text stored in a vector of lines.
void text_tokenizer(
    std::vector<std::string> &text_lines,         // Input: vector of (non-empty lines in the text)
    std::unordered_map<std::string, int> &dictk, // On return: dictionary of token counts
    unsigned k                                  // Token length
)
{
    regex_tokenizer(text_lines, dictk, k);
}
