#include <kv_list.h>
#include <stdlib.h>

kv_node_ptr kv_node_current = NULL;


struct KVNode{
    void *data;
    kv_nodeDtor_fptr dtor;
    kv_node_ptr prev, next;
};

struct KVList{
    kv_node_ptr head, tail;
    size_t length;
};

kv_node_ptr kv_node_init(void *data, kv_nodeDtor_fptr dtor){
    if(!data){
        errno = EINVAL;
        return NULL;
    }
    kv_node_ptr node = malloc(sizeof(kv_node_t));
    if(!node){
        errno = EINVAL;
        return NULL;
    }
    node->data = data;
    node->dtor = dtor;
    node->prev = node->next = NULL;
    return node;
}
errno_t kv_node_destroy(kv_node_ptr node){
    if(node && !node->dtor){
        free(node);
        return 0;
    }else if(!node){
        return (errno = EINVAL);
    }else if(node->data){
        if(node->dtor(node->data)){
            free(node);
            return errno;
        }
    }
    free(node);
    return 0;
}
kv_list_ptr kv_list_init(){
    kv_list_ptr list = malloc(sizeof(kv_list_t));
    if(!list){
        errno = EINVAL;
        return NULL;
    }
    list->head = list->tail = NULL;
    list->length = 0;
    return list;
}
errno_t kv_list_destroy(kv_list_ptr list){
    errno_t ret = 0;
    if(!list){
        return (errno = EINVAL);
    }
    kv_node_ptr iter = list->head;
    while (iter)
    {
        kv_node_ptr temp = iter;
        iter = iter->next;
        ret = kv_node_destroy(temp);
    }
    free(list);
    return ret;
}
errno_t kv_list_push(kv_list_ptr list, void *data, kv_nodeDtor_fptr dtor){
    if(!list || !data){
        return (errno = EINVAL);
    }
    if(!list->head){
        list->head = list->tail = kv_node_init(data, dtor);
        if(!list->head) return errno;
        return 0;
    }
    list->tail->next = kv_node_init(data, dtor);
    if(!list->tail->next) return errno;
    list->tail->next->prev = list->tail;
    list->tail = list->tail->next;
    return 0;
}

kv_node_ptr kv_list_each(kv_list_ptr list){
    if(list)
        kv_node_current = list->head;
    else if(kv_node_current)
        kv_node_current = kv_node_current->next;
    return kv_node_current;
}

void *kv_list_data(kv_node_ptr node){
    if(node) return node->data;
    errno = EINVAL;
    return NULL;
}