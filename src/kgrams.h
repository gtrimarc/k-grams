// #include "utils.h"
#include "tokenizer.h"
#include <fstream>
#include <string>
#include <unordered_map>


class kgram {
    private:
        int k_;
        std::unordered_map<std::string, int> kgram_vocabulary_;
        std::unordered_map<std::string, int> prefix_vocabulary_;
    public:
        // kgram(int, std::unordered_map<std::string, int>,
        //     std::unordered_map<std::string, int>);

        kgram(int);
        void predict(std::string);
        void fit(std::string);
        ~kgram();
};