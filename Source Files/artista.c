#include<stdlib.h>
#include<artista.h>

artista* create_artista(char* nombre, albums* _albums, artista* next, artista* prev){
    artista* new_artista = (artista*)malloc(sizeof(artista));
    new_artista->nombre = nombre;
    new_artista->_albums = _albums;
    new_artista->next = next;
    new_artista->prev = prev;
    return new_artista;
}
