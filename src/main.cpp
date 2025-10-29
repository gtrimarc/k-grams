#include "../include/char_seq.h"
#include "../include/kgrams.h"
#include <iostream>
#include <string>


int main(int argc, char *argv[]){
    if (argc > 1){
        std::string arg1 = argv[1];
        int k = stoi(arg1);

        std::string training_corpus = argv[2];

        kgram_set kgram_model(k);
        kgram_model.fit(training_corpus);

        std::string arg3 = argv[3];
        int completion_length = stoi(arg3);
        
        CharSeq char_seq;
        
        char_seq.generate_completion(kgram_model, completion_length);

        std::cout << char_seq.to_string() << "\n"; 
    }
    return 0;
}
