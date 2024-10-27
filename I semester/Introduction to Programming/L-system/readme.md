Lindenmayer System (L-system) Implementation
Introduction
The Lindenmayer System, or L-system, is a formal system that defines languages. It was created by biologist Aristid Lindenmayer to model plant growth.

A deterministic context-free L-system (known as D0L) is represented by the tuple (S, A, R), where:

S is the alphabet,
A is a word over S called the axiom,
R is a set of replacement rules associating symbols with words over S. For each element in S, there is at most one rule in R.
A word w belongs to the language defined by the L-system if and only if there exists a non-negative integer n such that w has a derivation of length n. The axiom is considered to have a derivation length of 0. A word with a derivation of length n + 1 is generated from a word with a derivation of length n by simultaneously replacing each symbol with the word specified by its rule, or leaving it unchanged if no rule exists.

We also consider a textual interpretation of words in the language defined by the L-system. The interpretation begins with a sequence of lines called the prologue, followed by lines corresponding to each symbol in the word, and ends with a sequence of lines called the epilogue. The lines corresponding to symbols are determined by interpretation rules. For each symbol, there is at most one interpretation rule. Symbols without an interpretation rule are omitted in the interpretation.

Task
Write a program that reads from the input:

The derivation length,
The description of the L-system,
The interpretation of the L-system word.
The program should output the interpretation of the derived word belonging to the language defined by the L-system.

Data Format
The input to the program consists of:

A line with a non-negative integer specifying the derivation length,
Lines describing the L-system, followed by lines describing the word interpretation.
L-system Description
The L-system description consists of:

A line containing the axiom,
A sequence of lines with replacement rules. Each replacement rule line begins with the symbol being replaced, followed by the word that replaces it.
The alphabet of the L-system is not explicitly given; it is assumed to be the set of symbols found in the axiom and replacement rules.

Word Interpretation Description
The interpretation description begins with:

A sequence of prologue lines,
Lines for interpretation rules,
A sequence of epilogue lines.
Each of these three sequences is preceded by an empty line. Each interpretation rule line begins with the symbol being interpreted, followed by the text to output for that symbol.

Output Format
The program’s output is a sequence of lines representing the interpretation of the derived word.
