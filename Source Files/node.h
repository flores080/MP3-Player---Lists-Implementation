#ifndef NODE_H
#define NODE_H
typedef struct node
{
    char* data;
    struct node* next;
} node;

node* create(char* data,node* next);


#endif // NODE_H
