#include <kv_list.h>

struct KVNode{
    void *data;
    kv_node_ptr prev, next;
};

struct KVList{
    kv_node_ptr head, tail;
    size_t length;
};

kv_node_ptr kv_node_init(void *data);
errno_t kv_node_destroy(kv_node_ptr node, errno_t (*funDestroy)(void*));
kv_list_ptr kv_list_init();
errno_t kv_list_destroy(kv_list_ptr list, errno_t (*funDestroy)(void*));
errno_t kv_list_push(kv_list_ptr list, void *data);