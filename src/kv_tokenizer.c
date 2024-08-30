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
    if (!value && type == COLON || type == SEMICOLON)
    {
        token->tokenValue = NULL;
        return token;
    }
    //if value is not null, type must be key or value
    else if (value && type == KEY || type == VALUE)
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
    return NULL;
}
errno_t kv_token_destroy(kv_token_ptr);

kv_tokenList_ptr kv_tokenList_init();
errno_t kv_tokenList_destroy(kv_tokenList_ptr);
errno_t kv_tokenList_push(kv_tokenList_ptr, kv_tokenType_t, const char *);