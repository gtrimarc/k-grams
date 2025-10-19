#include <iostream>
#include <string>

// Echo the user prompt as test message
void print_test_message(std::string user_input)
{
    std::cout << "Echo: " << user_input << std::endl;
}

// Prompt-reply loop: currently for testing the application 
// echoes the user prompt
int main()
{
    std::string user_input;
    bool continue_session = true;
    while (continue_session)
    {
        // Input prompt
        std::cout << "Prompt: ";
        // Add characters from cin to the user_input string until
        // the new line character '\n' is found.
        std::getline(std::cin, user_input);

        print_test_message(user_input);

        if (user_input == "quit")
        {
            continue_session = false;
        }
    }
    return 0;
}