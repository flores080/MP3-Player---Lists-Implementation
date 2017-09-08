#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H
#include <cancion.h>
typedef struct double_node
{
    cancion* data;
    struct double_node* next;
    struct double_node* prev;
} double_node;


double_node* create_d(cancion* data, double_node* next, double_node* prev);

#endif // DOUBLE_NODE_H
