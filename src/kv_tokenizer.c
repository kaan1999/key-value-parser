#include <kv_tokenizer.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

const char valid[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct KVToken
{
    kv_tokenType_t tokenType;
    char *tokenValue;
};

kv_tokenType_t kv_token_type(kv_token_ptr token)
{
    if (token)
    {
        return token->tokenType;
    }
    errno = EINVAL;
    return INT_MAX;
}

char *kv_token_value(kv_token_ptr token)
{
    if (token)
        return token->tokenValue;
    errno = EINVAL;
    return NULL;
}

kv_token_ptr kv_token_init(kv_tokenType_t type, const char *value)
{
    kv_token_ptr token = malloc(sizeof(kv_token_t));
    if (!token)
    {
        errno = ENOMEM;
        return NULL;
    }
    token->tokenType = type;
    // if value is null, type must be colon or semicolon
    if (!value && (type == COLON || type == SEMICOLON))
    {
        token->tokenValue = NULL;
        return token;
    }
    // if value is not null, type must be key or value
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
    // undefined type or invalid value
    errno = EINVAL;
    free(token);
    return NULL;
}
errno_t kv_token_destroy(void *pvToken)
{
    if (pvToken)
    {
        if (((kv_token_ptr)pvToken)->tokenValue)
            free(((kv_token_ptr)pvToken)->tokenValue);
        free(pvToken);
        return 0;
    }
    return (errno = EINVAL);
}

static errno_t
pushTokenToTheList(const char *tokenBuffer, kv_tokenType_t type, kv_list_ptr list)
{
    kv_token_ptr token = NULL;
    if ((token = kv_token_init(type, tokenBuffer)))
    {
        if (kv_list_push(list, token, kv_token_destroy))
        {
            kv_token_destroy(token);
            perror("Error");
        }
    }
    else
        perror("Error");
}

kv_list_ptr kv_tokenizer_read(const char *fileName)
{
    kv_list_ptr tokenList = kv_list_init();

    if (!tokenList)
        return NULL;

    char tokenBuffer[KV_MAX_SIZE] = {'\0'};
    size_t i = 0;

    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        errno = ENOENT;
        return NULL;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (isspace(ch))
            continue;


        switch (ch)
        {
        case COLON:
        {
            tokenBuffer[i] = '\0';
            pushTokenToTheList(tokenBuffer, KEY, tokenList);
            pushTokenToTheList(NULL, COLON, tokenList);
            i = 0;
            break;
        }
        case SEMICOLON:
            tokenBuffer[i] = '\0';
            pushTokenToTheList(tokenBuffer, VALUE, tokenList);
            pushTokenToTheList(NULL, SEMICOLON, tokenList);
            i = 0;
            break;
        default:
            if (i >= KV_MAX_SIZE - 1)
            {
                fclose(file);
                errno = ENOBUFS;
                return NULL;
            }
            tokenBuffer[i++] = ch;
            break;
        }
    }
    fclose(file);
    return tokenList;
}