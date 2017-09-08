#ifndef CANCION_H
#define CANCION_H
typedef struct cancion
{
    char* nombre;
    char* path;
    char* valoracion;
    struct cancion* next;
} cancion;

cancion* create_cancion(char* nombre, char* path, char* valoracion, cancion* next);
#endif // CANCION_H
