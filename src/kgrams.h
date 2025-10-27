#include "utils.h"
#include "tokenizer.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>


class kgram {
    private:
        int k_;
        std::vector<std::unordered_map<std::string, int>> kgram_vocabulary_;

        // Helper functions
        float prob_mass_func(std::string , char );
        std::vector<float> next_char_probabilities(std::string);
        char sample_next_char_probabilities(std::vector<float>);

    public:
        // kgram(int, std::unordered_map<std::string, int>,
        //     std::unordered_map<std::string, int>);

        kgram(int);
        char predict(std::string);
        void fit(std::string);
        ~kgram();
};