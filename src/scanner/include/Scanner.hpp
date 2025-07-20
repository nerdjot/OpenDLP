#pragma once

#include <string>
#include <vector>
#include <regex>
#include <fstream>

struct Rule {
    std::string name;
    std::regex pattern;
    std::string action;
};

class Scanner {
public:
    Scanner(const std::string& rulesFilePath, const std::string& scanDirectory, const std::string& violationsFilePath);

    void scan();

private:
    void loadRules();
    //void scan();
    void scanFile(const std::filesystem::path& filePath);
    void logViolation(const std::string& ruleName, const std::string& filePath, const std::string& match);

    std::vector<Rule> m_rules;
    std::string directoryToScan_;
    std::string m_rulesPath;
    std::string m_scanDir;
    std::string m_violationsPath;
};
