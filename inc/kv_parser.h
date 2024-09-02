#if !defined(KV_PARSER_H)
#define KV_PARSER_H
#include <kv_list.h>

typedef struct KVPair kv_pair_t, *kv_pair_ptr;

kv_pair_ptr kv_pair_init(const char *key, const char *value);
errno_t kv_pair_destroy(void *pvPair);
kv_list_ptr kv_parser(kv_list_ptr tokenList);
char *kv_pair_key(kv_pair_ptr pair);
char *kv_pair_value(kv_pair_ptr pair);
#endif // KV_PARSER_H
