// Scanner/src/Scanner.cpp
#include "../include/Scanner.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

Scanner::Scanner(const std::string& rulesFilePath, const std::string& scanDirectory, const std::string& violationsFilePath)
    : m_rulesPath(rulesFilePath), m_scanDir(scanDirectory), m_violationsPath(violationsFilePath) {
    loadRules();
}

void Scanner::loadRules() {
    std::ifstream file(m_rulesPath);
    if (!file) {
        std::cerr << "Failed to open rules file." << std::endl;
        return;
    }
    json j;
    file >> j;

    for (const auto& rule : j["rules"]) {
        m_rules.push_back({
            rule["name"].get<std::string>(),
            std::regex(rule["regex"].get<std::string>()),
            rule["action"].get<std::string>()
            });
    }
}

void Scanner::scan() {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(m_scanDir)) {
        if (entry.is_regular_file()) {
            scanFile(entry.path());
        }
    }
}

void Scanner::scanFile(const std::filesystem::path& filePath) {
    std::ifstream file(filePath);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        for (const auto& rule : m_rules) {
            std::smatch match;
            if (std::regex_search(line, match, rule.pattern)) {
                logViolation(rule.name, filePath.string(), match.str());
            }
        }
    }
}

void Scanner::logViolation(const std::string& ruleName, const std::string& filePath, const std::string& match) {
    std::ofstream out(m_violationsPath, std::ios::app);
    json j = {
        {"rule", ruleName},
        {"file", filePath},
        {"match", match},
        {"timestamp", std::time(nullptr)}
    };
    out << j.dump() << std::endl;
}
