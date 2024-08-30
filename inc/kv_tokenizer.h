typedef enum KVTokenType KVTokenType;
typedef struct KVToken kv_token_t, *kv_token_ptr;

enum KVTokenType{
    KEY, VALUE, COLON, SEMICOLON
};