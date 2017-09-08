#include<albums.h>
#include<stdlib.h>
#include<string.h>
//PILA
void insert_front_d(albums* _albums, char* nombre, canciones* _canciones)
{
    album* new_album = create_album(nombre, _canciones, _albums->head, NULL);
        _albums->head = new_album;
    if(_albums->head->next!=NULL){
        _albums->head->next->prev = _albums->head;
    }
}
void delete_front_d(albums* _albums)
{
    if(_albums->head !=NULL){
        if(_albums->head->next != NULL){
            album *front = _albums->head;
            _albums->head = _albums->head->next;
            _albums->head->prev = NULL;
            front->next = NULL;

            if(front == _albums->head)
                _albums->head = NULL;
            free(front);
       }else{
            _albums->head = NULL;
       }
    }
}

//COLA
void insert_back_d(albums* _albums, char* nombre, canciones* _canciones)
{
    if(_albums->head == NULL){
        insert_front_d(_albums,nombre,_canciones);
    }else{
    /* go to the last node */
    album *cursor = _albums->head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    album* new_album =  create_album(nombre,_canciones,NULL,cursor);
    cursor->next = new_album;
    }
}
void delete_back_d(albums* _albums){
    if(_albums->head == NULL){
        _albums->head = NULL;
    }else{
        album *cursor = _albums->head;
        album *back = NULL;
        while(cursor->next != NULL)
        {
            back = cursor;
            cursor = cursor->next;
        }

        if(back != NULL)
            back->next = NULL;
        /* if this is the last node in the list*/
        if(cursor == _albums->head)
            _albums->head = NULL;

        free(cursor);
    }
}

album* search_d(album* head, album* cursor, char* nombre){
if(cursor!=NULL){
    if(cursor->next!=head)
    {
        if(strcmp(cursor->nombre,nombre)==0){
            return cursor;
        }
        search_d(head,cursor->next,nombre);

    }else {
        printf("si...\n");
        if(strcmp(cursor->nombre,nombre)==0){
            printf("si...\n");
            return cursor;
        }else{
            printf("no...\n");
            return NULL;
        }
    }
}else{
    return NULL;
}
}

void dispose_d(albums* _albums){
    album *cursor, *tmp;

    if(_albums->head != NULL)
    {
        cursor = _albums->head;
        _albums->head = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}

void print_d(albums* _albums){
    album* cursor = _albums->head;
    if(_albums->head != NULL){
        while(cursor != NULL)
        {
            if(cursor->prev!=NULL){
                printf(cursor->prev->nombre);
                printf(" <- ");
            }
            printf(cursor->nombre);
            if(cursor->next!=NULL){
                printf(" -> ");
                printf(cursor->next->nombre);
            }
            printf("\n");
            printf("Canciones: \n");
            print(cursor->_canciones);
            cursor = cursor->next;
        }
    }
}

void remove_any_d(albums* _albums, char* nombre){//REMOVE AN ESPECIFIC DATA
    album* nd = search_d(_albums->head,_albums->head, nombre);
    if(nd == NULL){
        printf("\nSory, the word \"");
        printf(nombre);
        printf("\" wasn't found it.\n");
    }

    else if(nd == _albums->head){
         delete_front_d(_albums);
         printf("\nThe word \"");
         printf(nombre);
         printf("\", was deleted.\n");
    }
    /* if the node is the last node */
    else if(nd->next == _albums->head){
         delete_back_d(_albums);
         printf("\nThe word \"");
         printf(nombre);
         printf("\", was deleted.\n");
    }
    /* if the node is in the middle */
    else{
        album* cursor = nd->prev;
        album* tmp = cursor->next;
        cursor->next = tmp->next;
        cursor->next->prev = cursor;
        tmp->next = NULL;
        free(tmp);
        printf("\nThe word \"");
        printf(nombre);
        printf("\", was deleted.\n");

    }
}
