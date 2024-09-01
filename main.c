#include <kv_parser.h>
#include <kv_tokenizer.h>
#include <stdio.h>
int main(void)
{
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

    /*
    kv_list_ptr list = kv_list_init();
    kv_list_push(list, (void *)10, NULL);
    kv_list_push(list, "kaan", NULL);
    kv_list_push(list, (void *)30, NULL);
    kv_list_push(list, (void *)40, NULL);
    
    kv_list_forEach(list, i)
        printf("%ju ", (uintptr_t)kv_list_data(i));
    kv_end
    kv_list_destroy(list);
    */

    /*
    kv_list_ptr tokenList = kv_tokenizer_read("kvp.txt");
    kv_list_forEach(tokenList, i)
        kv_token_ptr t = kv_list_data(i);
        printf("token value: %s\n", kv_token_value(t));
    kv_end
    printf("%ju", kv_list_size(tokenList));
    kv_list_destroy(tokenList);
    */

   /*
    kv_pair_ptr pair1 = kv_pair_init(NULL, NULL);
    perror("err");
    errno = 0;
    kv_pair_ptr pair2 = kv_pair_init(NULL, "kaan");
    perror("err");
    errno = 0;
    kv_pair_ptr pair3 = kv_pair_init("name", NULL);
    perror("err");
    errno = 0;
    kv_pair_ptr pair4 = kv_pair_init("name", "kaan");
    perror("err");
    errno = 0;
    kv_pair_destroy(pair1);
    perror("err");
    errno = 0;
    kv_pair_destroy(pair2);
    perror("err");
    errno = 0;
    kv_pair_destroy(pair3);
    perror("err");
    errno = 0;
    kv_pair_destroy(pair4);
    perror("err");
    errno = 0;
    */


    kv_list_ptr tokenStream = kv_tokenizer_read("kvp.txt");
    if(!tokenStream) perror("Error");
    kv_list_ptr pairList = kv_parser(tokenStream);
    if(!pairList) perror("Error");

    kv_list_destroy(tokenStream);
    kv_list_destroy(pairList);
}