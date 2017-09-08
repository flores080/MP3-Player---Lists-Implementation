#include <stdio.h>
#include <stdlib.h>
#include <node.h>
#include <cancion.h>
#ifndef STACK_H
#define STACK_H
typedef struct stack_Play
{
     cancion* head;
} stack_Play;

void push_song(stack_Play *s, char* _nombre,char* _path, char* _val, cancion* _next);
void pop_song(stack_Play* s);
cancion* top_song(stack_Play* s);
void generar_imagen_stack(stack_Play* s);

typedef struct stack
{
     node* head;
} stack;

void push(stack* s, char* data);
void pop(stack* s);
node* top(stack* s);
#endif // STACK_H
