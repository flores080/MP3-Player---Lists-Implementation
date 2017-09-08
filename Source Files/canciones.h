#ifndef CANCIONES_H
#define CANCIONES_H
#include <cancion.h>
typedef struct canciones{
    cancion* head;
}canciones;

void insert_front(canciones* _canciones, char* nombre, char* path, char* valoracion);
void insert_cancion_top(canciones* _canciones, cancion* _cancion);
void delete_front(canciones* _canciones);

void insert_back(canciones* _canciones, char* nombre, char* path, char* valoracion);
void delete_back(canciones* _canciones);

void remove_any(canciones* _canciones, char* nombre);

cancion* search(cancion* head, cancion* cursor, char* nombre);

void print(canciones* _canciones);
void dispose(canciones* _canciones);


#endif // CANCIONES_H
