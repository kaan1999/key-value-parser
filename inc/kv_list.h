#include <errno.h>

typedef errno_t (*kv_nodeDtor_fptr)(void*);

typedef struct KVNode kv_node_t, *kv_node_ptr;
typedef struct KVList kv_list_t, *kv_list_ptr;


kv_node_ptr kv_node_init(void *data, kv_nodeDtor_fptr dtor);
errno_t kv_node_destroy(kv_node_ptr node);
kv_list_ptr kv_list_init();
errno_t kv_list_destroy(kv_list_ptr list);
errno_t kv_list_push(kv_list_ptr list, void *data, kv_nodeDtor_fptr dtor);
kv_node_ptr kv_list_each(kv_list_ptr list);
void *kv_list_data(kv_node_ptr node);

#define kv_list_forEach(list, i) \
for(kv_node_ptr i = kv_list_each(list); i != NULL; i = kv_list_each(NULL)){

#define kv_end }
