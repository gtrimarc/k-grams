#include "char_seq.h"
#include "kgrams.h"
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


        // char c = kgram_model.predict(arg3);
        // std::cout << arg3+c << "\n"; 
    //     std::string arg3 = argv[3];
    //     int out_length = stoi(arg3);
    }
    return 0;
}


// int main(int argc, char *argv[]){
//     if (argc > 1){
//         std::string arg1 = argv[1];
//         int k = stoi(arg1);

//         std::string fname = argv[2];

//         kgram_set kgram_model(k);
//         kgram_model.fit(fname);

//         std::string arg3 = argv[3];
//         char c = kgram_model.predict(arg3);
//         std::cout << arg3+c << "\n";
//     }
//     return 0;
// }




// int main(int argc, char *argv[])
// {
//     if (argc > 1)
//     {         
//         std::string fname = argv[1];
//         kgram kgram_model(5);
//         kgram_model.fit(fname);
//         kgram_model.predict("he v");
//     }
//     return 0;
// }

// // Echo the user prompt as test message
// void print_test_message(std::string user_input)
// {
//     std::cout << "Echo: " << user_input << std::endl;
// }
// // Prompt-reply loop: currently for testing the application 
// // echoes the user prompt
// int main()
// {
//     std::string user_input;
//     bool continue_session = true;
//     while (continue_session)
//     {
//         // Input prompt
//         std::cout << "Prompt: ";
//         // Add characters from cin to the user_input string until
//         // the new line character '\n' is found.
//         std::getline(std::cin, user_input);
//         print_test_message(user_input);
//         if (user_input == "quit")
//         {
//             continue_session = false;
//         }
//     }
//     return 0;
// }