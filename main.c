#include <kv_list.h>
#include <stdio.h>
int main(void){
    //kvpair_init and kvpair_destroy test
    kvpair_ptr pair = kvpair_init("key1", "value1");
    if(pair){
        puts("OK");
    }
    kvpair_destroy(pair);
}