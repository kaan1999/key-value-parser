#include <kv_tokenizer.h>

struct KVToken
{
    kv_tokenType_t tokenType;
    char *tokenValue;
    kv_token_ptr prev, next;
};
struct KVTokenList{
    kv_token_ptr head, tail;
};

