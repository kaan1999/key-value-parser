#include <kv_parser.h>
#include <stdlib.h>
#include <string.h>

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