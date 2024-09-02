# Key-Value Parser

## Intro
Key-Value Parser is a small parser program that parses pairs in key:value; format. The program reads the pairs from the given file and writes them to a file. The tokenizer function parses the data from the read file into tokens and creates a token list. Then the token list is passed to the parser function and if there are no syntax errors, key-value pairs are created.

## EBNF
This is the EBNF created for syntax rules:
```
syntax       = { pair } ;
pair         = key, ":", value, ";" ;
key          = letter, { letter | digit } ;
value        = letter, { letter | digit } ;

letter       = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" 
             | "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" ;
digit        = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

```
## Types
* struct KVNode: representing a node in the generic list.
* struct KVList: representing generic linked-list.
* struct KVPair: representing key-value pairs.
* struct KVToken: representing token to hold token type and token value.
* enum KVTokenType: Enumeration of token types.
* struct KVPair: representing Key-value pair.

## Functions
* kv_node_init: initialize a generic node.
* kv_node_destroy: destroys a generic node.
* kv_list_init: initializes a generic list.
* kv_list_destroy: destroys a generic list.
* kv_list_push: pushes data onto the generic list.
* kv_list_each: iterates over the generic list.
* kv_list_data: retrieves the data from a generic list.
* kv_list_size: retrieves the size of the generic list.
* kv_list_forEach: macro to iterate over each element in the generic list.
* kv_token_init: initializes a token.
* kv_token_destroy: destroys a token.
* kv_token_type: retrieves the type of a token.
* kv_token_value: retrieves the value of a token.
* kv_tokenizer_read: reads tokens from a file.
* kv_pair_init: initializes a key-value pair.
* kv_pair_destroy: destroys a key-value pair.
* kv_pair_key: retrieves the key from a key-value pair.
* kv_pair_value: retrieves the value from a key-value pair.
* kv_parser: parses a list of tokens into key-value pairs.

# Usage
The program gets an input file name and an output file name. The parse data is written to the output file.

```
<program_name> <input_file_name> <output_file_name>
```

# Build
## Build From Source
```
1. git clone https://github.com/kaan1999/key-value-parser.git
2. cd key-value-parser
3. cmake -B build -G "<generator name>"
4. cmake --build build --config Release
```