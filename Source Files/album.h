#include <canciones.h>
#ifndef ALBUM_H
#define ALBUM_H

typedef struct album{
    char* nombre;
    canciones* _canciones;
    struct album* next;
    struct album* prev;
}album;


album* create_album(char* nombre, canciones* _canciones, album* next, album* prev);
#endif // ALBUM_H
