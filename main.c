#include <kv_tokenizer.h>

int main(void){
    kv_token_ptr token = kv_token_init(KEY, "key1");
    kv_token_destroySafe(&token);
}