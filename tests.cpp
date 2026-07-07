#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "word_composition.h"

static int tests_run = 0;
static int tests_passed = 0;

static void check(bool condition, const std::string& name) {
    tests_run++;
    if (condition) {
        tests_passed++;
        std::cout << "  PASS: " << name << std::endl;
    } else {
        std::cout << "  FAIL: " << name << std::endl;
    }
}


static void test_empty_input() {
    std::cout << "\ntest_empty_input:" << std::endl;
    std::vector<std::string> words = {};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest.empty(), "no longest for empty input");
    check(r.second_longest.empty(), "no second longest for empty input");
}

static void test_no_compounds() {
    std::cout << "\ntest_no_compounds:" << std::endl;
    std::vector<std::string> words = {"apple", "banana", "cherry"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest.empty(), "no compounds in unrelated words");
}

static void test_single_compound_two_parts() {
    std::cout << "\ntest_single_compound_two_parts:" << std::endl;
    std::vector<std::string> words = {"sun", "flower", "sunflower"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "sunflower", "sunflower = sun + flower");
    check(r.second_longest.empty(), "only one compound exists");
}

static void test_multiple_compounds() {
    std::cout << "\ntest_multiple_compounds:" << std::endl;
    std::vector<std::string> words = {"sun", "flower", "sunflower", "rain", "bow", "rainbow"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "sunflower", "sunflower (9) is longest");
    check(r.second_longest == "rainbow", "rainbow (7) is second");
}

static void test_three_or_more_parts() {
    std::cout << "\ntest_three_or_more_parts:" << std::endl;
    std::vector<std::string> words = {"a", "b", "c", "ab", "abc"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "abc", "abc = a+b+c (3 parts)");
    check(r.second_longest == "ab", "ab = a+b (2 parts)");
}

static void test_repeated_components() {
    std::cout << "\ntest_repeated_components:" << std::endl;
    std::vector<std::string> words = {"ha", "haha", "hahaha"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "hahaha", "hahaha = ha+ha+ha");
    check(r.second_longest == "haha", "haha = ha+ha");
}

static void test_self_matching_prevention() {
    std::cout << "\ntest_self_matching_prevention:" << std::endl;
    std::unordered_set<std::string> dict = {"cat"};
    check(!is_compound("cat", dict), "single word 'cat' is not compound");

    // A word that exists in dict but cannot be split into two dict words
    std::unordered_set<std::string> dict2 = {"hello", "world"};
    check(!is_compound("hello", dict2), "'hello' is not compound");
}

static void test_overlapping_prefixes() {
    std::cout << "\ntest_overlapping_prefixes:" << std::endl;
    // "abc": split "a"+"bc" fails (bc not in dict), but "ab"+"c" succeeds
    std::vector<std::string> words = {"a", "ab", "c", "abc"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "abc", "abc found via ab+c despite a+bc failing");
}

static void test_long_non_compound_is_skipped() {
    std::cout << "\ntest_long_non_compound_is_skipped:" << std::endl;
    std::vector<std::string> words = {"hippopotamuses", "cat", "dog", "catdog"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "catdog", "catdog is compound, hippopotamuses is not");
}

static void test_assignment_example() {
    std::cout << "\ntest_assignment_example:" << std::endl;
    std::vector<std::string> words = {
        "cat", "cats", "catsdogcats", "catxdogcatsrat",
        "dog", "dogcatsdog", "hippopotamuses", "rat", "ratcatdogcat"
    };
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "ratcatdogcat", "longest is ratcatdogcat");
    check(r.second_longest == "catsdogcats", "second is catsdogcats");
}

static void test_duplicate_compound_words() {
    std::cout << "\ntest_duplicate_compound_words:" << std::endl;
    std::vector<std::string> words = {"cat", "dog", "catdog", "catdog"};
    CompoundResult r = find_longest_compounds(words);
    check(r.longest == "catdog", "catdog is longest compound");
    check(r.second_longest.empty(), "duplicate catdog is not returned as second");
}

static void test_word_not_fully_decomposable() {
    std::cout << "\ntest_word_not_fully_decomposable:" << std::endl;
    std::unordered_set<std::string> dict = {"cat", "dog"};
    check(!is_compound("catfish", dict), "catfish fails (fish not in dict)");
    check(!is_compound("xdog", dict), "xdog fails (x not in dict)");
}

int main() {
    std::cout << "Running word composition tests..." << std::endl;

    test_empty_input();
    test_no_compounds();
    test_single_compound_two_parts();
    test_multiple_compounds();
    test_three_or_more_parts();
    test_repeated_components();
    test_self_matching_prevention();
    test_overlapping_prefixes();
    test_long_non_compound_is_skipped();
    test_assignment_example();
    test_duplicate_compound_words();
    test_word_not_fully_decomposable();

    std::cout << "\n" << tests_passed << "/" << tests_run << " tests passed." << std::endl;
    return (tests_passed == tests_run) ? 0 : 1;
}
