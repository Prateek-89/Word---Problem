#ifndef WORD_COMPOSITION_H
#define WORD_COMPOSITION_H

#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <cstdint>

inline std::vector<std::string> read_words(const std::string& filepath, bool& file_opened) {
    std::vector<std::string> words;
    file_opened = false;
    std::ifstream file(filepath);
    if (!file.is_open()) return words;
    file_opened = true;

    std::string line;
    while (std::getline(file, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (!line.empty()) {
            words.push_back(line);
        }
    }
    return words;
}

// memo[i] caches whether word[i..end) can be formed from dictionary words.
inline bool can_form_suffix(const std::string& word, size_t start,
                            const std::unordered_set<std::string>& dict,
                            std::vector<int8_t>& memo) {
    if (start == word.size()) return true;
    if (memo[start] != -1) return memo[start];

    for (size_t len = 1; start + len <= word.size(); ++len) {
        if (dict.count(word.substr(start, len))) {
            if (can_form_suffix(word, start + len, dict, memo)) {
                return (memo[start] = 1);
            }
        }
    }
    return (memo[start] = 0);
}

// The outer loop tries prefixes strictly shorter than the full word,
// so a word can never match itself as a single-part compound.
inline bool is_compound(const std::string& word,
                        const std::unordered_set<std::string>& dict) {
    if (word.size() < 2) return false;

    std::vector<int8_t> memo(word.size() + 1, -1);

    for (size_t prefix_len = 1; prefix_len < word.size(); ++prefix_len) {
        if (dict.count(word.substr(0, prefix_len))) {
            if (can_form_suffix(word, prefix_len, dict, memo)) {
                return true;
            }
        }
    }
    return false;
}

struct CompoundResult {
    std::string longest;
    std::string second_longest;
};

inline CompoundResult find_longest_compounds(const std::vector<std::string>& words) {
    CompoundResult result;
    if (words.empty()) return result;

    std::unordered_set<std::string> dict(words.begin(), words.end());

    // Sort by length descending, then alphabetically for deterministic ordering.
    std::vector<std::string> sorted_words(words.begin(), words.end());
    std::sort(sorted_words.begin(), sorted_words.end(),
              [](const std::string& a, const std::string& b) {
                  if (a.size() != b.size()) return a.size() > b.size();
                  return a < b;
              });

    for (const auto& word : sorted_words) {
        if (is_compound(word, dict)) {
            if (result.longest.empty()) {
                result.longest = word;
            } else if (word != result.longest) {
                result.second_longest = word;
                break;
            }
        }
    }

    return result;
}

#endif // WORD_COMPOSITION_H
