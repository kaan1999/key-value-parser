#include <kv_list.h>

#define KV_MAX_SIZE 256

//typedefs
typedef struct KVToken kv_token_t, *kv_token_ptr;

typedef enum KVTokenType{
    KEY, VALUE, COLON = ':', SEMICOLON = ';'
}kv_tokenType_t;

//functions
kv_token_ptr kv_token_init(kv_tokenType_t type, const char *value);
errno_t kv_token_destroy(void*);
kv_tokenType_t kv_token_type(kv_token_ptr token);
char *kv_token_value(kv_token_ptr token);
kv_list_ptr kv_tokenizer_read(const char *fileName);