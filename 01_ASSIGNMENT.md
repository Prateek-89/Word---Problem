# Word Composition Problem

## Problem Statement

Write a program that:

1.  Reads the provided files `Input_01.txt` and `Input_02.txt`, which
    contain alphabetically sorted word lists:
    -   one word per line
    -   no spaces
    -   all lowercase
2.  Identifies and displays:
    -   the longest compounded word
    -   the second-longest compounded word
    -   the time taken to process the input file

A **compounded word** is a word that can be constructed by concatenating
two or more shorter words that are also present in the same input file.

## Input 01

`Input_01.txt` is a small word list containing:

-   cat
-   cats
-   catsdogcats
-   catxdogcatsrat
-   dog
-   dogcatsdog
-   hippopotamuses
-   rat
-   ratcatdogcat

### Expected Result

-   Longest Compound Word: `ratcatdogcat`
-   Second Longest Compound Word: `catsdogcats`

`hippopotamuses` is longer, but it is not a compounded word and
therefore is not an answer.

## Input 02

`Input_02.txt` is a large word list containing more than 100,000 items.

### Expected Result

-   Longest Compound Word: `ethylenediaminetetraacetates`
-   Second Longest Compound Word: `electroencephalographically`

The processing time must be measured from the actual program execution.
Do not hardcode a sample timing value.

## Solution Requirements

This assignment focuses on:

-   correctness
-   approach
-   code quality
-   performance
-   appropriate use of data structures
-   reduced search time complexity

Performance matters because the solution must work efficiently with word
lists containing more than 100,000 entries.

## Deliverables

Submit:

1.  A Google Drive or GitHub URL containing the source code. The
    solution may be written in any programming language.
2.  A concise `README` containing:
    -   steps to execute the code
    -   a short program overview
    -   design decisions
    -   the approach used

The README should be only a few paragraphs long.

## Important Note

Do not copy and paste an existing web solution. External resources may
be used for direction, but the implementation and reasoning should be
original.
