#include "ollama.hpp"
#include <iostream>

int main()
{
    if (anatheahbr::is_ollama_running())
    {
        std::string reply = anatheahbr::ask_ollama("Hello, how are you?", "gemma3:4b");
        std::cout << reply << std::endl;
    }
    else
    {
        std::cout << "Ollama is not running" << std::endl;
    }
}
