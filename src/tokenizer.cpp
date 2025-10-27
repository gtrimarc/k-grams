#include "tokenizer.h"

std::regex create_regex_pattern(){

    // Pattern that matches whole words, including hypheneated words
    std::regex pattern("\\w+(?:-\\w+)*", std::regex::icase);
    
    return pattern;
}

int tokenize_string(
    std::string str,
    std::unordered_map<std::string, int> &dictk,
    int k)
{
    // Extract tokens from word.
    int cursor = 0;
    std::string substr = "";
    int strsz = str.size();

    // std::cout << str.size() << " " << k << " " << wdsz - k << std::endl;
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

std::vector<std::string> get_regex_matches(
    std::string &str,
    std::regex rgx)
{
    std::vector<std::string> word_sequence;

    // extract the substrings in str that match rgx
    auto words_begin =
        std::sregex_iterator(str.begin(), str.end(), rgx);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        std::string match_str = match.str();

        // match to lowercase
        std::string lowercase_match = string_to_lower(match_str);

        // add space as end of word character
        lowercase_match = lowercase_match + ' ';

        word_sequence.push_back(lowercase_match);
    }

    return word_sequence;
}

void sliding_window_tokenizer(
    std::vector<std::string> & text_lines,         // Input: vector of (non-empty lines in the text)
    std::unordered_map<std::string, int> &dictk, // On return: dictionary of token counts
    unsigned k                                   // Token length
)
{
    int cursor = 0;
    std::string buffer_string = text_lines.at(0);
    for (unsigned i = 1; i < text_lines.size(); i++)
    {
        // std::cout << buffer_string << "\n";
        cursor = tokenize_string(buffer_string, dictk, k);
        buffer_string = buffer_string.substr(cursor, k - 1) + text_lines.at(i);
    }
};

void regex_tokenizer(
    std::vector<std::string> & text_lines,       // Input: vector of (non-empty lines in the text)
    std::unordered_map<std::string, int> &dictk, // On return: dictionary of token counts
    unsigned k                                   // Token length
)
{
    std::regex rgx = create_regex_pattern();

    for (unsigned i = 1; i < text_lines.size(); i++)
    {
        std::vector<std::string> word_sequence = get_regex_matches(text_lines.at(i), rgx);
        for (auto w : word_sequence)
        {
            // std::cout << w << "\n";
            tokenize_string(w, dictk, k); // tokenize each word in the sequence
        }
    }
};

// Tokenize a vector of lines. Two approaches to tokenization are available:
// i) sliding window, ii) regex matching.
void text_tokenizer(
    std::vector<std::string> &text_lines,         // Input: vector of (non-empty lines in the text)
    std::unordered_map<std::string, int> &dictk, // On return: dictionary of token counts
    unsigned k,                                  // Token length
    unsigned tokenizer                           //
)
{
    if (tokenizer == 0)
    {
        sliding_window_tokenizer(text_lines, dictk, k);
    }
    else
    {
        regex_tokenizer(text_lines, dictk, k);
    }
}
