#pragma once

#include <string>
#include <stdexcept>
#include <cstdio>
#include "json.hpp"

namespace anatheahbr {

// --------------------
// Check if Ollama running
// --------------------
inline bool is_ollama_running() {
    int result = system("curl -s http://localhost:11434/api/tags > nul 2>&1");
    return result == 0;
}

// --------------------
// Ask Ollama
// --------------------
inline std::string ask_ollama(
    const std::string& prompt,
    const std::string& model = "llama3"
) {
    using json = nlohmann::json;

    // Build JSON safely
    json req = {
        {"model", model},
        {"prompt", prompt},
        {"stream", false}
    };

    std::string json_str = req.dump();

    // IMPORTANT: escape quotes for Windows cmd
    std::string escaped;
    for (char c : json_str) {
        if (c == '"') escaped += "\\\"";
        else escaped += c;
    }

    // Curl command (no file)
    std::string cmd =
        "curl -s http://localhost:11434/api/generate "
        "-H \"Content-Type: application/json\" "
        "-d \"" + escaped + "\"";

    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe)
        throw std::runtime_error("Failed to run curl");

    std::string raw;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), pipe)) {
        raw += buffer;
    }

    _pclose(pipe);

    if (raw.empty())
        throw std::runtime_error("Empty response from Ollama");

    // Parse JSON response
    auto json_res = json::parse(raw);

    return json_res.value("response", "");
}

} // namespace anatheahbr