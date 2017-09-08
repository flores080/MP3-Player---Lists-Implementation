    #include <artistas.h>
    #include <stdlib.h>
    #include <string.h>
    //PILA
    void insert_front_cd(artistas* _artistas, albums* _albums, char* nombre)
    {
        artista* new_node = create_artista(nombre, _albums, _artistas->head, NULL);
            _artistas->head = new_node;

            artista* cursor = _artistas->head;

            if(cursor->next == NULL){
                _artistas->foot = _artistas->head;
            }
            _artistas->foot->next = _artistas->head;
            _artistas->head->prev = _artistas->foot;

        if(_artistas->head->next!=_artistas->head){
            _artistas->head->next->prev = _artistas->head;
        }
    }
    void delete_front_cd(artistas* _artistas)
    {
        if(_artistas->head != NULL){
            artista *front = _artistas->head;
            _artistas->head = _artistas->head->next;
            front->next = NULL;
            _artistas->foot->next = _artistas->head;
            _artistas->head->prev = _artistas->foot;

            /* is this the last node in the list */
            if(front == _artistas->head){
                _artistas->head = NULL;
                _artistas->foot = NULL;
                }
            free(front);
       }
    }

    //COLA
    void insert_back_cd(artistas* _artistas, albums* _albums, char* nombre)
    {
        if(_artistas->head == NULL){
            insert_front_cd(_artistas,_albums,nombre);
        }else{
        /* go to the last node */
            artista* cursor = _artistas->head;
            if(cursor->next == _artistas->head){
                 artista* new_node =  create_artista(nombre,_albums,_artistas->head,cursor);
                cursor->next = new_node;
                 _artistas->foot = new_node;
                 _artistas->foot->next = _artistas->head;
                 _artistas->head->prev = _artistas->foot;
            }else{
                cursor = _artistas->foot;
                artista* new_node =  create_artista(nombre,_albums,_artistas->head,cursor);
                cursor->next = new_node;
                _artistas->foot = new_node;
                _artistas->foot->next = _artistas->head;
                _artistas->head->prev = _artistas->foot;
            }
        }
    }
    void delete_back_cd(artistas* _artistas){
        if(_artistas->head != NULL){
            artista *cursor = _artistas->head;
            artista *back = NULL;
            while(cursor->next != _artistas->head)
            {
                back = cursor;
                cursor = cursor->next;
            }

            if(cursor != _artistas->head){
                back->next = _artistas->head;
                _artistas->foot = back;
                _artistas->head->prev = _artistas->foot;
            }else if(cursor == _artistas->head){
                _artistas->head = NULL;
                _artistas->foot = NULL;
            }

            free(cursor);
        }
    }


    artista* search_cd(artista* head,artista* cursor,char* nombre){//SEARCH FOR A VALUE (IT'S USED BY REMOVE FUNCTION
    if(cursor!=NULL){
        if(cursor->next!=head)
        {
            if(strcmp(cursor->nombre,nombre)==0){
                return cursor;
            }
            search_cd(head,cursor->next,nombre);

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

    void cancion_img(canciones* _canciones, FILE* f){
        cancion* cursor = _canciones->head;
       if(_canciones->head != NULL){
           while(cursor->next != NULL)
           {

               fprintf(f,"\"");
               fprintf(f, cursor->nombre);
               fprintf(f,"\"");
               fprintf(f," -> ");
               fprintf(f,"\"");
               fprintf(f, cursor->next->nombre);
               fprintf(f,"\"");
               fprintf(f,";\n");

               cursor = cursor->next;
           }
       }
    }

    void album_img(albums* _albums, FILE* f){
        album* cursor = _albums->head;
        if(_albums->head != NULL){
            while(cursor != NULL)
            {
                if(cursor->prev!=NULL){
                    fprintf(f,"\"");
                    fprintf(f, cursor->nombre);
                    fprintf(f,"\"");
                    fprintf(f," -> ");
                    fprintf(f,"\"");
                    fprintf(f,cursor->prev->nombre);
                    fprintf(f,"\"");
                    fprintf(f,";\n");
                }
                if(cursor->next!=NULL){
                    fprintf(f,"\"");
                    fprintf(f, cursor->nombre);
                    fprintf(f,"\"");
                    fprintf(f," -> ");
                    fprintf(f,"\"");
                    fprintf(f, cursor->next->nombre);
                    fprintf(f,"\"");
                    fprintf(f,";\n");
                }
                fprintf(f,"\"");
                fprintf(f, cursor->nombre);
                fprintf(f,"\"");
                fprintf(f, " -> ");
                fprintf(f,"\"");
                fprintf(f, cursor->_canciones->head->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");
                cancion_img(cursor->_canciones,f);
                cursor = cursor->next;
            }
        }
    }

    void generar_imagen(artistas* _artistas){//CREATE THE IMAGE FROM *.DOT FILE
        FILE *f = fopen("/home/ferflo/Música/file.dot","w");
        fprintf(f,"digraph G {\n");
        fprintf(f,"\n\tgraph [splines=true overlap=false];\n");
        fprintf(f,"\tedge[color=\"#1ed760\"];");
        fprintf(f,"\tgraph [bgcolor=\"#030515\"];");
        fprintf(f,"\tnode[style=filled fillcolor=\"#161420\" fontname=\"Montserratz\" fontcolor=white shape=Msquare];\n\trankdir=LR;\n\n");
        artista* cursor = _artistas->head;
        if(_artistas->head != NULL){
            if(cursor->next == _artistas->head){
                fprintf(f,"\"");
                fprintf(f, cursor->nombre);
                fprintf(f,"\"");
                fprintf(f," -> ");
                fprintf(f,"\"");
                fprintf(f,cursor->prev->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");

                fprintf(f,"\"");
                fprintf(f, cursor->nombre);
                fprintf(f,"\"");
                fprintf(f," -> ");
                fprintf(f,"\"");
                fprintf(f, cursor->next->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");

                fprintf(f,"\"");
                fprintf(f,cursor->nombre);
                fprintf(f,"\"");
                fprintf(f, " -> ");
                fprintf(f,"\"");
                fprintf(f,cursor->_albums->head->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");
                album_img(cursor->_albums,f);
            }
            while(cursor->next != _artistas->head)
            {
                fprintf(f,"\"");
                fprintf(f, cursor->nombre);
                fprintf(f,"\"");
                fprintf(f," -> ");
                fprintf(f,"\"");
                fprintf(f,cursor->prev->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");

                fprintf(f,"\"");
                fprintf(f, cursor->nombre);
                fprintf(f,"\"");
                fprintf(f," -> ");
                fprintf(f,"\"");
                fprintf(f, cursor->next->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");

                fprintf(f,"\"");
                fprintf(f,cursor->nombre);
                fprintf(f,"\"");
                fprintf(f, " -> ");
                fprintf(f,"\"");
                fprintf(f,cursor->_albums->head->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");

                album_img(cursor->_albums,f);

                cursor = cursor->next;
                if(cursor->next == _artistas->head){

                    fprintf(f,"\"");
                    fprintf(f, cursor->nombre);
                    fprintf(f,"\"");
                    fprintf(f," -> ");
                    fprintf(f,"\"");
                    fprintf(f,cursor->prev->nombre);
                    fprintf(f,"\"");
                    fprintf(f,";\n");

                    fprintf(f,"\"");
                    fprintf(f, cursor->nombre);
                    fprintf(f,"\"");
                    fprintf(f," -> ");
                    fprintf(f,"\"");
                    fprintf(f, cursor->next->nombre);
                    fprintf(f,"\"");
                    fprintf(f,";\n");

                    fprintf(f,"\"");
                    fprintf(f,cursor->nombre);
                    fprintf(f,"\"");
                    fprintf(f, " -> ");
                    fprintf(f,"\"");
                    fprintf(f,cursor->_albums->head->nombre);
                    fprintf(f,"\"");
                    fprintf(f,";\n");

                    album_img(cursor->_albums,f);
                }
            }
        }
        fprintf(f,"\n}");
        fclose(f);
        system("dot -Tpng </home/ferflo/Música/file.dot >/home/ferflo/Música/estructura.png");
    }

    void remove_any_cd(artistas* _artistas, char* nombre){//REMOVE AN ESPECIFIC DATA
        artista* nd = search_cd(_artistas->head,_artistas->head,nombre);
        if(nd == NULL){
            printf("\nSory, the word \"");
            printf(nombre);
            printf("\" wasn't found it.\n");
        }

        else if(nd == _artistas->head){
             delete_front_cd(_artistas);
             printf("\nThe word \"");
             printf(nombre);
             printf("\", was deleted.\n");
        }
        /* if the node is the last node */
        else if(nd->next == _artistas->head){
             delete_back_cd(_artistas);
             printf("\nThe word \"");
             printf(nombre);
             printf("\", was deleted.\n");
        }
        /* if the node is in the middle */
        else{
            artista* cursor = nd->prev;
            artista* tmp = cursor->next;
            cursor->next = tmp->next;
            cursor->next->prev = cursor;
            tmp->next = NULL;
            free(tmp);
            printf("\nThe word \"");
            printf(nombre);
            printf("\", was deleted.\n");

        }
    }

    void dispose_cd(artistas* _artistas){
        artista *cursor, *tmp;

        if(_artistas->head != NULL)
        {
            cursor = _artistas->head;
            _artistas->head = NULL;
            while(cursor->next != _artistas->foot)
            {
                tmp = cursor->next;
                free(cursor);
                cursor = tmp;
                if(cursor == _artistas->foot){
                    free(cursor);
                }
            }
        }
    }

    void print_cd(artistas* _artistas){
        FILE *f = fopen("file.dot","w");
        fprintf(f,"digraph G {\n");
        fprintf(f,"\n\tnode[shape=square];\n\trankdir=LR;\n\n");
        artista* cursor = _artistas->head;
        if(_artistas->head != NULL){
            if(cursor->next == _artistas->head){
                fprintf(f, cursor->nombre);
                fprintf(f," -> ");
                fprintf(f,cursor->prev->nombre);
                fprintf(f,";\n");
                fprintf(f, cursor->nombre);
                fprintf(f," -> ");
                fprintf(f, cursor->next->nombre);
                fprintf(f,";\n");

                printf(cursor->prev->nombre);
                printf(" <- ");
                printf(cursor->nombre);
                printf(" -> ");
                printf(cursor->next->nombre);
                printf("\n");

                print_d(cursor->_albums);

            }
            while(cursor->next != _artistas->head)
            {
                fprintf(f, cursor->nombre);
                fprintf(f," -> ");
                fprintf(f,cursor->prev->nombre);
                fprintf(f,";\n");
                fprintf(f, cursor->nombre);
                fprintf(f," -> ");
                fprintf(f, cursor->next->nombre);
                fprintf(f,";\n");

                printf(cursor->prev->nombre);
                printf(" <- ");
                printf(cursor->nombre);
                printf(" -> ");
                printf(cursor->next->nombre);
                printf("\n");

                 print_d(cursor->_albums);

                cursor = cursor->next;
                if(cursor->next == _artistas->head){
                    fprintf(f, cursor->nombre);
                    fprintf(f," -> ");
                    fprintf(f,cursor->prev->nombre);
                    fprintf(f,";\n");
                    fprintf(f, cursor->nombre);
                    fprintf(f," -> ");
                    fprintf(f, cursor->next->nombre);
                    fprintf(f,";\n");

                    printf(cursor->prev->nombre);
                    printf(" <- ");
                    printf(cursor->nombre);
                    printf(" -> ");
                    printf(cursor->next->nombre);
                    printf("\n");

                     print_d(cursor->_albums);
                }
            }
            printf("\nHEAD ");
            printf(_artistas->head->nombre);
            printf("\nFOOT ");
            printf(_artistas->foot->nombre);
        }else{
            printf("The list is empty...\n");
        }
        fprintf(f,"\n}");
        fclose(f);

    }



