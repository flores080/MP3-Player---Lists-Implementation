#include <stdio.h>
#include <double_node.h>
#ifndef CIRCLE_DOUBLE_LIST_H
#define CIRCLE_DOUBLE_LIST_H
typedef struct circle_double_list
{
    double_node* head;
    double_node* foot;
} circle_double_list;

void insert_front_d_song(circle_double_list* l,cancion* data);
void delete_front_d_song(circle_double_list* l);

void insert_back_d_song(circle_double_list* l, cancion* data);
void delete_back_d_song(circle_double_list* l);


double_node* search_d_song(double_node* head,double_node* cursor, char* _nombre);

cancion* front_d_song(circle_double_list* l);

void dispose_d_song(circle_double_list* l);

void generar_imagen_circular(circle_double_list* l);
#endif // CIRCLE_DOUBLE_LIST_H
