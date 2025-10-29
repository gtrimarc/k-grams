# k-grams

## Quick start

Please clone the repository with the command

    git clone https://github.com/gtrimarc/k-grams.git

The project root contains the `project_setup.sh` Bash script. The script creates the 
folders `obj` and `exec` in which the object files and the executable will be 
stored after building the project. 

Before running it make it executable with the command `chmod u+x project_setup.sh`. Running `project_setup.sh` will also execute the Makefile and build the executable `slm` in the `./exec` folder. 

The `corpus` folder contains two 
files of books in English downloaded from the Project Guthenberg website: `moby10b.txt` (Moby Dyck) and `pg10.txt` (The Bible). These files can be used to train k-gram models.s. 

Run the program from the command line with three arguments like in this example:

    ./exec/slm 3 corpus/pg10.txt 40

Here:
* the first argument specifies the k-gram length,
* the second is the training text file,
* the third defines the length of the generated completion.

The following is an example of a program execution

    (base) Wed Oct 29 [09:32 PM] (dev) $  
    ./exec/slm 3 corpus/pg10.txt 40
    on spon and and theave becrigne dregiver


## Modeling workflow

1. Process the corpus text to read iteratively the non-empty lines. 
In this step the alphabetic characters in a line are converted to lowercase. 
An empty space is added at the end of the extracted lines that are appended 
to a string vector.  

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
├── exec/
│ └── slm
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


## Utility Modules

### `tokenizer`
Defined in: `tokenizer.h` / `tokenizer.cpp`

**Purpose:**  
Provides tokenization and text preprocessing utilities for training.  

**Typical functions:**
- `regex_tokenizer(std::vector<std::string>& text_lines, std::unordered_map<std::string, int>& dictk, unsigned k)` : tokenizes the corpus text stored in a vector of lines passed as input argument. On completion `dictk` contains the dictionary of k-grams present in the corpus along with the corresponding counts.
- `std::string get_regex_matches(std::string &str, std::regex rgx)`: extracts the substrings that match the regular expression rgx in the input string.
- `tokenize_string(std::string str,std::unordered_map<std::string, int> &dictk, int k)`: tokenizes an input string and accumulates in `dictk` the counts of the unique k-grams of length `k`.

---

### `utils`
Defined in: `utils.h` / `utils.cpp`

**Purpose:**  
Handles the input file stream and the line by line preprocessing of the input text.

**Typical functions:**
- `connect_instream_to_file(std::string fname)`: connects the input stream to a specified file
- `std::vector<std::string> get_sequence_of_lines(std::ifstream &infstream)`: processes 
the input text line by line, converts characters to lowercase, and stores each line sequentially
in a vector of strings.
