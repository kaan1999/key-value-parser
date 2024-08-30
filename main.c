#include <kv_tokenizer.h>
#include <stdio.h>
int main(void){
    /*
    //test start tokenList_push 
    kv_tokenList_ptr tokenList = kv_tokenList_init();
    if(!tokenList) perror("Error");
    if(kv_tokenList_push(tokenList, 300, NULL)) perror("Error");
    if(kv_tokenList_push(tokenList, KEY, NULL)) perror("Error");
    if(kv_tokenList_push(tokenList, VALUE, NULL)) perror("Error");
    if(kv_tokenList_push(tokenList, COLON, NULL)) perror("Error");
    if(kv_tokenList_push(tokenList, SEMICOLON, NULL)) perror("Error");
    if(kv_tokenList_push(tokenList, 300, "a")) perror("Error");
    if(kv_tokenList_push(tokenList, KEY, "a")) perror("Error");
    if(kv_tokenList_push(tokenList, VALUE, "a")) perror("Error");
    if(kv_tokenList_push(tokenList, COLON, "a")) perror("Error");
    if(kv_tokenList_push(tokenList, SEMICOLON, "a")) perror("Error");
    if(kv_tokenList_destroy(tokenList)) perror("Error");
    //test end tokenList_push 
    */
   kv_tokenList_ptr tokenList = kv_tokenizer_read("kvp.txt");
   if(!tokenList) perror("Error");
}