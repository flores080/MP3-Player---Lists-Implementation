#include <circle_double_list.h>
#include <stdlib.h>

//PILA
void insert_front_d_song(circle_double_list* l, cancion* data)
{
    double_node* new_node = create_d_song(data,l->head, NULL);
        l->head = new_node;

        double_node* cursor = l->head;

        if(cursor->next == NULL){
            l->foot = l->head;
        }
        l->foot->next = l->head;
        l->head->prev = l->foot;

    if(l->head->next!=l->head){
        l->head->next->prev = l->head;
    }
}
void delete_front_d_song(circle_double_list* l)
{
    if(l->head != NULL){
        double_node *front = l->head;
        l->head = l->head->next;
        front->next = NULL;
        l->foot->next = l->head;
        l->head->prev = l->foot;

        /* is this the last node in the list */
        if(front == l->head){
            l->head = NULL;
            l->foot = NULL;
            }
        free(front);
   }
}

//COLA
void insert_back_d_song(circle_double_list* l, cancion* data)
{
    if(l->head == NULL){
        insert_front_d_song(l,data);
    }else{
    /* go to the last node */
        double_node* cursor = l->head;
        if(cursor->next == l->head){
             double_node* new_node =  create_d_song(data,l->head,cursor);
            cursor->next = new_node;
             l->foot = new_node;
             l->foot->next = l->head;
             l->head->prev = l->foot;
        }else{
            while(cursor->next != l->head)
            {
                cursor = cursor->next;
            }
             double_node* new_node =  create_d_song(data,l->head,cursor);
            cursor->next = new_node;
            l->foot = new_node;
            l->foot->next = l->head;
            l->head->prev = l->foot;
        }
    }
}
void delete_back_d_song(circle_double_list* l){
    if(l->head != NULL){
        double_node *cursor = l->head;
        double_node *back = NULL;
        while(cursor->next != l->head)
        {
            back = cursor;
            cursor = cursor->next;
        }

        if(cursor != l->head){
            back->next = l->head;
            l->foot = back;
            l->head->prev = l->foot;
        }else if(cursor == l->head){
            l->head = NULL;
            l->foot = NULL;
        }

        free(cursor);
    }
}

void dispose_d_song(circle_double_list* l){
    double_node *cursor, *tmp;

    if(l->head != NULL)
    {
        cursor = l->head;
        l->head = NULL;
        while(cursor->next != l->foot)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
            if(cursor == l->foot){
                free(cursor);
            }
        }
    }
}

cancion* front_d_song(circle_double_list* l){
    return l->head->data;
}

double_node* search_d_song(double_node* head,double_node* cursor,char* nombre){//SEARCH FOR A VALUE (IT'S USED BY REMOVE FUNCTION
if(cursor!=NULL){
    if(cursor->next!=head)
    {
        if(strcmp(cursor->data->nombre,nombre)==0){
            return cursor;
        }
        search_d_song(head,cursor->next,nombre);

    }else {
        if(strcmp(cursor->data->nombre,nombre)==0){
            return cursor;
        }else{
            return NULL;
        }
    }
}else{
    return NULL;
}
}

void generar_imagen_circular(circle_double_list* l){
    FILE *f = fopen("/home/ferflo/Música/circular.dot","w");
    fprintf(f,"digraph G {\n");
    fprintf(f,"\n\tgraph [splines=true overlap=false];\n");
    fprintf(f,"\tedge[color=\"#1ed760\"];");
    fprintf(f,"\tgraph [bgcolor=\"#030515\"];");
    fprintf(f,"\tnode[style=filled fillcolor=\"#161420\" fontname=\"Montserratz\" fontcolor=white shape=Msquare];\n\trankdir=LR;\n\n");
    double_node* cursor = l->head;
    if(l->head != NULL){
        if(cursor->next == l->head){
            fprintf(f,"\"");
            fprintf(f, cursor->data->nombre);
            fprintf(f,"\"");
            fprintf(f," -> ");
            fprintf(f,"\"");
            fprintf(f,cursor->prev->data->nombre);
            fprintf(f,"\"");
            fprintf(f,";\n");

            fprintf(f,"\"");
            fprintf(f, cursor->data->nombre);
            fprintf(f,"\"");
            fprintf(f," -> ");
            fprintf(f,"\"");
            fprintf(f, cursor->next->data->nombre);
            fprintf(f,"\"");
            fprintf(f,";\n");

        }
        while(cursor->next != l->head)
        {
            fprintf(f,"\"");
            fprintf(f, cursor->data->nombre);
            fprintf(f,"\"");
            fprintf(f," -> ");
            fprintf(f,"\"");
            fprintf(f,cursor->prev->data->nombre);
            fprintf(f,"\"");
            fprintf(f,";\n");

            fprintf(f,"\"");
            fprintf(f, cursor->data->nombre);
            fprintf(f,"\"");
            fprintf(f," -> ");
            fprintf(f,"\"");
            fprintf(f, cursor->next->data->nombre);
            fprintf(f,"\"");
            fprintf(f,";\n");

            cursor = cursor->next;
            if(cursor->next == l->head){

                fprintf(f,"\"");
                fprintf(f, cursor->data->nombre);
                fprintf(f,"\"");
                fprintf(f," -> ");
                fprintf(f,"\"");
                fprintf(f,cursor->prev->data->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");

                fprintf(f,"\"");
                fprintf(f, cursor->data->nombre);
                fprintf(f,"\"");
                fprintf(f," -> ");
                fprintf(f,"\"");
                fprintf(f, cursor->next->data->nombre);
                fprintf(f,"\"");
                fprintf(f,";\n");
            }
        }
    }
    fprintf(f,"\n}");
    fclose(f);
    system("dot -Tpng </home/ferflo/Música/circular.dot >/home/ferflo/Música/circular.png");

}
