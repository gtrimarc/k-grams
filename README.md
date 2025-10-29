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

This class models character-level transition probabilities using k-grams (substrings of length k) extracted from a text corpus. It learns frequency counts of all k-grams up to a specified maximum order, enabling it to estimate the probability of each possible next character given a preceding context.

The model supports:

* Training (`fit`) on a text corpus to build k-gram frequency tables.

* Probability estimation (`transition_probability`) of a character following a given substring.

* Sampling (`predict`) to stochastically generate the next character based on learned transition probabilities.

Internally, it implements Laplace (add-one) smoothing and uses a Mersenne Twister RNG to ensure reproducible, unbiased character sampling.