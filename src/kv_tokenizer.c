#include <kv_tokenizer.h>
#include <stdlib.h>
#include <string.h>

struct KVToken
{
    kv_tokenType_t tokenType;
    char *tokenValue;
    kv_token_ptr prev, next;
};
struct KVTokenList{
    kv_token_ptr head, tail;
};

kv_token_ptr kv_token_init(kv_tokenType_t type, const char *value){
    if(!value){
        errno = EINVAL;
        return NULL;
    }
    kv_token_ptr token = malloc(sizeof(kv_token_t));
    if(!token){
        errno = ENOMEM;
        return NULL;
    }
    size_t szValue = strlen(value);
    if(szValue >= KV_MAX_SIZE){
        errno = ENAMETOOLONG;
        free(token);
        return NULL;
    }
    token->tokenValue = malloc(szValue + 1);
    if(!token->tokenValue){
        errno = ENOMEM;
        free(token);
        return NULL;
    }
    strcpy(token->tokenValue, value);
    token->tokenType = type;

    token->next = token->prev = NULL;
    
    return token;
}
errno_t kv_token_destroy(kv_token_ptr);

kv_tokenList_ptr kv_tokenList_init();
errno_t kv_tokenList_destroy(kv_tokenList_ptr);
errno_t kv_tokenList_push(kv_tokenList_ptr, kv_tokenType_t, const char *);