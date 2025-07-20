#include "scanner.hpp"
#include <chrono>
#include <thread>
#include <iostream>

int main() {
    std::string solutionDir = SOLUTION_DIR;
    const std::string rules_path = solutionDir + "/src/scanner/config/rules.json";
    const std::string violations_path = solutionDir + "/src/scanner/output/violations.json";
    const std::string scan_path = solutionDir + "/src/scanner/sample_data/";
    const int scan_interval_seconds = 60;

    Scanner scanner(rules_path, scan_path, violations_path);  // Initialize once

    while (true) {
        std::cout << "[Scanner] Starting new scan cycle...\n";
        scanner.scan();
        std::cout << "[Scanner] Scan complete. Sleeping for " << scan_interval_seconds << " seconds.\n";
        std::this_thread::sleep_for(std::chrono::seconds(scan_interval_seconds));
    }

    return 0;
}
