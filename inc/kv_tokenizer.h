typedef enum KVTokenType kv_tokenType_t;
typedef struct KVToken kv_token_t, *kv_token_ptr;
typedef struct KVTokenList kv_tokenList_t, *kv_tokenList_ptr;

enum KVTokenType{
    KEY, VALUE, COLON, SEMICOLON
};