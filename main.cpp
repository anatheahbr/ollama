#include <iostream>
#include "ollama.hpp"

int main() {
    // Check if Ollama is running
    if (!anatheahbr::is_ollama_running()) {
        std::cout << "Ollama is not running on localhost:11434\n";
        return 1;
    }

    try {
        std::string prompt = "Explain C++ namespaces in simple terms.";

        std::string response = anatheahbr::ask_ollama(prompt);

        std::cout << "AI Response:\n";
        std::cout << response << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}