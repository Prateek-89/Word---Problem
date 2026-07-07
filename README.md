# Word Composition Problem

## Overview

Given a file of alphabetically sorted words (one per line, all lowercase), this program finds the longest and second-longest **compounded words** — words that can be formed by concatenating two or more shorter words from the same file.

## Approach

The algorithm uses an `unordered_set` for O(1) word lookup and recursive decomposition to test whether each word can be split into dictionary words.

For a candidate word, the function tries every possible prefix. When a prefix exists in the dictionary, it recursively checks whether the remaining suffix can also be fully built from dictionary words. A per-word positional memo array prevents redundant suffix checks. Self-matching is avoided structurally: the outer loop only tries prefixes strictly shorter than the full word, so a word can never "match itself" as a single-part compound.

Words are sorted by length (descending) before checking, so the first two compounds found are guaranteed to be the longest and second-longest. The search stops immediately after finding both.

## Data Structure Choices

- **`unordered_set<string>`**: Provides average O(1) lookup for checking whether a substring exists in the dictionary. A trie could avoid creating temporary substring objects during prefix traversal, but it would require more implementation code and additional per-node storage. For this assignment and dataset, `unordered_set` keeps the solution simpler while still providing good practical performance.
- **`vector<int8_t>` memo**: Per-word positional cache indexed by character position. Avoids re-checking the same suffix start position within a single word.

## Complexity

- **Time**: O(N · L³) worst case, where N is the number of words and L is the maximum word length. Per word, positional memoization ensures each suffix start position is fully evaluated at most once, giving up to L positions. At each position, the algorithm tries up to L substring lengths, and each `substr` call plus hash-set lookup costs up to O(L) for string construction and hashing. In practice, runtime is much lower because word lengths are small and the search stops after finding two distinct longest compounds.
- **Space**: O(N · L) for stored words and the hash set. O(L) additional per candidate word for the memoization array and recursion stack.

## Project Structure

```
Word Composition Problem/
├── word_composition.h   — core algorithm (read_words, is_compound, find_longest_compounds)
├── main.cpp             — entry point, timing, output
├── tests.cpp            — focused unit tests
├── Input_01.txt         — small test dataset (9 words)
├── Input_02.txt         — large dataset (173,526 words)
├── README.md
└── .gitignore
```

## Build and Run

Requires a C++ compiler with C++17 support (g++, clang++, or MSVC).

```bash
# Build
g++ -std=c++17 -O2 -o main.exe main.cpp

# Run
./main.exe Input_01.txt
./main.exe Input_02.txt

# Build and run tests
g++ -std=c++17 -O2 -o tests.exe tests.cpp
./tests.exe
```

## Example Output

```
Longest Compound Word: ethylenediaminetetraacetates
Second Longest Compound Word: electroencephalographically
Time taken: <measured at runtime>
```

