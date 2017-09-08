#include <stdio.h>
#include <stdlib.h>
#include <node.h>
#include <cancion.h>
#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue
{
    node* head;
} queue;

void eque(queue* q, int data);
void deque(queue* q);
node* front(queue* q);
void especial(queue* q, int data);

typedef struct queue_Play
{
    cancion* head;
} queue_Play;

void eque_song(queue_Play* q, char* _nombre,char* _path, char* _val, cancion* _next);
void deque_song(queue_Play* q);
cancion* front_song(queue_Play* q);
void especial_song(queue_Play* q, char* _nombre,char* _path, char* _val, cancion* _next);
void generar_imagen_queue(queue_Play* q);
#endif // QUEUE_H
