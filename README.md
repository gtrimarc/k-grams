# k-grams

## Quick start

Please clone the repository with the command

`git clone https://github.com/gtrimarc/k-grams.git`

The project root contains the `project_setup.sh` Bash script to create the 
folders `obj` and `exec` in which the object files and the executable will be 
respectively located after running the makefile. Use `chmod` to make 
`project_setup.sh` executable running, e.g., the command `chmod u+x project_setup.sh` 
in a terminal. The `project_setup.sh` will also run the Makefile and build 
the executable `slm` in the `./exec` folder.

Run the program from command line like this:

./exec/slm 3 corpus/pg10.txt 15

where the first argument is the length of the k-grams, the second is the name of
the file containing the text used to train the model, and the third length of the
completion. 


## Modeling workflow

1. Process the corpus text to read iteratively the non-empty lines. 
   In this step the alphabetic characters in a line are converted to 
   lowercase. An empty space is added at the end of the extracted lines
   that are appended to a string vector.  

2. Transform the text into a sequence of words. Loop over the lines and extract 
   sequentially the substrings that match a regular expression pattern that represents 
   whole words, including hypthenated words. A space is added to each matching
   substring which is then sequentially accumulated in a master string.  

3. Tokenize the master string and accumulate the counts of the unique kgrams 
   of length k in a master dictionary. This tokenization process is performed to count
   the unique kgrams of up to a given maximum length.

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
├── corpus/
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

* `get_tail_substring(unsigned k)`: returns a string with the last *k* characters in the character sequence.

* `generate_completion(kgram_set model, int length)`: modifies the character sequence generating a completion of the requested length with the input `kgram_set` model. 

