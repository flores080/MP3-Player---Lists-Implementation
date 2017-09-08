#include <stdio.h>
#include <artista.h>
#ifndef ARTISTAS_H
#define ARTISTAS_H
typedef struct artistas
{
    artista* head;
    artista* foot;
} artistas;

void insert_front_cd(artistas* _artistas, albums* _albums, char* nombre);
void delete_front_cd(artistas* _artistas);

void insert_back_cd(artistas* _artistas, albums* _albums, char* nombre);
void delete_back_cd(artistas* _artistas);


artista* search_cd(artista* head,artista* cursor,char* nombre);



void dispose_cd(artistas* _artistas);

void print_cd(artistas* _artistas);

void cancion_img(canciones* _canciones, FILE* f);
void album_img(albums* _albums, FILE* f);
void generar_imagen(artistas* _artistas);

void remove_any_cd(artistas* _artistas, char* nombre);


#endif // ARTISTAS_H
