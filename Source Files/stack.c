#include <stack.h>

void push(stack* s, char* data)
{
    node* new_node = create(data,s->head);
    s->head = new_node;
}
void pop(stack* s)
{
    if(s->head == NULL){

    }else{
        node *front = s->head;
        s->head = s->head->next;
        front->next = NULL;
        /* is this the last node in the list */
        if(front == s->head)
            s->head = NULL;
        free(front);
   }
}
node* top(stack* s)
{
    return s->head;
}

void push_song(stack_Play *s, char* _nombre,char* _path, char* _val, cancion* _next)
{
    cancion* new_node = create_cancion(_nombre,_path,_val,_next);
    s->head = new_node;
}
void pop_song(stack_Play* s)
{
    if(s->head == NULL){

    }else{
        cancion *front = s->head;
        s->head = s->head->next;
        front->next = NULL;
        /* is this the last node in the list */
        if(front == s->head)
            s->head = NULL;
        free(front);
   }
}
cancion* top_song(stack_Play* s)
{
    return s->head;
}

void generar_imagen_stack(stack_Play* s){
    FILE *f = fopen("/home/ferflo/Música/stack.dot","w");
    fprintf(f,"digraph G {\n");
    fprintf(f,"\n\tgraph [splines=true overlap=false];\n");
    fprintf(f,"\tedge[color=\"#1ed760\"];");
    fprintf(f,"\tgraph [bgcolor=\"#030515\"];");
    fprintf(f,"\tnode[style=filled fillcolor=\"#161420\" fontname=\"Montserratz\" fontcolor=white shape=Msquare];\n\trankdir=LR;\n\n");
    if(s->head!=NULL){
        cancion* cursor = s->head;
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
    system("dot -Tpng </home/ferflo/Música/stack.dot >/home/ferflo/Música/stack.png");
}


//    printf("----------STACK----------\n");
//    printf("values (3, 5, 6, 1000, 423\n\n");
//    stack* b = (stack*)malloc(sizeof(stack));
//    b->head = NULL;

//    push(b,3);print(b->head);printf("\n");
//    push(b,5);print(b->head);printf("\n");
//    push(b,6);print(b->head);printf("\n");
//    push(b,1000);print(b->head);printf("\n");
//    push(b,423);print(b->head);printf("\n");
//    while (b->head!=NULL) {
//        pop(b);print(b->head);printf("\n");
//    }
//    printf("%s","\n\n");

//    dispose(b->head);
