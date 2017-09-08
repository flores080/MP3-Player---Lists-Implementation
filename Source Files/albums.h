#include <stdio.h>
#include <album.h>
#ifndef ALBUMS_H
#define ALBUMS_H
typedef struct albums
{
    album* head;
} albums;

void insert_front_d(albums* _albums, char* nombre, canciones* _canciones);
void delete_front_d(albums* _albums);

void insert_back_d(albums* _albums, char* nombre, canciones* _canciones);
void delete_back_d(albums* _albums);

album* search_d(album* head, album* cursor, char* nombre);

void dispose_d(albums* _albums);

void print_d(albums* _albums);

void remove_any_d(albums* _albums, char* nombre);

#endif // ALBUMS_H
