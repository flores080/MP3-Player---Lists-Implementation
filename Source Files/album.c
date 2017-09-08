#include <stdlib.h>
#include <album.h>

album* create_album(char* nombre, canciones* _canciones, album* next, album* prev){
    album* new_album = (album*)malloc((sizeof(album)));
    new_album->nombre = nombre;
    new_album->_canciones = _canciones;
    new_album->next = next;
    new_album->prev = prev;
    return new_album;
}
