#include <kv_tokenizer.h>
#include <stdlib.h>
#include <string.h>

struct KVToken
{
    kv_tokenType_t tokenType;
    char *tokenValue;
    kv_token_ptr prev, next;
};
struct KVTokenList
{
    kv_token_ptr head, tail;
};

kv_token_ptr kv_token_init(kv_tokenType_t type, const char *value)
{
    kv_token_ptr token = malloc(sizeof(kv_token_t));
    if (!token)
    {
        errno = ENOMEM;
        return NULL;
    }
    token->prev = token->next = NULL;
    token->tokenType = type;
    //if value is null, type must be colon or semicolon
    if (!value && (type == COLON || type == SEMICOLON))
    {
        token->tokenValue = NULL;
        return token;
    }
    //if value is not null, type must be key or value
    else if (value && (type == KEY || type == VALUE))
    {
        size_t szValue = strlen(value);
        if (szValue >= KV_MAX_SIZE)
        {
            errno = ENAMETOOLONG;
            free(token);
            return NULL;
        }
        token->tokenValue = malloc(szValue + 1);
        if (!token->tokenValue)
        {
            errno = ENOMEM;
            free(token);
            return NULL;
        }
        strcpy(token->tokenValue, value);
        return token;
    }
    //undefined type or invalid value
    errno = EINVAL;
    free(token);
    return NULL;
}
errno_t kv_token_destroy(kv_token_ptr token){
    if(token){
        if(token->tokenValue) free(token->tokenValue);
        free(token);
        return 0;
    }
    return (errno = EINVAL);
}
errno_t kv_token_destroySafe(kv_token_ptr *ptoken){
    if(!ptoken || !*ptoken) return (errno = EINVAL);
    if((*ptoken)->tokenValue) free((*ptoken)->tokenValue);
    free(*ptoken);
    *ptoken = NULL;
    return 0;
}
kv_tokenList_ptr kv_tokenList_init(){
    kv_tokenList_ptr list = malloc(sizeof(kv_tokenList_t));
    if(!list){
        errno = EINVAL;
        return NULL;
    }
    list->head = list->tail = NULL;
    return list;
}
errno_t kv_tokenList_destroy(kv_tokenList_ptr list){
    if(!list) return (errno = EINVAL);
    kv_token_ptr iter = list->head;
    while (iter)
    {
        kv_token_ptr temp = iter;
        iter = iter->next;
        kv_token_destroy(temp);
    }
    list->head = list->tail = NULL;
    free(list);
    return 0;
}
errno_t kv_tokenList_push(kv_tokenList_ptr list, kv_tokenType_t type, const char *value){
    if(!list->head){
        list->head = list->tail = kv_token_init(type, value);
        if(!list->head) return errno;
        return 0;
    }
    list->tail->next = kv_token_init(type, value);
    if(!list->tail->next) return errno;
    list->tail->next->prev = list->tail;
    list->tail = list->tail->next;
    return 0;
}