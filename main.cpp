#include <iostream>
#include <chrono>
#include "word_composition.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string filepath = argv[1];

    auto start = std::chrono::steady_clock::now();

    bool file_opened = false;
    std::vector<std::string> words = read_words(filepath, file_opened);
    if (!file_opened) {
        std::cerr << "Error: Could not open file '" << filepath << "'" << std::endl;
        return 1;
    }
    if (words.empty()) {
        std::cerr << "Error: No words found in '" << filepath << "'" << std::endl;
        return 1;
    }

    CompoundResult result = find_longest_compounds(words);

    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Longest Compound Word: "
              << (result.longest.empty() ? "(none)" : result.longest) << std::endl;
    std::cout << "Second Longest Compound Word: "
              << (result.second_longest.empty() ? "(none)" : result.second_longest) << std::endl;
    std::cout << "Time taken: " << ms.count() << " milliseconds" << std::endl;

    return 0;
}
