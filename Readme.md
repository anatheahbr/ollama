// usage:

#include "ollama.hpp"
#include <iostream>

int main() {
    if (anatheahbr::is_ollama_running()) {
        std::string reply = anatheahbr::ask_ollama("Hello, how are you?");
        std::cout << reply << std::endl;
    } else {
        std::cout << "Ollama is not running" << std::endl;
    }
}

// compile with g++ main.cpp -o main.exe -std=c++17 -lws2_32