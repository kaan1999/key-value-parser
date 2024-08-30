#include <kv_list.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

struct KVPair
{
    char *key, *value;
    kvpair_ptr prev, next;
};
struct KVList
{
    kvpair_ptr head, tail;
    size_t length;
};

kvpair_ptr kvpair_init(char *key, char *value)
{
    if (!key || !value)
    {
        errno = EINVAL;
        return NULL;
    }
    size_t szKey = strlen(key);
    size_t szValue = strlen(value);
    if (szKey >= KV_MAX_LEN || szValue >= KV_MAX_LEN)
    {
        errno = ENAMETOOLONG;
        return NULL;
    }

    kvpair_ptr newPair = malloc(sizeof(kvpair_t));
    if (!newPair)
    {
        errno = ENOMEM;
        return NULL;
    }
    newPair->key = malloc(szKey + 1);
    newPair->value = malloc(szValue + 1);
    if (!newPair->key || !newPair->value)
    {
        free(newPair->key);
        free(newPair->value);
        free(newPair);
        errno = ENOMEM;
        return NULL;
    }
    strcpy(newPair->key, key);
    strcpy(newPair->value, value);
    newPair->prev = newPair->next = NULL;
    return newPair;
}
void kvpair_destroy(kvpair_ptr pair)
{
    if (pair)
    {
        if (pair->key)
            free(pair->key);
        if (pair->value)
            free(pair->value);
        free(pair);
    }
}
kvlist_ptr kvlist_init();
void kvlist_destroy(kvlist_ptr);
void kvlist_push(kvlist_ptr, char *key, char *value);
void kvlist_pop(kvlist_ptr);