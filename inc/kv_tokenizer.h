#include <errno.h>
//typedefs
typedef enum KVTokenType kv_tokenType_t;
typedef struct KVToken kv_token_t, *kv_token_ptr;
typedef struct KVTokenList kv_tokenList_t, *kv_tokenList_ptr;

enum KVTokenType{
    KEY, VALUE, COLON, SEMICOLON
};

//functions

kv_token_ptr kv_token_init(kv_tokenType_t, const char *);
errno_t kv_token_destroy(kv_token_ptr);

kv_tokenList_ptr kv_tokenList_init();
errno_t kv_tokenList_destroy(kv_tokenList_ptr);
errno_t kv_tokenList_push(kv_tokenList_ptr, kv_tokenType_t, const char *);