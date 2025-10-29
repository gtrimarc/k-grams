# k-grams

## Project structure

This project implements a character-level k-gram model for text generation and completion.  
It is organized into two core classes and two supporting utility modules.

```bash

project_root/
├── src/
│ ├── main.cpp
│ ├── kgrams.cpp
│ ├── char_seq.cpp
│ ├── tokenizer.cpp
│ └── utils.cpp
├── include/
│ ├── kgrams.h
│ ├── char_seq.h
│ ├── tokenizer.h
│ └── utils.h
├── data/
│ └── *.txt
├── obj/
│ └── *.o
└── Makefile
```

## Main components

### Class `kgram_set`

This class models character-level transition probabilities using k-grams (substrings of length k) extracted from a text corpus. It learns frequency counts of all k-grams up to a specified maximum order, enabling it to estimate the probability of each possible next character given a preceding context. The class exposes the following key methods:

* `fit(std::string fname)`: trains (`fit`) the model on the text corpus in the `fname` file to build k-gram frequency tables.

* `predict(std::string in_str)`: stochastically generate (`predict`) the next character given the prefix string `in_str` based on learned transition probabilities.

* `transition_probability(std::string s, char c)`: estimate the transition_probability of character `c` following substring `s`.


Internally, it implements Laplace (add-one) smoothing and uses a Mersenne Twister random number generator for the character sampling.

### Class `char_seq`

This class models sequence of characters as character lists using the standard library `std::list` container. Key methods provided by the class:

* `get_tail_substring(unsigned k)` – returns a string with the last *k* characters in the character sequence.

* `generate_completion(kgram_set model, int length)` - Modifies the character set generating a completion of the requested length with the input `kgram_set` model. 
