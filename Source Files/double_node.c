#include <stdlib.h>
#include <double_node.h>
double_node* create_d_song(cancion* data, double_node* next, double_node* prev)
{
    double_node* new_node = (double_node*)malloc(sizeof(double_node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;
    new_node->prev = prev;
    return new_node;
}



