#pragma once

// ---- FORCE Windows 10 target (override toolchain) ----
#ifdef _WIN32
    #undef _WIN32_WINNT
    #define _WIN32_WINNT 0x0A00
#endif

#define CPPHTTPLIB_USE_POLL

#include "httplib.h"
#include "json.hpp"

#include <string>
#include <stdexcept>

namespace anatheahbr {

// --------------------
// Check if Ollama running
// --------------------
inline bool is_ollama_running() {
    httplib::Client cli("http://127.0.0.1:11434");

    cli.set_connection_timeout(2); // seconds

    if (auto res = cli.Get("/api/tags")) {
        return res->status == 200;
    }

    return false;
}

// --------------------
// Ask Ollama
// --------------------
inline std::string ask_ollama(
    const std::string& prompt,
    const std::string& model = "llama3"
) {
    httplib::Client cli("http://127.0.0.1:11434");

    cli.set_connection_timeout(5);

    nlohmann::json body = {
        {"model", model},
        {"prompt", prompt},
        {"stream", false}
    };

    auto res = cli.Post(
        "/api/generate",
        body.dump(),
        "application/json"
    );

    if (!res) {
        throw std::runtime_error("Connection to Ollama failed");
    }

    if (res->status != 200) {
        throw std::runtime_error("HTTP error: " + std::to_string(res->status));
    }

    nlohmann::json json = nlohmann::json::parse(res->body);

    return json.value("response", "");
}

} // namespace anatheahbr