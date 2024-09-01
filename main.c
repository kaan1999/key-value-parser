#include <kv_tokenizer.h>
#include <kv_list.h>
#include <stdio.h>
#include <stdlib.h>

errno_t intptr_dtor(void *pv)
{
    free(pv);
    return 0;
}

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

    kv_list_ptr list = kv_list_init();
    kv_list_push(list, (void *)10, NULL);
    kv_list_push(list, "kaan", NULL);
    kv_list_push(list, (void *)30, NULL);
    kv_list_push(list, (void *)40, NULL);
    
    kv_list_forEach(list, i)
        printf("%ju ", (uintptr_t)kv_list_data(i));
    kv_end
    

    kv_list_destroy(list);
}