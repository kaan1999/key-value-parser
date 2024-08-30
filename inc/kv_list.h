#define KV_MAX_LEN 256

//Type definitions
typedef struct KVPair kvpair_t, *kvpair_ptr;
typedef struct KVList kvlist_t, *kvlist_ptr;

//Functions
kvpair_ptr kvpair_init(char *key, char *value);
void kvpair_destroy(kvpair_ptr);
kvlist_ptr kvlist_init();
void kvlist_destroy(kvlist_ptr);
void kvlist_push(kvlist_ptr, char *key, char *value);
void kvlist_pop(kvlist_ptr);
