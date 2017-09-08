#include <canciones.h>
#include <stdlib.h>
#include <string.h>
//PILA
void insert_front(canciones* _canciones, char* nombre, char* path, char* valoracion)
{
    cancion* new_node = create_cancion(nombre,path,valoracion, _canciones->head);
    _canciones->head = new_node;
}

void insert_cancion_top(canciones* _canciones, cancion* _cancion){
    cancion* cursor = _canciones->head;
    cancion* prev = NULL;
    cancion* new_node = create_cancion(_cancion->nombre,_cancion->path,_cancion->valoracion, NULL);

    if(cursor==NULL){
        _canciones->head = new_node;
    }else if(cursor->next==NULL){
        if(strcmp(new_node->valoracion,cursor->valoracion)>=0){
            new_node->next = cursor;
            cursor->next = NULL;
        }else{
            cursor->next = new_node;
        }
    }else{
        while(cursor->next!=NULL&&strcmp(new_node->valoracion,cursor->valoracion)>=0){
            prev = cursor;
            cursor = cursor->next;
        }
        if(prev!=NULL){
        prev->next = new_node;
        new_node->next = cursor;
        }

    }

}

void delete_front(canciones* _canciones)
{
    if(_canciones->head == NULL){

    }else{
        cancion *front = _canciones->head;
        _canciones->head = _canciones->head->next;
        front->next = NULL;
        /* is this the last node in the list */
        if(front == _canciones->head)
            _canciones->head = NULL;
        free(front);
   }
}

//COLA
void insert_back(canciones* _canciones, char* nombre, char* path, char* valoracion)
{
    if(_canciones->head == NULL){
        insert_front(_canciones,nombre,path,valoracion);
    }else{
    /* go to the last node */
    cancion *cursor = _canciones->head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    cancion* new_node =  create_cancion(nombre,path,valoracion, NULL);
    cursor->next = new_node;
    }
}
void delete_back(canciones* _canciones){
    if(_canciones->head == NULL){
        _canciones->head = NULL;
    }else{
        cancion *cursor = _canciones->head;
        cancion *back = NULL;
        while(cursor->next != NULL)
        {
            back = cursor;
            cursor = cursor->next;
        }

        if(back != NULL)
            back->next = NULL;

        /* if this is the last node in the list*/
        if(cursor == _canciones->head)
            _canciones->head = NULL;

        free(cursor);
    }
}

void remove_any(canciones* _canciones, char* nombre){
    cancion* nd = search(_canciones->head,_canciones->head,nombre);
    if(nd == NULL){

    }

    else if(nd == _canciones->head){
         delete_front(_canciones);
    }
    /* if the node is the last node */
    else if(nd->next == NULL){
         delete_back(_canciones);
    }
    /* if the node is in the middle */
    else{
        cancion* cursor = _canciones->head;
        while(cursor != NULL)
        {
            if(cursor->next == nd)
                break;
            cursor = cursor->next;
        }

        if(cursor != NULL)
        {
            cancion* tmp = cursor->next;
            cursor->next = tmp->next;
            tmp->next = NULL;
            free(tmp);
        }

    }
}

cancion* search(cancion* head, cancion* cursor, char* nombre){//SEARCH FOR A VALUE (IT'S USED BY REMOVE FUNCTION
if(cursor!=NULL){
    if(cursor->next!=head)
    {
        if(strcmp(cursor->nombre,nombre)==0){
            return cursor;
        }
        search(head,cursor->next,nombre);

    }else {
        if(strcmp(cursor->nombre,nombre)==0){
            return cursor;
        }else{
            return NULL;
        }
    }
}else{
    return NULL;
}
}



void dispose(canciones* _canciones){
    cancion *cursor, *tmp;

    if(_canciones->head != NULL)
    {
        cursor = _canciones->head;
        _canciones->head = NULL;
        while(cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}
void print(canciones* _canciones){
     cancion* cursor = _canciones->head;
    if(_canciones->head != NULL){
        while(cursor != NULL)
        {
            printf(cursor->nombre);
            printf("\n");
            printf(cursor->path);
            printf("\n");
            printf(cursor->valoracion);
             printf("\n");
            if(cursor->next!=NULL){
            printf(" -> ");
            }
            cursor = cursor->next;
        }
    }
     printf("\n");
}





//cancion* search(canciones* _canciones, char* nombre){


//    cancion *cursor = _canciones->head;
//    while(cursor!=NULL)
//    {
//        if(cursor->data == data)
//            return cursor;
//        cursor = cursor->next;
//    }
//    return NULL;
//}


