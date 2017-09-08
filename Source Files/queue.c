#include <queue.h>

void eque(queue* q, int data)
{
    if(q->head == NULL){
        especial(q,data);
    }else{
    /* go to the last node */
    node *cursor = q->head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    node* new_node =  create(data,NULL);
    cursor->next = new_node;
    }
}
void deque(queue* q)
{
    if(q->head == NULL){
        q->head = NULL;
    }else{
        node *cursor = q->head;
        node *back = NULL;
        while(cursor->next != NULL)
        {
            back = cursor;
            cursor = cursor->next;
        }

        if(back != NULL)
            back->next = NULL;

        /* if this is the last node in the list*/
        if(cursor == q->head)
            q->head = NULL;

        free(cursor);
    }
}
node* front(queue* q)
{
    return q->head;
}
void especial(queue* q, int data)
{
    node* new_node = create(data,q->head);
    q->head = new_node;
}

void eque_song(queue_Play* q, char* _nombre,char* _path, char* _val, cancion* _next)
{
    if(q->head == NULL){
        especial_song(q,_nombre,_path,_val,_next);
    }else{
    /* go to the last node */
    cancion *cursor = q->head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    cancion* new_node =  create_cancion(_nombre,_path,_val,_next);
    cursor->next = new_node;
    }
}
void deque_song(queue_Play* q)
{
    if(q->head == NULL){

    }else{
        cancion *front = q->head;
        q->head = q->head->next;
        front->next = NULL;
        /* is this the last node in the list */
        if(front == q->head)
            q->head = NULL;
        free(front);
   }
//    if(q->head == NULL){
//        q->head = NULL;
//    }else{
//        cancion *cursor = q->head;
//        cancion *back = NULL;
//        while(cursor->next != NULL)
//        {
//            back = cursor;
//            cursor = cursor->next;
//        }

//        if(back != NULL)
//            back->next = NULL;

//        /* if this is the last node in the list*/
//        if(cursor == q->head)
//            q->head = NULL;

//        free(cursor);
//    }
}
cancion* front_song(queue_Play* q)
{
    return q->head;
}
void especial_song(queue_Play* q, char* _nombre,char* _path, char* _val, cancion* _next)
{
    cancion* new_node = create_cancion(_nombre,_path,_val,_next);
    q->head = new_node;
}

void generar_imagen_queue(queue_Play* q){
    FILE *f = fopen("/home/ferflo/Música/queue.dot","w");
    fprintf(f,"digraph G {\n");
    fprintf(f,"\n\tgraph [splines=true overlap=false];\n");
    fprintf(f,"\tedge[color=\"#1ed760\"];");
    fprintf(f,"\tgraph [bgcolor=\"#030515\"];");
    fprintf(f,"\tnode[style=filled fillcolor=\"#161420\" fontname=\"Montserratz\" fontcolor=white shape=Msquare];\n\trankdir=LR;\n\n");
    if(q->head!=NULL){
        cancion* cursor = q->head;
        if(cursor->next==NULL){
            fprintf(f,"\"");
            fprintf(f, cursor->nombre);
            fprintf(f,"\"");
        }else{
            while(cursor->next!=NULL){
                fprintf(f,"\"");
                fprintf(f, cursor->nombre);
                fprintf(f,"\"");
                fprintf(f," -> ");
                fprintf(f,"\"");
                fprintf(f,cursor->next->nombre);
                fprintf(f,"\"");
                cursor = cursor->next;
            }
        }
    }
    fprintf(f,"\n}");
    fclose(f);
    system("dot -Tpng </home/ferflo/Música/queue.dot >/home/ferflo/Música/queue.png");

}
//    printf("----------QUEUE----------\n");
//    printf("values (3, 5, 6, 1000, 423\n\n");
//    queue* a = (queue*)malloc(sizeof(queue));
//    a->head = NULL;
//    eque(a,3);print(a->head);printf("\n");
//    eque(a,5);print(a->head);printf("\n");
//    eque(a,6);print(a->head);printf("\n");
//    eque(a,1000);print(a->head);printf("\n");
//    eque(a,423);print(a->head);printf("\n");
//    while (a->head!=NULL) {
//        deque(a);print(a->head);printf("\n");
//    }
//    printf("%s","\n\n");


//    dispose(a->head);
