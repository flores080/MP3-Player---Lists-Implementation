#include<albums.h>
#ifndef ARTISTA_H
#define ARTISTA_H
typedef struct artista{
    char* nombre;
    albums* _albums;
    struct artista* next;
    struct artista* prev;
}artista;

artista* create_artista(char* nombre, albums* _albums, artista* next, artista* prev);
#endif // ARTISTA_H
