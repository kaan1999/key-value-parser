#include <kv_parser.h>
#include <stdlib.h>
#include <string.h>
#include <kv_tokenizer.h>
#include <stdio.h>

struct KVPair
{
    char *key, *value;
};

kv_pair_ptr kv_pair_init(const char *key, const char *value)
{
    if (!key || !value)
    {
        errno = EINVAL;
        return NULL;
    }
    kv_pair_ptr pair = malloc(sizeof(kv_pair_t));
    if (!pair)
    {
        errno = ENOMEM;
        return NULL;
    }
    size_t szKey = strlen(key);
    size_t szValue = strlen(value);
    pair->key = malloc(szKey + 1);
    pair->value = malloc(szValue + 1);

    if (!pair->key || !pair->value)
    {
        errno = ENOMEM;
        free(pair);
        return NULL;
    }
    strcpy(pair->key, key);
    strcpy(pair->value, value);
    return pair;
}
errno_t kv_pair_destroy(void *pvPair)
{
    if (pvPair)
    {
        if (((kv_pair_ptr)pvPair)->key)
            free(((kv_pair_ptr)pvPair)->key);
        if (((kv_pair_ptr)pvPair)->value)
            free(((kv_pair_ptr)pvPair)->value);
        free(pvPair);
        return 0;
    }
    return (errno = EINVAL);
}

kv_list_ptr kv_parser(kv_list_ptr tokenList)
{
    if (!tokenList)
    {
        errno = EINVAL;
        return NULL;
    }

    kv_list_ptr pairList = kv_list_init();

    kv_list_forEach(tokenList, token)
        char *key, *value;
        kv_token_ptr t = kv_list_data(token);
        if(kv_token_type(t) != KEY){
            fprintf(stderr, "Synax Error: Expected 'key'\n");
            kv_list_destroy(tokenList);
            kv_list_destroy(pairList);
            return NULL;
        }
        key = kv_token_value(t);
        token = kv_list_each(NULL);
        t = kv_list_data(token);
        if(kv_token_type(t) != COLON){
            fprintf(stderr, "Synax Error: Expected 'colon(:)' after 'key'!\n");
            kv_list_destroy(tokenList);
            kv_list_destroy(pairList);
            return NULL;
        }
        token = kv_list_each(NULL);
        t = kv_list_data(token);
        if(kv_token_type(t) != VALUE){
            fprintf(stderr, "Synax Error: Expected 'value' after 'colon(:)'!\n");
            kv_list_destroy(tokenList);
            kv_list_destroy(pairList);
            return NULL;
        }
        value = kv_token_value(t);
        token = kv_list_each(NULL);
        t = kv_list_data(token);
        if(kv_token_type(t) != SEMICOLON){
            fprintf(stderr, "Synax Error: Expected 'semicolon(;)' after 'value'!\n");
            kv_list_destroy(tokenList);
            kv_list_destroy(pairList);
            return NULL;
        }
        kv_pair_ptr pair = kv_pair_init(key, value);
        kv_list_push(pairList, pair, kv_pair_destroy);
    kv_end

    return pairList;
}