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

## Tutorial
```
//first you need to add kv_parser and kv_tokenizer header files.
#include <kv_tokenizer>
#include <kv_parser>

int main(void){
    //declare two lists to hold tokens and pairs
    kv_list_ptr tokenList = NULL, pairList = NULL;
    //Let's parse the tokens from the file with the tokenizer_read function
    tokenList = kv_tokenizer_read("example.txt");
    //Let's do error handling here.
    if(!tokenList){
        perror("Error");
        return 1;
    }
    //If there are no errors, let's send the tokens in tokenList to the parser.
    pairList = kv_parser(tokenList);
    //we don't need tokenList anymore
    kv_list_destroy(tokenList);
    //Let's check for errors again (if there is an error in the parser, the program will end without returning)
    if(!pairList){
        perror("Error");
        return 1;
    }
    //If there are no errors, our pairs are now stored in pairList.
    //use the kv_list_forEach macro to access each pair
    //The forEach macro takes two parameters, first is a list to iterate and second the node returned from that list.
    kv_list_forEach(pairList, pairNode)
        //Here we access the pair by giving the pairNode to the kv_list_data function
        kv_pair_ptr pair = kv_list_data(pairNode);
        //You can use kv_pair_key and kv_pair_value to access key and value in pair
        char *key = kv_pair_key(pair);
        char *value = kv_pair_value(pair);
    kv_end //each forEach must end with kv_end
    //destroy after you are done with pairList
    kv_list_destroy(pairList);
}
```

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