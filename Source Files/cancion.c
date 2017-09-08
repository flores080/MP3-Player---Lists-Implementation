#include <stdlib.h>
#include <cancion.h>

cancion* create_cancion(char* nombre, char* path, char* valoracion, cancion* next){
    cancion* new_cancion = (cancion*)malloc(sizeof(cancion));
    new_cancion->nombre=nombre;
    new_cancion->path=path;
    new_cancion->valoracion=valoracion;
    new_cancion->next = next;
    return new_cancion;
}
